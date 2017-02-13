<?php
/**
 * @file
 *
 * Plugin to provide an argument handler for a node id
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t("Pets Owners: ID"),
//  'keyword' => 'owner',
  'description' => t('Creates a pets owner context from a Pets Owners ID argument.'),
  'context' => 'pets_owners_panels_argument_oid_context',
);

/**
 * @param null $arg
 * @param null $conf
 * @param bool $empty
 *
 * @return bool
 */
function pets_owners_panels_argument_oid_context($arg = NULL, $conf = NULL, $empty = FALSE) {
  if ($empty) {
    return ctools_context_create_empty('owner');
  }
  // We can accept a owner object.
  if (is_object($arg)) {
    return ctools_context_create('owner', $arg);
  }
  if (!is_numeric($arg)) {
    return FALSE;
  }

  module_load_include('inc', 'pets_owners_storage', 'pets_owners_storage');
  $result = pets_owners_storage_read($arg);
  if (!$result) {
    return FALSE;
  }

  return ctools_context_create('owner', $result);
}
