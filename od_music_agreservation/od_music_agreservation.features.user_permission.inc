<?php
/**
 * @file
 * od_music_agreservation.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function od_music_agreservation_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'view agres_views bookingcalendar'.
  $permissions['view agres_views bookingcalendar'] = array(
    'name' => 'view agres_views bookingcalendar',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'agres_views',
  );

  return $permissions;
}
