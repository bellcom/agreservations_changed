<?php
/**
 * @file
 *
 * Contains the controller for uc_cart_item entities.
 */
//class AgresBookingsCartItemController extends UcOrderProductController {   
//  public function attachLoad(&$items, $revision_id = FALSE) {
//     
//    foreach ($items as &$item) {
//      $product = uc_product_load_variant($item->nid, $item->data);
//      // Merge in fields from the product.
//      foreach ($product as $key => $value) {
//        $item->$key = $value;
//      }
//      $item->module = $item->data['module'];
//      
//    }
////    drupal_set_message('<pre>'.print_r($items,true).'</pre>');
//    parent::attachLoad($items, $revision_id);
//  }
//
//}
//class UcCartItemController extends UcOrderProductController {
////
////  public function attachLoad(&$items, $revision_id = FALSE) {
////    foreach ($items as &$item) {
////      $product = uc_product_load_variant($item->nid, $item->data);
////      // Merge in fields from the product.
////      foreach ($product as $key => $value) {
////        $item->$key = $value;
////      }
////      $item->module = $item->data['module'];
////    }
////    parent::attachLoad($items, $revision_id);
////  }UcOrderProductController   EntityAPIController
//}
/**
 * Controller class for the uc_order_product entity.UcCartItemController
 */
class AgrUcOrderProductController extends UcOrderProductController {

  /**
   * Overrides EntityAPIController::buildContent().
   */
  public function buildContent($product, $view_mode = 'full', $langcode = NULL, $content = array()) {
//      drupal_set_message('<pre>AgrUcOrderProductControllerbuildContent' . print_r($product, true) . '</pre>');
    $updown = '';
    $content['qty'] = array(
      '#theme' => 'uc_qty',
      '#qty' => $product->qty,
      '#cell_attributes' => array('class' => array('qty')),
    );
//    $content['updown'] = array(
//      '#theme' => 'updown',
//      '#updown' => $updown,
//      '#cell_attributes' => array('class' => array('updown')),
//    );        
    $node = node_load($product->nid);
    $title = node_access('view', $node) ? l($product->title, 'node/' . $node->nid) : check_plain($product->title); 
       $content['product'] = array(
      '#markup' =>$title . uc_product_get_description($product),
      '#cell_attributes' => array('class' => array('product')),
    );
    $content['model'] = array(
      '#markup' => check_plain($product->model),
      '#cell_attributes' => array('class' => array('sku')),
    );
    if (user_access('administer products')) {
      $content['cost'] = array(
        '#theme' => 'uc_price',
        '#price' => $product->cost,
        '#cell_attributes' => array('class' => array('cost')),
      );
    }
    $content['price'] = array(
      '#theme' => 'uc_price',
      '#price' => $product->price,
      '#suffixes' => array(),
      '#cell_attributes' => array('class' => array('price')),
    );
    $content['total'] = array(
      '#theme' => 'uc_price',
      '#price' => $product->price * $product->qty,
      '#suffixes' => array(),
      '#cell_attributes' => array('class' => array('total')),
    );

    return parent::buildContent($product, $view_mode, $langcode, $content);
  }

  /**
   * Overrides EntityAPIController::save().
   */
  public function save($product, DatabaseTransaction $transaction = NULL) {
    // Product kits, particularly, shouldn't actually be added to an order,
    // but instead they cause other products to be added.
    if (isset($product->skip_save) && $product->skip_save == TRUE) {
      return;
    }

    if (empty($product->weight_units)) {
      if (empty($product->nid)) {
        $product->weight_units = variable_get('uc_weight_unit', 'lb');
      }
      else {
        $units = db_query("SELECT weight_units FROM {node} n JOIN {uc_products} p ON n.vid = p.vid WHERE n.nid = :nid", array(':nid' => $product->nid))->fetchField();
        $product->weight_units = empty($units) ? variable_get('uc_weight_unit', 'lb') : $units;
      }
    }
    return parent::save($product, $transaction);
  }
}
