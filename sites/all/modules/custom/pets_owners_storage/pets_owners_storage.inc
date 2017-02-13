<?php
/**
 * @file
 *
 * The file contains CRUD functions
 */


/**
 * Implements function for db_insert.
 *
 * @param $form_state
 * @param $file
 * The file object
 *
 */
function pets_owners_storage_create(&$form_state, &$file) {
  $id_inserted = db_insert('pets_owners_storage_submissions')
    ->fields(array(
      'name' => $form_state['values']['name'],
      'gender' => $form_state['values']['gender'],
      'other_gender' => $form_state['values']['other_gender'],
      'title' => $form_state['values']['title'],
      'age' => $form_state['values']['age'],
      'hobby' => $form_state['values']['hobby'],
      'have_pets' => $form_state['values']['question'],
      'pet_name' => $form_state['values']['petsname'],
      'country' => $form_state['values']['country'],
      'city' => $form_state['values']['city'],
      'fid' => isset($file->fid) ? $file->fid : 0,
      'email' => $form_state['values']['email'],
    ))
    ->execute();
  $form_state['values']['id'] = $id_inserted;
}

/**
 * Implements function for db_update.
 *
 * @param $form_state
 * @param $file
 * @param $check_id
 * @param $check_fid
 */
function pets_owners_storage_update(&$form_state, &$file, $check_id, $check_fid) {
  $file_object = file_load($check_fid);
  if (is_object($file_object)) {
    file_usage_delete($file_object, 'pets_owners_storage', 'pet_owner', $check_id);
    file_delete($file_object);
  }
  $id_updated = db_update('pets_owners_storage_submissions')
    ->fields(array(
      'name' => $form_state['values']['name'],
      'gender' => $form_state['values']['gender'],
      'other_gender' => $form_state['values']['other_gender'],
      'title' => $form_state['values']['title'],
      'age' => $form_state['values']['age'],
      'hobby' => $form_state['values']['hobby'],
      'have_pets' => $form_state['values']['question'],
      'pet_name' => $form_state['values']['petsname'],
      'country' => $form_state['values']['country'],
      'city' => $form_state['values']['city'],
      'fid' => isset($file->fid) ? $file->fid : 0,
      'email' => $form_state['values']['email'],
    ))
    ->condition('id', $check_id, '=')
    ->execute();
  if ($id_updated) {
    $form_state['values']['id'] = $form_state['build_info']['args'][0]['id'];
    $permanent_cache_id = "cache_pets_owners_view_id_" . $id_updated;
    drupal_static_reset($permanent_cache_id);
    cache_clear_all("*", 'cache_pets_owners_storage', TRUE);
    dpm('clear cache');
  }
}

/**
 * Implements function for db_select.
 *
 * @param $id
 *
 * @return array|mixed|string
 */
function pets_owners_storage_read($id, $reset = FALSE) {
  $permanent_cache_id = "cache_pets_owners_view_id_" . $id;

  $permanent_cache = cache_get($permanent_cache_id, 'cache');
  $cache_var = &drupal_static($permanent_cache_id);
  if ($reset) {
    $cache_var = FALSE;
  }

  if ($cache_var != NULL) {
//    dpm("static cache");
    return $cache_var;
  }
  elseif ($permanent_cache != FALSE) {
//    dpm("permanent cache");
    $cache_var = $permanent_cache->data;
    return $permanent_cache->data;
  }

  $query = db_select('pets_owners_storage_submissions', 'p');
  $query->leftJoin('file_managed', 'f', 'p.fid = f.fid');
  $result = $query
    ->fields('p')
    ->fields('f', array('uri', 'filename'))
    ->condition('id', $id, '=')
    ->execute()
    ->fetchObject();
//  dpm($result);
  $cache_var = $result;
  cache_set($permanent_cache_id, $result, 'cache', time() + 5 * 60);
  return $result;
}

/**
 * Implements function for db_delete.
 *
 * @param $id
 *
 * @return bool
 */
function pets_owners_storage_final_delete($id) {
  $query = db_select('pets_owners_storage_submissions', 'pt')
    ->fields('pt', array('fid'))
    ->condition('id', $id);
  $result = $query->execute();
  $fid = $result->fetchField();
  $file_obj = file_load($fid);

  if (is_object($file_obj)) {
    file_usage_delete($file_obj, 'pets_owners_storage', 'pet_owner', $id);
    file_delete($file_obj);
  }

  $num_deleted = db_delete('pets_owners_storage_submissions')
    ->condition('id', $id)
    ->execute();
  if ($num_deleted) {
    drupal_static_reset('cache_var');
    cache_clear_all("*", 'cache_pets_owners_storage', TRUE);
    return TRUE;
  }

  return FALSE;

}
