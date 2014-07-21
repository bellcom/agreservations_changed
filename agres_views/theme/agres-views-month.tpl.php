<?php
/**
 * @file
 * Template to display a view as a calendar month.
 *
 * @see template_preprocess_calendar_month.
 * agdaysresitems agreservations
 * $day_names: An array of the day of week names for the table header.
 * $rows: An array of data for each day of the week.
 * $view: The view.
 * $calendar_links: Array of formatted links to other calendar displays - year, month, week, day.
 * $display_type: year, month, day, or week.
 * $block: Whether or not this calendar is in a block.
 * $min_date_formatted: The minimum date for this calendar in the format YYYY-MM-DD HH:MM:SS.
 * $max_date_formatted: The maximum date for this calendar in the format YYYY-MM-DD HH:MM:SS.
 * $date_id: a css id that is unique for this date,
 *   it is in the form: calendar-nid-field_name-delta
 *
 */
//dsm('Display: '. $display_type .': '. $min_date_formatted .' to '. $max_date_formatted);
//dpm($agmonth_rows);
?>
<div class="agreservations-calendar"><div class="month-view">
    <table class="agreservations-table"  style="table-layout:fixed">
      <colgroup>
        <col width="20px">
        <?php foreach ((array) $units as $unit): ?>
        <col width="40px" >
        <?php endforeach; ?>
      </colgroup>
      <tr>
          <th>Dato</th>
        <?php foreach ((array) $units as $unit): ?>
          <th class="agreservations-calendar unitname" style="font-size:14px;">
           <?php  print(l(t($unit->title), 'node/'.$unit->nid, array('attributes' => array('class' => array('agr_unitlink','agr_unitlink2')))) )?>
          </th>
        <?php endforeach; ?>
      </tr>

      <?php foreach ((array) $agmonth_rows[$unit->title] as $no => $roomrow): ?>
      <?php if (!empty($roomrow['datebox'])) : ?>

      <tr>
        <?php $weekend = "";
              if (date('D',strtotime($roomrow['date'])) == 'Sat' || date('D',strtotime($roomrow['date'])) == 'Sun')
              $weekend = "weekend";
        ?>
          <td style="text-align: center" class="<?php print $weekend; ?>">
            <?php if (date('D',strtotime($roomrow['date'])) == 'Mon'):?>
            <?php print "<span style='float:left'>Uge " . date('W',strtotime($roomrow['date'])) . '</span>'; ?>
            <?php endif;?>
            <?php print($roomrow['datebox']); ?>

          </td>
        <?php foreach ((array) $units as $unit): ?>
        <?php $roomrow = $agmonth_rows[$unit->title][$no]; ?>
        <td class="<?php print $weekend; ?>">
          <?php if (!empty($roomrow['data'])) : ?>
          
              <?php foreach ((array) $roomrow['data'] as $key => $roomrowres): ?>
                  <?php if ($roomrowres !== '***busy***') : ?>
                      <?php $tmpres = node_load($key);
                      $tmpres_date = '';
                      $tmpres_date = field_view_field('node', $tmpres, 'field_agres_rdate');
                      $tiptext = $tmpres->title.': '.strip_tags($tmpres_date[0]['#markup']); 
                      ?>
                    <div class="beautytips"<?php print("title=".'"'.$tiptext.'"'); ?>>
                      <?php print($roomrowres); ?>
                    </div>

                  <?php endif; ?>
                <?php endforeach; ?>
              <div>
                  <a href="/agres_view/day/<?php print $roomrow['date'];?>">Mere info</a>
              </div>
          <?php else: ?>
            <?php //if (date('D',strtotime($roomrow['date'])) !== 'Sat'): ?>
             <?php  print(l( "&nbsp;", 'node/add/agreservation', array('html'=>true,'query' => array('agres_sel_unit'=>$unit->nid,'default_agres_title' => 'Reservation','default_agres_date'=>$roomrow['date'] . ' 10:00'),'attributes' => array('class' => array('agrcelllink')))) )?>
           <?php //endif; ?>
          <?php endif; ?>
        </td>
        <?php endforeach; ?>
      </tr>
       <?php endif; ?>
      <?php endforeach; ?>
    </table>
    
  </div>
</div>
