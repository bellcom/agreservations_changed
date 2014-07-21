<?php

/**
 * @file
 * Views handler: Simpler "Add to cart" form as a field.
 */

/**
 * Displays the simpler Add to cart form like the catalog.
 */
class agres_categories_views_handler_field_select_unittype extends views_handler_field {

  /**
   * Overrides views_handler_field::query().
   */
  function query() {
   //no changes to query necessary
  }

  /**
   * Overrides views_handler_field::render().
   */
  function render($values) {
//      drupal_set_message('<pre>renderrender_'.print_r($values,true).'</pre>');
        $select_unittype_package_button_params = array('unittypenid' => $values->nid,
        'packagenid' => $values->field_agr_pack_units_node_nid,);
        $form = drupal_get_form('agres_categories_select_unittype_btn_form_' . $values->nid, $select_unittype_package_button_params);
        return drupal_render($form);
    }
}
