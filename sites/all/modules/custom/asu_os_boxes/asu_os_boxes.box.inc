<?php
/**
 * @file
 * asu_brand_os.box.inc
 */

/**
 * Implements hook_default_box().
 */
function asu_os_boxes_default_box() {
  $export = array();

  // Header.
  $h_box = new stdClass();
  $h_box->disabled = FALSE; /* Edit this to true to make a default box disabled initially */
  $h_box->api_version = 1;
  $h_box->delta = 'os_box_asu_more_site_info';
  $h_box->plugin_key = 'asu_os_boxes_site_info';
  $h_box->title = '';
  $h_box->description = 'ASU Site Info';
  $h_box->options = array(
    'visibility' => 'feature',
    'api' => FALSE,
    'list' => FALSE,
    'text' => 'ASU Site Info',
    'display' => 'header',
  );
  $export['os_box_asu_more_site_info'] = $h_box;

  // Footer.
  $f_box = new stdClass();
  $f_box->disabled = FALSE; /* Edit this to true to make a default box disabled initially */
  $f_box->api_version = 1;
  $f_box->delta = 'os_box_asu_more_main_menu';
  $f_box->plugin_key = 'asu_os_boxes_main_menu';
  $f_box->title = '';
  $f_box->description = 'ASU Main Menu';
  $f_box->options = array(
    'visibility' => 'feature',
    'api' => FALSE,
    'list' => FALSE,
    'text' => 'ASU Main Menu',
    'display' => 'header',
  );
  $export['os_box_asu_more_menu'] = $f_box;

  return $export;
}
