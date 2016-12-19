<?php

/**
 * @file
 * The class for the site's main menu
 */
class asu_os_boxes_main_menu extends os_boxes_default {

  /**
   * TODO - Add code to render the site's 'primary menu'.
   */

  /**
   * Implementation of boxes_content::options_defaults().
   */
  public function options_defaults() {
    $options = parent::options_defaults();
    return $options;
  }

  /**
   * Implementation of boxes_content::options_form().
   */
  public function options_form(&$form_state) {
    $form = parent::options_form();
    return $form;
  }

  /**
   * Implementation of boxes_content::render().
   *
   * Generates Primary Menu content for global ASU header
   */
  public function render() {
    if (module_exists('vsite') && !vsite_get_vsite()) {
      return;
    }
    $block = parent::render();
    if (module_exists('vsite_menu')) {
      // pulled in code from os_menu_tree in os module inc
      ctools_include('menu', 'os');
      $menus = os_get_menus();
      if (!isset($menus['primary-menu'])) {
        return $block;
      }
      // Generate new block with main menu code.
      $block2 = module_invoke('os', 'block_view', 'primary-menu');
      $block = array_merge($block, $block2);
      // Create theme variables, per os_theme definition (os.module)
      $primary_menu = array(
        'region' => 'none__go_with_default__down',
        'menu_name' => 'primary-menu',
      );
      // Now manually theme output for primary menu, using OS's custom
      // nice_menus theme call in os.module
      $block['content'] = '<div class="asu-global asu-global--outer">' . "\n";
      $block['content'] .= '    <nav class="block block-os no-title menu-wrapper menu-bar-wrapper clearfix" id="block-asu-primary-menu">' .
        theme('os_nice_menus', $primary_menu);
      $block['content'] .= "\n  </nav>\n</div>";

      switch ($this->options['display']) {
        case 'header':
          // nothing for now
        default :
          $block['content'] = render($block['content']);
          break;
      }
    }

    return $block;
  }
}
