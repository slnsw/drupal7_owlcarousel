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
    // Load instance setting.
    $options = $vars['options'];
    $view = $vars['view'];

    if (variable_get_value('owlcarousel_override_ajax_pagination_' . $options['instance'])) {
      drupal_add_js(drupal_get_path('module', 'owlcarousel_views') . '/js/owlcarousel.views.js', array('scope' => 'footer', 'type' => 'file'));
    }

    $items = array();
    $row_plugin = $view->style_plugin->row_plugin;
    foreach ($vars['rows'] as $id => $row) {
      $view->row_index = $id;
      $item['row'] = $row_plugin->render($row);

      $items[] = $item;
    }

    // Add the slide items.
    $vars['items'] = $items;

    $options['attributes']['id'] = $vars['options']['id'];
    $vars['settings'] = $options;
  }

  return $vars;
}
