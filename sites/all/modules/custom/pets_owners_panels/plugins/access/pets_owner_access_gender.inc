<?php
/**
 * @file
 * Access plugin file
 */

/**
 * plugin array config
 */
$plugin = array(
  'title' => t("Owner: gender"),
  'description' => t('Control access by the gender checked.'),
  'callback' => 'pets_owners_panels_access_check',
  'settings form' => 'context_owner_gender_add_form_settings_form',
  'required context' => new ctools_context_required(t('Owner'), 'owner'),
);

/**
 * @param $conf
 * @param $context
 *
 * @return bool
 */
function pets_owners_panels_access_check($conf, $context) {
  $compare = $context->data->gender;
  if (empty($context) || empty($context->data)) {
    return FALSE;
  }

  if (isset($conf['gender'])) {
    $options[0] = is_string($conf['gender'][0]) ? $conf['gender'][0] : NULL;
    $options[1] = is_string($conf['gender'][1]) ? $conf['gender'][1] : NULL;
    $options[2] = is_string($conf['gender'][2]) ? $conf['gender'][2] : NULL;

    if ($compare == $options[0] || $compare == $options[1] || $compare == $options[2]) {
      return TRUE;
    }
  }
  return FALSE;
}

/**
 * @param $form
 * @param $form_state
 * @param $conf
 *
 * @return mixed
 */
function context_owner_gender_add_form_settings_form($form, &$form_state, $conf) {
  $options = array();

  if (isset($conf['gender'])) {
    $options[0] = is_string($conf['gender'][0]) ? $conf['gender'][0] : NULL;
    $options[1] = is_string($conf['gender'][1]) ? $conf['gender'][1] : NULL;
    $options[2] = is_string($conf['gender'][2]) ? $conf['gender'][2] : NULL;
  }

  $form['settings']['gender'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Gender variants'),
    '#description' => t('Select the gender for this form.'),
    '#default_value' => $options,
    '#options' => array(0 => t('male'), 1 => t('female'), 2 => t('other')),
  );

  return $form;
}
