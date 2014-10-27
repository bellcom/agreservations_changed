<?php
/**
 * @file
 * Template to display a view as a calendar day, grouped by resources
 * and optionally organized into columns by a field value.
 *
 * @see template_preprocess_calendar_day.
 * $resources: An Array of the rooms or resources which can be booked.
 * $resources[$name][$rows] - An array of resourcenames each containing
 * the rows for that day and the current resource.(usually just 1 to 1 except
 * you have 1 room and multiple beds to book seperately)
 *
 * $rows: The rendered data for this day and this resource.
 * $rows['date'] - the date for this day, formatted as YYYY-MM-DD.
 * $rows['datebox'] - the formatted datebox for this day.
 * $rows['empty'] - empty text for this day, if no items were found.
 * $rows['all_day'] - an array of formatted all day items.
 * $rows['items'] - an array of timed items for the day.
 * $rows['items'][$time_period]['hour'] - the formatted hour for a time period.
 * $rows['items'][$time_period]['ampm'] - the formatted ampm value, if any for a time period.
 * $rows['items'][$time_period][$column]['values'] - An array of formatted
 *   items for a time period and field column.
 *
 * $view: The view.
 * $columns: an array of column names.
 * $min_date_formatted: The minimum date for this calendar in the format YYYY-MM-DD HH:MM:SS.
 * $max_date_formatted: The maximum date for this calendar in the format YYYY-MM-DD HH:MM:SS.

 */
//dsm('Display: '. $display_type .': '. $min_date_formatted .' to '. $max_date_formatted);
//dpm($rows);
?>
<div  class="agreservations-calendar">
  <div class="day-view">
    <table class="agreservations-table">
      <colgroup>
         <col width="20">
        <?php foreach ($units as $unit): ?>
        <col width="40">
        <?php endforeach; ?>
         <col width="10">
      </colgroup>
      <tbody>
        <tr>

          <?php foreach ($units as $unit): ?>
            <th><span style="float: left;"><?php print "Uge " . date('W',strtotime($rows['date'])); ?></span>
              <?php print t(date('D',strtotime($rows['date']))) . " " . date('d.m.Y', strtotime($rows['date'])); ?>
            </th>
            <th class="agreservations-calendar unitname"><a href="<?php print(base_path()); ?>node/<?php print $unit->nid ?>"><?php print $unit->title ?></a>
            </th>
          <?php endforeach; ?>

        </tr>

        <?php  foreach ($rows['items'][$unit->title] as $key => $hour):?>
        <?php
          $sat = (date('D',strtotime($rows['date'])) == 'Sat');
          $sun = (date('D',strtotime($rows['date'])) == 'Sun');
          if ($sat || $sun) {
            if (strtotime($hour['hour']) < strtotime('09:59:00') || strtotime($hour['hour']) > strtotime('21:01:00')) {
              continue;
            }
          }
          else {
            if (strtotime($hour['hour']) < strtotime('15:59:00') || strtotime($hour['hour']) > strtotime('21:01:00')) {
              continue;
            }
          }
        ?>
        <tr>
          <?php foreach ($units as $unit): ?>
            <?php $hour = $rows['items'][$unit->title][$key]; ?>
              <?php if (isset($hour['values'])) : ?>
              <?php
                global $language;
                if ($language->language == "en")
                   $item = 'Items';
                elseif($language->language == "da")
                   $item = "Overskrifter";
              ?>
              <td>
                 <?php print date('H.i', strtotime($hour['hour'])); ?>
              </td>
              <?php if ($hour['values'][$item.'-0'] != '***busy***' ) : ?>
                <td class="agreservations-calendar <?php if (isset($hour['span'][$item.'-0'])) print " agreservations-inner"; ?>" rowspan="<?php print isset($hour['span']) ? $hour['span'][$item.'-0'] : 1; ?>"><?php print $hour['values'][$item.'-0'];?></a>
                <?php if (!isset($hour['span'][$item.'-0'])) : ?>
                    <div class="agreservations-calendar">
                    <!--<a href="<?php print(base_path()); ?>node/add/agreservation?&agres_sel_unit=<?php print $unit->nid ?>&default_agres_title=&Oslash;vetid&default_agres_date=<?php print $currentselectedday ?> <?php print $hour['hour']; ?>">+</a>-->
                              </div>
                    <?php endif; ?>
                </td>
              <?php endif; ?>
            <?php else: ?>
            <td>
               <?php print date('H.i', strtotime($hour['hour'])); ?>
            </td>
            <td class="agreservations-agenda-items">
                      <div class="agreservations-calendar">
                          <a class ="agrcelllink" style = "text-align:center;" href="<?php print(base_path()); ?>node/add/agreservation?&agres_sel_unit=<?php print $unit->nid ?>&default_agres_title=&Oslash;vetid&default_agres_date=<?php print $currentselectedday ?> <?php print $hour['hour']; ?>"> <?php print date('H.i', strtotime($hour['hour'])); ?></a>
                      </div>
                  </td>
            <?php endif; ?>
          <?php endforeach; ?>
        </tr>
        <?php endforeach; ?>
        
      </tbody>
    </table>
  </div>
</div>
