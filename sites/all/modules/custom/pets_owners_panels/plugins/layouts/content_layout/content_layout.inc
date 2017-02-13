<?php
/**
 * @file
 *
 * Array of layouts configs
 */

$plugin = array(
  'title' => t('First Layout'),
  'icon' => 'content_layout.png',
  'category' => t('Pets owners'),
  'theme' => 'pets_owners_panels_content_layout',
  'css' => 'content_layout.css',
  'admin css' => 'content_layout.css',
  'admin theme' => 'pets_owners_panels_admin_content_layout',
  'regions' => array(
    'header' => t('Header'),
    'content' => t('Content'),
    'footer' => t('Footer'),
  ),
);
