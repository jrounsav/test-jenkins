<?php
/**
 * @file
 * asu_os_lab_site.features.metatag.inc
 */

/**
 * Implements hook_metatag_export_default().
 */
function asu_os_lab_site_metatag_export_default() {
  $config = array();

  // Exported Metatag config instance: node:lab.
  $config['node:lab'] = array(
    'instance' => 'node:lab',
    'config' => array(
      'description' => array(
        'value' => '[node:field_meta_description]',
      ),
      'og:type' => array(
        'value' => 'company',
      ),
      'og:image' => array(
        'value' => '[node:field_site_logo]',
      ),
    ),
  );

  return $config;
}
