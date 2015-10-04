<?php

/**
 * @file
 * owlcarousel_colorbox.theme.inc
 */

/**
 * Override the default theme implementation for Owl Carousel item.
 *
 * @todo, pass image url as variable for imagestyle.
 */
function theme_owlcarousel_colorbox_list_item(&$vars) {
  $output = '<div class="' . $vars['class'] . '">' . $vars['item'] . '</div>';

  if (variable_get('owlcarousel_colorbox_' . $vars['group'])) {
    $output = l($vars['item'], '', array('attributes' => array('class' => 'colorbox', 'rel' => $vars['group']), 'fragment' => 'colorbox', 'html' => TRUE));
  }

  return $output;
}
