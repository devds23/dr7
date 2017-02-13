<?php
/**
 * @file
 * products_feature.features.inc
 */

/**
 * Implements hook_node_info().
 */
function products_feature_node_info() {
  $items = array(
    'product' => array(
      'name' => t('Product'),
      'base' => 'node_content',
      'description' => t('This CT is used to display products.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
