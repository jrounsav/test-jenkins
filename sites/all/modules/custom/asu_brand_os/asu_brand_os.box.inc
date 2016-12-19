<?php
/**
 * @file
 * asu_brand_os.box.inc
 */

/**
 * Implements hook_default_box().
 */
function asu_brand_os_default_box() {
  $export = array();

  // Header.
  $h_box = new stdClass();
  $h_box->disabled = FALSE; /* Edit this to true to make a default box disabled initially */
  $h_box->api_version = 1;
  $h_box->delta = 'os_box_asu_brand_header';
  $h_box->plugin_key = 'os_boxes_asu_brand';
  $h_box->title = '';
  $h_box->description = 'ASU Brand Header';
  $h_box->options = array(
    'visibility' => 'feature',
    'api' => FALSE,
    'list' => FALSE,
    'text' => 'ASU Brand Header',
    'display' => 'header',
  );
  $export['os_box_asu_brand_header'] = $h_box;

  // Footer.
  $f_box = new stdClass();
  $f_box->disabled = FALSE; /* Edit this to true to make a default box disabled initially */
  $f_box->api_version = 1;
  $f_box->delta = 'os_box_asu_brand_footer';
  $f_box->plugin_key = 'os_boxes_asu_brand';
  $f_box->title = '';
  $f_box->description = 'ASU Brand Header';
  $f_box->options = array(
    'visibility' => 'feature',
    'api' => FALSE,
    'list' => FALSE,
    'text' => 'ASU Brand footer',
    'display' => 'footer',
  );
  $export['os_box_asu_brand_footer'] = $f_box;

  return $export;
}
