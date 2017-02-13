<?php
/**
 * @file
 * Implements custom handler for pet owner gender.
 */

/**
 * Class pets_owners_views_filter_by_gender
 */
class pets_owners_views_filter_by_gender extends views_handler_filter_in_operator {
  function get_value_options() {
    if (!isset($this->value_options)) {
      $this->value_title = t('Gender');
      $operators = array(0 => 'male', 1 => 'female', 2 => 'other');
      $this->value_options = $operators;
    }
    return $this->value_options;
  }
}
