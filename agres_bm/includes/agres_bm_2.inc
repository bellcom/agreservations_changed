<?php

/**
 * @file
 * agres_bm -> bookingmode base class to derive from when creating new
 * bookingmodes
 */
require_once('./' . drupal_get_path('module', 'agres_bm') . '/includes/agres_bm.inc');
/**
 * 
 */
 class agres_bm_2 extends agres_bm{
    //display booking and reservation info in the ubercart cart
     static function agr_cart_info_form(){
         
     }
     
    //reserve and add to cart according to bookingmode which implements this function
     static function agr_reserve_and_fillcart(){
  //initialize:    
  $ratesntypes = array();
  if ($resnid <> null) {    
//  drupal_set_message('<pre>$alreadyincartitems:'.print_r($resnid,true).'</pre>');  
    $lang_aut = 'und';
    $uid = $uid ? $uid : uc_cart_get_id();
    $resnode = node_load($resnid);
//    drupal_set_message('<pre>_agres_bookings_reserve_and_fillcart:'.print_r($resnode,true).'</pre>');  
    $dateTimezone1 = new DateTimeZone(date_default_timezone());
    $langur = 'und';
    $langur = field_language('node', $resnode,'field_agres_ref_unit');     
    $lang = 'und';
    $lang = field_language('node', $resnode,'field_agres_rdate');    
    $tmpcheckindt = new DateTime($resnode->field_agres_rdate[$lang][0]['value'], $dateTimezone1);
    $tmpcheckoutdt = new DateTime($resnode->field_agres_rdate[$lang][0]['value2'], $dateTimezone1);
    $offset = $tmpcheckindt->getOffset();
    $offset = $offset * 1;
    $tmpcheckindt->modify($offset . 'seconds');
    $tmpcheckoutdt->modify($offset . 'seconds');
    $tmpcheckin = new DateObject($tmpcheckindt->format('Y-m-d H:i:s'));
    $tmpcheckout = new DateObject($tmpcheckoutdt->format('Y-m-d H:i:s'));
    $unitsToBook = array();
    $lang = 'und';
    $lang = field_language('node', $resnode,'field_agres_ref_unit');  
          //packagenrs herausfinden:
    $package = null;
//     drupal_set_message('<pre>$puserrequest$puserrequest'.print_r($puserrequest, true) . '</pre>');
      if(isset($puserrequest['packagenid'])){
        $package = node_load($puserrequest['packagenid']);  
      }
//********************************************************************************************************************************
//************************take into account already in cart products and count if already reserved units match:*******************    
    $alreadyincartitems = uc_cart_get_contents(uc_cart_get_id());
    foreach ($alreadyincartitems as $ckey => $cartitem) {
//        drupal_set_message('<pre>$cartitem$cartitem$cartitem-----'.print_r($cartitem, true) . '</pre>');
        if (isset($cartitem->data['times'])){
            $unittypesincart[$cartitem->nid]['count'] =  ($cartitem->qty / $cartitem->data['times']);
        }        
    }      
    $unitsnumberperunittypeinres = array();
    foreach ($resnode->field_agres_ref_unit[$langur] as $key => $refunit) {         
            $tmpunit = node_load($refunit['nid']);
            $lang = 'und';
            $lang = field_language('node', $tmpunit, 'field_agreservations_unittype');
//             drupal_set_message('<pre>$tmpunit:'.print_r($tmpunit,true).'</pre>');  
            $tmpunittype = $tmpunit->field_agreservations_unittype[$lang][0]['nid'];      
//            $unitsnumberperunittypeinres = array($tmpunittype)
            $unitsnumberperunittypeinres[$tmpunittype]['count'] += 1;
//             drupal_set_message('<pre>in_multi_assoc_array'.print_r($refunit->nid, true) . '</pre>');
//             drupal_set_message('<pre>$unitsnumberperunittypeinres  '.print_r($unitsnumberperunittypeinres, true) . '</pre>');
            if ($package) {                 
                ///vergleichen ob unitnid = in package
                $langcode = field_language('node', $package, 'field_agr_pack_units');              
                //Z/setzt voraus dass nur package reservierung eines gewählten packages gerade stattfindet:
//                drupal_set_message('<pre>$unitsnumberperunittypeinres:'.print_r($tmpunit,true).'</pre>');
                if (in_multi_assoc_array($tmpunit->nid, $package->field_agr_pack_units[$langcode])) {
//                     drupal_set_message('<pre>in_multi_assoc_array'.print_r($refunit->nid, true) . '</pre>');
                    $unitsinrespackage[$package->nid]['count'] += 1;
                }
            }
        }
//         drupal_set_message('<pre>$unitsnumberperunittypeinres:'.print_r($unitsnumberperunittypeinres,true).'</pre>');  
//********************************************************************************************************************************
//********************************************************************************************************************************    
      foreach ($resnode->field_agres_ref_unit[$langur] as $key => $refunit) {
      $tmpunit = node_load($refunit['nid']);
      $lang = 'und';
      $lang = field_language('node', $tmpunit,'field_agreservations_unittype'); 
      $tmpunittype = $tmpunit->field_agreservations_unittype[$lang][0]['nid'];
     
      if (variable_get('agres_createresmode', 'unit') == 'unit_type'){
        $lang_aut = 'und';
        $lang_aut = field_language('node', $resnode,'field_agr_unit_type'); 
        if((isset($resnode->field_agr_unit_type) && isset($resnode->field_agr_unit_type[$lang_aut][0]['nid']))) {
          $tmpunittype = $resnode->field_agr_unit_type[$lang_aut][0]['nid'];
           
        }     
      }
      if($package){
            
        if (($unitsinrespackage[$package->nid]['count']) > ($unittypesincart[$package->nid]['count'])){
            $unitsToBookAll[$package->nid][] = $tmpunit;
            if ($unitsinrespackage[$package->nid]['count']>0)
            $unitsinrespackage[$package->nid]['count'] -=1;         
        }              
      }else {
          
//          drupal_set_message('<pre>vvvvvv '.$unitsnumberperunittypeinres[$tmpunittype]['count'].'--'.$unittypesincart[$tmpunittype]['count'].'</pre>');
        if (($unitsnumberperunittypeinres[$tmpunittype]['count']) > ($unittypesincart[$tmpunittype]['count'])){
            $unitsToBookAll[$tmpunittype][] = $tmpunit;
            $unitsnumberperunittypeinres[$tmpunittype]['count'] -=1;
        }else{
          
        }          
      } 
    }
//    drupal_set_message('<pre>DOWNGRADINGS'.print_r($unitsToBookAll,true).'</pre>');
    foreach ($unitsToBookAll as $kutba => $unitsToBook) {
      $tmpunittype2 = node_load($kutba);
      
      // Should be only one
      $lang = 'und';
      $lang = field_language('node', $tmpunittype2,'field_agres_ref_category');       
      $tmpunittype2->field_agres_ref_category;
      
      if (module_exists('agres_categories')) {
        $tmpcat = node_load($tmpunittype2->field_agres_ref_category[$lang][0]['nid']);
        if (isset($puserrequest['catnid'])){
            $tmpcat = node_load($puserrequest['catnid']);
        }
        $lang = 'und';
        $lang = field_language('node', $tmpcat,'field_agres_bookingmode');           
        $bookmode = $tmpcat->field_agres_bookingmode[$lang][0]['value'];
        $lang = field_language('node', $tmpcat,'field_agres_measuringunit'); 
        $measureingunit = $tmpcat->field_agres_measuringunit[$lang][0]['value'];
      } else {
        $bookmode = 2;
        $measureingunit = t('nights');
      }
//      if ($bookmode == BOOKING_MODE_BY_DAYS) {
//        $times = $tmpcheckin->difference($tmpcheckout, 'days');
//      } elseif (($bookmode == BOOKING_MODE_BY_HOURS)||($bookmode == BOOKING_MODE_PICKUP_PLACE)) {
//        $times = ceil($tmpcheckin->difference($tmpcheckout, 'hours'));
//      } 
        if ($bookmode == BOOKING_MODE_BY_DAYS) {

          $times = $tmpcheckin->difference($tmpcheckout, 'days');
          $agres_singletimes = _agreservations_create_date_range(date_format($tmpcheckin, 'Y-m-d H:i:s'), date_format($tmpcheckout, 'Y-m-d H:i:s'));
          
        } elseif (($bookmode == BOOKING_MODE_BY_HOURS)||($bookmode == BOOKING_MODE_PICKUP_PLACE)) {
//          $times = ceil($tmpcheckin->difference($tmpcheckout, 'hours'));
          $agres_singletimes = _agreservations_create_datehour_range(date_format($tmpcheckin, 'Y-m-d H:i:s'), date_format($tmpcheckout, 'Y-m-d H:i:s'));
          $times = count($agres_singletimes);
        }  elseif ($bookmode == BOOKING_MODE_PACKAGE) {
            $times = 1;
            //@TODO: implement package booking:
//            $agres_singletimes
        }      
      $agres_singletimes = _agreservations_create_date_range($tmpcheckin->format('Y-m-d H:i:s'), $tmpcheckout->format('Y-m-d H:i:s'));
      $lang = 'und';
      $lang = field_language('node', $tmpcat,'field_agres_count_last_dh');        
      if (!isset($tmpcat->field_agres_count_last_dh[$lang]) || ($tmpcat->field_agres_count_last_dh[$lang][0]['value'] == 2)) {
         array_pop($agres_singletimes); //!!!
      }

//****************HANDLE UP AND DOWNGRADINGS in the BOOKINGMODES 3 and 4**********************************************
//********************************************************************************************************************
     if (isset($_SESSION['agreservationuserrequest']['updowngrade'])){
         if (isset($_SESSION['agreservationuserrequest']['updowngrade']['mode'])) {
                    switch ($_SESSION['agreservationuserrequest']['updowngrade']['mode']) {
                        case '3':
                             
                            if($_SESSION['agreservationuserrequest']['updowngrade']['updown']==1){
                                //upgrade package
                                //get price from previous:
                                $prevpack = node_load($_SESSION['agreservationuserrequest']['updowngrade']['prodoldnid']);
//                                drupal_set_message('<pre>DOWNGRADINGS'.print_r($prevpack,true).'</pre>');
                                $alteredprice = $prevpack->price;
                            }elseif($_SESSION['agreservationuserrequest']['updowngrade']['updown']==-1){
                                //downgrade package
                                $currentpack = node_load($_SESSION['agreservationuserrequest']['updowngrade']['prodnewnid']);
//                                drupal_set_message('<pre>DOWNGRADINGS'.print_r($prevpack,true).'</pre>');
                                $alteredprice = $currentpack->price-($currentpack->price*variable_get('agres_uc_item_downgrade_discount', '0.1'));                                
                            }elseif($_SESSION['agreservationuserrequest']['updowngrade']['updown']==0){
                                //downgrade package
                                $currentpack = node_load($_SESSION['agreservationuserrequest']['updowngrade']['prodnewnid']);
//                                drupal_set_message('<pre>DOWNGRADINGS'.print_r($prevpack,true).'</pre>');
                                $alteredprice = $currentpack->price;//-($currentpack->price*variable_get('agres_uc_item_downgrade_discount', '0.1'));                                
                            }
                           break;
                        case '4':
                            if($_SESSION['agreservationuserrequest']['updowngrade']['updown']==1){
                                //upgrade unittype
                                $prevprod = node_load($_SESSION['agreservationuserrequest']['updowngrade']['prodoldnid']);
//                                drupal_set_message('<pre>DOWNGRADINGS'.print_r($prevpack,true).'</pre>');
                                $alteredprice = $prevprod->price;                                
                            }elseif($_SESSION['agreservationuserrequest']['updowngrade']['updown']==-1){
                                //downgrade unittype
                                $currentprod = node_load($_SESSION['agreservationuserrequest']['updowngrade']['prodnewnid']);
//                                drupal_set_message('<pre>DOWNGRADINGS'.print_r($prevpack,true).'</pre>');
                                $alteredprice = $currentprod->price-($currentprod->price*variable_get('agres_uc_item_downgrade_discount', '0.1'));                                 
                           
                            }elseif($_SESSION['agreservationuserrequest']['updowngrade']['updown']==0){
                                //downgrade unittype
                                $currentprod = node_load($_SESSION['agreservationuserrequest']['updowngrade']['prodnewnid']);
//                                drupal_set_message('<pre>DOWNGRADINGS'.print_r($prevpack,true).'</pre>');
                                $alteredprice = $currentprod->price;//-($currentprod->price*variable_get('agres_uc_item_downgrade_discount', '0.1'));                                 
                            }                            
                            break;
                    }
                }
          
           
     }
//     $_SESSION['agreservationuserrequest']['updowngrade']=array('mode'=>4,
//        'prodoldnid'=>$_SESSION['agreservationuserrequest']['selectedunittypenid'],
//        'prodnewnid'=>$_SESSION['agreservationuserrequest']['selectedunittypenid'],'updown'=>0);   
//      
 
//      
//      if (isset($_SESSION['agreservationuserrequest']['updowngrade'])){
//          if ($_SESSION['agreservationuserrequest']['updowngrade']==0){
//              
//          }
//          if ($_SESSION['agreservationuserrequest']['updowngrade']==-1){
//              //downgrade => use discount on new product
//              $prevproduct = node_load($_SESSION['agreservationuserrequest']['prev_upgrade_prodnid']);
//              drupal_set_message('<pre>$prevproduct$prevproduct'.print_r($prevproduct,true).'</pre>');
////            $alteredprice = 33;
//          }
//          if ($_SESSION['agreservationuserrequest']['updowngrade']==1){
//              //upgrade => use price of original selected cheaper product
//              if (isset($_SESSION['agreservationuserrequest']['prev_upgrade_prodnid'])){
//                  $prevproduct = node_load($_SESSION['agreservationuserrequest']['prev_upgrade_prodnid']);
////                  drupal_set_message('<pre>$prevproduct$prevproduct'.print_r($prevproduct,true).'</pre>');
//                  $alteredprice = 33;
//              }         
//          }          
//      }
//////////////////////*********************************************************************************************************
/////////////*******************************************************************************************************************
     $units_of_cartitem = array();
     if ($package){
         $units_of_cartitem = _agres_package_get_units($package);
     }else{
         $units_of_cartitem = $unitsToBook;
     }
      $data = array(          
        'agres' => array('agreservations_request' => ''),
        'agres_category_nid'=>$tmpcat->nid,
        'agreservations_resid' => $resnid,          
        'units_of_cartitem' => $units_of_cartitem,  
        'module' => 'agres_categories',
        'times' => $times,
        'agres_singletimes' => $agres_singletimes,
        'agres_diffproducts' => '',
        'measuringunit' => $measureingunit,
        'bookingmode' => $bookmode,
        'checkintime' => $tmpcheckin->format('Y-m-d H:i:s'),
        'checkouttime' => $tmpcheckout->format('Y-m-d H:i:s'),
        'alteredprice' =>   $alteredprice
      );
     
      $_SESSION['agres_bookings_checkintime'] = $tmpcheckin->format(variable_get('date_format_short', 'Y-m-d H:i:s'));
      $_SESSION['agres_bookings_checkouttime'] = $tmpcheckout->format(variable_get('date_format_short', 'Y-m-d H:i:s'));
      $_SESSION['agres_bookings_times'] = $times;
      $_SESSION['agres_bookings_measuringunit'] = $measureingunit;
            
      foreach ($unitsToBook as $unittobook) {
      $lang = 'und';
      $lang = field_language('node', $unittobook,'field_agreservations_unittype');          
        $unittyporrateesums[$unittobook->field_agreservations_unittype[$lang][0]['nid']][] = $unittobook->nid;
      }
       if (variable_get('agres_createresmode', 'unit') == 'unit_type'){        
        $lang_aut = 'und';
        $lang_aut = field_language('node', $resnode,'field_agr_unit_type'); 
        if((isset($resnode->field_agr_unit_type) && isset($resnode->field_agr_unit_type[$lang_aut][0]['nid']))) {
          $unittyporrateesums = array(); //empty array;
          foreach ($unitsToBook as $unittobook) {
             $lang = 'und';
             $lang = field_language('node', $unittobook,'field_agreservations_unittype');          
             $unittyporrateesums[$resnode->field_agr_unit_type[$lang_aut][0]['nid']][] = $unittobook->nid;
           }      
        }     
      }
      
      foreach ($unittyporrateesums as $key => $unittyporrateesum) {
        $unittyporrateesums[$key] = count($unittyporrateesum);
      }
      foreach ($unitsToBook as $unittobook) {
        // Rates are activated
        if (module_exists('agres_rate')) {
          $lang = 'und';
          $lang = field_language('node', $unittobook,'field_agreservations_unittype');           
          $ratesntypes = _agres_get_products_for_reservation($unittobook->field_agreservations_unittype[$lang][0]['nid'], $data);
 
       if (variable_get('agres_createresmode', 'unit') == 'unit_type'){        
        $lang_aut = 'und';
        $lang_aut = field_language('node', $resnode,'field_agr_unit_type'); 
        if((isset($resnode->field_agr_unit_type) && isset($resnode->field_agr_unit_type[$lang_aut][0]['nid']))) {
            
             $lang = 'und';
             $lang = field_language('node', $unittobook,'field_agreservations_unittype');    
             $ratesntypes = _agres_get_products_for_reservation($resnode->field_agr_unit_type[$lang_aut][0]['nid'], $data);
       
              
        }     
      }          
          
          
          
          $ratesntypessums = array_count_values($ratesntypes);
          foreach ($ratesntypessums as $rot => $rateortypesum) {
            $data['times'] = $rateortypesum;
            $data['agres_singletimes'] = array_keys($ratesntypes, $rot);
            $data['agres_diffproducts'] = $data['times'] / (count($data['agres_singletimes']));
          if(module_exists('agres_enable_attributes')&&(module_exists('uc_attribute'))) {
            _agres_enable_attributes_set_attributes($data,$form_state);
          }  
          $tmpdata = $data;
         $data+= module_invoke_all('uc_add_to_cart_data', $tmpdata);
            if(isset($puserrequest['packagenid'])){
//                drupal_set_message('<pre>addtocarttttt****'.print_r($data,TRUE).'</pre>');
                uc_cart_add_item($puserrequest['packagenid'], $rateortypesum,$data, $uid);
            }else{
//                drupal_set_message('<pre>_agres_bookings_reserve_and_fillcart****'.print_r($rot,TRUE).'</pre>');
               uc_cart_add_item($rot, $rateortypesum,$data, $uid);
            }
//             drupal_set_message('<pre>_agres_bookings_reserve_and_fillcart****'.print_r($data,TRUE).'</pre>');
          }
        } else {
          //else also wenn kien rates modul aktiv ist:
          $lang = 'und';
          $lang = field_language('node', $unittobook,'field_agreservations_unittype');             
          $data['times'] = $times * $unittyporrateesums[$unittobook->field_agreservations_unittype[$lang][0]['nid']];

       if (variable_get('agres_createresmode', 'unit') == 'unit_type'){        
        $lang_aut = 'und';
        $lang_aut = field_language('node', $resnode,'field_agr_unit_type'); 
        if((isset($resnode->field_agr_unit_type) && isset($resnode->field_agr_unit_type[$lang_aut][0]['nid']))) {
            
             $lang = 'und';
             $lang = field_language('node', $unittobook,'field_agreservations_unittype');    
             $data['times'] = $times * $unittyporrateesums[$resnode->field_agr_unit_type[$lang_aut][0]['nid']];
           
       
              
        }     
      }           
          
          
          if(module_exists('agres_enable_attributes')&&(module_exists('uc_attribute'))) {
            _agres_enable_attributes_set_attributes($data,$form_state);
          }
          $tmpdata = $data;
          $data+= module_invoke_all('uc_add_to_cart_data', $tmpdata);
          $unittype_from_reservation = false;
       if (variable_get('agres_createresmode', 'unit') == 'unit_type'){        
        $lang_aut = 'und';
        $lang_aut = field_language('node', $resnode,'field_agr_unit_type'); 
        if((isset($resnode->field_agr_unit_type) && isset($resnode->field_agr_unit_type[$lang_aut][0]['nid']))) {
            
          $unittype_from_reservation = true;
           
       
              
        }     
      } 
//      drupal_set_message('<pre>addtocarttttt**222**'.print_r($unittype_from_reservation,TRUE).'</pre>');
          if ($unittype_from_reservation) {
            $lang_aut = field_language('node', $resnode,'field_agr_unit_type'); 
            uc_cart_add_item($resnode->field_agr_unit_type[$lang_aut][0]['nid'], 1 * $times, $data , $uid); //*$nights
          } else {
            uc_cart_add_item($unittobook->field_agreservations_unittype[$lang][0]['nid'], 1 * $times, $data , $uid); //*$nights
          }
          
        }
        
      }
    }
    drupal_set_message(t('items added to cart of user.'));
    return;
  }
  /////////////////////////////////////
  //There is no existent reservation://
  /////////////////////////////////////
  else {
    if (count($puserrequest) > 0 and $categorynid > 0) {
      $category = node_load($categorynid);
      $userrequest = $puserrequest;
      $lang = 'und';
      $lang = field_language('node', $category,'field_agres_titleresform'); 
      if (!isset($category->field_agres_titleresform[$lang])) {
        $langcode = language_default('language');
        if (!isset($category->field_agres_titleresform[$lang])) {
          $langcode = 'und';
        }
      }
      $agreservations_request = array(
        '',
        array(
          $userrequest['checkintime'],
          $userrequest['checkouttime'],
        ),
      );
      $productnid = 0;
      if (intval($pselectunittype) > 0) {
        $productnid = $pselectunittype;
      } else {
        if (isset($userrequest['preselectedunit'])) {
          $productnid = $userrequest['preselectedunit'];
        }
      }
      $tmpprodnode = null;
      if ($productnid > 0) {
        $tmpprodnode = node_load($productnid);
      }
      //if the $tmpprodnode( the product which is only set in 1 item buys) is set and it is a rate or unit type then proceed, or $tmpprodnode is still null):
      if ((isset($tmpprodnode) && (($tmpprodnode->type == 'agres_rate') || ($tmpprodnode->type == 'agreservations_unittype')||($tmpprodnode->type == 'agres_service'))) || ($productnid == 0)) {
        if (count($userrequestunit) > 0) {
          
        } else {
          $userrequestunit[]['selectunittype'] = $productnid;
        }
        $unitsToBook = array();
        if (isset($tmpprodnode)&&($tmpprodnode->type <> 'agres_service')||(!isset($tmpprodnode))) {
          $unitsToBook = _agreservations_find_units_for_user_request($userrequestunit, $userrequest['checkintime'], $userrequest['checkouttime'], $category);
        }else{
          $unitsToBook = false;
        }
        if (isset($category)) {
          $lang = 'und';
          $lang = field_language('node', $category,'field_agres_bookingmode');           
          $bookmode = $category->field_agres_bookingmode[$lang][0]['value'];
          $lang = field_language('node', $category,'field_agres_measuringunit'); 
          $measureingunit = $category->field_agres_measuringunit[$lang][0]['value'];
        }
        $tmpcheckin = new DateObject($userrequest['checkintime']);
        $tmpcheckout = new DateObject($userrequest['checkouttime']);
//        drupal_set_message('<pre>----___'.print_r($bookmode,true).'</pre>');
        
        if ($bookmode == BOOKING_MODE_BY_DAYS) {
          $times = $tmpcheckin->difference($tmpcheckout, 'days');
          $agres_singletimes = _agreservations_create_date_range(date_format($tmpcheckin, 'Y-m-d H:i:s'), date_format($tmpcheckout, 'Y-m-d H:i:s'));
        } elseif (($bookmode == BOOKING_MODE_BY_HOURS)||($bookmode == BOOKING_MODE_PICKUP_PLACE)) {
          $times = ceil($tmpcheckin->difference($tmpcheckout, 'hours'));
          $agres_singletimes = _agreservations_create_datehour_range(date_format($tmpcheckin, 'Y-m-d H:i:s'), date_format($tmpcheckout, 'Y-m-d H:i:s'));
        }  elseif ($bookmode == BOOKING_MODE_PACKAGE) {
            //@TODO: implement package booking:
//            $agres_singletimes
        }
        
        $lang = 'und';
        if (isset($category)) {
           $lang = 'und';
           $lang = field_language('node', $category,'field_agres_count_last_dh');
        }
        if (!isset($category->field_agres_count_last_dh[$lang])||($category->field_agres_count_last_dh[$lang][0]['value']==2)) {
           array_pop($agres_singletimes); //!!!        
        }             
        $times = count($agres_singletimes);        
        if (!$unitsToBook) {
          if (isset($tmpprodnode)&&($tmpprodnode->type <> 'agres_service')||(!isset($tmpprodnode))) {
          form_set_error('unitinfo', t('Booking not possible anymore. Not enough free units, try another selection please.'));

            $node = node_load($productnid);
            return;            
          } else {//this is a service product, add to cart according to unittype
            $data = array(
              'agres' => array('agreservations_request' => $agreservations_request),              
              'agreservations_resid' => $resnid,
              'unitsbooked' => $unitsToBook,    
              'module' => 'agres_categories',
              'times' => $times,
              'shippable' => false,
              'agres_singletimes' => $agres_singletimes,
              'measuringunit' => $measureingunit,
              'bookingmode' => $bookmode,
              'checkintime' => date_format($tmpcheckin, 'Y-m-d H:i:s'),
              'checkouttime' => date_format($tmpcheckout, 'Y-m-d H:i:s'),
              'agres_category_nid' => $categorynid,
            );            
             uc_cart_add_item($tmpprodnode->nid, $times, $data); //*$nights$productnid
            return;
          }

        } else {
          $_SESSION['agres_res_info'] = '';
          unset($_SESSION['agres_res_info']);
          $resnid = NULL;
          $resnid = 0;
          // Check if there are already items in the cart!
          $items = uc_cart_get_contents(uc_cart_get_id());
        
          if (count($items) > 0) {
            reset($items);
            $firstitem = current($items);
            //check if item in cart has same booking date as new item:
            if (isset($firstitem->data['agreservations_resid'])) {
              $resnid = $firstitem->data['agreservations_resid'];
              $resnid = _agreservations_update_Reservation($resnid, $unitsToBook, $userrequest['checkintime'], $userrequest['checkouttime'], NULL, NULL, AGRES_STATUS_ONLINE_NO_ORDER_YET);              
            } else {
              $resnid = _agreservations_create_Reservation($unitsToBook, $userrequest['checkintime'], $userrequest['checkouttime'], NULL, NULL, AGRES_STATUS_ONLINE_NO_ORDER_YET, t('Reservation'),1);              
            }
          } else {
            $resnid = _agreservations_create_Reservation($unitsToBook, $userrequest['checkintime'], $userrequest['checkouttime'], NULL, NULL, AGRES_STATUS_ONLINE_NO_ORDER_YET, t('Reservation'),1);

          }
          if ($resnid > 0) {
            $times = 0;
            $bookmode = BOOKING_MODE_BY_DAYS;
            $measureingunit = t('night');
            $lang = 'und';
            if (isset($category)) {
              $lang = 'und';
              $lang = field_language('node', $category,'field_agres_bookingmode');              
              $bookmode = $category->field_agres_bookingmode[$lang][0]['value'];
              $lang = field_language('node', $category,'field_agres_measuringunit'); 
              $measureingunit = $category->field_agres_measuringunit[$lang][0]['value'];
              $lang = field_language('node', $category,'field_agres_count_last_dh');
            }
            $agres_singletimes = array();
            if ($bookmode == BOOKING_MODE_BY_DAYS) {
              $times = $tmpcheckin->difference($tmpcheckout, 'days');
              $agres_singletimes = _agreservations_create_date_range(date_format($tmpcheckin, 'Y-m-d H:i:s'), date_format($tmpcheckout, 'Y-m-d H:i:s'));
            } elseif ($bookmode == BOOKING_MODE_BY_HOURS) {
              $times = ceil($tmpcheckin->difference($tmpcheckout, 'hours'));

              $agres_singletimes = _agreservations_create_datehour_range(date_format($tmpcheckin, 'Y-m-d H:i:s'), date_format($tmpcheckout, 'Y-m-d H:i:s'));
            }
            
      if (!isset($category->field_agres_count_last_dh[$lang])||($category->field_agres_count_last_dh[$lang][0]['value']==2)) {
        array_pop($agres_singletimes); //!!!        
      }         
           $times = count($agres_singletimes);
            $data = array(
              'agres' => array('agreservations_request' => $agreservations_request),              
              'agreservations_resid' => $resnid,
              'unitsbooked' => $unitsToBook,    
              'module' => 'agres_categories',
              'times' => $times,
              'shippable' => false,
              'agres_singletimes' => $agres_singletimes,
              'measuringunit' => $measureingunit,
              'bookingmode' => $bookmode,
              'checkintime' => date_format($tmpcheckin, 'Y-m-d H:i:s'),
              'checkouttime' => date_format($tmpcheckout, 'Y-m-d H:i:s'),
              'agres_category_nid' => $categorynid,
            );

            foreach ($unitsToBook as $unittobook) {
             $lang = 'und';
             $lang = field_language('node', $unittobook,'field_agreservations_unittype');                  
              $unittyporrateesums[$unittobook->field_agreservations_unittype[$lang][0]['nid']][] = $unittobook->nid;
            }
            foreach ($unittyporrateesums as $key => $unittyporrateesum) {
              $unittyporrateesums[$key] = count($unittyporrateesum);
            }
            foreach ($unitsToBook as $unittobook) {
              if (module_exists('agres_rate')) {
//                
      if (!isset($category->field_agres_count_last_dh[$lang])||$category->field_agres_count_last_dh[$lang][0]['value']==2) {
         $lang = 'und';
         $lang = field_language('node', $unittobook,'field_agreservations_unittype');          
         $ratesntypes = _agres_get_products_for_reservation($unittobook->field_agreservations_unittype[$lang][0]['nid'],$data, true);
      } 
         $lang = 'und';
         $lang = field_language('node', $category,'field_agres_count_last_dh');       
      if (isset($category->field_agres_count_last_dh[$lang])&&$category->field_agres_count_last_dh[$lang][0]['value']==1) {
         $lang = 'und';
         $lang = field_language('node', $unittobook,'field_agreservations_unittype');        
         $ratesntypes = _agres_get_products_for_reservation($unittobook->field_agreservations_unittype[$lang][0]['nid'], $data,false);
      }       
//                $ratesntypes = _agres_get_products_for_reservation($unittobook->field_agreservations_unittype[$unittobook->language][0]['nid'], $data);
                   $lang = 'und';
                   $lang = field_language('node', $unittobook,'field_agreservations_unittype');     
                $ratesntypessums = array_count_values($ratesntypes);
                foreach ($ratesntypes as $rot => $rateortype) {
              
                  $data['times'] = $ratesntypessums[$rateortype] * $unittyporrateesums[$unittobook->field_agreservations_unittype[$lang][0]['nid']];
                  $data['agres_singletimes'] = array_keys($ratesntypes, $rateortype);
                  $data['agres_diffproducts'] = $data['times'] / (count($data['agres_singletimes']));
                  if(module_exists('agres_enable_attributes')&&(module_exists('uc_attribute'))) {
                    _agres_enable_attributes_set_attributes($data,$form_state);
                  }
                     uc_cart_add_item($rateortype, 1, $data);
                }//uc_cart_add_item($rot, $rateortypesum, module_invoke_all('uc_add_to_cart_data', $data), $uid);
              } else {
                $data['times'] = $times * count($unittyporrateesums[$unittobook->field_agreservations_unittype[$lang][0]['nid']]);
                $data['agres_diffproducts'] = $data['times'] / (count($data['agres_singletimes']));
               if(module_exists('agres_enable_attributes')&&(module_exists('uc_attribute'))) {
                    _agres_enable_attributes_set_attributes($data,$form_state);
               }
                uc_cart_add_item($unittobook->field_agreservations_unittype[$lang][0]['nid'], $unittyporrateesums[$unittobook->field_agreservations_unittype[$lang][0]['nid']] * $times, $data); //*$nights
              }
            }
          }
        }
      } else {
        $data = array('agres' => array('agreservations_request' => $agreservations_request),
          'agreservations_resid' => $resnid,
          'module' => 'agres_categories',
          'times' => 1,
          'agr_nottimebased' => 1,
////         'agr_lasttimefree' => $agr_lasttimefree,
////         'agr_altprice' => $agr_altprice,
          'agres_singletimes' => 1,
//           'measuringunit' => $measureingunit,
//           'bookingmode' => $bookmode,
//           'checkintime' => date_format($tmpcheckin, variable_get('date_format_short', 'Y-m-d H:i:s')),
//           'checkouttime' => date_format($tmpcheckout, variable_get('date_format_short', 'Y-m-d H:i:s')));  
        );
        if(module_exists('agres_enable_attributes')&&(module_exists('uc_attribute'))) {
           _agres_enable_attributes_set_attributes($data,$form_state);
        }
        uc_cart_add_item($productnid, 1, $data); //*$nights$productnid
      }
      drupal_set_message(t('items added to cart of user.'));
      if ($goto <> '') {
        drupal_goto($goto);
      }
      return;
    }
  }
     }
     //_searchwidget_form
     static function _agr_searchwidget_form($form_state, $args){
//       

    $cat = $args['build_info']['args'][0];
//    drupal_set_message('<pre>_agr_searchwidget_form_agr_searchwidget_formcategorie::::'.print_r($cat,true).'</pre>');
    $lang = 'und';
    $lang = field_language('node', $cat, 'field_agres_datelabel1');
    $datform_default = date_default_format('date_popup');
    $datform = str_replace(':s', '', $datform_default);
    $datform = 'Y-m-d';
//  $datform = str_replace('H:i','', $datform);
//  $datform = str_replace('H:i:s','', $datform);
//  $datform .= ' H:i';
    $langbm = 'und';
    $langbm = field_language('node', $cat, 'field_agres_bookingmode');

    if (module_exists('agres_package') && $cat->field_agres_bookingmode[$langbm][0]['value'] == '3') {
        $pickuppoints = _agres_getpickup_options();
        $dropoffpoints = _agres_getdropoff_options();
        $form['unitsearch']['pickup' . $cat->nid]['pickuppoint'] = array(
           '#prefix' => '<div class="agrplacesselect">',
            '#type' => 'select',
            '#title' => t('Pickup Place'), //$category->title . ' ' . t('count'), //t('Units'),
            '#default_value' => reset($pickuppoints),
            '#options' => $pickuppoints,
            '#weight' => 125,
               '#suffix' => '</div>',
        );
        $form['unitsearch']['dropoff' . $cat->nid]['dropoffpoint'] = array(
            '#prefix' => '<div class="agrplacesselect">',
            '#type' => 'select',
            '#title' => t('Destination'), //$category->title . ' ' . t('count'), //t('Units'),
            '#default_value' => reset($dropoffpoints),
            '#options' => $dropoffpoints,
            //      '#suffix' => '</div>',
            '#weight' => 125,
               '#suffix' => '</div>',
        );
//       drupal_set_message('<pre>categorie::::'.print_r($dropoffpoints,true).'</pre>');
    }
    $form['unitsearch']['checkin' . $cat->nid] = array(
//  '#prefix' => '<div>',
//  '#type' => 'date_popup',
        '#type' => 'date_popup',
//  '#datepicker_options' => array(
//    'showOn' => 'button',
//    'buttonImage' => base_path() . path_to_theme('my_theme') . '/images/icon/calendar.png',
//    'buttonImageOnly' => false,
//  ),      
//  '#theme' => 'table',
        '#title' => $cat->field_agres_datelabel1[$lang][0]['safe_value'],
        '#required' => TRUE,
        '#size' => 13,
        '#date_type' => 'datetime',
        '#date_timezone' => date_default_timezone(), //Y-m-d H:i
        '#date_format' => $datform,
        '#default_value' => '',
        '#date_year_range' => '-0:+1',
//  '#suffix' => '</div>',
        '#weight' => 100,
    );
    if ($cat->field_agres_bookingmode[$langbm][0]['value'] == '4') {
        
//        $pickuppoints = _agres_getplaces_options();
          $pickuppoints = array('22'=>'Bangkok Area and Hotels');
//        drupal_set_message('<pre>categorie:bbb::'.print_r($pickuppoints,true).'</pre>');
        $form['unitsearch']['pickup' . $cat->nid]['pickuppoint'] = array(
            //      '#prefix' => '<div>',
            '#prefix' => '<div class="agrplacesselect">',
            '#type' => 'select',
//            '#size' => 2,
            '#title' => t('Pickup Place'), //$category->title . ' ' . t('count'), //t('Units'),
            '#default_value' => reset($pickuppoints),
            '#options' => $pickuppoints,
            //      '#suffix' => '</div>',
            '#weight' => 125,
             '#suffix' => '</div>',
        );  
    $timeoptions = _agres_categories_create_options_servicehours(0, $cat);
    $lang = 'und';
    $lang = field_language('node', $cat, 'field_agres_showtime');
        if (($cat->field_agres_showtime[$lang][0]['value'] == 1) || ($cat->field_agres_showtime[$lang][0]['value'] == 2)) {

    //      drupal_set_message('<pre>categorie::::'.print_r($cat->nid,true).'</pre>');
            $form['unitsearch']['checkin' . $cat->nid]['checkintime'] = array(
    //      '#prefix' => '<div>',
                '#type' => 'select',
                '#title' => t('from'), //$category->title . ' ' . t('count'), //t('Units'),
                '#default_value' => reset($timeoptions),
                '#options' => $timeoptions,
    //      '#suffix' => '</div>',
                '#weight' => 150,
            );
    //    $datform .= ' H:i';
        }    
        $form['unitsearch']['duration' . $cat->nid] = array(
            //      '#prefix' => '<div>',
            '#type' => 'select',
            '#title' => t('Duration'), //$category->title . ' ' . t('count'), //t('Units'),
            '#default_value' => '3 hours',//reset($timeoptions1),
            '#options' => array(
                '3 hours' => t('3 hours'),
                '4 hours' => t('4 hours'),
                '5 hours' => t('5 hours'),
                '6 hours' => t('6 hours'),
                '7 hours' => t('7 hours'),
                '8 hours' => t('8 hours'),
                '9 hours' => t('9 hours'),
                '10 hours' => t('10 hours'),
                '11 hours' => t('11 hours'),
                '12 hours' => t('12 hours'),
                '13 hours' => t('13 hours'),
                '14 hours' => t('14 hours'),
                '15 hours' => t('15 hours'),
                '16 hours' => t('16 hours'),
                '17 hours' => t('17 hours'),
                '18 hours' => t('18 hours'),
                '19 hours' => t('19 hours'),
                '20 hours' => t('20 hours'),
                '21 hours' => t('21 hours'),
                '22 hours' => t('22 hours'),
                '23 hours' => t('23 hours'),
                '24 hours' => t('24 hours'),
            ),
            //      '#suffix' => '</div>',
            '#weight' => 200,
        );
//        $timeoptions1 = _agres_categories_create_options_servicehours(0, $cat);
//        $form['unitsearch']['checkin' . $cat->nid]['checkouttime'] = array(
//            //      '#prefix' => '<div>',
//            '#type' => 'select',
//            '#title' => t('to'), //$category->title . ' ' . t('count'), //t('Units'),
//            '#default_value' => reset($timeoptions1),
//            '#options' => $timeoptions1,
//            //      '#suffix' => '</div>',
//            '#weight' => 200,
//        );
        $datform .= ' H:i';    
    } else {

    $timeoptions = _agres_categories_create_options_servicehours(0, $cat);
    $lang = 'und';
    $lang = field_language('node', $cat, 'field_agres_showtime');
    if (($cat->field_agres_showtime[$lang][0]['value'] == 1) || ($cat->field_agres_showtime[$lang][0]['value'] == 2)) {

//      drupal_set_message('<pre>categorie::::'.print_r($cat->nid,true).'</pre>');
        $form['unitsearch']['checkin' . $cat->nid]['checkintime'] = array(
//      '#prefix' => '<div>',
            '#type' => 'select',
            '#title' => 'time', //$category->title . ' ' . t('count'), //t('Units'),
            '#default_value' => reset($timeoptions),
            '#options' => $timeoptions,
//      '#suffix' => '</div>',
            '#weight' => 150,
        );
//    $datform .= ' H:i';
    }
    $lang = 'und';
    $lang = field_language('node', $cat, 'field_agres_datelabel2');

    $timeoptions1 = _agres_categories_create_options_servicehours(0, $cat);
    $lang = 'und';
    $lang = field_language('node', $cat, 'field_agres_showtime');
    if (isset($cat->field_agres_datelabel2[$lang][0]['safe_value'])) {
        $form['unitsearch']['checkout' . $cat->nid] = array(
//      '#prefix' => '<div>',
            '#type' => 'date_popup',
            '#title' => $cat->field_agres_datelabel2[$lang][0]['safe_value'],
            //      '#default_value' =>
            '#required' => TRUE,
            '#size' => 13,
            '#date_type' => 'datetime',
            '#date_timezone' => date_default_timezone(),
            '#date_format' => $datform,
            '#default_value' => '',
            '#date_year_range' => '-0:+1',
//      '#suffix' => '</div>',
            '#weight' => 200,
        );
        if ($cat->field_agres_showtime[$lang][0]['value'] > 0) {
            //
            $form['unitsearch']['checkout' . $cat->nid]['checkouttime'] = array(
                //      '#prefix' => '<div>',
                '#type' => 'select',
                '#title' => 'time', //$category->title . ' ' . t('count'), //t('Units'),
                '#default_value' => reset($timeoptions1),
                '#options' => $timeoptions1,
                //      '#suffix' => '</div>',
                '#weight' => 250,
            );
            $datform .= ' H:i';
        }
    } elseif (($cat->field_agres_showtime[$lang][0]['value'] == 3) || ($cat->field_agres_showtime[$lang][0]['value'] == 1)) {
        $form['unitsearch']['checkin' . $cat->nid]['checkouttime'] = array(
            //      '#prefix' => '<div>',
            '#type' => 'select',
            '#title' => 'time', //$category->title . ' ' . t('count'), //t('Units'),
            '#default_value' => reset($timeoptions1),
            '#options' => $timeoptions1,
            //      '#suffix' => '</div>',
            '#weight' => 200,
        );
        $datform .= ' H:i';
    }


    $langnu = 'und';
    $langnu = field_language('node', $cat, 'field_agres_shownumberunits');
    if ($cat->field_agres_shownumberunits[$lang][0]['value'] == 1) {
        $lang = 'und';
        $lang = field_language('node', $cat, 'field_agres_unitslabel');
        if (isset($cat->field_agres_unitslabel[$lang])) {
            $title = $cat->field_agres_unitslabel[$lang][0]['safe_value'];
        } else {
            $title = t('units');
        }
        $lang = 'und';
        $lang = field_language('node', $cat, 'field_agres_numberunits');
        
        $form['unitsearch']['units'] = array(
//      '#prefix' => '<div>',
            '#type' => 'select',
            '#title' => $title, //$category->title . ' ' . t('count'), //t('Units'),
            '#default_value' => $cat->field_agres_numberunits[$langnu][0]['value'],
            '#options' => array(
                1 => 1,
                2 => 2,
                3 => 3,
                4 => 4,
                5 => 5,
                6 => 6,
                7 => 7,
                8 => 8,
                9 => 9,
                10 => 10,
            ),
//      '#suffix' => '</div>',
            '#weight' => 300,
        );
    }
       }//End Else bookingmode 4
    $form['unitsearch']['submit'] = array(
//    '#prefix' => '<div>',
        '#type' => 'submit',
        '#title' => 'Search',
        '#value' => t('Calculate Price'),
        // '#submit' => array('agres_categories_searchwidget_form_submit'),
//    '#suffix' => '</div>',
        '#weight' => 500,
    );

    return $form;
     }
    //_searchwidget_form_validate
     static function _agr_searchwidget_form_validate($form, &$form_state){
        if (module_exists('uc_cart')) {
            $items = uc_cart_get_contents(uc_cart_get_id());
            // Now delete the reservations. In case where not allowed to delete,
            // follow the suggestion posted here:http://drupal.org/node/218104
            foreach ($items as $productunit) {
                if (isset($productunit->data['agreservations_resid'])) {
                    if (intval($productunit->data['agreservations_resid']) > 0) {
                        global $user;
                        $original_user = $user;
                        drupal_save_session(FALSE);
                        $user = user_load(1);
                        node_delete(intval($productunit->data['agreservations_resid']));
                        // Restore original user
                        $user = $original_user;
                        drupal_save_session(TRUE);
                    }
                }
            }
            uc_cart_empty(uc_cart_get_id());
            if (isset($_SESSION['availableunittypes'])) {
                unset($_SESSION['availableunittypes']);
            }
            if (isset($_SESSION['agreservationuserrequest'])) {
                unset($_SESSION['agreservationuserrequest']);
            }
        }
//  drupal_set_message('<pre>agres_categories_searchwidget_form_validate::::'.print_r($form_state,true).'</pre>');
        $datform = 'Y-m-d H:i:s'; //:s
        if (isset($form_state['build_info']['args'][0])) {
            $cat = $form_state['build_info']['args'][0];
            $lang = 'und';
            $lang = field_language('node', $cat, 'field_agres_showtime');
            $langd = 'und';
            $langd = field_language('node', $cat, 'field_agres_datelabel1');


            if (!isset($form_state['values']['units'])) {

                $form_state['values']['units'] = 1;
            }
            $requestedunits = 1;
            $requestedunits = $form_state['values']['units'];

            if (!isset($form_state['input']['checkin' . $cat->nid]['date'])) {
                form_set_error('unitinfo', t('First Date has to be entered.'));
                return;
            }
            if (!isset($form_state['input']['checkin' . $cat->nid]['checkintime']) && ($cat->field_agres_showtime[$lang][0]['value'] == 1)) {
                form_set_error('unitinfo', t('Time for first Date has to be entered.'));
                return;
            }
            $form_state['values']['checkin' . $cat->nid] = $form_state['input']['checkin' . $cat->nid]['date'];
//    drupal_set_message('<pre>agres_categories_searchwidget_form_validate'.print_r($form_state['input']['checkin'.$cat->nid]['checkintime'],true).'</pre>');
            if (isset($form_state['input']['checkin' . $cat->nid]['checkintime'])) {
                $form_state['values']['checkin' . $cat->nid] .=' ' . $form_state['input']['checkin' . $cat->nid]['checkintime'];
            }
            $tmpDateCheckin = date_create($form_state['values']['checkin' . $cat->nid]);

            if (!isset($form_state['input']['checkout' . $cat->nid]['date'])) {
                if (isset($cat->field_agres_datelabel2[$lang][0]['safe_value'])) {
                    form_set_error('unitinfo', t('Second Date has to be entered.'));
                    return;
                } else {
                    if (!isset($form_state['input']['checkin' . $cat->nid]['date'])) {
                        form_set_error('unitinfo', t('Date has to be entered.'));
                        return;
                    } else {
                        $form_state['input']['checkout' . $cat->nid]['date'] = $form_state['input']['checkin' . $cat->nid]['date'];
                        if (isset($form_state['input']['checkin' . $cat->nid]['checkouttime'])) {
                            $form_state['input']['checkout' . $cat->nid]['checkouttime'] = $form_state['input']['checkin' . $cat->nid]['checkouttime'];
                        } elseif (isset($form_state['input']['duration' . $cat->nid])) {
                            $tmpDateCheckout = date_create($form_state['values']['checkin' . $cat->nid]);
                            $tmpDateCheckout->modify('+' . $form_state['input']['duration' . $cat->nid]);
                            $form_state['input']['checkout' . $cat->nid]['date'] = $tmpDateCheckout->format('Y-m-d');
                            $form_state['input']['checkout' . $cat->nid]['checkouttime'] = $tmpDateCheckout->format('H:i');
//                         drupal_set_message('<pre>___###'.print_r($tmpDateCheckout->format('H:i'),true).'</pre>');
//                        $form_state['input']['checkout' . $cat->nid]['checkouttime'] = $form_state['input']['checkin' . $cat->nid]['checkouttime'];
                        }
                    }
                }

//      drupal_set_message('<pre>zeittttt_ '.print_r($form_state['input'],true).'</pre>');
            }
            if (!isset($form_state['input']['checkout' . $cat->nid]['checkouttime']) && ($cat->field_agres_showtime[$lang][0]['value'] == 1)) {
                form_set_error('unitinfo', t('Time for second Date has to be entered.'));
                return;
            }
            $form_state['values']['checkout' . $cat->nid] = $form_state['input']['checkout' . $cat->nid]['date'];
            if ((isset($form_state['input']['checkin' . $cat->nid]['checkintime'])) && (isset($form_state['input']['checkout' . $cat->nid]['checkouttime']))) {
                $form_state['values']['checkout' . $cat->nid] .= ' ' . $form_state['input']['checkout' . $cat->nid]['checkouttime'];
            }
            $tmpDateCheckout = date_create($form_state['values']['checkout' . $cat->nid]);
            //days a reservation has to be in the future:
            $langdia = 'und';
            $langdia = field_language('node', $cat, 'field_agres_mindaysadvance');
            if (isset($cat->field_agres_mindaysadvance[$lang])) {
                $mindaysinadvance = $cat->field_agres_mindaysadvance[$lang][0]['value'];
                $tmptodayplus = date_create();
                date_modify($tmptodayplus, '+' . $mindaysinadvance . ' days');
                if (!is_a($tmpDateCheckin, 'DateTime')) {
//         drupal_set_message('<pre> allet nict juut '.print_r($mindaysinadvance,true).'</pre>');
                    form_set_error('unitinfo', t('Please enter valid dates only!') . $mindaysinadvance . t(' days in advance'));
                } else {
//         drupal_set_message('<pre> allet juut '.print_r($mindaysinadvance,true).'</pre>');
                    if ($tmptodayplus->format('Y-m-d') > $tmpDateCheckin->format('Y-m-d')) {
                        form_set_error('unitinfo', t('Checkin-time has to be at least ') . $mindaysinadvance . t(' days in advance'));
                    }
                }
            }
            $langsnu = 'und';
            $langsnu = field_language('node', $cat, 'field_agres_shownumberunits');
            $langnu = 'und';
            $langnu = field_language('node', $cat, 'field_agres_numberunits');
            if (($cat->field_agres_shownumberunits[$langsnu][0]['value'] !== '1') && (isset($cat->field_agres_numberunits[$langnu][0]['value']))) {
//      drupal_set_message('<pre>agresdddddddddd_categories_searchwidget_form_validate'.print_r($cat->field_agres_shownumberunits[$langsnu][0]['value'],true).'</pre>');
                $form_state['values']['units'] = $cat->field_agres_numberunits[$langnu][0]['value'];
            }

            if (!is_a($tmpDateCheckout, 'DateTime')) {
                form_set_error('unitinfo', t('Please enter valid dates only!') . $mindaysinadvance . t(' days in advance'));
            } else {
                //check restrictions if modules is enabled:
                if (module_exists('agres_restriction') && (variable_get('agr_checkglobalrestriction_swidget', 'yes') == 'yes')) {
                    $message = agres_timeframe_api('check_restrictions', array(
                        'start_date' => $form_state['values']['checkin' . $cat->nid],
                        'end_date' => $form_state['values']['checkout' . $cat->nid],
                    ));
                }
                $langdcit = 'und';
                $langdcit = field_language('node', $cat, 'field_agres_defaultcheckintime');
                $langdcot = 'und';
                $langdcot = field_language('node', $cat, 'field_agres_defaultcheckouttime');
                $langst = 'und';
                $langst = field_language('node', $cat, 'field_agres_showtime');
                if (($cat->field_agres_showtime[$langst][0]['value'] <> 1) && (isset($cat->field_agres_defaultcheckintime[$langdcit][0]['value']))) {
                    date_modify($tmpDateCheckin, $cat->field_agres_defaultcheckintime[$langdcit][0]['value']);
                    $form_state['values']['checkin' . $cat->nid] = $tmpDateCheckin->format($datform);
                    date_modify($tmpDateCheckout, $cat->field_agres_defaultcheckouttime[$langdcot][0]['value']);
                    $form_state['values']['checkout' . $cat->nid] = $tmpDateCheckout->format($datform);
                }

                /*                 * *******************check servicehours!****************************************************************** */

                $checkinisinrange = _agres_categories_check_servicehours($tmpDateCheckin, $cat);
                $checkoutisinrange = _agres_categories_check_servicehours($tmpDateCheckout, $cat);
                if ($checkinisinrange === FALSE) {
                    form_set_error('unitinfo', t('Checkin-time has to be within service hours '));
                }
                if ($checkoutisinrange === FALSE) {
                    form_set_error('unitinfo', t('Checkout-time has to be within service hours '));
                }

                $langbm = 'und';
                $langbm = field_language('node', $cat, 'field_agres_bookingmode');

                if ($tmpDateCheckin >= $tmpDateCheckout) {
                    if (module_exists('agres_package') && !$cat->field_agres_bookingmode[$langbm][0]['value'] == '3') {
//                    drupal_set_message('<pre>zeittttt_ ' . print_r($cat, true) . '</pre>');
                        form_set_error('unitinfo', t('Checkin has to be before Checkout '));
                    }
                }


                if ($tmpDateCheckin <= new DateTime()) {
                    form_set_error('unitinfo', t('Checkin is has to be in the future !!! '));
                }
//    $checkintime = date_format($tmpDateCheckin, 'Y-m-d H:i:s');
//    $checkouttime = date_format($tmpDateCheckout, 'Y-m-d H:i:s');

                /* get reservable units: */
                $resnodes = agreservations_get_reservable_items('agreservations_unit', date_format($tmpDateCheckin, 'Y-m-d H:i'), date_format($tmpDateCheckout, 'Y-m-d H:i'), $cat);

                $foundunits = count($resnodes);
                if ($requestedunits > 0) {
                    if ($requestedunits > $foundunits) {
                        if (!$cat->field_agres_bookingmode[$langbm][0]['value'] == 3) {
                            form_set_error('unitinfo', t('Not enough free units found.'));
                        }
                    }
                } elseif ($requestedunits == 0) {
                    $langsnu = 'und';
                    $langsnu = field_language('node', $cat, 'field_agres_shownumberunits');
                    $langsm = 'und';
                    $langsm = field_language('node', $cat, 'field_agres_unitselectionmethod');
                    if (!($cat->field_agres_shownumberunits[$langsnu][0]['value'] == 2 && $cat->field_agres_unitselectionmethod[$langsm][0]['value'] == 2)) {
                        form_set_error('unitinfo', t('Number of units has to be > 0'));
                    }
                }
//    $tmpagres_onlineformjelements = variable_get('agres_onlineformjelements', 'standard');
            }
        } else {
            form_set_error('unitinfo', t('agres_category not set! Please try again'));
        }        
    }
    //_searchwidget_form_submit
     static function _agr_searchwidget_form_submit($form, &$form_state){
         
        if (isset($form_state['build_info']['args'][0])) {
            $cat = $form_state['build_info']['args'][0];
            $lang = 'und';
            $lang = field_language('node', $cat, 'field_agres_showtime');


            $preselectedunit = 0;
            if (isset($_SESSION['agres_current_page_nid'])) {
                $currently_viewed_producttype = null;
                $currently_viewed_producttype = node_load($_SESSION['agres_current_page_nid']);
                if (_agres_categories_unittype_has_cat($_SESSION['agres_current_page_nid'], $cat->nid)) {
                    $preselectedunit = $_SESSION['agres_current_page_nid'];
                }
            }
            if (isset($form_state['build_info']['args'][0])) {
                if (isset($form_state['values']['adults'])) {
                    $adults = $form_state['values']['adults'];
                }

                if (isset($form_state['values']['children'])) {
                    $children = $form_state['values']['children'];
                }

                if (isset($form_state['values']['units'])) {
                    $requestedunits = $form_state['values']['units'];
                }
                if (isset($form_state['values']['checkin' . $cat->nid])) {
                    $tmpDateCheckin = date_create($form_state['values']['checkin' . $cat->nid]);
                }

                if (isset($form_state['values']['checkout' . $cat->nid])) {
                    $tmpDateCheckout = date_create($form_state['values']['checkout' . $cat->nid]);
                }

//      $tmpDateCheckout->modify('+3 hour');
                $checkintime = date_format($tmpDateCheckin, 'Y-m-d H:i:s');
                $checkouttime = date_format($tmpDateCheckout, 'Y-m-d H:i:s');

//      drupal_set_message('<pre>agres_categories_searchwidget_form_submit_ '.print_r($checkintime,true).'</pre>');
//    /* get reservable units: */
                $langbm = 'und';
                $langbm = field_language('node', $cat, 'field_agres_bookingmode');

                if (intval($cat->field_agres_bookingmode[$langbm][0]['value']) < 3) {
                    if (isset($form_state['build_info']['args'][0])) {
                        $categorynid = $form_state['build_info']['args'][0]->nid;
                        $resnodes = agreservations_get_reservable_items('agreservations_unit', date_format($tmpDateCheckin, 'Y-m-d H:i:s'), date_format($tmpDateCheckout, 'Y-m-d H:i:s'), $categorynid);
                    } else {
                        
                    }
                    $availableunittypes = _agreservations_get_reservable_unittypes($resnodes, FALSE);
                    $_SESSION['availableunittypes'] = $availableunittypes;

                    $userrequest['checkintime'] = $checkintime;
                    $userrequest['checkouttime'] = $checkouttime;
                    if (isset($adults)) {
                        $userrequest['adults'] = $adults;
                    }
                    if (isset($children)) {
                        $userrequest['children'] = $children;
                    }

                    if (isset($requestedunits)) {
                        $userrequest['requestedunits'] = $requestedunits;
                    } else {
                        $userrequest['requestedunits'] = 1;
                        $requestedunits = 1;
                    }
                    $datstr = date_format($tmpDateCheckin, 'YmdHis') . date_format($tmpDateCheckout, 'YmdHis') . $requestedunits;
                    $cat = $form_state['build_info']['args'][0];
                    $form_state['rebuild'] = true;
                    unset($form_state['values']);

                    $availableunittypenids = array_keys($availableunittypes);
                    if (in_array($preselectedunit, $availableunittypenids)) {
                        $userrequest['preselectedunit'] = $preselectedunit;
                        $_SESSION['agreservationuserrequest'] = $userrequest;
                        $_SESSION['agreservationcategory'] = $cat->nid;
                        _agres_bookings_reserve_and_fillcart(null, null, $userrequest, $cat->nid, $preselectedunit, array(), 'cart', $form_state);
                    } else {

                       $agrsearchredirect =  agres_categories_search_result($userrequest, $cat, $datstr);
                        
                    }
                } elseif (module_exists('agres_package') && $cat->field_agres_bookingmode[$langbm][0]['value'] == '3') {
                    /**
                     * If bookingmode Package, dont check availability now, just
                     * present all unittypes and units attached to all packages which are attached
                     * to the current category: 
                     */
                    $userrequest['checkintime'] = $checkintime;
                    $userrequest['pickuppoint'] = $form_state['values']['pickuppoint'];
                    $userrequest['dropoffpoint'] = $form_state['values']['dropoffpoint'];

                    //for caching generate rather unique url...or better an url which fits:
                    $datstr = date_format($tmpDateCheckin, 'YmdHis') . $requestedunits;
                   $agrsearchredirect =  agres_categories_search_result($userrequest, $cat, $datstr);
                } elseif (module_exists('agres_place') && $cat->field_agres_bookingmode[$langbm][0]['value'] == '4') {
                    $userrequest['checkintime'] = $checkintime;
                    $userrequest['checkouttime'] = $checkouttime;
                    $userrequest['pickuppoint'] = $form_state['values']['pickuppoint'];
                    $datstr = date_format($tmpDateCheckin, 'YmdHis') . $requestedunits;
//                drupal_set_message('<pre>d****__'.print_r($userrequest,true).'</pre>');  
                    $agrsearchredirect =  agres_categories_search_result($userrequest, $cat, $datstr);
//                    agres_categories_search_result($userrequest, $cat, $datstr);
                }
                drupal_goto($agrsearchredirect);
            } else {
                $content = '<div>' . t('Category not set') . '</div>';
                $content = $content . '<br><a href="' . base_path() . '">' . t('back') . '<a>';
                print theme('page', $content);
            }
            
        } else {
            drupal_set_message('Category not set!');
        }        
    }       
    //call this inside hook_form
     static function _agr_get_details_form(){
    $userrequest = $_SESSION['agreservationuserrequest'];
    $flightnumber = '';
    $pickupplate = '';
    $referencenumber = '';
    $numberpersons = '1';
    $firstname = '';
    $lastname = '';
    $email = '';
    if (isset($_SESSION['agreservationuserrequest']['numberpassengers'])){
        $numberpersons = $_SESSION['agreservationuserrequest']['numberpassengers'];  
    }
    if (isset($_SESSION['agreservationuserrequest']['firstname'])){
        $firstname = $_SESSION['agreservationuserrequest']['firstname'];  
    }   
    if (isset($_SESSION['agreservationuserrequest']['lastname'])){
        $lastname = $_SESSION['agreservationuserrequest']['lastname'];  
    }      
    if (isset($_SESSION['agreservationuserrequest']['email'])){
        $email = $_SESSION['agreservationuserrequest']['email'];  
    }   
$form = array();
        $fieldsetclass = 'agr_additionalinfo_';
        if (isset($_SESSION['agreservationuserrequest']['pickuppoint'])){
            $fieldsetclass .= $_SESSION['agreservationuserrequest']['pickuppoint'];
        }
        $fieldsetclassdest = 'agr_additionalinfo_dest_';
        if (isset($_SESSION['agreservationuserrequest']['dropoffpoint'])){
            $fieldsetclassdest .= $_SESSION['agreservationuserrequest']['dropoffpoint'];
        }        
$form['agrdetails'] = array(
  '#prefix' => '<div class="'.$fieldsetclass.' '.$fieldsetclassdest.'">',
  '#type' => 'fieldset',
//  '#title' => t('Additional Info'),
  '#weight' => 5,
  '#collapsible' => FALSE,
  '#collapsed' => FALSE,
    '#suffix' => '</div>',
);
$form['agrdetails']['numberpersons'] = array(
  '#required' => '1',
  '#multiple' => '0',
  '#key_type_toggled' => '0',
  '#default_value' => $numberpersons,
  '#weight' => '3',
  '#type' => 'select',
  '#options' => array(
    '1' => t('1'),
    '2' => t('2'),
    '3' => t('3'),
    '4' => t('4'),
    '5' => t('5'),
    '6' => t('6'),
    '7' => t('7'),
    '8' => t('8'),
    '9' => t('9'),
  ),
  '#multiple_toggle' => '1',
  '#title' => t('Enter Number of Passengers'),
);

$form['agrdetails']['firstname'] = array(
  '#required' => '0',
  '#description' => t('First name'),
  '#weight' => '5',
  '#type' => 'textfield',
   '#default_value' => $firstname,
  '#title' => t('First name'),
);

$form['agrdetails']['lastname'] = array(
  '#required' => '0',
  '#description' => t('last name'),
  '#weight' => '6',
  '#type' => 'textfield',
   '#default_value' => $lastname,
  '#title' => t('last name'),
);

$form['agrdetails']['email'] = array(
  '#required' => '0',
  '#description' => t('Contact E-Mail'),
  '#weight' => '7',
  '#type' => 'textfield',
   '#default_value' => $email,
  '#title' => t('Contact E-Mail'),
);

//  $form['#validate']
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Continue'),
    '#id' => 'submit-unitselect',
      '#submit' => array('agres_categories_get_details_submithandler'),
//      '#validate' =>array('agres_bm_3::_agr_get_details_form_validate'),
    '#attributes' => array(
      'class' => array('submit-additional-info'),
    ),
      '#weight' => '5',
  );
  
return $form;             
         }   
    //call this inside hook_form_validate
  static function _agr_get_details_form_validate($form, &$form_state) {   
    //Basic validation first:  
    if (($form_state['values']['firstname']=='' || $form_state['values']['firstname']===null) ) {
        drupal_set_message(t('Please enter your first name.'), 'error');
        return;
    }    
    if (($form_state['values']['lastname']=='' || $form_state['values']['lastname']===null) ) {
        drupal_set_message(t('Please enter your last name.'), 'error');
        return;
    }    
            
    if (($form_state['values']['email']=='' || $form_state['values']['email']===null) || !valid_email_address($form_state['values']['email'])) {
        drupal_set_message(t('Please enter a valid email address.'), 'error');
        return;
    }    
    
    /////////////////////////////
    $userrequest = $_SESSION['agreservationuserrequest'];
    $selectedunittypenid = $userrequest['selectedunittypenid'];
    $selectedunittype = node_load($userrequest['selectedunittypenid']);
    $cat = node_load($userrequest['catnid']);
    $langbm = 'und';
    $langbm = field_language('node', $cat, 'field_agres_bookingmode');
    $selcapacity = 4;
    $langcap = field_language('node', $selectedunittype, 'field_agreservations_capacity');
    $selcapacity = $selectedunittype->field_agreservations_capacity[$langcap][0]['value'];    
//***************************************Reservation******************************
    if ($cat->field_agres_bookingmode[$langbm][0]['value'] == '3') {
        //take into account the unpublished reservations from this very session:
        $res = null;
        if (isset($_SESSION['agreservationuserrequest']['resnid'])) {
            $res = node_load($_SESSION['agreservationuserrequest']['resnid']);
            if (isset($res) && $res !== false && res !== null && $res->status == 0) {
                _agreservations_setstatus_reservation($_SESSION['agreservationuserrequest']['resnid'], TRUE);
                $_SESSION['agreservationuserrequest']['tmppublished'] = '1';
            }
        }
        $userrequestunit = array();
        $userrequestunit[]['selectunittype'] = $selectedunittypenid;
        $unitsToBook = false;
        $currentpackage = node_load($_SESSION['agreservationuserrequest']['packagenid']);
        $reservable_units = agreservations_get_reservable_items('agreservations_unit', $_SESSION['agreservationuserrequest']['checkintime'], $_SESSION['agreservationuserrequest']['checkouttime'], $_SESSION['agreservationuserrequest']['catnid']);
//            drupal_set_message('<pre>reservables: ' . print_r($reservable_units, true) . '   </pre>');
        $langcode = field_language('node', $currentpackage, 'field_agr_pack_units');

        foreach ($reservable_units as $reskey => $resunit) {
            if (in_multi_assoc_array($resunit->nid, $currentpackage->field_agr_pack_units[$langcode])) {
                $_SESSION['agreservationuserrequest']['packagenid'] = $currentpackage->nid;
                $unitsToBook[] = $resunit;
                break; //just 1
            }
        }
        //  remember previous choosed package:
        $_SESSION['agreservationuserrequest']['updowngrade'] = array('mode' => 3,
            'prodoldnid' => $_SESSION['agreservationuserrequest']['packagenid'],
            'prodnewnid' => $_SESSION['agreservationuserrequest']['packagenid'], 'updown' => 0); //  
        

        if (count($unitsToBook) < 1 || $unitsToBook === false) {
//*********find Packages with selected pcikup and dropoff points:*********************************        
           //$packs = _agres_package_get_packages($_SESSION['agreservationuserrequest']['pickuppoint'], $_SESSION['agreservationuserrequest']['dropoffpoint']);
           $packs = _agres_package_get_packages_of_capacity($_SESSION['agreservationuserrequest']['pickuppoint'], $_SESSION['agreservationuserrequest']['dropoffpoint'],$selcapacity);            
          // drupal_set_message('<pre>$packs$packs'.print_r($packs,true).'</pre>');           
            foreach ($packs as $packkey => $pack) {
                $packprices[$packkey] = $pack->sell_price;
            }
            asort($packprices, SORT_NUMERIC);
            //hier anfangen:
            $unitsToBook = false;
            $unitsToBook = _find_same_level_avbl_packages($packs, $packprices, $currentpackage->sell_price, $userrequest['pickuppoint'], $userrequest['dropoffpoint']);            
            if (is_array($unitsToBook)) { 
                $newpacakge = node_load($_SESSION['agreservationuserrequest']['packagenid']);
                $_SESSION['agreservationuserrequest']['updowngrade']['updown'] = 0;
                $_SESSION['agreservationuserrequest']['updowngrade']['prodnewnid'] = $_SESSION['agreservationuserrequest']['packagenid'];
                drupal_set_message('<div class="agr_downgradepackagemessage">' . print_r(t('Sorry the selected car was not available, a different car of the same quality was selected: <div class="agr_downgradepackagetitle"> @new. </div>', array('@new' => $newpacakge->title)), true) . '</div>', 'error');                
            } else {         
            $unitsToBook = false;
            $unitsToBook = _find_next_higher_avbl_packages($packs, $packprices, $currentpackage->sell_price, $userrequest['pickuppoint'], $userrequest['dropoffpoint']);
            if (is_array($unitsToBook)) {
                $prevpackage = node_load($_SESSION['agreservationuserrequest']['prev_upgrade_prodnid']); //agr_get_field_value_from_node_id($_SESSION['agreservationuserrequest']['prev_upgrade_prodnid'],'title');
//              drupal_set_message('<pre>'.print_r($prevpackage,true).'</pre>');
                $newpacakge = node_load($_SESSION['agreservationuserrequest']['packagenid']);
                $_SESSION['agreservationuserrequest']['updowngrade']['updown'] = 1;
                $_SESSION['agreservationuserrequest']['updowngrade']['prodnewnid'] = $_SESSION['agreservationuserrequest']['packagenid'];
                drupal_set_message('<div class="agr_upgradecarmessage">' . print_r(t('Sorry the selected car was not available, you have been upgraded for').'<span class="free">'.t(' free ').'</span>'.t('to').t('<div class="agr_upgradecartitle"> @new. </div>', array('@new' => $newpacakge->title)), true) . '</div>', 'error');
            } else {
                $unitsToBook = false;
                $unitsToBook = _find_next_lower_avbl_packages($packs, $packprices, $currentpackage->sell_price, $userrequest['pickuppoint'], $userrequest['dropoffpoint']);
                //find next lower:         
                if (!$unitsToBook) {
                    drupal_set_message('<div class="agr_noavailablesfound">'.t('Sorry, no available vehicles were found. Please make a different choice!').'</div>', 'error');
                    $form_state['redirect'] = 'agrbookingstep1/' . $userrequest['catnid'] . '/' . $userrequest['resformtitel'] . '/' . $userrequest['datstring'];
//                 $form_state['redirect'] = '';
                } else {
                    $newpacakge = node_load($_SESSION['agreservationuserrequest']['packagenid']);
                    $_SESSION['agreservationuserrequest']['updowngrade']['updown'] = -1;
                    $_SESSION['agreservationuserrequest']['updowngrade']['prodnewnid'] = $_SESSION['agreservationuserrequest']['packagenid'];
                    drupal_set_message('<div class="agr_downgradepackagemessage">' . print_r(t('Sorry the selected car was not available, you have been downgraded for the lower price - 10% to <div class="agr_downgradepackagetitle"> @new. </div>', array('@new' => $newpacakge->title)), true) . '</div>', 'error');
                }
            }
        }
        }
        if ((is_array($unitsToBook)) && (count($unitsToBook) > 0)) {
            if (isset($res) && $res !== false && $res !== null) {
//                 drupal_set_message('<pre>call::_agreservations_update_Reservation:::'.print_r($unitsToBook,true).'</pre>');
                $resnid = _agreservations_update_Reservation($_SESSION['agreservationuserrequest']['resnid'], $unitsToBook);
            } else {
                $resnid = _agreservations_create_Reservation($unitsToBook, $userrequest['checkintime'], $userrequest['checkouttime'], NULL, NULL, AGRES_STATUS_ONLINE_NO_ORDER_YET, t('Reservation'), 0);
                $_SESSION['agreservationuserrequest']['resnid'] = $resnid;
            }
        } else {
            drupal_set_message(t('Sorry, no units available.'), 'error');
            drupal_goto('agrbookingstep1/' . $userrequest['catnid'] . '/' . $userrequest['resformtitel'] . '/' . $userrequest['datstring']);
        }
    } elseif ($cat->field_agres_bookingmode[$langbm][0]['value'] == '4') {
//*************************************************by the hour booking:********************************
//*****************************************************************************************************     
        $userrequestunit = array();
        $userrequestunit[]['selectunittype'] = $selectedunittypenid;
        $selectedunittype = node_load($selectedunittypenid);
        //take into account the unpublished reservations from this very session:
        $res = null;
        if (isset($_SESSION['agreservationuserrequest']['resnid'])) {
            $res = node_load($_SESSION['agreservationuserrequest']['resnid']);
            if (isset($res) && $res !== false && $res !== null && $res->status == 0) {
//                _agreservations_setstatus_reservation($_SESSION['agreservationuserrequest']['resnid'], TRUE);
//                $_SESSION['agreservationuserrequest']['tmppublished'] = '1';
            }
        }
//        drupal_set_message('<pre>uuuuuuuuuuuuuuuuuuuuuud'.print_r($res,true).'</pre>');
//***************************************************************************************
        $unitsToBook = false;
        $reservable_units = agreservations_get_reservable_items('agreservations_unit', $userrequest['checkintime'], $userrequest['checkouttime'], $userrequest['catnid']);
        $reservable_unittypes = _agreservations_get_reservable_unittypes($reservable_units, true);
        if (array_key_exists($selectedunittype->nid, $reservable_unittypes)) {
            $userrequestunit = array();
            $userrequestunit[]['selectunittype'] = $selectedunittype->nid;
            $unitsToBook = _agreservations_find_units_for_user_request($userrequestunit, $userrequest['checkintime'], $userrequest['checkouttime'], $userrequest['catnid']);
        }
//***************************************************************************************    
//  remember previous choosed unittype:
        $_SESSION['agreservationuserrequest']['updowngrade'] = array('mode' => 4,
            'prodoldnid' => $_SESSION['agreservationuserrequest']['selectedunittypenid'],
            'prodnewnid' => $_SESSION['agreservationuserrequest']['selectedunittypenid'], 'updown' => 0);
        
        if (count($unitsToBook) < 1 || $unitsToBook === false) {
            $orderedunittypes = _agres_categories_get_priceordered_products_with_capacity($userrequest['catnid'],$selcapacity);
            //$orderedunittypes = _agres_categories_get_priceordered_products($userrequest['catnid']);
            $unitsToBook = false;
            $unitsToBook = _find_same_level_avbl_unittypes($orderedunittypes, $selectedunittype->sell_price, $userrequest['checkintime'], $userrequest['checkouttime'], $userrequest['catnid']);            
            if (is_array($unitsToBook)) {
                $newprod = node_load($_SESSION['agreservationuserrequest']['selectedunittypenid']);
                $_SESSION['agreservationuserrequest']['updowngrade']['updown'] = 0;
                $_SESSION['agreservationuserrequest']['updowngrade']['prodnewnid'] = $_SESSION['agreservationuserrequest']['selectedunittypenid'];
                drupal_set_message('<div class="agr_upgradecarmessage">' . print_r(t('Sorry the selected car was not available, a different car of the same price was selected: <div class="agr_upgradecartitle"> @new. </div>', array('@new' => $newprod->title)), true) . '</div>', 'error');
            } else {    
            $unitsToBook = false;
            //remember previous selected unittype:        
            $unitsToBook = _find_next_higher_avbl_unittypes($orderedunittypes, $selectedunittype->sell_price, $userrequest['checkintime'], $userrequest['checkouttime'], $userrequest['catnid'], 2);
            if (is_array($unitsToBook)) {
                $newprod = node_load($_SESSION['agreservationuserrequest']['selectedunittypenid']);
                $_SESSION['agreservationuserrequest']['updowngrade']['updown'] = 1;
                $_SESSION['agreservationuserrequest']['updowngrade']['prodnewnid'] = $_SESSION['agreservationuserrequest']['selectedunittypenid'];
                drupal_set_message('<div class="agr_upgradecarmessage">' . print_r(t('Sorry the selected car was not available, you have been upgraded for').'<span class="free">'.t(' free ').'</span>'.t('to').t('<div class="agr_upgradecartitle"> @new. </div>', array('@new' => $newprod->title)), true) . '</div>', 'error');
            } else {
                $unitsToBook = false;
                $unitsToBook = _find_next_lower_avbl_unittypes($orderedunittypes, $selectedunittype->sell_price, $userrequest['checkintime'], $userrequest['checkouttime'], $userrequest['catnid'], 2);
                //find next lower:         
                if (!$unitsToBook) {
                    drupal_set_message(t('Could not find a unit for the selected type of car! Please make a different choice!'), 'error');
                    $form_state['redirect'] = 'agrbookingstep1/' . $userrequest['catnid'] . '/' . $userrequest['resformtitel'] . '/' . $userrequest['datstring'];
                } else {
                    $newprod = node_load($_SESSION['agreservationuserrequest']['selectedunittypenid']);
                    $_SESSION['agreservationuserrequest']['updowngrade']['updown'] = -1;
                    $_SESSION['agreservationuserrequest']['updowngrade']['prodnewnid'] = $_SESSION['agreservationuserrequest']['selectedunittypenid'];
                    drupal_set_message('<div class="agr_downgradepackagemessage">' . print_r(t('Sorry the selected car was not available, you have been downgraded for the lower price - 10% to <div class="agr_downgradepackagetitle"> @new. </div>', array('@new' => $newprod->title)), true) . '</div>', 'error');
                }
            }
        }
        }
//        drupal_set_message('<pre>agres_categories_get_details_form_validate:::++fdd++----'. print_r($unitsToBook, true) . '</pre>');             
        if ((is_array($unitsToBook)) && (count($unitsToBook) > 0)) {
            if (isset($res) && $res !== false && $res !== null) {
//                 drupal_set_message('<pre>call::_agreservations_update_Reservation:::'.print_r($unitsToBook,true).'</pre>');
                $resnid = _agreservations_update_Reservation($_SESSION['agreservationuserrequest']['resnid'], $unitsToBook);
            } else {
                $resnid = _agreservations_create_Reservation($unitsToBook, $userrequest['checkintime'], $userrequest['checkouttime'], NULL, NULL, AGRES_STATUS_ONLINE_NO_ORDER_YET, t('Reservation'), 0);
                $_SESSION['agreservationuserrequest']['resnid'] = $resnid;
            }
        } else {
            drupal_set_message(t('Sorry, no units available.'), 'error');
        }
    }
///*************************************************************************************
///*************************************************************************************    
///*************************************************************************************
    $capacity_reservation = 0;
//      drupal_set_message('<pre>_UNITSTOBOOK: ' . print_r($capacity_reservation, true) . '   </pre>'); 
    $capacity_reservation = _agreservations_get_capacity_from_reservation($_SESSION['agreservationuserrequest']['resnid']);
    if (intval($form_state['values']['numberpersons']) > intval($capacity_reservation)) {
        drupal_set_message('<div class="agr_exceedpassenger">' .t('The number of Passengers you selected exceed the available space! Please choose a different vehicle.').'</div>', 'error');
        //choose additional unit but before add to cart this one so it does not get forgotton
        //there needs to be implemented a more modern way of doing this in the future...OOP needed.
        $packagenode = node_load($_SESSION['agreservationuserrequest']['packagenid']);
        $emptyform = array();
        _agres_bookings_reserve_and_fillcart($resnid, null, $userrequest, $userrequest['catnid'], $userrequest['selectedunittypenid'], array(), '', $emptyform);
        ////////////////////////////////////////////////////////////////////////////////////////////
        $_SESSION['agreservationuserrequest']['secondchoice'] = 1;
        $_SESSION['agreservationuserrequest']['redirect'] = 'agrbookingstep1/' . $userrequest['catnid'] . '/' . $userrequest['resformtitel'] . '/' . $userrequest['datstring'];
        $form_state['redirect'] = 'agrbookingstep1/' . $userrequest['catnid'] . '/' . $userrequest['resformtitel'] . '/' . $userrequest['datstring'];
        return;
    } else {
        $form_state['redirect'] = 'cart';
        $_SESSION['agreservationuserrequest']['redirect'] = 'cart';
    }

    $tmpDateCheckin = date_create($userrequest['checkintime']);
    $tmpDateCheckout = date_create($userrequest['checkintime']);
    //special for package booking mode:
}
    //call this inside hook_form_submit
     static function _agr_get_details_form_submit($form, &$form_state) {
    //save form entry field values in the session: 
//    drupal_set_message('<pre>_agr_get_details_form_submit_agr_get_details_form_submit: ' . print_r($form_state['values'], true) . '   </pre>'); 
     //only if $form_state['redirect']='cart'; only then validation succeeded:
    if ($form_state['redirect']=='cart'){
    $_SESSION['agreservationuserrequest']['numberpassengers'] = $form_state['values']['numberpersons'];  
    $_SESSION['agreservationuserrequest']['firstname'] = $form_state['values']['firstname']; 
    $_SESSION['agreservationuserrequest']['lastname'] = $form_state['values']['lastname']; 
    $_SESSION['agreservationuserrequest']['email'] = $form_state['values']['email']; 
    if (isset($_SESSION['agreservationuserrequest']['firstname'])){
        $firstname = $_SESSION['agreservationuserrequest']['firstname'];  
    }   
    if (isset($_SESSION['agreservationuserrequest']['lastname'])){
        $lastname = $_SESSION['agreservationuserrequest']['lastname'];  
    }      
    if (isset($_SESSION['agreservationuserrequest']['email'])){
        $email = $_SESSION['agreservationuserrequest']['email'];  
    }      
    $userrequest = $_SESSION['agreservationuserrequest'];
    if (module_exists('agr_additional_infos')){
      $resnid = _agres_additional_infos_update_userrequestdata_to_Reservation($userrequest['resnid'],$userrequest);                      
    }
    
    $selectedunittypenid = $_SESSION['agreservationuserrequest']['selectedunittypenid'];
    $selectedunittype = node_load($selectedunittypenid);
    
    $cat = node_load($userrequest['catnid']);

    $langbm = 'und';
    $langbm = field_language('node', $cat, 'field_agres_bookingmode');
    $tmpDateCheckin = date_create($userrequest['checkintime']);
    $tmpDateCheckout = date_create($userrequest['checkintime']);   
   // special for package booking mode:
    $langc = 'und';
    $langc = field_language('node', $selectedunittype, 'field_agreservations_capacity');
//  $_SESSION['agreservationuserrequest']['capacity']+=$selectedunittype->field_agreservations_capacity[$langc][0]['value'];    
    if (isset($userrequest['packagenid'])) {//           
        $packagenode = node_load($userrequest['packagenid']);
        $langh = 'und';
        $langh = field_language('node', $packagenode, 'field_agr_pack_hours');
        $hours = $packagenode->field_agr_pack_hours[$langh][0]['value'];
        $tmpDateCheckout = $tmpDateCheckout->modify('+' . $hours+1 . ' hours');
        $userrequest['checkouttime'] = $tmpDateCheckout->format('Y-m-d H:i:s');
        $emptyform = array();   
        _agres_bookings_reserve_and_fillcart($_SESSION['agreservationuserrequest']['resnid'], null,$userrequest, $userrequest['catnid'],$userrequest['selectedunittypenid'],array(),'',$emptyform);                      
    }else {
        $tmpDateCheckout = date_create($userrequest['checkouttime']);   
        $emptyform = array();      
        _agres_bookings_reserve_and_fillcart( $_SESSION['agreservationuserrequest']['resnid'], null,$userrequest, $userrequest['catnid'],$userrequest['selectedunittypenid'],array(),'',$emptyform);              
    }
//    drupal_set_message('<pre>reeeeeeeeeeeeeeedirect:::++++___' . print_r($form_state['redirect'], true) . '</pre>');
    if (isset($_SESSION['agreservationuserrequest']['redirect'])){        
       $form_state['redirect'] = $_SESSION['agreservationuserrequest']['redirect'];
    } else {
        $form_state['redirect'] = 'cart';
    }
    }
//  drupal_set_message('<pre>reeeeeeeeeeeeeeedirect:::++++___' . print_r($form_state['redirect'], true) . '</pre>');
        
//   
//      drupal_goto('cart');
}
     
        
}
