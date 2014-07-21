<?php

/**
 * Formats the cart contents table on the checkout page.
 *
 * @param $variables
 *   An associative array containing:
 *   - show_subtotal: TRUE or FALSE indicating if you want a subtotal row
 *     displayed in the table.
 *   - items: An associative array of cart item information containing:
 *     - qty: Quantity in cart.
 *     - title: Item title.
 *     - price: Item price.
 *     - desc: Item description.
 *
 * @return
 *   The HTML output for the cart review table.
 *
 * @ingroup themeable
 */
function theme_agres_bookings_cart_review_table($variables) {
 $items = $variables['items'];
  $show_subtotal = $variables['show_subtotal'];

  $subtotal = 0;

  // Set up table header.
  $header = array(
    array('data' => theme('uc_qty_label'), 'class' => array('qty')),
    array('data' => t('Products'), 'class' => array('products')),
    array('data' => t('Price'), 'class' => array('price')),
  );

  // Set up table rows.
  $display_items = uc_order_product_view_multiple($items);
//  drupal_set_message('<pre>theme_agres_bookings_cart_review_tafxghxfghxfgble#####'.print_r($display_items,true).'</pre>');
  if (!empty($display_items['uc_order_product'])) {
    foreach (element_children($display_items['uc_order_product']) as $key) {
        
      $display_item = $display_items['uc_order_product'][$key];
      $subtotal += $display_item['total']['#price'];
//      if (isset($display_item['#entity']->data['returnbooking']) && ($display_item['#entity']->data['returnbooking']==1)){
//          $display_item['product']['#markup'] = t('Return Booking:').' '.$display_item['product']['#markup'];
//      }
//      drupal_set_message('<pre>theme_agres_bookings_cart_review_tafxghxfghxfgble#####'.print_r($display_item['#entity']->data['checkintime'],true).'</pre>');
//      $display_item['#entity']->title = 'hhh';

      //empty row:
     
//      $rows[] = array(
//        array('data' => '', 'class' => array('checkintime')),
//        array('data' => t( 'Date/Time: ').$display_item['#entity']->data['checkintime'].'  '.$display_item['#entity']->data['checkouttime'], 'class' => array('dateinfo')),
//        array('data' => '', 'class' => array('empty')),
//      );
      $rows[] = array(
        array('data' => $display_item['qty'], 'class' => array('qty')),
        array('data' => $display_item['product'], 'class' => array('products')),
        array('data' => $display_item['total'], 'class' => array('price')),
      );      
    }
  }

  // Add the subtotal as the final row.
  if ($show_subtotal) {
    $rows[] = array(
      'data' => array(
        // One cell
        array(
          'data' => array(
            '#theme' => 'uc_price',
            '#prefix' => '<span id="subtotal-title">' . t('Subtotal:') . '</span> ',
            '#price' => $subtotal,
          ),
          // Cell attributes
          'colspan' => 3,
          'class' => array('subtotal'),
        ),
      ),
      // Row attributes
      'class' => array('subtotal'),
    );
  }

  return theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('class' => array('cart-review'))));

}