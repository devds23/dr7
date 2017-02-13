<?php
/**
 * @file
 *
 * Build form file
 */

/**
 * Implements function pets_owners_form.
 */
function pets_owners_form($form, &$form_state) {
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Your name'),
    '#maxlength' => 100,
    '#required' => TRUE,
  );

  $active = array(0 => t('male'), 1 => t('female'), 2 => t('other'));
  $form['gender'] = array(
    '#type' => 'radios',
    '#title' => t('Gender'),
    '#options' => $active,
    '#default_value' => 0,
    '#required' => TRUE,
  );

  $form['other_gender'] = array(
    '#type' => 'textfield',
    '#title' => t('Other gender'),
    '#states' => array(
      'visible' => array(
        ':input[name="gender"]' => array('value' => 2),
      ),
      'required' => array(
        ':input[name="gender"]' => array('value' => 2),
      ),
    ),
  );

  $form['title'] = array(
    '#type' => 'select',
    '#title' => t('Title'),
    '#options' => array(
      'mr' => t("mr"),
      'mrs' => t("mrs"),
      'ms' => t("ms"),
    ),
  );

  $form['age'] = array(
    '#type' => 'textfield',
    '#title' => t('Your age'),
    '#maxlength' => 3,
    '#size' => 3,
    '#required' => TRUE,
  );

  $form['hobby'] = array(
    '#type' => 'textfield',
    '#title' => t("Your hobby"),
    '#autocomplete_path' => 'pets_owners/autocomplete/hobby',
  );
  $arr = array();
  for ($i = 1; $i < 18; $i++) {
    $arr[] = array(':input[name="age"]' => array('value' => $i));
  }
  $form['parents'] = array(
    '#type' => 'fieldset',
    '#title' => t('Parents'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#states' => array(
      'visible' => array($arr),
      'required' => array($arr),
    )
  );

  $form['parents']['father'] = array(
    '#type' => 'textfield',
    '#title' => t("Your father's name"),
    '#maxlength' => 100,
  );

  $form['parents']['mother'] = array(
    '#type' => 'textfield',
    '#title' => t("Your mother's name"),
    '#maxlength' => 100,
  );

  $form['question'] = array(
    '#type' => 'checkbox',
    '#title' => t('Have you some pets?'),
  );

  $form['petsname'] = array(
    '#type' => 'textfield',
    '#title' => t('Name(s) of your pet(s)'),
    '#states' => array(
      'visible' => array(
        'input[name="question"]' => array('checked' => TRUE),
      ),
      'required' => array(
        ':input[name="question"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['email'] = array(
    '#type' => 'textfield',
    '#title' => t('Your email'),
    '#required' => TRUE,
  );

  $form['submit_button'] = array(
    '#type' => 'submit',
    '#value' => t('Click Here!'),
  );

  $form['#attached']['js'][] = drupal_get_path('module', 'pets_owners') . '/pets_owners_js_validate.js';
  $form['#attached']['js'][] = drupal_get_path('module', 'pets_owners') . '/pets_owners_preview.js';
  $form['#attached']['js'][] = drupal_get_path('module', 'pets_owners') . '/pets_owners_color_picker.js';

  $form['preview_button'] = array(
    '#type' => 'button',
    '#value' => t('Preview'),
    '#ajax' => array(
      'path' => 'pets_owners/ajax'
    ),
    '#weight' => 10,
  );

  $form['colorizer'] = array(
    '#type' => 'link',
    '#title' => t('Colorize'),
    '#href' => 'pets_owners/colorizer',
    '#attributes' => array('class' => array('use-ajax')),
//    '#markup' => l(t('Colorizer'), "http://drupal-site.naz/pets_owners/colorizer", array(
//        'attributes' => array(
//          'class' => 'use-ajax',
//          'id' => 'colorizer'
//        ),
//      )
//    ),
    '#weight' => 10,
  );

  $form["#validate"][] = 'pets_owners_email_validate';
  $form["#validate"][] = 'pets_owners_age_validate';
  $form["#validate"][] = 'pets_owners_hobby_validate';
  $form["#validate"][] = 'pets_owners_name_validate';
  $form["#validate"][] = 'pets_owners_other_gender_validate';
  $form["#validate"][] = 'pets_owners_pets_name_validate';

  return $form;
}

/**
 * Implements function Email validate
 *
 * @param $form
 * @param $form_state
 */
function pets_owners_email_validate($form, &$form_state) {
  $valid_email = $form_state['values']['email'];
  if (!empty($valid_email) and !valid_email_address($valid_email)) {
    form_set_error('email', 'Sorry. Your email address,' . $valid_email . ', is not valid. Please submit a valid E-mail address.');
  }
}

/**
 * Implements function Age validate
 *
 * @param $form
 * @param $form_state
 */
function pets_owners_age_validate($form, $form_state) {
  $age = $form_state['values']['age'];
  if (!is_numeric($age)) {
    form_set_error('age', "Please enter Only numbers in age field");
  }
  elseif ($age < 1 or $age > 120) {
    form_set_error('age', 'Your age ' . $age . ' is illegal.');
  }
}

/**
 * Implements function hobby validation
 *
 * @param $form
 * @param $form_state
 */
function pets_owners_hobby_validate($form, $form_state) {
  $hobby = $form_state['values']['hobby'];
  $term = taxonomy_get_term_by_name($hobby, 'hobby');

  if (!count($term) && trim($hobby) != '') {
    form_set_error('hobby', "Your hobby does not exist in our hobbies list");
  }
}

/**
 * Implements function name validate
 *
 * @param $form
 * @param $form_state
 */
function pets_owners_name_validate($form, $form_state) {
  $name = trim($form_state['values']['name']);
  $father = trim($form_state['values']['father']);
  $mother = trim($form_state['values']['mother']);
  $age = $form_state['values']['age'];

  if (strlen($name) > 100) {
    form_set_error('name', 'Maximal symbols of name is 100');
  }
  if (strlen($father) > 100) {
    form_set_error('father', "Maximal symbols of father's name is 100");
  }
  if (strlen($mother) > 100) {
    form_set_error('mother', "Maximal symbols of mother's name is 100");
  }

  if (($age > 0 and $age < 18) and strlen($father) == 0) {
    form_set_error('father', "Field father's name is required");
  }
  if (($age > 0 and $age < 18) and strlen($mother) == 0) {
    form_set_error('mother', "Field mother's name is required");
  }
}

/**
 * @param $form
 * @param $form_state
 */
function pets_owners_other_gender_validate($form, $form_state) {
  if ($form_state['values']["gender"] == 2 && trim($form_state['values']["other_gender"]) == '') {
    form_set_error('other_gender', 'Field other gender is required.');
  }
}

/**
 * @param $form
 * @param $form_state
 */
function pets_owners_pets_name_validate($form, $form_state) {
  if ($form_state['values']["question"] == 1 && trim($form_state['values']["petsname"]) == '') {
    form_set_error('petsname', 'Field pets name is required.');
  }
}

/**
 * Implements hook_submit().
 *
 * @param $form
 * @param $form_state
 */
function pets_owners_form_submit($form, &$form_state) {
//  dpm($form_state['values']['title']);
  drupal_set_message(t('Thank you!'));
}
