<?php

class asu_os_boxes_site_info extends os_boxes_default {

  function options_defaults() {
    $options = parent::options_defaults();

    $options += array(
      'site_title' => 'Your site name in the main header',
    );

    return $options;
  }

  function box_form(&$form_state) {
    $form = parent::options_form($form_state);

    if (module_exists('vsite') && $vsite = spaces_get_space()) {
      $group = $vsite->group;
      $this->options = array_merge($this->options, array(
        'site_title' => $group->title,
      ));
    }
    $form['site_title'] = array(
      '#type' => 'textfield',
      '#title' => t('Title'),
      '#default_value' => $this->options['site_title'],
      '#size' => 60,
      '#required' => true,
    );
    $form['contact'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enable contact form.'),
      '#default_value' => variable_get('show_email', variable_get('vsite_users_contact_form_anonymous', TRUE)),
      '#description' => t('Will print an (email) link to your contact form.'),
    );
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
      '#submit' => array('asu_os_boxes_site_info_submit'),
    );
    $form['cancel'] = array(
      '#type' => 'submit',
      '#value' => t('Cancel'),
      '#limit_validation_errors' => array(),
    );

    return $form;
  }

  function render() {
    if (module_exists('vsite') && !vsite_get_vsite()) {
      return;
    }
    $block = parent::render();

    $contact = variable_get('show_email', variable_get('vsite_users_contact_form_anonymous', TRUE));
    if (module_exists('vsite') && $vsite = spaces_get_space()) {
      $group = $vsite->group;
      $this->options = array_merge($this->options, array(
        'site_title' => $group->title,
      ));
    }

    $tags = array('br', 'a', 'em', 'strong', 'cite', 'blockquote', 'code', 'ul', 'ol', 'li', 'dl', 'dt', 'dd');

    // Removed any rendering of site info collected - ONLY the site name goes out.
    $output = '<div class="asu-global asu-global--outer">' . "\n";
    $output .= '  <div class="header__sitename asu-global--inner"><span>' . l($this->options['site_title'], '<front>');
    $output .= "</span>\n  </div>\n</div>";

    // Contact info currently hidden

    $block['content'] = $output;
    return $block;
  }
}

function asu_os_boxes_site_info_submit($form, &$form_state) {
  $box = $form_state['box'];
  if (module_exists('vsite') && $space = spaces_get_space()) {
    // Populate the VSite with this information.
    $node = $space->group;
    $node->title = $form_state['values']['site_title'];

    if (empty($node->field_site_logo[LANGUAGE_NONE][0])){
      $node->field_site_logo = NULL;
    }

    try {
      node_save($node);
      $space->controllers->variable->set('show_email', $form_state['values']['contact']);
    }
    catch (Exception $e) {
      drupal_set_message(t('Error saving site information. Contact your site administrator.'), 'error');
      error_log($e);
    }
  }
  else {
    boxes_box_form_submit($form, $form_state);
    variable_set('show_email', $form_state['values']['contact']);
  }
}

