<?php

/**
 * @file
 * owlcarousel_views_plugin_pager_owlcarousel.inc
 */

/**
 * Views pager plugin.
 */
class owlcarousel_views_plugin_pager_owlcarousel extends views_plugin_pager {

  /**
   * Short summary containing items per page count.
   */
  function summary_title() {
    return format_plural($this->options['items_per_page'], '@count item', '@count items', array('@count' => $this->options['items_per_page']));
  }

  /**
   * View pager options.
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['items_per_page'] = array('default' => 10);
    $options['offset'] = array('default' => 0);
    $options['id'] = array('default' => 0);
    $options['prev_label'] = array('default' => 'previous', 'translatable' => TRUE);
    $options['next_label'] = array('default' => 'next', 'translatable' => TRUE);

    return $options;
  }

  /**
   * Default form for pager setting options.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['items_per_page'] = array(
      '#title' => t('Items to display'),
      '#type' => 'textfield',
      '#description' => t('Loading only 1 item per page is currently supported.'),
      '#default_value' => 1,
      '#attributes' => array('disabled' => 'disabled'),
    );
    $form['offset'] = array(
      '#type' => 'textfield',
      '#title' => t('Offset'),
      '#description' => t('The number of items to skip. For example, if this field is 3, the first 3 items will be skipped and not displayed.'),
      '#default_value' => $this->options['offset'],
    );
    $form['id'] = array(
      '#type' => 'textfield',
      '#title' => t('Pager ID'),
      '#description' => t("Unless you're experiencing problems with pagers related to this view, you should leave this at 0. If using multiple pagers on one page you may need to set this number to a higher value so as not to conflict within the ?page= array. Large values will add a lot of commas to your URLs, so avoid if possible."),
      '#default_value' => $this->options['id'],
    );
    $form['navigation'] = array(
      '#type' => 'fieldset',
      '#title' => t('Navigation'),
    );
    $form['navigation']['prev_label'] = array(
      '#type' => 'textfield',
      '#title' => t('Label for "previous" pager'),
      '#description' => t('The label to use for the "previous" pager element.'),
      '#default_value' => $this->options['prev_label'],
    );
    $form['navigation']['next_label'] = array(
      '#type' => 'textfield',
      '#title' => t('Label for "next" pager'),
      '#description' => t('The label to use for the "next" pager element.'),
      '#default_value' => $this->options['next_label'],
    );
    // @todo, add pagination settings.
  }

  /**
   * Default callback for validating pager settings.
   */
  function options_validate(&$form, &$form_state) {
    if (!is_numeric($form_state['values']['pager_options']['items_per_page'])) {
      form_set_error('pager_options][items_per_page', t('Items per page must contain a numeric value.'));
    }
    if (!isset($form_state['values']['pager_options']['offset']) || !is_numeric($form_state['values']['pager_options']['offset'])) {
      form_set_error('pager_options][offset', t('Offset must contain a numeric value.'));
    }
  }

  /**
   * Alter pager query.
   */
  function query() {
    $limit = $this->options['items_per_page'];
    $offset = $this->current_page * $this->options['items_per_page'] + $this->options['offset'];

    $this->view->query->set_limit($limit);
    $this->view->query->set_offset($offset);
  }

  /**
   * Render the pager.
   */
  function render($input) {
    return theme(views_theme_functions('owlcarousel_views_pager', $this->view, $this->display), array(
      'parameters' => $input, 
      'element' => $this->options['id'],
      'options' => $this->options,
    ));
  }

  /**
   * Total pager items.
   */
  function get_pager_total() {
    if ($items_per_page = intval($this->get_items_per_page())) {
      return ceil($this->total_items / $items_per_page);
    }
    else {
      return 1;
    }
  }

  /**
   * Update global paging info.
   */
  function update_page_info() {
    if (!empty($this->options['total_pages'])) {
      if (($this->options['total_pages'] * $this->options['items_per_page']) < $this->total_items) {
        $this->total_items = $this->options['total_pages'] * $this->options['items_per_page'];
      }
    }

    $items_per_page = $this->get_items_per_page();
    if (!empty($items_per_page)) {
      global $pager_total, $pager_total_items, $pager_limits;

      // Set pager settings.
      $pager_limits[$this->options['id']] = $this->options['items_per_page'];
      $pager_total_items[$this->options['id']] = $this->total_items;
      $pager_total[$this->options['id']] = $this->get_pager_total();
    }
  }
}
