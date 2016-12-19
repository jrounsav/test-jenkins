<?php
/**
 * @file
 * asu_os_lab_site.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function asu_os_lab_site_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create lab content'.
  $permissions['create lab content'] = array(
    'name' => 'create lab content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
      'web services' => 'web services',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any lab content'.
  $permissions['delete any lab content'] = array(
    'name' => 'delete any lab content',
    'roles' => array(
      'administrator' => 'administrator',
      'manager' => 'manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own lab content'.
  $permissions['delete own lab content'] = array(
    'name' => 'delete own lab content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any lab content'.
  $permissions['edit any lab content'] = array(
    'name' => 'edit any lab content',
    'roles' => array(
      'administrator' => 'administrator',
      'manager' => 'manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own lab content'.
  $permissions['edit own lab content'] = array(
    'name' => 'edit own lab content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  return $permissions;
}
