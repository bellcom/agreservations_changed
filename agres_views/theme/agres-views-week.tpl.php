<?php
/**
 * @file
 * Template to display a view as a calendar week this template is used when the agres_categories module is activated.
 *
 * @see template_preprocess_calendar_week.
 *
 * $day_names: An array of the day of week names for the table header.
 * $rows: The rendered data for this week.
 *
 * For each day of the week, you have:
 * $rows['date'] - the date for this day, formatted as YYYY-MM-DD.
 * $rows['datebox'] - the formatted datebox for this day.
 * $rows['empty'] - empty text for this day, if no items were found.
 * $rows['all_day'] - an array of formatted all day items.
 * $rows['items'] - an array of timed items for the day.
 * $rows['items'][$time_period]['hour'] - the formatted hour for a time period.
 * $rows['items'][$time_period]['ampm'] - the formatted ampm value, if any for a time period.
 * $rows['items'][$time_period]['values'] - An array of formatted items for a time period.
 *
 * $view: The view.
 * $min_date_formatted: The minimum date for this calendar in the format YYYY-MM-DD HH:MM:SS.
 * $max_date_formatted: The maximum date for this calendar in the format YYYY-MM-DD HH:MM:SS.
 *
 */
//dsm('Display: '. $display_type .': '. $min_date_formatted .' to '. $max_date_formatted);
//dpm($rows);
//dsm($items);//currentunittype calendarname
?>
<div class="agreservations-calendar"><div class="week-view">
    <table class="agreservations-table">
      <tr>
        <th class="agreservations-calendar"><?php print "Uge " . date('W',strtotime($rows[0]['date'])) . '</span>'; ?><?php //print $by_hour_count > 0 ? t('units') : ''; ?></th>
        <?php foreach ($rows as $diw => $day): ?>
        <?php //foreach ($day_names as $cell): ?>
          <th class="agreservations-calendar">
            <?php print '<a href ="/agres_view/day/'.$day['date'] . '">'.t(date('D',strtotime($day['date']))). " - ". date('d/m',strtotime($day['date'])). '</a>'; ?>
          </th>
        <?php endforeach; ?>
      </tr>
      </thead>
      <tbody>
        <?php foreach ($units as $unit): ?>
          <tr>
            <td class="agreservations-calendar" style="vertical-align: middle">
              <a href="<?php print(base_path()); ?>node/<?php print $unit->nid ?>"><?php print $unit->title ?></a>
              <span class="agreservations-calendar-hour"></span>
            </td>
            <?php foreach ($rows as $diw => $day): ?>
            <?php $weekend = "";
              if (date('D',strtotime($day['date'])) == 'Sat' || date('D',strtotime($day['date'])) == 'Sun')
              $weekend = "weekend";
            ?>
              <?php if (isset($day['night'][$unit->title])) : ?>
              <td class="agreservations-calendar-agenda-items <?php print $weekend; ?>">
                  <div>
                  <?php $start = 8;$i = 0; while($i < 15):?>

                    <?php
                      $rowspan = 1;
                      if(strlen($start) == 1) {
                        $time_str = '0'.$start.":00";
                      }
                      else
                      $time_str = $start . ":00";
                    ?>
                    <?php foreach ($day['night'][$unit->title] as $itemnid => $unitbookings): ?>

                    <?php if (isset($day['night'][$unit->title][$itemnid])) : ?>
                    <?php
                      $node = node_load($itemnid);
                      $field_start = field_get_items('node',$node,'field_agres_rdate');
                      $field_start_h = date('H',strtotime($field_start[0]['value'])) + 2;
                      $field_end_h = date('H',strtotime($field_start[0]['value2'])) + 2;
                      $field_end_m = date('i',strtotime($field_start[0]['value2']));

                      $rowspan = $field_end_h - $field_start_h;
                      if ($field_end_m) {
                        $rowspan += 1;
                      }
                      ?>
                      <?php if ($field_start_h == $start):?>
                        <div class="agreservations-calendar-agenda-items" <?php print isset($spaninfo[$unit->title][$itemnid]) ? "rowspan=" . $spaninfo[$unit->title][$itemnid] : ""; ?> >
                           <?php print ($day['night'][$unit->title][$itemnid]); ?>
                        </div>
                       
                      <?php elseif($field_end_h <= $start || $field_start_h > $start): ?>
                     <div style="border-top: 1px solid #ccc;border-collapse: collapse; border-spacing: 0;">
                          <a class="agrcelllink" style = "text-align:center;" href="<?php print(base_path()); ?>node/add/agreservation?&agres_sel_unit=<?php print $unit->nid ?>&default_agres_title=Reservation&default_agres_date=<?php print $day['date'] ?> <?php print $time_str; ?> "> <?php print $time_str; ?> </a>
                      </div>
                        
                      <?php endif; ?>
                    <?php endif; ?>
                    <?php endforeach; ?>

                  <?php $start += 1; $i += 1; endwhile;?>
                  </div>
              </td>
              <?php else: ?>
                <td class="agreservations-calendar-agenda-items <?php print $weekend; ?>">
                  <table>
                  <?php $start = 8;$i = 0; while($i < 15):?>
                    <?php 
                      $time_str = $start . ":00";
                    ?>
                    <tr>
                      <td>
                      <a class="agrcelllink" style = "text-align:center;" href="<?php print(base_path()); ?>node/add/agreservation?&agres_sel_unit=<?php print $unit->nid ?>&default_agres_title=Reservation&default_agres_date=<?php print$day['date'] ?> <?php print $time_str; ?> "> <?php print $time_str; ?> </a>
                      </td>
                    </tr>
                  <?php $start += 1; $i += 1; endwhile;?>
                  </table>
                  <?php //print ($day['datebox']); ?>
                </td>
              <?php endif; ?>
            <?php endforeach; ?>
          </tr>
        <?php endforeach; ?>
      </tbody>
    </table>
  </div>
</div>
