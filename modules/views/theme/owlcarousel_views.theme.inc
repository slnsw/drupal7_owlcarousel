<?php

/**
 * @file
 * owlcarousel_views.theme.inc
 */

/**
 * Add helper variables for carousel view.
 */
function template_process_owlcarousel_views(&$vars) {
  if (!empty($vars['view'])) {
    $items = array();

    $options = $vars['options'];
    $view = $vars['view'];

    $row_plugin = $view->style_plugin->row_plugin;
    foreach ($vars['rows'] as $id => $row) {
      $view->row_index = $id;
      $item['row'] = $row_plugin->render($row);

      $items[] = $item;
    }

    // @todo, add items per slide.
    // $vars['items_per_slide'] = $items_per_slide;

    // Add the slide items.
    $vars['items'] = $items;

    // Add the attributes
    $options['attributes']['id'] = $vars['options']['id'];

    // Reset the options to the processed values
    $vars['settings'] = $options;
  }

  return $vars;
}
