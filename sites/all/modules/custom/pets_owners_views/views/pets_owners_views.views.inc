<?php
/**
 * @file
 *
 * Views integration for the pets_owners_views module
 */


/**
 * Implements hook_views_data().
 */
function pets_owners_views_views_data() {
  $table = array();

  $table['pets_owners_storage_submissions']['table']['group'] = t('Pets Owners Table');
  $table['pets_owners_storage_submissions']['table']['base'] = array(
    'field' => 'pets_owners_id',
    'title' => t('Pets owners table'),
    'help' => t('Pets owners contains pets owners content'),
    'weight' => -10,
  );

  $table['pets_owners_storage_submissions']['table']['join'] = array(
    'file_managed' => array(
      'left_field' => 'fid',
      'field' => 'fid',
    ),
  );

  $table['pets_owners_storage_submissions']['id'] = array(
    'title' => t('Owner Id'),
    'help' => t('Describe of owners id field'),
    'field' => array(
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort'
    ),
  );

  $table['pets_owners_storage_submissions']['fid'] = array(
    'title' => t('Pet owner uri'),
    'help' => t('Pet owner custom table uri field'),
    'relationship' => array(
      'base' => 'file_managed',
      'base field' => 'fid',
      'handler' => 'views_handler_relationship',
      'label' => t('Default label for the relationship'),
      'title' => t('Title shown when adding the relationship'),
      'help' => t('More information on this relationship'),
    ),
  );

  $table['pets_owners_storage_submissions']['name'] = array(
    'title' => t('Pet owner name'),
    'help' => t('Pet owner custom table name field'),
    'field' => array(
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort'
    ),
  );

  $table['pets_owners_storage_submissions']['title'] = array(
    'title' => t('Pet owner title'),
    'help' => t('Pet owner custom table title field'),
    'field' => array(
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort'
    ),
  );

  $table['pets_owners_storage_submissions']['gender'] = array(
    'title' => t('Gender field'),
    'help' => t('Gender field value is 0, 1 or 2.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['example_table']['age'] = array(
    'title' => t('Age field'),
    'help' => t('Age field.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $table['pets_owners_storage_submissions']['email'] = array(
    'title' => t('Pet owner email'),
    'help' => t('Pet owner custom table email field'),
    'field' => array(
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort'
    ),
  );

  $table['pets_owners_storage_submissions']['country'] = array(
    'title' => t('Pet owner country'),
    'help' => t('Pet owner custom table country field'),
    'field' => array(
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort'
    ),
  );

  $table['pets_owners_storage_submissions']['pet_name'] = array(
    'title' => t('Pet owner pet name'),
    'help' => t('Pet owner custom table pet name field'),
    'field' => array(
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort'
    ),
  );

  return $table;
}

/**
 * Implements hook_views_data_alter().
 *
 * @param array $data
 */
function pets_owners_views_views_data_alter(&$data) {
  $data['pets_owners_storage_submissions']['gender']['filter']['handler'] = 'pets_owners_views_filter_by_gender';
//  dpm($data);
  $data['file_managed']['uri']['field']['handler'] = 'pets_owners_views_field_image';
  $data['field_data_field_ep_product_type']['field_ep_product_type_target_id']['filter']['handler'] = 'pets_owners_views_product_type_field';
}
