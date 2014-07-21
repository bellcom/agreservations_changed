<?php

/**
 * @file
 * @todo Fill this in. 
 */

/**
 * Return fields array.
 * 
 * @todo Documentation
 */
function _agres_bookings_fields() {
  $fields = array();
   // Exported field: 'uc_order-uc_order-field_agr_associated_res'
  $fields['uc_order-uc_order-field_agr_associated_res'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '-1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_agr_associated_res',
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
      'module' => 'node_reference',
      'settings' => array(
        'referenceable_types' => array(
          'agres_category' => 0,
          'agres_rate' => 0,
          'agres_service' => 0,
          'agres_timeframe' => 0,
          'agreservation' => 'agreservation',
          'agreservation_unit_info' => 0,
          'agreservations_unit' => 0,
          'agreservations_unittype' => 0,
          'article' => 0,
          'page' => 0,
          'product' => 0,
          'product_kit' => 0,
          'service_product' => 0,
        ),
        'view' => array(
          'args' => array(),
          'display_name' => '',
          'view_name' => '',
        ),
      ),
      'translatable' => '0',
      'type' => 'node_reference',
    ),
    'field_instance' => array(
      'bundle' => 'uc_order',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'node_reference',
          'settings' => array(),
          'type' => 'node_reference_default',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'uc_order',
      'field_name' => 'field_agr_associated_res',
      'label' => 'associated reservation',
      'required' => 0,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'node_reference',
        'settings' => array(
          'autocomplete_match' => 'contains',
          'autocomplete_path' => 'node_reference/autocomplete',
          'size' => '60',
        ),
        'type' => 'node_reference_autocomplete',
        'weight' => '10',
      ),
    ),
  );
  // Exported field: 'node-agreservation-field_agr_uc_products_references'.
  $fields['node-agreservation-field_agr_uc_products_references'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_agr_uc_products_references',
      'foreign keys' => array(
        'node' => array(
          'columns' => array(
            'target_id' => 'nid',
          ),
          'table' => 'node',
        ),
      ),
      'indexes' => array(
        'target_id' => array(
          0 => 'target_id',
        ),
      ),
      'locked' => '0',
      'module' => 'entityreference',
      'settings' => array(
        'handler' => 'base',
        'handler_settings' => array(
          'behaviors' => array(
            'field_default_token' => array(
              'status' => TRUE,
            ),
            'views-select-list' => array(
              'status' => 0,
            ),
          ),
          'sort' => array(
            'type' => 'none',
          ),
          'target_bundles' => array(
            'agres_package' => 'agres_package',
            'agres_rate' => 'agres_rate',
            'agreservations_unittype' => 'agreservations_unittype',
          ),
        ),
        'target_type' => 'node',
      ),
      'translatable' => '0',
      'type' => 'entityreference',
    ),
    'field_instance' => array(
      'bundle' => 'agreservation',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => t('AGreservations used this field to sync uc_cart items with reservations.'),
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'entityreference',
          'settings' => array(
            'colorbox_node_height' => '600',
            'colorbox_node_link' => FALSE,
            'colorbox_node_width' => '600',
            'link' => FALSE,
          ),
          'type' => 'entityreference_label',
          'weight' => 16,
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'field_agr_uc_products_references',
      'label' => 'agr_uc_products_references',
      'required' => 0,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'options',
        'settings' => array(
          'apply_chosen' => 0,
        ),
        'type' => 'options_select',
        'weight' => '20',
      ),
    ),
  );
  // Translatables
  // Included for use with string extractors like potx.
   t('agr_uc_products_references');
  t('associated reservation');

  return $fields;
}