<?php
/**
 * @file
 */

/**
 * Implements function pets_owners_storage_table().
 */
function pets_owners_storage_page_table() {
  $args = drupal_get_query_parameters();
//  dpm($args);
  $cid = 'pets_owners_storage_cache_dashboard';
  if (isset($args['page']) && !isset($args['sort']) && !isset($args['order'])) {
    $cid = "pets_owners_storage_cache_page_" . $args['page'];
  }
  elseif (!isset($args['page']) && isset($args['sort']) && isset($args['order'])) {
    $cid = "pets_owners_storage_cache_page_" . "_" . $args['sort'] . "_" . $args['order'];
  }
  elseif (isset($args['page']) && isset($args['sort']) && isset($args['order'])) {
    $cid = "pets_owners_storage_cache_page_" . $args['page'] . "_" . $args['sort'] . "_" . $args['order'];
  }


  $cache = cache_get($cid, 'cache_pets_owners_storage');

  if ($cache != FALSE) {
    dpm("cache");
    $build = $cache->data;
  }

  if (empty($build)) {
    dpm("no cache");
    $header = array(
      array('data' => t('ID'), 'field' => 'pt.id'),
      array('data' => t('Name'), 'field' => 'pt.name'),
      array('data' => t('Title'), 'field' => 'pt.title'),
      array('data' => t('Gender'), 'field' => 'pt.gender'),
      array('data' => t('Other gender'), 'field' => 'pt.other_gender'),
      array('data' => t('Age'), 'field' => 'pt.age'),
      array('data' => t('Hobby'), 'field' => 'pt.hobby'),
      array('data' => t('email'), 'field' => 'pt.email'),
      array('data' => t('pet_name'), 'field' => 'pt.pet_name'),
      array('data' => t('pet_image')),
      array('data' => t('fid'), 'field' => 'pt.fid'),
      array('data' => t('city')),
      array('data' => t('country')),
      array('data' => ''),
      array('data' => ''),
      array('data' => ''),
    );
    $rows = array();

    $query = db_select('pets_owners_storage_submissions', 'pt');
    $query->leftJoin('file_managed', 'fm', 'pt.fid = fm.fid');
    $query = $query
      ->extend('PagerDefault')
      ->fields('pt')
      ->fields('fm')
      ->limit(3);

    $result = $query
      ->extend('TableSort')
      ->orderByHeader($header)
      ->execute();

    foreach ($result as $record) {
      $city_obj = taxonomy_term_load($record->city);
      $city_label = entity_label('taxonomy_term', $city_obj);
      $country_obj = taxonomy_term_load($record->country);
      $country_label = entity_label('taxonomy_term', $country_obj);
      $variables = array(
        'path' => $record->uri,
        'style_name' => 'pets_image_style',
        'getsize' => FALSE,
        'alt' => $record->filename,
      );

      $rows[] = array(
        array('data' => $record->id),
        array('data' => $record->name),
        array('data' => $record->title),
        array('data' => $record->gender),
        array('data' => empty($record->other_gender) ? t('N/A') : $record->other_gender),
        array('data' => $record->age,),
        array('data' => $record->hobby,),
        array('data' => $record->email,),
        array('data' => isset($record->uri) ? $record->pet_name : "N/A",),
        array('data' => isset($record->uri) ? theme('image_style', $variables) : "N/A",),
        array('data' => $record->fid,),
        array('data' => $city_label,),
        array('data' => $country_label,),
        array('data' => l(t('View'), '/pets_owners/' . $record->id . '/view')),
        array('data' => l(t('Edit'), '/pets_owners/' . $record->id . '/edit')),
        array('data' => l(t('Delete'), '/pets_owners/' . $record->id . '/delete')),
      );
    }

    $build['pager_table'] = array(
      '#theme' => 'table',
      '#header' => $header,
      '#rows' => $rows,
      '#empty' => t('There are no data found in the db'),
    );

    // Attach the pager theme.
    $build['pager_pager'] = array('#markup' => theme('pager'));
  }
  if (isset($cid)) {
    cache_set($cid, $build, 'cache_pets_owners_storage', time() + 5 * 60);
  }
  return $build;
}

/**
 * Implements callback function
 *
 * @param $id
 *
 * @return array|mixed
 */
function pets_owners_storage_page_wrapper_delete($id) {
  module_load_include('inc', 'pets_owners_storage', 'pets_owners_storage.form');

  return drupal_get_form('pets_owners_storage_delete', $id);
}

/**
 * Implements pets_owners_storage_edit_form().
 *
 * @param $id
 *
 * @return array|mixed
 */
function pets_owners_storage_page_edit_form($id) {
  module_load_include('inc', 'pets_owners', 'pets_owners.forms');
  module_load_include('inc', 'pets_owners_storage', 'pets_owners_storage.form');

  $query = db_select('pets_owners_storage_submissions', 'pt');
  $query->fields('pt');
  $result = $query
    ->condition('pt.id', $id)
    ->execute();

  if ($result->rowCount() == 1 && is_numeric($id) && intval($id)) {
    $row = $result->fetchAssoc();

    return drupal_get_form('pets_owners_form', $row);
  }

  return t("Page Not Found");
}

/**
 * Implements callback function pets_owners_storage_page_view().
 *
 * @param $id
 *
 * @return array|string
 */
function pets_owners_storage_page_view($id) {
  module_load_include('inc', 'pets_owners_storage', 'pets_owners_storage');
//  pets_owners_storage_read($id);
  $row = pets_owners_storage_read($id);
  if (is_numeric($id) && intval($id) ) {
    $output = array(
      'About pet owner' => array(
        '#theme' => 'html_tag',
        '#tag' => 'h2',
        '#value' => "Pet owner:". $row->title . $row->name,
      ),
      'information' => array(
        '#items' => array(
          "Age:" . $row->age,
          "Email:" . $row->email,
          "Hobby:" . $row->hobby,
          "Pet name:" . $row->pet_name,
        ),
        '#theme' => 'item_list',
      ),
    );
    if ($row->have_pets) {
      $output['pet_info'] = array(
        '#path' => $row->uri,
        '#style_name' => 'pet_image_style',
        '#title' => 'pet of owner',
        '#getsize' => FALSE,
        '#alt' => $row->filename,
        '#theme' => 'image_style',
      );
    }
  }
  else {
    $output = "Page Not Found";
  }
  return $output;
}
