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
    <div>
      <div class="passed"></div>
    </div>
    <table class="agreservations-table">
      <tr>
        <th class="agreservations-calendar"><?php print "Uge " . date('W',strtotime($rows[0]['date'])) . '</span>'; ?></th>
        <?php foreach ($rows as $diw => $day): ?>
          <th class="agreservations-calendar">
            <?php print '<a href ="/agres_view/day/'.$day['date'] . '">'.t(date('D',strtotime($day['date']))). " ". date('d.m.Y',strtotime($day['date'])). '</a>'; ?>
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

          <?php
            foreach ($rows as $diw => $day) {
              $weekend = "";
              $sat = (date('D',strtotime($day['date'])) == 'Sat');
              $sun = (date('D',strtotime($day['date'])) == 'Sun');

              // Sat and sun start at 10 to 21 (22 included), other weekend days start 16 to 21 (22 included)
              if ($sat || $sun) {
                $weekend = "weekend";
                $start = 10;
                $h = 12;
              }
              else {
                $start = 16;
                $h = 6;
              }

              $i = 0;

              // If there are booking for the day
              if (count($day['items']) > 0) {
                print "<td class='agreservations-calendar-agenda-items ". $weekend . "'>";
                print "<div>";

                // loop in the hours.
                while ($i < $h) {
                  $rowspan = 1;
                  if(strlen($start) == 1) {
                    $time_str = '0'.$start.".00";
                  }
                  else {
                    $time_str = $start . ".00";
                  }

                  $booking = array();

                  foreach ($day['night'][$unit->title] as $itemnid => $unitbookings) {

                    if (isset($day['night'][$unit->title][$itemnid])) {

                      $node = node_load($itemnid);
                      $field_start = field_get_items('node',$node,'field_agres_rdate');
                      $tmp_start = new DateTime($field_start[0]['value'], new DateTimeZone($field_start[0]['timezone_db']));
                      $tmp_start->setTimezone(new DateTimeZone('Europe/Copenhagen'));
                      $tmp_end = new DateTime($field_start[0]['value2'], new DateTimeZone($field_start[0]['timezone_db']));
                      $tmp_end->setTimezone(new DateTimeZone('Europe/Copenhagen'));
                      $field_start_h = date('H',strtotime($tmp_start->format('Y-m-d H.i.s')));
                      $field_end_h = date('H',strtotime($tmp_end->format('Y-m-d H.i.s')));
                      $field_end_m = date('i',strtotime($field_start[0]['value2']));

                      $rowspan = $field_end_h - $field_start_h;

                      if ((integer)$field_end_m > 0) {
                        $rowspan += 1;
                        $field_end_h += 1;
                      }

                      if ($field_start_h == $start) {
                        $booking = array(
                          'nid' => $itemnid,
                          'start_h' => $field_start_h,
                          'end_h' => $field_end_h,
                          'rowspan' => $rowspan,
                        );
                        }
                    }
                  } // end foreach

                  if (empty($booking)) {
                    print '<div style="border-top: 1px solid #ccc;border-collapse: collapse; border-spacing: 0;">';
                    print '<a class="agrcelllink" style = "text-align:center;" href="' . base_path() . 'node/add/agreservation?&agres_sel_unit=' . $unit->nid .
                    '&default_agres_title=Reservation&default_agres_date=' . $day['date'] . $time_str . ' ">' . $time_str . '</a>';
                    print '</div>';
                    $rpan = 1;
                  }
                  else {
                    print '<div class="agreservations-calendar-agenda-items"';
                    $rows_pan = isset($spaninfo[$unit->title][$itemnid]) ? $spaninfo[$unit->title][$booking['nid']] : '';
                    print 'rowspan="' . $rows_pan . '">';
                    print $day['night'][$unit->title][$booking['nid']];
                    print '</div>';
                    $rpan = $booking['rowspan'];
                  }
                  $start += $rpan;
                  $i += $rpan;
                } // end while.
                print "
                  </div>
              </td>";
            } // end if count($day['items']) > 0

            else {
              print '<td class="agreservations-calendar-agenda-items ' . $weekend . '">';
              print  '<table>';

              // Sat and sun start at 10 to 21 (22 included), other weekend days start 16 to 21 (22 included)
              if ($sat || $sun) {
                $weekend = "weekend";
                $start = 10;
                $h = 12;
              }
              else {
                $start = 16;
                $h = 6;
              }
              $i = 0;
              // Empty days.
              while($i < $h) {

                $time_str = $start . ".00";

                print '<tr>
                      <td>';
                print '<a class="agrcelllink" style = "text-align:center;" href="' . base_path() . 'node/add/agreservation?&agres_sel_unit=' . $unit->nid .
                '&default_agres_title=Reservation&default_agres_date=' . $day['date'] . $time_str . '">' . $time_str . '</a>';
                print '</td>
                    </tr>';
                $start += 1;
                $i += 1;
              } // end while
            print '</table>
                </td>';
            }
          } // end foreach
          ?>
        </tr>
      <?php endforeach; ?>
      </tbody>
    </table>
  </div>
</div>
