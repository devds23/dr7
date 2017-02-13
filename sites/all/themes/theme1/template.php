<?php
/**
 * @file
 * template.php file implements preprocess and process functions.
 */

drupal_add_js(drupal_get_path('theme', 'theme1') . '/js/script-theme.js', array(
  'type' => 'file',
  'group' => JS_THEME,
));
/**
 * Override or insert variables into the node template.
 *
 * @param $variables
 */
function theme1_preprocess_node(&$variables) {
//  $variables['view_mode'] = variable_get('content_view_mode');
  if (isset($variables['node']) && $variables['node']->type) {
    $variables['theme_hook_suggestions'][] = 'node__' . $variables['type'] . '__' . $variables['view_mode'];  //['content']['body']['#view_mode']
  }
}

/**
 * Override or insert variables into the node template
 *
 * @param $variables
 */
function theme1_preprocess_taxonomy_term(&$variables) {
  $variables['theme_hook_suggestions'][] = 'taxonomy_term__' . $variables['view_mode'];
//  dsm($variables['elements']['#entity_view_mode']['view_mode']);
}

function theme1_preprocess_block(&$variables) {
}
