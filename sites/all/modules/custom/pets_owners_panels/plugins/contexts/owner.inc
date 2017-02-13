<?php

/**
 * @file
 * Plugin to provide a taxonomy_term_add_form context
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Owner'),
  'description' => t('This is pet owner description'),
  'context' => 'context_owner_create_context',
  'keyword' => 'owner',
  'context name' => 'owner',
);

/**
 * It's important to remember that $conf is optional here, because contexts
 * are not always created from the UI.
 */
function context_owner_create_context($empty, $data = NULL, $conf = FALSE) {
  $context = new ctools_context('owner');
  $context->plugin = 'owner';

  if ($empty) {
    return $context;
  }
  if ($conf) {
    if (!empty($data)) {
      $context->data = new stdClass();

      $context->data->item1 = $data;
      $context->title = t("Owner context from config");
      return $context;
    }
  }
  else {
    $context->data = $data;
    $context->title = t("Owner context from config");

    return $context;
  }
}
