<?php
/**
 * @file
 * File with functions for delete records.
 */


/**
 * Implements function pets_owners_storage_delete().
 *
 * @param $id
 *
 * @return string
 */
function pets_owners_storage_delete($form, &$form_state, $id) {

  return confirm_form(
    $form,
    t("Do you really want delete this record @id", array("@id" => $id)),
    "pets_owners/dashboard",
    t('This action cannot be undone.'),
    t("Delete"), t("Cancel")
  );
}

/**
 * Implements pets_owners_storage_button_delete().
 *
 * @param $form
 * @param $form_state
 */
function pets_owners_storage_button_delete($form, &$form_state) {
  $id = $form_state['build_info']['args'][0];
  $form_state['redirect'] = 'pets_owners/' . $id['id'] . '/delete';
}

/**
 * Implements pets_owners_storage_delete_submit().
 *
 * @param $form
 * @param $form_state
 */
function pets_owners_storage_delete_submit($form, &$form_state) {
  $id = $form_state['build_info']['args'][0];
  module_load_include('inc', 'pets_owners_storage', 'pets_owners_storage');
  $deleted = pets_owners_storage_final_delete($id);
  if ($deleted) {
    drupal_set_message(t("The record with id @id is deleted", array('@id' => $id)));
    $form_state['redirect'] = 'pets_owners/dashboard';
  }
}

