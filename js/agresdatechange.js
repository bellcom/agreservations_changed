//author: Andreas Gill
(function ($) {
  Drupal.behaviors.agreservations = {
    attach: function(context, settings) {
      $("[id^="+'edit-checkin'+"][id*="+'datepicker-popup'+"]").change(function (context, settings) {
        $(this).each(function(context, settings) {  
//          alert($(this).attr('id'));
          var catnidstr = 0;
               catnidstr   = $(this).parents().find("[id*="+'agres-categories-searchwidget-form'+"]").attr('id');
               if (catnidstr === 0){
//                    alert('0 '+catnidstr);
               }else{
                   
                 catnidstr = $(this).parents().find("[id*="+'edit-checkin'+"]").attr('id');
               }
//          alert(catnidstr);
          var catnid = catnidstr.charAt(catnidstr.length-1);
          if ($('#edit-checkin'+catnid+'-checkintime').length > 0) {
          $('#edit-checkin'+catnid+'-checkintime').get(0).options.length=0;
          var i= 0;
          $.getJSON(Drupal.settings.basePath+"agptcallback/"+$(this).attr("value")+"/"+catnid+"/time",function(data){
            $.each(data, function(k,v){
              $('#edit-checkin'+catnid+'-checkintime').get(0).options[i] = new Option(v);
              i++;
            });
          });   
          }
        });  
        var catnidstr = $(this).parents().find("[id*="+'agres-categories-searchwidget-form'+"]").attr('id');
        var catnid = catnidstr.charAt(catnidstr.length-1);
//         alert(catnidstr);
        var strdate = $(this).attr("value");
        var msecsdate  = Date.parse(strdate);
        var interval = +1;
        var dateto = new Date(msecsdate);
        dateto.setDate(dateto.getDate() -0+interval);//"[id*="+'edit-checkout-datepicker-popup'+"]"       
        var tdate = $(this).closest("[id*="+'agres-categories-searchwidget-form'+"]").find("[id^="+'edit-checkout'+catnid+"][id*="+'datepicker-popup'+"]");

        var result = dateto.getFullYear()+'-'+(dateto.getMonth()+1)+'-'+dateto.getDate(); //dateto.toLocaleFormat("%Y-%m-%d");  
        tdate.value = result
        $(this).parents().find("[id^="+'edit-checkout'+catnid+"][id*="+'datepicker-popup'+"]").attr('value',result);       

      });    
    }
  }
  
  Drupal.behaviors.agreservations1 = {
    attach: function(context, settings) {
      $("[id^="+'edit-checkout'+"][id*="+'datepicker-popup'+"]").change(function (context, settings) {
        $(this).each(function(context, settings) {  
//          alert($(this).attr('id'));
          var catnidstr = $(this).parent().parent().attr('id');
//          alert(catnidstr);
          var catnid = catnidstr.charAt(catnidstr.length-1);
          if ($('#edit-checkout'+catnid+'-checkouttime').length > 0) {
          $('#edit-checkout'+catnid+'-checkouttime').get(0).options.length=0;
          var i= 0;
          $.getJSON(Drupal.settings.basePath+"agptcallback/"+$(this).attr("value")+"/"+catnid+"/time",function(data){
            $.each(data, function(k,v){
              $('#edit-checkout'+catnid+'-checkouttime').get(0).options[i] = new Option(v);
              i++;
            });
          }); 
          }
        });  
   

      });    
    }
  }  
//handle unit type datepicker fields:
 Drupal.behaviors.agreservations2 = {
    attach: function(context, settings) {
      $("[id^="+'edit-unittypebook-checkin'+"][id*="+'datepicker-popup'+"]").change(function (context, settings) {
        $(this).each(function(context, settings) {  
//          alert($(this).attr('id'));
          var catnidstr = $(this).parent().parent().attr('id');
//          alert(catnidstr);
          var catnid = catnidstr.charAt(catnidstr.length-1);
          if ($('#edit-unittypebook-checkin'+catnid+'-checkintime').length > 0) {
          $('#edit-unittypebook-checkin'+catnid+'-checkintime').get(0).options.length=0;
          var i= 0;
          $.getJSON(Drupal.settings.basePath+"agptcallback/"+$(this).attr("value")+"/"+catnid+"/time",function(data){
            $.each(data, function(k,v){
              $('#edit-unittypebook-checkin'+catnid+'-checkintime').get(0).options[i] = new Option(v);
              i++;
            });
          });   
          }
        });  
//        var catnidstr = $(this).parents().find("[id*="+'agreservations-unittype-form'+"]").attr('id');
//        var catnid = catnidstr.charAt(catnidstr.length-1);
        var strdate = $(this).attr("value");
        var msecsdate  = Date.parse(strdate);
        var interval = +1;
        var dateto = new Date(msecsdate);
        dateto.setDate(dateto.getDate() -0+interval);//"[id*="+'edit-checkout-datepicker-popup'+"]"       
        var tdate = $(this).closest("[id*="+'agreservations-unittype-form'+"]").find("[id^="+'edit-unittypebook-checkout'+catnid+"][id*="+'datepicker-popup'+"]");

        var result = dateto.getFullYear()+'-'+(dateto.getMonth()+1)+'-'+dateto.getDate(); //dateto.toLocaleFormat("%Y-%m-%d");  
        tdate.value = result
        $(this).parents().find("[id^="+'edit-unittypebook-checkout'+catnid+"][id*="+'datepicker-popup'+"]").attr('value',result);       

      });    
    }
  }
})(jQuery);