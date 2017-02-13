<?php
/**
 * @file
 * File contains method render().
 */
/**
 * Class pets_owners_views_field_image
 */
class pets_owners_views_field_image extends views_handler_field {
  /**
   * Render callback handler.
   *
   * Return the markup that will appear in the rendered field.
   */
  function render($values) {

    $variables = array(
      'path' => $values->file_managed_pets_owners_storage_submissions_uri,
      'alt' => 'Pet image',
      'title' => 'Pet',
      'width' => '100px',
      'height' => '100px',
    );
    return theme('image', $variables);
  }
}
