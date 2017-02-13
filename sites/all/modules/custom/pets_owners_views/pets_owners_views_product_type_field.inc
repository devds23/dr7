<?php

class pets_owners_views_product_type_field extends views_handler_filter_in_operator {
  function get_value_options() {
    if (!isset($this->value_options)) {
      $this->value_title = t('Product Types');
      $arr = taxonomy_vocabulary_machine_name_load('product_type');

      $terms = taxonomy_get_tree($arr->vid);
      $list_terms = array();
      foreach ($terms as $term) {
        $list_terms[$term->tid] = $term->name;
      }
      $this->value_options = $list_terms;
    }

    return $this->value_options;
  }
}
