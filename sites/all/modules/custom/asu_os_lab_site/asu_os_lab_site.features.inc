<?php
/**
 * @file
 * asu_os_lab_site.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function asu_os_lab_site_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function asu_os_lab_site_node_info() {
  $items = array(
    'lab' => array(
      'name' => t('Lab Site'),
      'base' => 'node_content',
      'description' => t('An OpenScholar site for labs.'),
      'has_title' => '1',
      'title_label' => t('Site Name'),
      'help' => '',
    ),
  );
  return $items;
}
