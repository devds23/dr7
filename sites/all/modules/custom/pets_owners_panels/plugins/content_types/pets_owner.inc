<?php
/**
 * @file
 *
 * Content types plugin file
 */

$plugin = array(
  'title' => t('Example content type plugin'),
  'description' => t('The output a custom text.'),
  'render callback' => 'example_text_content_type_render',
  'edit form' => 'pet_show_edit_form',
  'hook theme' => 'pets_owners_panels_pets_owner_theme',
  'category' => t('Custom panes'),
  'setting form' => 'pets_owners_panels_pets_owner_edit_form',
  'required context' => new ctools_context_required(t('Owner'), 'owner'),
  'single' => TRUE,
);

/**
 * 'Edit form' callback for the content type.
 */
function pet_show_edit_form($form, &$form_state) {
  $form['name'] = array(
    '#type' => 'checkbox',
    '#title' => t('Do you want to show pets owners picture?'),
    '#default_value' => !empty($form_state['conf']['name']) ? TRUE : FALSE
  );

  $conf = $form_state['conf'];
//  dpm($form_state['conf']);
  $options = array(
    'full' => t('Full mode'),
    'teaser' => t('Teaser mode'),
  );

  $form['mode'] = array(
    '#type' => 'select',
    '#title' => t('List information type'),
    '#options' => $options,
    '#required' => TRUE,
    '#default_value' => $conf['mode'],
  );

  return $form;
}

/**
 * Submit callback for the example_text_edit_form().
 */
function pet_show_edit_form_submit($form, &$form_state) {
  if (isset($form_state['values']['name'])) {
    $form_state['conf']['name'] = $form_state['values']['name'];
  }
  if (isset($form_state['values']['mode'])) {
    $form_state['conf']['mode'] = $form_state['values']['mode'];
  }
}

/**
 * Render callback for the content type.
 */
function example_text_content_type_render($subtype, $conf, $args, $context) {
  $items = array();
  $items["name"] = $context->data->name;
  $items["pet_name"] = $context->data->pet_name;
  $items["age"] = $context->data->age;
  $items["hobby"] = $context->data->hobby;
  $items["email"] = $context->data->email;

  $block = new stdClass();
  $block->content = '';
  if ($conf['name'] == TRUE) {
    $block->content = theme('image_style', array(
      'style_name' => 'pet_image_style',
      'path' => $context->data->uri
    ));
  }


  if (isset($conf['mode']) && $conf['mode'] == 'full') {
    $block->content .= theme('pets_owners_panels_pets_owner_full', $items);
  }
  else {
    $block->content .= theme('pets_owners_panels_pets_owner_teaser', $items);
  }
  return $block;
}

/**
 * @param $theme
 * @param $plugin
 */
function pets_owners_panels_pets_owner_theme(&$theme, $plugin) {
  $theme['pets_owners_panels_pets_owner_full'] = array(
    'path' => $plugin['path'],
    'template' => 'pets-owners-panels-pets-owner-full',
  );

  $theme['pets_owners_panels_pets_owner_teaser'] = array(
    'path' => $plugin['path'],
    'template' => 'pets-owners-panels-pets-owner-teaser',
  );
}
