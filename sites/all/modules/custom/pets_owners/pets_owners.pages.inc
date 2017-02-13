<?php
/**
 * @file
 *
 * Build form
 */

/**
 * Implements function wrapper_form
 * @param $current_form
 *
 * @return array|mixed
 */
function pets_owners_page($current_form) {
  module_load_include('inc', 'pets_owners', 'pets_owners.forms');
//  drupal_add_js(drupal_get_path('module', 'pets_owners') . '/pets_owners_js_validate.js');

  $arr = drupal_get_form($current_form);
  return $arr;
}

/**Implement pets_owners_page_autocomplete().
 * @param $field_name
 * @param $term_name
 */
function pets_owners_page_autocomplete($field_name, $term_name) {
  $hobby = taxonomy_vocabulary_machine_name_load($field_name);

  if ($hobby === FALSE) {
    print t('Taxonomy field @field_name not found.', array('@field_name' => $field_name));
    exit;
  }

  $tax_node = taxonomy_get_tree($hobby->vid);
  $tax_node[0]->name;
  $matches = array();

  foreach ($tax_node as $elem) {
    if (strpos(strtolower($elem->name), strtolower($term_name)) !== FALSE) {
      $matches[$elem->name] = $elem->name;
    }
  }

  drupal_json_output($matches);
}

/**
 * Implements function pets_owners_page_ajax().
 */
function pets_owners_page_ajax() {

//  $preview = array();
//  $preview['name'] = array(
//    '#type' => 'html_tag',
//    '#tag' => 'p',
//    '#value' => "Name: " .  $_POST['name'],
//  );
  if ($_POST['gender'] == 0) {
    $gender = 'male';
  }
  else if ($_POST['gender'] == 1) {
    $gender = 'female';
  }
  else {
    $gender = $_POST['other_gender'];
  }

  $items['Name'] = $_POST['name'];
  $items['Gender'] = $gender;
  $items['age'] = $_POST['age'];
  $items['hobby'] = $_POST['hobby'];
  $items['email'] = $_POST['email'];
  $items['title'] = $_POST['title'];

  $result = theme('item_list', array('items' => $items));
//  $result = drupal_render($preview);
  $commands = array();
  $commands[] = ajax_command_html('#preview-content', $result);

  return array('#type' => 'ajax', '#commands' => $commands);
}

/**
 * @return string
 */
function pets_owners_page_rand_color() {
  return '#' . str_pad(dechex(mt_rand(0, 0xFFFFFF)), 6, '0', STR_PAD_LEFT);
}

/**
 * Implements function pets_owners_colorizer().
 */
function pets_owners_page_colorizer() {
  module_load_include('inc', 'pets_owners', 'pets_owners');

  $color = pets_owners_page_rand_color();
  $commands[] = pets_owners_command_colorize($color);

  return array('#type' => 'ajax', '#commands' => $commands);
}
