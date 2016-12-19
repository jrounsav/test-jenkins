<?php

function cp_theme_preprocess_page(&$vars) {
  $vars['breadcrumb'] = '';
}

/**
 * Override theme_file_icon
 */
function cp_theme_file_icon($variables) {
  $file = $variables['file'];
  $alt = $variables['alt'];
  $icon_directory = $variables['icon_directory'];

  // Setting icon directory for svg files
  $icon_directory = variable_get('file_icon_directory', drupal_get_path('module', 'os_files') . '/icons');
  $icon_url = file_icon_url($file, $icon_directory);

  // Replacing png icons with svg
  $svg_url = str_replace('.png', '.svg', $icon_url );
  $mime = check_plain($file->filemime);
  return '<img class="file-icon" alt="' . check_plain($alt) . '" title="' . $mime . '" src="' . $svg_url . '" />';
}