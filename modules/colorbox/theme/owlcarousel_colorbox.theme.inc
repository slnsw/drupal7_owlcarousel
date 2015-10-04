<?php

/**
 * @file
 * owlcarousel_colorbox.theme.inc
 */

/**
 * Override the default theme implementation for Owl Carousel item.
 *
 * @todo, pass image url as variable.
 * @todo, pass id of group for gallery/rel support.
 */
function theme_owlcarousel_colorbox_list_item(&$vars) {
  return l($vars['item'], '', array('attributes' => array('class' => 'colorbox', 'rel' => 'gallery'), 'fragment' => 'colorbox', 'html' => TRUE));
}
