<?php
/**
 * @file
 * od_music_agreservation.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function od_music_agreservation_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_agr_unit_type'
  $field_bases['field_agr_unit_type'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(
      0 => 'node',
    ),
    'field_name' => 'field_agr_unit_type',
    'foreign keys' => array(
      'nid' => array(
        'columns' => array(
          'nid' => 'nid',
        ),
        'table' => 'node',
      ),
    ),
    'indexes' => array(
      'nid' => array(
        0 => 'nid',
      ),
    ),
    'locked' => 0,
    'module' => 'node_reference',
    'settings' => array(
      'field_permissions' => array(
        'create' => 0,
        'edit' => 0,
        'edit own' => 0,
        'view' => 0,
        'view own' => 0,
      ),
      'referenceable_types' => array(
        'agres_category' => 0,
        'agres_timeframe' => 0,
        'agreservation' => 0,
        'agreservations_unit' => 0,
        'agreservations_unittype' => 'agreservations_unittype',
        'article' => 0,
        'page' => 0,
      ),
      'view' => array(
        'args' => array(),
        'display_name' => '',
        'view_name' => '',
      ),
    ),
    'translatable' => 1,
    'type' => 'node_reference',
  );

  // Exported field_base: 'field_agres_orderid'
  $field_bases['field_agres_orderid'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(
      0 => 'node',
    ),
    'field_name' => 'field_agres_orderid',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'number',
    'settings' => array(
      'field_permissions' => array(
        'create' => 0,
        'edit' => 0,
        'edit own' => 0,
        'view' => 0,
        'view own' => 0,
      ),
    ),
    'translatable' => 1,
    'type' => 'number_integer',
  );

  // Exported field_base: 'field_agres_rdate'
  $field_bases['field_agres_rdate'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(
      0 => 'node',
    ),
    'field_name' => 'field_agres_rdate',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'date',
    'settings' => array(
      'cache_count' => 4,
      'cache_enabled' => 0,
      'field_permissions' => array(
        'create' => 0,
        'edit' => 0,
        'edit own' => 0,
        'view' => 0,
        'view own' => 0,
      ),
      'granularity' => array(
        'day' => 'day',
        'hour' => 'hour',
        'minute' => 'minute',
        'month' => 'month',
        'second' => 0,
        'year' => 'year',
      ),
      'repeat' => 0,
      'timezone_db' => 'UTC',
      'todate' => 'required',
      'tz_handling' => 'site',
    ),
    'translatable' => 1,
    'type' => 'datetime',
  );

  // Exported field_base: 'field_agres_ref_agreservation'
  $field_bases['field_agres_ref_agreservation'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_agres_ref_agreservation',
    'foreign keys' => array(
      'nid' => array(
        'columns' => array(
          'nid' => 'nid',
        ),
        'table' => 'node',
      ),
    ),
    'indexes' => array(
      'nid' => array(
        0 => 'nid',
      ),
    ),
    'locked' => 0,
    'module' => 'node_reference',
    'settings' => array(
      'field_permissions' => array(
        'create' => 0,
        'edit' => 0,
        'edit own' => 0,
        'view' => 0,
        'view own' => 0,
      ),
      'referenceable_types' => array(
        'agres_category' => 0,
        'agres_timeframe' => 0,
        'agreservation' => 'agreservation',
        'agreservations_unit' => 0,
        'agreservations_unittype' => 0,
        'article' => 0,
        'page' => 0,
      ),
      'view' => array(
        'args' => array(),
        'display_name' => '',
        'view_name' => '',
      ),
    ),
    'translatable' => 1,
    'type' => 'node_reference',
  );

  // Exported field_base: 'field_agres_ref_category'
  $field_bases['field_agres_ref_category'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(
      0 => 'node',
    ),
    'field_name' => 'field_agres_ref_category',
    'foreign keys' => array(
      'nid' => array(
        'columns' => array(
          'nid' => 'nid',
        ),
        'table' => 'node',
      ),
    ),
    'indexes' => array(
      'nid' => array(
        0 => 'nid',
      ),
    ),
    'locked' => 0,
    'module' => 'node_reference',
    'settings' => array(
      'field_permissions' => array(
        'create' => 0,
        'edit' => 0,
        'edit own' => 0,
        'view' => 0,
        'view own' => 0,
      ),
      'referenceable_types' => array(
        'agres_category' => 'agres_category',
        'agres_timeframe' => 0,
        'agreservations_unittype' => 0,
        'article' => 0,
        'page' => 0,
      ),
      'view' => array(
        'args' => array(),
        'display_name' => '',
        'view_name' => '',
      ),
    ),
    'translatable' => 1,
    'type' => 'node_reference',
  );

  // Exported field_base: 'field_agres_ref_unit'
  $field_bases['field_agres_ref_unit'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(
      0 => 'node',
    ),
    'field_name' => 'field_agres_ref_unit',
    'foreign keys' => array(
      'nid' => array(
        'columns' => array(
          'nid' => 'nid',
        ),
        'table' => 'node',
      ),
    ),
    'indexes' => array(
      'nid' => array(
        0 => 'nid',
      ),
    ),
    'locked' => 0,
    'module' => 'node_reference',
    'settings' => array(
      'field_permissions' => array(
        'create' => 0,
        'edit' => 0,
        'edit own' => 0,
        'view' => 0,
        'view own' => 0,
      ),
      'referenceable_types' => array(
        'agreservation' => 0,
        'agreservation_unit_info' => 0,
        'agreservations_unit' => 'agreservations_unit',
        'agreservations_unittype' => 0,
        'article' => 0,
        'banner' => 0,
        'kontaktinfo' => 0,
        'os2web_borger_dk_article' => 0,
        'page' => 0,
        'selv' => 0,
        'spotboks' => 0,
        'subsite_nyhed' => 0,
        'velkomst' => 0,
      ),
      'view' => array(
        'args' => array(),
        'display_name' => '',
        'view_name' => '',
      ),
    ),
    'translatable' => 1,
    'type' => 'node_reference',
  );

  // Exported field_base: 'field_agres_refsingle_unit'
  $field_bases['field_agres_refsingle_unit'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(
      0 => 'node',
    ),
    'field_name' => 'field_agres_refsingle_unit',
    'foreign keys' => array(
      'nid' => array(
        'columns' => array(
          'nid' => 'nid',
        ),
        'table' => 'node',
      ),
    ),
    'indexes' => array(
      'nid' => array(
        0 => 'nid',
      ),
    ),
    'locked' => 0,
    'module' => 'node_reference',
    'settings' => array(
      'field_permissions' => array(
        'create' => 0,
        'edit' => 0,
        'edit own' => 0,
        'view' => 0,
        'view own' => 0,
      ),
      'referenceable_types' => array(
        'agres_category' => 0,
        'agres_timeframe' => 0,
        'agreservation' => 0,
        'agreservation_unit_info' => 0,
        'agreservations_unit' => 'agreservations_unit',
        'agreservations_unittype' => 0,
        'article' => 0,
        'page' => 0,
      ),
      'view' => array(
        'args' => array(),
        'display_name' => '',
        'view_name' => '',
      ),
    ),
    'translatable' => 1,
    'type' => 'node_reference',
  );

  // Exported field_base: 'field_agres_status'
  $field_bases['field_agres_status'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(
      0 => 'node',
    ),
    'field_name' => 'field_agres_status',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'number',
    'settings' => array(
      'field_permissions' => array(
        'create' => 0,
        'edit' => 0,
        'edit own' => 0,
        'view' => 0,
        'view own' => 0,
      ),
    ),
    'translatable' => 1,
    'type' => 'number_integer',
  );

  // Exported field_base: 'field_agres_unit_persons'
  $field_bases['field_agres_unit_persons'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(
      0 => 'node',
    ),
    'field_name' => 'field_agres_unit_persons',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'number',
    'settings' => array(
      'field_permissions' => array(
        'create' => 0,
        'edit' => 0,
        'edit own' => 0,
        'view' => 0,
        'view own' => 0,
      ),
    ),
    'translatable' => 1,
    'type' => 'number_integer',
  );

  // Exported field_base: 'field_agres_userref'
  $field_bases['field_agres_userref'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(
      0 => 'node',
    ),
    'field_name' => 'field_agres_userref',
    'foreign keys' => array(
      'uid' => array(
        'columns' => array(
          'uid' => 'uid',
        ),
        'table' => 'users',
      ),
    ),
    'indexes' => array(
      'uid' => array(
        0 => 'uid',
      ),
    ),
    'locked' => 0,
    'module' => 'user_reference',
    'settings' => array(
      'field_permissions' => array(
        'create' => 0,
        'edit' => 0,
        'edit own' => 0,
        'view' => 0,
        'view own' => 0,
      ),
      'referenceable_roles' => array(
        2 => 2,
        3 => 0,
        4 => 0,
        5 => 0,
        6 => 0,
        7 => 0,
        8 => 0,
        9 => 0,
      ),
      'referenceable_status' => array(
        0 => 0,
        1 => 1,
      ),
      'view' => array(
        'args' => array(),
        'display_name' => '',
        'view_name' => '',
      ),
    ),
    'translatable' => 1,
    'type' => 'user_reference',
  );

  // Exported field_base: 'field_agreservations_capacity'
  $field_bases['field_agreservations_capacity'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(
      0 => 'node',
    ),
    'field_name' => 'field_agreservations_capacity',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'number',
    'settings' => array(
      'field_permissions' => array(
        'create' => 0,
        'edit' => 0,
        'edit own' => 0,
        'view' => 0,
        'view own' => 0,
      ),
    ),
    'translatable' => 1,
    'type' => 'number_integer',
  );

  // Exported field_base: 'field_agreservations_unitnumber'
  $field_bases['field_agreservations_unitnumber'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(
      0 => 'node',
    ),
    'field_name' => 'field_agreservations_unitnumber',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'number',
    'settings' => array(
      'field_permissions' => array(
        'create' => 0,
        'edit' => 0,
        'edit own' => 0,
        'view' => 0,
        'view own' => 0,
      ),
    ),
    'translatable' => 1,
    'type' => 'number_integer',
  );

  // Exported field_base: 'field_agreservations_unittype'
  $field_bases['field_agreservations_unittype'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(
      0 => 'node',
    ),
    'field_name' => 'field_agreservations_unittype',
    'foreign keys' => array(
      'nid' => array(
        'columns' => array(
          'nid' => 'nid',
        ),
        'table' => 'node',
      ),
    ),
    'indexes' => array(
      'nid' => array(
        0 => 'nid',
      ),
    ),
    'locked' => 0,
    'module' => 'node_reference',
    'settings' => array(
      'field_permissions' => array(
        'create' => 0,
        'edit' => 0,
        'edit own' => 0,
        'view' => 0,
        'view own' => 0,
      ),
      'referenceable_types' => array(
        'agres_category' => 0,
        'agres_timeframe' => 0,
        'agreservations_unit' => 0,
        'agreservations_unittype' => 'agreservations_unittype',
        'article' => 0,
        'page' => 0,
      ),
      'view' => array(
        'args' => array(),
        'display_name' => '',
        'view_name' => '',
      ),
    ),
    'translatable' => 1,
    'type' => 'node_reference',
  );

  // Exported field_base: 'field_telefon'
  $field_bases['field_telefon'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_telefon',
    'foreign keys' => array(
      'format' => array(
        'columns' => array(
          'format' => 'format',
        ),
        'table' => 'filter_format',
      ),
    ),
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  return $field_bases;
}
