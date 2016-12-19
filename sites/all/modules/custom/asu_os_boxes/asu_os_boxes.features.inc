<?php
/**
 * @file
 * asu_os_boxes.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function asu_os_boxes_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "boxes" && $api == "box") {
    return array("version" => "1");
  }
}
