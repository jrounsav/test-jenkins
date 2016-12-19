<?php
/**
 * @file
 * asu_brand_os.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function asu_brand_os_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "boxes" && $api == "box") {
    return array("version" => "1");
  }
}
