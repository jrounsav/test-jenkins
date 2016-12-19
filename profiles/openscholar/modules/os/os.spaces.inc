<?php
/**
 * @file
 * os.spaces.inc
 */

/**
 * Implements hook_spaces_presets().
 */
function os_spaces_presets() {
  $export = array();

  $spaces_presets = new stdClass();
  $spaces_presets->disabled = FALSE; /* Edit this to true to make a default spaces_presets disabled initially */
  $spaces_presets->api_version = 3;
  $spaces_presets->name = 'os_department';
  $spaces_presets->title = 'HWP Academic';
  $spaces_presets->description = '';
  $spaces_presets->space_type = 'og';
  $spaces_presets->value = array(
    'bundles' => array(
      0 => 'department',
    ),
    'og_tasks' => array(
      0 => 'vsite_preset_section_about',
      1 => 'vsite_preset_section_academics',
      2 => 'vsite_preset_section_research',
      3 => 'vsite_preset_section_activities',
      4 => 'vsite_preset_section_resources',
      5 => 'vsite_preset_section_news_&_events',
      6 => 'vsite_preset_menu_order',
    ),
    'variable' => array(
      'vsite_preset_menu_order' => array(
        'primary-menu' => array(
          'HOME' => -8,
          'Academics' => -7,
          'Research' => -6,
          'Activities' => -5,
          'People' => -4,
          'Resources' => -3,
          'News & Events' => -2,
          'About' => -1,
        ),
      ),
      'spaces_features' => array(
        'os' => '1',
        'os_pages' => '1',
        'os_news' => '1',
        'os_events' => '1',
        'os_profiles' => '1',
        'os_links' => '1',
      ),
      'spaces_features_available' => array(
        0 => 'os_blog',
        1 => 'os_booklets',
        2 => 'os_classes',
        3 => 'os_events',
        4 => 'os_faq',
        5 => 'os_files_private',
        6 => 'os_image_gallery',
        7 => 'os_links',
        8 => 'os_news',
        9 => 'os_pages',
        10 => 'os_presentations',
        11 => 'os_profiles',
        12 => 'os_publications',
        13 => 'os_reader',
        14 => 'os_software',
        15 => 'harvard_courses',
      ),
      'site_frontpage' => 'home',
      'theme_default' => 'hwpi_classic',
      'os_breadcrumbs_show_breadcrumbs' => 0,
    ),
    'menus' => array(
      'primary-menu' => array(
        900 => array(
          'link_path' => 'home',
          'link_title' => 'HOME',
          'options' => array(),
          'mlid' => 900,
          'p1' => 900,
          'depth' => 1,
          'router_path' => 'home',
          'menu_name' => 'primary-menu',
          'external' => 1,
          'weight' => 0,
          'hidden' => 0,
          'has_children' => 0,
          'expanded' => 0,
          'module' => 'menu',
          'customized' => 0,
          'updated' => 0,
          'plid' => 0,
          'p2' => 0,
          'p3' => 0,
          'p4' => 0,
          'p5' => 0,
          'p6' => 0,
          'p7' => 0,
          'p8' => 0,
          'p9' => 0,
        ),
        902 => array(
          'link_path' => 'people',
          'link_title' => 'People',
          'options' => array(),
          'mlid' => 902,
          'p1' => 902,
          'depth' => 1,
          'router_path' => 'people',
          'menu_name' => 'primary-menu',
          'external' => 1,
          'weight' => 0,
          'hidden' => 0,
          'has_children' => 0,
          'expanded' => 0,
          'module' => 'menu',
          'customized' => 0,
          'updated' => 0,
          'plid' => 0,
          'p2' => 0,
          'p3' => 0,
          'p4' => 0,
          'p5' => 0,
          'p6' => 0,
          'p7' => 0,
          'p8' => 0,
          'p9' => 0,
        ),
      ),
    ),
    'context' => array(
      'os_public:reaction:block' => array(
        'blocks' => array(
          'os-secondary-menu' => array(
            'module' => 'os',
            'delta' => 'secondary-menu',
            'region' => 'header_third',
            'weight' => '-11',
            'status' => 0,
            'title' => '',
          ),
          'os-primary-menu' => array(
            'module' => 'os',
            'delta' => 'primary-menu',
            'region' => 'menu_bar',
            'weight' => '-10',
            'status' => 0,
            'title' => '',
          ),
          'boxes-site_info' => array(
            'module' => 'boxes',
            'delta' => 'site_info',
            'region' => 'header_second',
            'weight' => '-10',
            'status' => 0,
            'title' => '',
          ),
          'os_search_solr-site-search' => array(
            'module' => 'os_search_solr',
            'delta' => 'site-search',
            'region' => 'header_third',
            'weight' => '-10',
            'status' => 0,
            'title' => '',
          ),
        ),
      ),
      'os_front:reaction:block' => array(
        'blocks' => array(),
      ),
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('HWP Academic');
  $export['os_department'] = $spaces_presets;

  $spaces_presets = new stdClass();
  $spaces_presets->disabled = FALSE; /* Edit this to true to make a default spaces_presets disabled initially */
  $spaces_presets->api_version = 3;
  $spaces_presets->name = 'os_department_minimal';
  $spaces_presets->title = 'Department Minimal';
  $spaces_presets->description = '';
  $spaces_presets->space_type = 'og';
  $spaces_presets->value = array(
    'bundles' => array(
      0 => 'department',
    ),
    'variable' => array(
      'spaces_features' => array(
        'os' => '1',
        'os_pages' => '1',
      ),
      'spaces_features_available' => array(
        0 => 'os_blog',
        1 => 'os_booklets',
        2 => 'os_classes',
        3 => 'os_events',
        4 => 'os_faq',
        5 => 'os_files_private',
        6 => 'os_image_gallery',
        7 => 'os_links',
        8 => 'os_news',
        9 => 'os_pages',
        10 => 'os_presentations',
        11 => 'os_profiles',
        12 => 'os_publications',
        13 => 'os_reader',
        14 => 'os_software',
        15 => 'harvard_courses',
      ),
      'site_frontpage' => 'home',
      'theme_default' => 'hwpi_classic',
      'os_breadcrumbs_show_breadcrumbs' => 0,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Department Minimal');
  $export['os_department_minimal'] = $spaces_presets;

  $spaces_presets = new stdClass();
  $spaces_presets->disabled = FALSE; /* Edit this to true to make a default spaces_presets disabled initially */
  $spaces_presets->api_version = 3;
  $spaces_presets->name = 'os_project';
  $spaces_presets->title = 'Project Minimal';
  $spaces_presets->description = '';
  $spaces_presets->space_type = 'og';
  $spaces_presets->value = array(
    'bundles' => array(
      0 => 'project',
    ),
    'variable' => array(
      'spaces_features' => array(
        'os' => '1',
        'os_pages' => '1',
        'os_news' => '1',
        'os_events' => '1',
        'os_profiles' => '1',
        'os_links' => '1',
      ),
      'spaces_features_available' => array(
        0 => 'os_blog',
        1 => 'os_booklets',
        2 => 'os_classes',
        3 => 'os_events',
        4 => 'os_faq',
        5 => 'os_files_private',
        6 => 'os_image_gallery',
        7 => 'os_links',
        8 => 'os_news',
        9 => 'os_pages',
        10 => 'os_presentations',
        11 => 'os_profiles',
        12 => 'os_publications',
        13 => 'os_reader',
        14 => 'os_software',
        15 => 'harvard_courses',
      ),
      'site_frontpage' => 'home',
      'theme_default' => 'hwpi_classic',
      'os_breadcrumbs_show_breadcrumbs' => 0,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Project Minimal');
  $export['os_project'] = $spaces_presets;

  $spaces_presets = new stdClass();
  $spaces_presets->disabled = FALSE; /* Edit this to true to make a default spaces_presets disabled initially */
  $spaces_presets->api_version = 3;
  $spaces_presets->name = 'os_scholar';
  $spaces_presets->title = 'Personal Minimal';
  $spaces_presets->description = '';
  $spaces_presets->space_type = 'og';
  $spaces_presets->value = array(
    'bundles' => array(
      0 => 'personal',
    ),
    'og_tasks' => array(
      0 => 'vsite_preset_section_bio',
    ),
    'variable' => array(
      'spaces_features' => array(
        'os' => '1',
        'os_pages' => 1,
        'os_classes' => 1,
        'os_publications' => 1,
        'os_biocv' => 0,
     ),
      'vsite_preset_menu_order' => array(
        'primary-menu' => array(
          'Bio' => -3,
          'Classes' => -2,
          'Publications' => -1,
        ),
      ),
      'spaces_features_available' => array(
        0 => 'os_blog',
        1 => 'os_booklets',
        2 => 'os_classes',
        3 => 'os_events',
        4 => 'os_faq',
        5 => 'os_files_private',
        6 => 'os_image_gallery',
        7 => 'os_links',
        8 => 'os_news',
        9 => 'os_pages',
        10 => 'os_presentations',
        11 => 'os_profiles',
        12 => 'os_publications',
        13 => 'os_reader',
        14 => 'os_software',
        15 => 'harvard_courses',
      ),
      'site_frontpage' => 'home',
      'theme_default' => 'hwpi_classic',
      'os_breadcrumbs_show_breadcrumbs' => 0,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Personal Minimal');
  $export['os_scholar'] = $spaces_presets;

  return $export;
}
