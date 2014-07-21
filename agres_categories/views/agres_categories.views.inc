<?php

/**
 * @file
 * Views hooks for Ubercart products.
 */
//function agres_bookings_views_data_alter(&$data) {
//  // This example alters the title of the node:nid field in the Views UI.
//  $data['node']['nid']['title'] = t('Node-Nid');
//
//  // This example adds an example field to the users table.
//  $data['users']['example_field'] = array(
//    'title' => t('Example field'),
//    'help' => t('Some example content that references a user'),
//    'field' => array(
//      'handler' => 'modulename_handler_field_example_field',
//    ),
//  );
//
//  // This example changes the handler of the node title field.
//  // In this handler you could do stuff, like preview of the node when clicking
//  // the node title.
//  $data['node']['title']['field']['handler'] = 'modulename_handler_field_node_title';
//
//  // This example adds a relationship to table {foo}, so that 'foo' views can
//  // add this table using a relationship. Because we don't want to write over
//  // the primary key field definition for the {foo}.fid field, we use a dummy
//  // field name as the key.
//  $data['foo']['dummy_name'] = array(
//    'title' => t('Example relationship'),
//    'help' => t('Example help'),
//    'relationship' => array(
//      'base' => 'example_table', // Table we're joining to.
//      'base field' => 'eid', // Field on the joined table.
//      'field' => 'fid', // Real field name on the 'foo' table.
//      'handler' => 'views_handler_relationship',
//      'label' => t('Default label for relationship'),
//      'title' => t('Title seen when adding relationship'),
//      'help' => t('More information about relationship.'),
//    ),
//  );
//
//  // Note that the $data array is not returned – it is modified by reference.
//}
/**
 * Implements hook_views_data().
 */
function agres_categories_views_data() {

  $data['node']['actions2'] = array(
    'title' => t('AGR2 Actions'),
    'help' => t('Select UnitType for Hourly Booking'),
    'field' => array(
      'handler' => 'agres_categories_views_handler_field_select_utypehourly',
      'group' => 'AGR2',
      'click sortable' => FALSE,
    ),
  );
  $data['node']['actions'] = array(
    'title' => t('AGR Actions'),
    'help' => t('Select Unit Type for Package Booking'),
    'field' => array(
      'handler' => 'agres_categories_views_handler_field_select_unittype',
      'group' => 'AGR',
      'click sortable' => FALSE,
    ),
  );
//  $data['node']['select_unit'] = array(
//    'title' => t('AGR Select Unit Package Booking'),
//    'help' => t('select a unit - button for Package Booking'),
//    'field' => array(
//      'handler' => 'agres_bookings_handler_field_select_unit',
//    ),
//  );
//  
//    $data['uc_product']['table']['group'] = t('AGR Product');

//  $data['uc_product']['table']['join'] = array(
//    'node' => array(
//      'left_field' => 'vid',
//      'field' => 'vid',
//    ),
//    'node_revisions' => array(
//      'left_field' => 'vid',
//      'field' => 'vid',
//    ),
//  );

  
//  $data['uc_product']['agrselunitpackagebutton'] = array(
//    'title' => t('AGR Select unit'),
//    'help' => t('AGR: A button to add a product to the cart without quantity or attribute fields.'),
//    'group' => t('Product'),
//    'field' => array(
//      'table' => 'node',
//      'additional fields' => array(
//        'nid' => array(
//          'table' => 'node',
//          'field' => 'nid',
//        ),
//      ),
//      'handler' => 'agres_bookings_handler_field_selectunit',
//      'element type' => 'div',
//    ),
//  );

  return $data;
}
