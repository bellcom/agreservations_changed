<?php
/**
 * @file
 * od_music_agreservation.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function od_music_agreservation_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function od_music_agreservation_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function od_music_agreservation_node_info() {
  $items = array(
    'agreservation' => array(
      'name' => t('Reservation'),
      'base' => 'node_content',
      'description' => t('Enter reservations for Units with from and to time.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'agreservation_unit_info' => array(
      'name' => t('Unit info per reservation'),
      'base' => 'node_content',
      'description' => t('Info of an agreservations booked units like number of persons...'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'agreservations_unit' => array(
      'name' => t('Unit'),
      'base' => 'node_content',
      'description' => t('"reservable units: each unit is of 1 Unit Type, each Unit Type can be of n categories, if categories is enabled.
example: Unit "room #1" is of Unit Type "single" which is of category "Room" .
other example: Unit "Porsche red #434224" is of Unit type "sport cars" which is of categories "cars daily bookable"  AND "cars - hourly bookable" '),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'agreservations_unittype' => array(
      'name' => t('Unit type'),
      'base' => 'node_content',
      'description' => t('The Type of unit by agreservations module: Single, Double, Large, Presidents Suite, ...'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
