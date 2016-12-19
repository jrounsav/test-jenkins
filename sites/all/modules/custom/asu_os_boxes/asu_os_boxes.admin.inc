<?php

/**
 * @function asu_os_boxes_admin
 *
 * returns ASU OS admin form for misc. top-level elements
 */
function asu_brand_os_admin() {
  $form = array();
  $form['asu_os_boxes'] = array(
    '#type' => 'fieldset',
    '#title' => t('Configure ASU Brand OS'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#description' => t('Note: This module assumes responsibility for default global settings.'),
  );
  return system_settings_form($form);
}