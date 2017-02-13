<?php
/**
 * @file
 * correctfeature.features.inc
 */

/**
 * Implements hook_node_info().
 */
function correctfeature_node_info() {
  $items = array(
    'content_for_multi' => array(
      'name' => t('content_for_multi'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
