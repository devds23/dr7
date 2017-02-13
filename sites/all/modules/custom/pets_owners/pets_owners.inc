<?php

/**
 * @file
 *
 * File contain custom ajax command.
 */

/**
 * Implements custom ajax command.
 *
 * @param $color
 *
 * @return array
 */
function pets_owners_command_colorize($color) {
  return array(
    'command' => 'color_picker',
    'color' => $color,
  );
}
