<?php

class asu_os_boxes_hero extends os_boxes_default
{

  public function options_defaults()
  {
    $options = parent::options_defaults();

    $options['fid'] = 0;

    $options['name'] = array(
      'value' => '',
    );
    $options['name_ext'] = array(
      'value' => '',
    );
    $options['email'] = array(
      'value' => '',
    );
    $options['phone'] = array(
      'value' => '',
    );
    $options['office'] = array(
      'value' => '',
    );
    $options['bus_title'] = array(
      'value' => '',
    );
    $options['organization'] = array(
      'value' => '',
    );
    $options['extra'] = array(
      'value' => '',
    );
    $options['background'] = array();
    $options['background']['hero_options'] = 'd1';

    return $options;
  }

  public function options_form(&$form_state)
  {
    $form = parent::options_form($form_state);

    $form['fid'] = array(
      '#title' => t('Profile Picture'),
      '#type' => 'media',
      '#default_value' => array('fid' => $this->options['fid']),
      '#description' => t('Choose, enter or link to the media you wish to embed.'),
      '#media_options' => array(
        'global' => array(
          'id' => 'media_embed_widget',
          'types' => array(
            'image',
          ),
          'schemes' => array(
            'public' => 'public',
            'oembed' => 'oembed',
            'embed' => 'embed',
          ),
        ),
      )
    );

    $form['name'] = array(
      '#type' => 'textfield',
      '#title' => t('Name'),
      '#default_value' => isset($this->options['name']) ? $this->options['name'] : '',
      '#description' => t('A name to be featured on the hero in bold.'),
      '#size' => 120,
    );

    $form['name_ext'] = array(
      '#type' => 'textfield',
      '#title' => t('Name Extension'),
      '#default_value' => isset($this->options['name_ext']) ? $this->options['name_ext'] : '',
      '#description' => t('Extra text to follow the name inline without bold.'),
      '#size' => 120,
    );

    $form['email'] = array(
      '#type' => 'textfield',
      '#title' => t('Email'),
      '#default_value' => isset($this->options['email']) ? $this->options['email'] : '',
      '#description' => t('A contact email address for the name listed above.'),
      '#size' => 120,
    );

    $form['phone'] = array(
      '#type' => 'textfield',
      '#title' => t('Phone'),
      '#default_value' => isset($this->options['phone']) ? $this->options['phone'] : '',
      '#description' => t('A contact phone number for the name listed above.'),
      '#size' => 60,
    );

    $form['office'] = array(
      '#type' => 'textfield',
      '#title' => t('Location'),
      '#default_value' => isset($this->options['office']) ? $this->options['office'] : '',
      '#description' => t('A campus location where the subject can be found.'),
      '#size' => 60,
    );

    $form['bus_title'] = array(
      '#type' => 'textfield',
      '#title' => t('Business Title'),
      '#default_value' => isset($this->options['bus_title']) ? $this->options['bus_title'] : '',
      '#description' => t('The subject\'s business title or function.'),
      '#size' => 120,
    );

    $form['organization'] = array(
      '#type' => 'textfield',
      '#title' => t('Organization'),
      '#default_value' => isset($this->options['organization']) ? $this->options['organization'] : '',
      '#description' => t('The organization that the subject is associated with.'),
      '#size' => 120,
    );

    $form['extra'] = array(
      '#type' => 'textfield',
      '#title' => t('Additional Information'),
      '#default_value' => isset($this->options['extra']) ? $this->options['extra'] : '',
      '#description' => t('One line of extra information.'),
      '#size' => 120,
    );

    $form['background'] = array(
      '#type' => 'fieldset',
      '#title' => t('Hero Background'),
    );

    $form['background']['hero_options'] = array(
      '#type' => 'radios',
      '#title' => t('Hero Options'),
      '#default_value' => isset($this->options['background']['hero_options']) ? $this->options['background']['hero_options'] : 0,
      '#description' => t('You may choose between default backgrounds, or to upload your own.'),
      '#options' => array(
        'd1' => t('Alpha'),
        'd2' => t('Bravo'),
        'd3' => t('Charlie'),
      ),
    );

    /*
    $form['#attached']['js'][] = drupal_get_path('module', 'asu_os_boxes').'/plugins/asu_os_boxes_hero/asu_os_boxes_hero_form.js';
    */

    return $form;
  }

  public function options_submit($form, $form_state)
  {
    parent::options_submit($form, $form_state);

    $this->options['background']['hero_options'] = $form_state['input']['hero_options'];

    $old = $form['options']['fid']['#default_value']['fid'];

    if ($old != $this->options['fid']) {

      $id = FALSE;
      if (module_exists('vsite') && $vsite = vsite_get_vsite()) {
        $id = $vsite->group->nid;
      }

      if ($id && $file = file_load($this->options['fid'])) {
        file_usage_add($file, 'os_boxes', 'node', $id, 1);
      }

      if ($old && $old_file = file_load($old)) {
        if ($id) {
          file_usage_delete($old_file, 'os_boxes', 'node', $id, 1);
        }
        file_delete($old_file);
      }
    }
    $this->options['fid'] = $form_state['input']['fid'];

  }

  public function render()
  {
    $block = parent::render();

    $module_path = drupal_get_path('module', 'asu_os_boxes');
    $full_path = $module_path .'/plugins/asu_os_boxes_hero/css/asu_os_boxes_hero.css';
    drupal_add_css($full_path);

    $fid = $this->options['fid'];
    try {
      if (!empty($fid) && $file = file_load($fid)) {
        $path = $file->uri;
        $width = $file->image_dimensions['width'];
        $height = $file->image_dimensions['height'];
      } else {
        $path = drupal_get_path('module', 'asu_os_boxes') . '/plugins/asu_os_boxes_hero/default_pic.jpg';
      }
    } catch (Exception $e) {
      $path = drupal_get_path('module', 'asu_os_boxes') . '/plugins/asu_os_boxes_hero/default_pic.jpg';
    }

    $image = theme('image', array('path' => $path, 'alt' => 'Profile Image'));

    $heroName = asu_os_boxes_heroname($this->options["name"], $this->options["name_ext"]);
    $contactInfo = asu_os_boxes_herocontact($this->options["email"], $this->options["phone"], $this->options["office"]);
    $association = asu_os_boxes_hero_association($this->options);

    if (($block['content'] = $this->get_cache()) === FALSE) {
      $bgURL = asu_os_boxes_hero_background($this->options['background']['hero_options']);
      $this->set_cache($block['content']);
      $block['content'] = '<div class="asu_os_hero_wrapper">
  <div class="asu_os_hero" style="background-image:url( ' . $bgURL . ');">
    <div class="container">
      <div class="row">
        <div class="col-md-12">
            <h2>' . $heroName . '</h2>
        </div>
      </div>
      <div class="row">
        <div class="col-md-12">
          ' . $contactInfo . '
        </div>
      </div>
      <div class="row">
        <div class="col-sm-12 col-md-2">
          <div class="asu_os_hero_picture">
            ' . $image . '
          </div>
        </div>
        <div class="col-sm-12 col-md-10">
          <div class="asu_os_hero_associations">
            ' . $association . '
          </div>
        </div>
      </div>
    </div>
  </div>
  </div>';
    }

    return $block;
  }
}

function asu_os_boxes_heroname($name, $ext)
{
  $ret = '';
  if (!empty($name)) {
    $main = '<span class="asu_os_hero_name" style="font-weight: bold;">' . $name . '</span>';
  }
  if (!empty($ext)) {
    $second = '<span class="asu_os_hero_name_ext">' . $ext . '</span>';
  }
  if (!empty($main) && !empty($second)) {
    $ret = $main . ', ' . $second;
  } else if (!empty($main) && empty($second)) {
    $ret = $main;
  } else if (empty($main) && !empty($second)) {
    $ret = '<span class="asu_os_hero_name" style="font-weight: bold;">' . $ext . '</span>';
  }

  return $ret;
}

function asu_os_boxes_herocontact($email, $phone, $location)
{
  $output = "";
  if (!empty($email)) {
    $output .= '<span class="asu_os_hero_contact asu_os_hero_contact_email"><i class="fa fa-envelope" aria-hidden="true"></i> ' . $email . '</span>';
  }
  if (!empty($phone)) {
    $output .= '<span class="asu_os_hero_contact asu_os_hero_contact_phone"><i class="fa fa-phone" aria-hidden="true"></i> ' . $phone . '</span>';
  }
  if (!empty($location)) {
    $output .= '<span class="asu_os_hero_contact asu_os_hero_contact_location"><i class="fa fa-map-marker" aria-hidden="true"></i> ' . $location . '</span>';
  }

  return $output;
}

function asu_os_boxes_hero_association($information)
{
  $output = "";
  if (!empty($information['bus_title'])) {
    $output .= '<div class="asu_os_hero_associations_title">' . $information["bus_title"] . '</div>';
  }
  if (!empty($information['organization'])) {
    $output .= '<div class="asu_os_hero_associations_organization">' . $information["organization"] . '</div>';
  }
  if (!empty($information['extra'])) {
    $output .= '<div class="asu_os_hero_associations_extra">' . $information["extra"] . '</div>';
  }

  return $output;
}

function asu_os_boxes_hero_background($choice){
  global $base_url;
  $bgURL = $base_url . "/sites/all/modules/custom/asu_os_boxes/plugins/asu_os_boxes_hero/images/";

  switch($choice) {
    case "d1":
        $bgURL .= "Hero.png";
      break;
    case "d2":
      $bgURL .= "Hero2.png";
      break;
    case "d3":
      $bgURL .= "Hero3.png";
      break;
  }

  return $bgURL;
}