<?php
/**
 * @file
 * Default views for the Calendar module.
 */

/**
 * Set up so it can be used as an API to create default calendars for
 * specific date fields.
 *
 * Use variable_set() to establish criteria for default calendars.
 * Set the variable in custom modules or in settings.
 *
 * Example: Add a new default calendar to custom
 * calendars that are already configured:
 *
 * $options = variable_get('agres_views_default_view_options', array());
 * $option = array(
 *   'name' => 'example_event',
 *   'description' => 'An example event calendar for the date field.',
 *   'path' => 'example_event',
 *   'types' => array('example_content_type'),
 *   'date_fields' => array('field_example_date'),
 *   );
 * $options[] = $option;
 * variable_set('agres_views_default_view_options', $options);
 *
 */
function agres_views_views_default_views() {
  $views = array();

$view = new view();
$view->name = 'agres_view';
$view->description = 'A bookingcalendar';
$view->tag = 'agres_view';
$view->base_table = 'node';
$view->human_name = 'Booking Calendar';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'Booking Calendar';
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['use_more_text'] = 'mere';
$handler->display->display_options['link_display'] = 'page_1';
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['access']['perm'] = 'view agres_views bookingcalendar';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['query']['options']['query_comment'] = FALSE;
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['exposed_form']['options']['submit_button'] = 'Udfør';
$handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Gendan';
$handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Sortér efter';
$handler->display->display_options['exposed_form']['options']['sort_asc_label'] = 'Stigende';
$handler->display->display_options['exposed_form']['options']['sort_desc_label'] = 'Faldende';
$handler->display->display_options['pager']['type'] = 'date_views_pager';
$handler->display->display_options['pager']['options']['date_id'] = 'month';
$handler->display->display_options['style_plugin'] = 'agres_views_style';
$handler->display->display_options['style_options']['name_size'] = '3';
$handler->display->display_options['style_options']['with_weekno'] = '0';
$handler->display->display_options['style_options']['multiday_theme'] = '1';
$handler->display->display_options['style_options']['theme_style'] = '1';
$handler->display->display_options['style_options']['max_items'] = '0';
$handler->display->display_options['row_plugin'] = 'agres_views_node';
/* Felt: Indhold: Titel */
$handler->display->display_options['fields']['title']['id'] = 'title';
$handler->display->display_options['fields']['title']['table'] = 'node';
$handler->display->display_options['fields']['title']['field'] = 'title';
$handler->display->display_options['fields']['title']['label'] = '';
$handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
$handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
$handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['title']['hide_alter_empty'] = FALSE;
/* Felt: Indhold: Booking Date */
$handler->display->display_options['fields']['field_agres_rdate']['id'] = 'field_agres_rdate';
$handler->display->display_options['fields']['field_agres_rdate']['table'] = 'field_data_field_agres_rdate';
$handler->display->display_options['fields']['field_agres_rdate']['field'] = 'field_agres_rdate';
$handler->display->display_options['fields']['field_agres_rdate']['exclude'] = TRUE;
$handler->display->display_options['fields']['field_agres_rdate']['hide_alter_empty'] = FALSE;
$handler->display->display_options['fields']['field_agres_rdate']['settings'] = array(
  'format_type' => 'long',
  'fromto' => 'both',
  'multiple_number' => '',
  'multiple_from' => '',
  'multiple_to' => '',
  'show_repeat_rule' => 'show',
);
/* Felt: Indhold: Nid */
$handler->display->display_options['fields']['nid']['id'] = 'nid';
$handler->display->display_options['fields']['nid']['table'] = 'node';
$handler->display->display_options['fields']['nid']['field'] = 'nid';
/* Sorteringskriterie: Indhold: Opdateringsdato */
$handler->display->display_options['sorts']['changed']['id'] = 'changed';
$handler->display->display_options['sorts']['changed']['table'] = 'node';
$handler->display->display_options['sorts']['changed']['field'] = 'changed';
/* Filterkriterie: Indhold: Udgivet */
$handler->display->display_options['filters']['status']['id'] = 'status';
$handler->display->display_options['filters']['status']['table'] = 'node';
$handler->display->display_options['filters']['status']['field'] = 'status';
$handler->display->display_options['filters']['status']['value'] = 1;
$handler->display->display_options['filters']['status']['group'] = 0;
$handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;

/* Display: Month */
$handler = $view->new_display('page', 'Month', 'page_1');
$handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
$handler->display->display_options['defaults']['pager'] = FALSE;
$handler->display->display_options['pager']['type'] = 'date_views_pager';
$handler->display->display_options['pager']['options']['date_id'] = 'month';
$handler->display->display_options['pager']['options']['link_format'] = 'clean';
$handler->display->display_options['defaults']['style_plugin'] = FALSE;
$handler->display->display_options['style_plugin'] = 'agres_views_style';
$handler->display->display_options['style_options']['name_size'] = '3';
$handler->display->display_options['style_options']['mini'] = '0';
$handler->display->display_options['style_options']['with_weekno'] = '0';
$handler->display->display_options['style_options']['multiday_theme'] = '0';
$handler->display->display_options['style_options']['theme_style'] = '1';
$handler->display->display_options['style_options']['max_items'] = '0';
$handler->display->display_options['defaults']['style_options'] = FALSE;
$handler->display->display_options['defaults']['row_plugin'] = FALSE;
$handler->display->display_options['row_plugin'] = 'agres_views_node';
$handler->display->display_options['row_options']['colors']['legend'] = 'type';
$handler->display->display_options['row_options']['colors']['calendar_colors_type'] = array(
  'article' => '#ffffff',
  'page' => '#ffffff',
  'product' => '#ffffff',
  'agreservation' => '#ffffff',
  'agres_timeframe' => '#ffffff',
  'agreservations_unit' => '#ffffff',
  'agreservation_unit_info' => '#ffffff',
  'agres_category' => '#ffffff',
  'agres_rate' => '#ffffff',
  'agreservations_unittype' => '#ffffff',
);
$handler->display->display_options['defaults']['row_options'] = FALSE;
$handler->display->display_options['defaults']['fields'] = FALSE;
/* Felt: Indhold: Titel */
$handler->display->display_options['fields']['title']['id'] = 'title';
$handler->display->display_options['fields']['title']['table'] = 'node';
$handler->display->display_options['fields']['title']['field'] = 'title';
$handler->display->display_options['fields']['title']['label'] = '';
$handler->display->display_options['fields']['title']['exclude'] = TRUE;
$handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
$handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
$handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['title']['hide_alter_empty'] = FALSE;
/* Felt: Indhold: Booking Date */
$handler->display->display_options['fields']['field_agres_rdate']['id'] = 'field_agres_rdate';
$handler->display->display_options['fields']['field_agres_rdate']['table'] = 'field_data_field_agres_rdate';
$handler->display->display_options['fields']['field_agres_rdate']['field'] = 'field_agres_rdate';
$handler->display->display_options['fields']['field_agres_rdate']['exclude'] = TRUE;
$handler->display->display_options['fields']['field_agres_rdate']['hide_alter_empty'] = FALSE;
$handler->display->display_options['fields']['field_agres_rdate']['settings'] = array(
  'format_type' => 'long',
  'fromto' => 'both',
  'multiple_number' => '',
  'multiple_from' => '',
  'multiple_to' => '',
  'show_repeat_rule' => 'show',
);
/* Felt: Indhold: Nid */
$handler->display->display_options['fields']['nid']['id'] = 'nid';
$handler->display->display_options['fields']['nid']['table'] = 'node';
$handler->display->display_options['fields']['nid']['field'] = 'nid';
$handler->display->display_options['fields']['nid']['label'] = '';
$handler->display->display_options['fields']['nid']['exclude'] = TRUE;
$handler->display->display_options['fields']['nid']['alter']['alter_text'] = TRUE;
$handler->display->display_options['fields']['nid']['alter']['text'] = 'N:[nid]';
$handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['nid']['link_to_node'] = TRUE;
/* Felt: Indhold: Order_id */
$handler->display->display_options['fields']['field_agres_orderid']['id'] = 'field_agres_orderid';
$handler->display->display_options['fields']['field_agres_orderid']['table'] = 'field_data_field_agres_orderid';
$handler->display->display_options['fields']['field_agres_orderid']['field'] = 'field_agres_orderid';
$handler->display->display_options['fields']['field_agres_orderid']['label'] = '';
$handler->display->display_options['fields']['field_agres_orderid']['alter']['alter_text'] = TRUE;
$handler->display->display_options['fields']['field_agres_orderid']['alter']['text'] = 'O:[field_agres_orderid]';
$handler->display->display_options['fields']['field_agres_orderid']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['field_agres_orderid']['type'] = 'number_unformatted';
$handler->display->display_options['fields']['field_agres_orderid']['settings'] = array(
  'thousand_separator' => ' ',
  'prefix_suffix' => 1,
);
/* Felt: Global: Tilpasset tekst */
$handler->display->display_options['fields']['nothing']['id'] = 'nothing';
$handler->display->display_options['fields']['nothing']['table'] = 'views';
$handler->display->display_options['fields']['nothing']['field'] = 'nothing';
$handler->display->display_options['fields']['nothing']['label'] = '';
$handler->display->display_options['fields']['nothing']['alter']['text'] = '[title] - [field_agres_rdate] ';
$handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
$handler->display->display_options['defaults']['arguments'] = FALSE;
/* Kontekstuelt filter: Dato: Dato (node) */
$handler->display->display_options['arguments']['date_argument']['id'] = 'date_argument';
$handler->display->display_options['arguments']['date_argument']['table'] = 'node';
$handler->display->display_options['arguments']['date_argument']['field'] = 'date_argument';
$handler->display->display_options['arguments']['date_argument']['default_action'] = 'default';
$handler->display->display_options['arguments']['date_argument']['exception']['title'] = 'Alle';
$handler->display->display_options['arguments']['date_argument']['default_argument_type'] = 'date';
$handler->display->display_options['arguments']['date_argument']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['date_argument']['add_delta'] = 'yes';
$handler->display->display_options['arguments']['date_argument']['date_fields'] = array(
  'field_data_field_agres_rdate.field_agres_rdate_value' => 'field_data_field_agres_rdate.field_agres_rdate_value',
  'field_data_field_agres_rdate.field_agres_rdate_value2' => 'field_data_field_agres_rdate.field_agres_rdate_value2',
);
$handler->display->display_options['arguments']['date_argument']['date_method'] = 'AND';
$handler->display->display_options['path'] = 'agres_view/month';
$handler->display->display_options['menu']['type'] = 'default tab';
$handler->display->display_options['menu']['title'] = 'Month';
$handler->display->display_options['menu']['description'] = 'A booking Calendar';
$handler->display->display_options['menu']['weight'] = '0';
$handler->display->display_options['menu']['name'] = 'main-menu';
$handler->display->display_options['menu']['context'] = 0;
$handler->display->display_options['tab_options']['type'] = 'normal';
$handler->display->display_options['tab_options']['title'] = 'Booking Calendar';
$handler->display->display_options['tab_options']['weight'] = '0';
$handler->display->display_options['tab_options']['name'] = 'main-menu';

/* Display: Week */
$handler = $view->new_display('page', 'Week', 'page_2');
$handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
$handler->display->display_options['defaults']['pager'] = FALSE;
$handler->display->display_options['pager']['type'] = 'date_views_pager';
$handler->display->display_options['pager']['options']['date_id'] = 'week';
$handler->display->display_options['pager']['options']['link_format'] = 'clean';
$handler->display->display_options['defaults']['style_plugin'] = FALSE;
$handler->display->display_options['style_plugin'] = 'agres_views_style';
$handler->display->display_options['style_options']['name_size'] = '3';
$handler->display->display_options['style_options']['mini'] = '0';
$handler->display->display_options['style_options']['with_weekno'] = '0';
$handler->display->display_options['style_options']['multiday_theme'] = '1';
$handler->display->display_options['style_options']['theme_style'] = '0';
$handler->display->display_options['style_options']['max_items'] = '0';
$handler->display->display_options['style_options']['agres_views_type'] = 'week';
$handler->display->display_options['defaults']['style_options'] = FALSE;
$handler->display->display_options['defaults']['row_plugin'] = FALSE;
$handler->display->display_options['row_plugin'] = 'agres_views_node';
$handler->display->display_options['defaults']['row_options'] = FALSE;
$handler->display->display_options['defaults']['fields'] = FALSE;
/* Felt: Indhold: Titel */
$handler->display->display_options['fields']['title']['id'] = 'title';
$handler->display->display_options['fields']['title']['table'] = 'node';
$handler->display->display_options['fields']['title']['field'] = 'title';
$handler->display->display_options['fields']['title']['label'] = '';
$handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
$handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
$handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['title']['hide_alter_empty'] = FALSE;
/* Felt: Indhold: Booking Date */
$handler->display->display_options['fields']['field_agres_rdate']['id'] = 'field_agres_rdate';
$handler->display->display_options['fields']['field_agres_rdate']['table'] = 'field_data_field_agres_rdate';
$handler->display->display_options['fields']['field_agres_rdate']['field'] = 'field_agres_rdate';
$handler->display->display_options['fields']['field_agres_rdate']['label'] = '';
$handler->display->display_options['fields']['field_agres_rdate']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['field_agres_rdate']['hide_alter_empty'] = FALSE;
$handler->display->display_options['fields']['field_agres_rdate']['settings'] = array(
  'format_type' => 'short',
  'fromto' => 'both',
  'multiple_number' => '',
  'multiple_from' => '',
  'multiple_to' => '',
);
/* Felt: Indhold: Nid */
$handler->display->display_options['fields']['nid']['id'] = 'nid';
$handler->display->display_options['fields']['nid']['table'] = 'node';
$handler->display->display_options['fields']['nid']['field'] = 'nid';
$handler->display->display_options['fields']['nid']['label'] = '';
$handler->display->display_options['fields']['nid']['exclude'] = TRUE;
$handler->display->display_options['fields']['nid']['alter']['alter_text'] = TRUE;
$handler->display->display_options['fields']['nid']['alter']['text'] = 'N:[nid]';
$handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['nid']['link_to_node'] = TRUE;
/* Felt: Indhold: Order_id */
$handler->display->display_options['fields']['field_agres_orderid']['id'] = 'field_agres_orderid';
$handler->display->display_options['fields']['field_agres_orderid']['table'] = 'field_data_field_agres_orderid';
$handler->display->display_options['fields']['field_agres_orderid']['field'] = 'field_agres_orderid';
$handler->display->display_options['fields']['field_agres_orderid']['label'] = '';
$handler->display->display_options['fields']['field_agres_orderid']['alter']['alter_text'] = TRUE;
$handler->display->display_options['fields']['field_agres_orderid']['alter']['text'] = 'O:[field_agres_orderid] ';
$handler->display->display_options['fields']['field_agres_orderid']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['field_agres_orderid']['settings'] = array(
  'thousand_separator' => ' ',
  'prefix_suffix' => 0,
);
$handler->display->display_options['defaults']['arguments'] = FALSE;
/* Kontekstuelt filter: Dato: Dato (node) */
$handler->display->display_options['arguments']['date_argument']['id'] = 'date_argument';
$handler->display->display_options['arguments']['date_argument']['table'] = 'node';
$handler->display->display_options['arguments']['date_argument']['field'] = 'date_argument';
$handler->display->display_options['arguments']['date_argument']['default_action'] = 'default';
$handler->display->display_options['arguments']['date_argument']['exception']['title'] = 'Alle';
$handler->display->display_options['arguments']['date_argument']['default_argument_type'] = 'date';
$handler->display->display_options['arguments']['date_argument']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['date_argument']['granularity'] = 'week';
$handler->display->display_options['arguments']['date_argument']['add_delta'] = 'yes';
$handler->display->display_options['arguments']['date_argument']['date_fields'] = array(
  'field_data_field_agres_rdate.field_agres_rdate_value' => 'field_data_field_agres_rdate.field_agres_rdate_value',
  'field_data_field_agres_rdate.field_agres_rdate_value2' => 'field_data_field_agres_rdate.field_agres_rdate_value2',
);
$handler->display->display_options['arguments']['date_argument']['date_method'] = 'AND';
$handler->display->display_options['path'] = 'agres_view/week';
$handler->display->display_options['menu']['type'] = 'tab';
$handler->display->display_options['menu']['title'] = 'Week';
$handler->display->display_options['menu']['weight'] = '2';
$handler->display->display_options['menu']['context'] = 0;

/* Display: Day */
$handler = $view->new_display('page', 'Day', 'page_3');
$handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
$handler->display->display_options['defaults']['pager'] = FALSE;
$handler->display->display_options['pager']['type'] = 'date_views_pager';
$handler->display->display_options['pager']['options']['date_id'] = 'day';
$handler->display->display_options['defaults']['style_plugin'] = FALSE;
$handler->display->display_options['style_plugin'] = 'agres_views_style';
$handler->display->display_options['style_options']['name_size'] = '3';
$handler->display->display_options['style_options']['mini'] = '0';
$handler->display->display_options['style_options']['with_weekno'] = '0';
$handler->display->display_options['style_options']['multiday_theme'] = '0';
$handler->display->display_options['style_options']['theme_style'] = '0';
$handler->display->display_options['style_options']['max_items'] = '0';
$handler->display->display_options['style_options']['agres_views_type'] = 'day';
$handler->display->display_options['defaults']['style_options'] = FALSE;
$handler->display->display_options['defaults']['row_plugin'] = FALSE;
$handler->display->display_options['row_plugin'] = 'agres_views_node';
$handler->display->display_options['defaults']['row_options'] = FALSE;
$handler->display->display_options['defaults']['fields'] = FALSE;
/* Felt: Indhold: Titel */
$handler->display->display_options['fields']['title']['id'] = 'title';
$handler->display->display_options['fields']['title']['table'] = 'node';
$handler->display->display_options['fields']['title']['field'] = 'title';
$handler->display->display_options['fields']['title']['label'] = '';
$handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
$handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
$handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['title']['hide_alter_empty'] = FALSE;
/* Felt: Indhold: Booking Date */
$handler->display->display_options['fields']['field_agres_rdate']['id'] = 'field_agres_rdate';
$handler->display->display_options['fields']['field_agres_rdate']['table'] = 'field_data_field_agres_rdate';
$handler->display->display_options['fields']['field_agres_rdate']['field'] = 'field_agres_rdate';
$handler->display->display_options['fields']['field_agres_rdate']['label'] = '';
$handler->display->display_options['fields']['field_agres_rdate']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['field_agres_rdate']['hide_alter_empty'] = FALSE;
$handler->display->display_options['fields']['field_agres_rdate']['settings'] = array(
  'format_type' => 'short',
  'fromto' => 'both',
  'multiple_number' => '',
  'multiple_from' => '',
  'multiple_to' => '',
);
/* Felt: Indhold: Nid */
$handler->display->display_options['fields']['nid']['id'] = 'nid';
$handler->display->display_options['fields']['nid']['table'] = 'node';
$handler->display->display_options['fields']['nid']['field'] = 'nid';
$handler->display->display_options['fields']['nid']['label'] = '';
$handler->display->display_options['fields']['nid']['exclude'] = TRUE;
$handler->display->display_options['fields']['nid']['alter']['alter_text'] = TRUE;
$handler->display->display_options['fields']['nid']['alter']['text'] = 'N:[nid]';
$handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['nid']['link_to_node'] = TRUE;
/* Felt: Indhold: Order_id */
$handler->display->display_options['fields']['field_agres_orderid']['id'] = 'field_agres_orderid';
$handler->display->display_options['fields']['field_agres_orderid']['table'] = 'field_data_field_agres_orderid';
$handler->display->display_options['fields']['field_agres_orderid']['field'] = 'field_agres_orderid';
$handler->display->display_options['fields']['field_agres_orderid']['label'] = '';
$handler->display->display_options['fields']['field_agres_orderid']['alter']['alter_text'] = TRUE;
$handler->display->display_options['fields']['field_agres_orderid']['alter']['text'] = 'O:[field_agres_orderid]';
$handler->display->display_options['fields']['field_agres_orderid']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['field_agres_orderid']['settings'] = array(
  'thousand_separator' => ' ',
  'prefix_suffix' => 0,
);
$handler->display->display_options['defaults']['arguments'] = FALSE;
/* Kontekstuelt filter: Dato: Dato (node) */
$handler->display->display_options['arguments']['date_argument']['id'] = 'date_argument';
$handler->display->display_options['arguments']['date_argument']['table'] = 'node';
$handler->display->display_options['arguments']['date_argument']['field'] = 'date_argument';
$handler->display->display_options['arguments']['date_argument']['default_action'] = 'default';
$handler->display->display_options['arguments']['date_argument']['exception']['title'] = 'Alle';
$handler->display->display_options['arguments']['date_argument']['default_argument_type'] = 'date';
$handler->display->display_options['arguments']['date_argument']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['date_argument']['granularity'] = 'day';
$handler->display->display_options['arguments']['date_argument']['date_fields'] = array(
  'field_data_field_agres_rdate.field_agres_rdate_value' => 'field_data_field_agres_rdate.field_agres_rdate_value',
  'field_data_field_agres_rdate.field_agres_rdate_value2' => 'field_data_field_agres_rdate.field_agres_rdate_value2',
);
$handler->display->display_options['arguments']['date_argument']['date_method'] = 'AND';
$handler->display->display_options['path'] = 'agres_view/day';
$handler->display->display_options['menu']['type'] = 'tab';
$handler->display->display_options['menu']['title'] = 'Day';
$handler->display->display_options['menu']['weight'] = '3';
$handler->display->display_options['menu']['context'] = 0;

/* Display: Year */
$handler = $view->new_display('page', 'Year', 'page');
$handler->display->display_options['enabled'] = FALSE;
$handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
$handler->display->display_options['defaults']['pager'] = FALSE;
$handler->display->display_options['pager']['type'] = 'date_views_pager';
$handler->display->display_options['pager']['options']['date_id'] = 'year';
$handler->display->display_options['defaults']['style_plugin'] = FALSE;
$handler->display->display_options['style_plugin'] = 'agres_views_style';
$handler->display->display_options['style_options']['name_size'] = '1';
$handler->display->display_options['style_options']['mini'] = '0';
$handler->display->display_options['style_options']['with_weekno'] = '0';
$handler->display->display_options['style_options']['multiday_theme'] = '1';
$handler->display->display_options['style_options']['theme_style'] = '1';
$handler->display->display_options['style_options']['max_items'] = '0';
$handler->display->display_options['style_options']['agres_views_type'] = 'year';
$handler->display->display_options['defaults']['style_options'] = FALSE;
$handler->display->display_options['defaults']['row_plugin'] = FALSE;
$handler->display->display_options['row_plugin'] = 'agres_views_node';
$handler->display->display_options['defaults']['row_options'] = FALSE;
$handler->display->display_options['defaults']['arguments'] = FALSE;
/* Kontekstuelt filter: Dato: Dato (node) */
$handler->display->display_options['arguments']['date_argument']['id'] = 'date_argument';
$handler->display->display_options['arguments']['date_argument']['table'] = 'node';
$handler->display->display_options['arguments']['date_argument']['field'] = 'date_argument';
$handler->display->display_options['arguments']['date_argument']['default_action'] = 'default';
$handler->display->display_options['arguments']['date_argument']['exception']['title'] = 'Alle';
$handler->display->display_options['arguments']['date_argument']['default_argument_type'] = 'date';
$handler->display->display_options['arguments']['date_argument']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['date_argument']['granularity'] = 'year';
$handler->display->display_options['arguments']['date_argument']['add_delta'] = 'yes';
$handler->display->display_options['arguments']['date_argument']['date_fields'] = array(
  'node.changed' => 'node.changed',
);
$handler->display->display_options['path'] = 'agres_view/year';
$handler->display->display_options['menu']['type'] = 'tab';
$handler->display->display_options['menu']['title'] = 'Year';
$handler->display->display_options['menu']['weight'] = '4';
$handler->display->display_options['menu']['context'] = 0;

/* Display: Block */
$handler = $view->new_display('block', 'Block', 'block_1');
$handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
$handler->display->display_options['defaults']['pager'] = FALSE;
$handler->display->display_options['pager']['type'] = 'date_views_pager';
$handler->display->display_options['pager']['options']['date_id'] = 'mini';
$handler->display->display_options['defaults']['style_plugin'] = FALSE;
$handler->display->display_options['style_plugin'] = 'agres_views_style';
$handler->display->display_options['style_options']['name_size'] = '1';
$handler->display->display_options['style_options']['mini'] = '1';
$handler->display->display_options['style_options']['with_weekno'] = '0';
$handler->display->display_options['style_options']['multiday_theme'] = '1';
$handler->display->display_options['style_options']['theme_style'] = '1';
$handler->display->display_options['style_options']['max_items'] = '0';
$handler->display->display_options['defaults']['style_options'] = FALSE;
$handler->display->display_options['defaults']['row_plugin'] = FALSE;
$handler->display->display_options['row_plugin'] = 'agres_views_node';
$handler->display->display_options['defaults']['row_options'] = FALSE;
$handler->display->display_options['defaults']['arguments'] = FALSE;
/* Kontekstuelt filter: Dato: Dato (node) */
$handler->display->display_options['arguments']['date_argument']['id'] = 'date_argument';
$handler->display->display_options['arguments']['date_argument']['table'] = 'node';
$handler->display->display_options['arguments']['date_argument']['field'] = 'date_argument';
$handler->display->display_options['arguments']['date_argument']['default_action'] = 'default';
$handler->display->display_options['arguments']['date_argument']['exception']['title'] = 'Alle';
$handler->display->display_options['arguments']['date_argument']['default_argument_type'] = 'date';
$handler->display->display_options['arguments']['date_argument']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['date_argument']['add_delta'] = 'yes';
$handler->display->display_options['arguments']['date_argument']['date_fields'] = array(
  'node.changed' => 'node.changed',
);

/* Display: Upcoming */
$handler = $view->new_display('block', 'Upcoming', 'block_2');
$handler->display->display_options['display_description'] = 'Upcoming events block';
$handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
$handler->display->display_options['defaults']['pager'] = FALSE;
$handler->display->display_options['pager']['type'] = 'some';
$handler->display->display_options['pager']['options']['items_per_page'] = '5';
$handler->display->display_options['pager']['options']['offset'] = '0';
$handler->display->display_options['defaults']['style_plugin'] = FALSE;
$handler->display->display_options['style_plugin'] = 'list';
$handler->display->display_options['defaults']['style_options'] = FALSE;
$handler->display->display_options['defaults']['row_plugin'] = FALSE;
$handler->display->display_options['row_plugin'] = 'fields';
$handler->display->display_options['defaults']['row_options'] = FALSE;
$handler->display->display_options['defaults']['filter_groups'] = FALSE;
$handler->display->display_options['defaults']['filters'] = FALSE;
/* Filterkriterie: Indhold: Udgivet */
$handler->display->display_options['filters']['status']['id'] = 'status';
$handler->display->display_options['filters']['status']['table'] = 'node';
$handler->display->display_options['filters']['status']['field'] = 'status';
$handler->display->display_options['filters']['status']['value'] = 1;
$handler->display->display_options['filters']['status']['group'] = 0;
$handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
/* Filterkriterie: Dato: Dato (node) */
$handler->display->display_options['filters']['date_filter']['id'] = 'date_filter';
$handler->display->display_options['filters']['date_filter']['table'] = 'node';
$handler->display->display_options['filters']['date_filter']['field'] = 'date_filter';
$handler->display->display_options['filters']['date_filter']['operator'] = '>=';
$handler->display->display_options['filters']['date_filter']['default_date'] = 'now';
$handler->display->display_options['filters']['date_filter']['add_delta'] = 'yes';
$handler->display->display_options['filters']['date_filter']['date_fields'] = array(
  'node.changed' => 'node.changed',
);
$translatables['agres_view'] = array(
  t('Master'),
  t('Booking Calendar'),
  t('mere'),
  t('Udfør'),
  t('Gendan'),
  t('Sortér efter'),
  t('Stigende'),
  t('Faldende'),
  t('Booking Date'),
  t('Nid'),
  t('Month'),
  t('N:[nid]'),
  t('O:[field_agres_orderid]'),
  t('[title] - [field_agres_rdate] '),
  t('Alle'),
  t('Week'),
  t('O:[field_agres_orderid] '),
  t('Day'),
  t('Year'),
  t('Block'),
  t('Upcoming'),
  t('Upcoming events block'),
);

 $views['agres_view'] = $view;
  return $views;
}
