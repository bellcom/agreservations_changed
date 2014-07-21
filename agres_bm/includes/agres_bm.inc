<?php

/**
 * @file
 * agres_bm -> bookingmode base class to derive from when creating new
 * bookingmodes
 */

/**
 * 
 */
abstract class  agres_bm {
    //how to display the current cart item depending on items bookingmode
     static function _agr_return_booking_link($item){}
    //display booking and reservation info in the ubercart cart
     static function agr_cart_info_form(){}
    //reserve and add to cart according to bookingmode which implements this function
     static function _agres_bookings_reserve_and_fillcart($resnid = null, $uid = null, $puserrequest = array(), $categorynid = 0, $pselectunittype = 0, $userrequestunit = array(), $goto = '',&$form_state) {}
    //_searchwidget_form
     static function _agr_searchwidget_form($form_state, $args){}
    //_searchwidget_form_validate
     static function _agr_searchwidget_form_validate($form, &$form_state){}
    //_searchwidget_form_submit
     static function _agr_searchwidget_form_submit($form, &$form_state){}
    //call this inside hook_form    
     static function _agr_get_details_form(){}    
    //call this inside hook_form_validate
     static function _agr_get_details_form_validate($form, &$form_state){}
    //call this inside hook_form_submit
     static function _agr_get_details_form_submit($form, &$form_state){}         
}
