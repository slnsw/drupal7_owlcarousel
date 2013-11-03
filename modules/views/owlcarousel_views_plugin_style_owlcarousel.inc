<?php

/**
 * @file
 * owlcarousel_views_plugin_style_owlcarousel.inc
 */

/**
  * Implements a style type plugin for the Views module.
  */
class owlcarousel_views_plugin_style_owlcarousel extends views_plugin_style {

  /**
   * Set default options.
   */
  function options(&$options) {
    $options = parent::option_definition();

    $options = array(
      'items_desktop' => array('default' => array(1199, 4)),
      'items_desktop_small' => array('default' => array(979, 3)),
      'items_tablet' => array('default' => array(768, 2)),
      'items_tablet_small' => array('default' => array(FALSE)),
      'items_mobile' => array('default' => array(479, 1)),
      'items' => array('default' => 5),
      'singleItem' => array('default' => FALSE),
      'itemsScaleUp' => array('default' => FALSE),
      'slideSpeed' => array('default' => 200),
      'paginationSpeed' => array('default' => 800),
      'rewindSpeed' => array('default' => 1000),
      'autoPlay' => array('default' => FALSE),
      'stopOnHover' => array('default' => FALSE),
      'navigation' => array('default' => FALSE),
      'navigationText' => array('default' => array('prev', 'next')),
      'rewindNav' => array('default' => TRUE),
      'scrollPerPage' => array('default' => FALSE),
      'pagination' => array('default' => TRUE),
      'paginationNumbers' => array('default' => FALSE),
      'responsive' => array('default' => TRUE),
      'responsiveRefreshRate' => array('default' => 200),
      'responsiveBaseWidth' => array('default' => 'window'),
      'baseClass' => array('default' => 'owl-carousel'),
      'theme' => array('default' => 'owl-theme'),
      'lazyLoad' => array('default' => FALSE),
      'lazyFollow' => array('default' => TRUE),
      'lazyEffect' => array('default' => 'fade'),
      'autoHeight' => array('default' => FALSE),
      'jsonPath' => array('default' => FALSE),
      'jsonSuccess' => array('default' => FALSE),
      'dragBeforeAnimFinish' => array('default' => TRUE),
      'mouseDrag' => array('default' => TRUE),
      'touchDrag' => array('default' => TRUE),
      'addClassActive' => array('default' => FALSE),
      'transitionStyle' => array('default' => FALSE),
      'id' => array('default' => ''),
    );

    return $options;
  }

  /**
   * Show a form to edit the style options.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['settings'] = array(
      '#type' => 'fieldset',
      '#title' => t('Settings'),
    );

    /* @todo, add row groups.
    $form['settings']['items'] = array(
      '#title' => t('Items'),
      '#type' => 'textfield',
      '#description' => t('This variable allows you to set the maximum amount of items displayed at a time with the widest browser width.'),
      '#default_value' => $this->options['items'],
    );*/
    $form['settings']['singleItem'] = array(
      '#title' => t('Single Item'),
      '#type' => 'select',
      '#description' => t('Override the views pager & only display one item.'),
      '#options' => array(
        TRUE => 'Yes',
        FALSE => 'No',
      ),
      '#default_value' => $this->options['singleItem'],
    );
    $form['settings']['itemsScaleUp'] = array(
      '#title' => t('Items Scale Up'),
      '#type' => 'select',
      '#description' => t('Option to not stretch items when it is less than the supplied items.'),
      '#options' => array(
        TRUE => 'Yes',
        FALSE => 'No',
      ),
      '#default_value' => $this->options['itemsScaleUp'],
    );
    $form['settings']['slideSpeed'] = array(
      '#title' => t('Slide Speed'),
      '#type' => 'textfield',
      '#description' => t('Slide speed in milliseconds'),
      '#default_value' => $this->options['slideSpeed'],
    );
    $form['settings']['paginationSpeed'] = array(
      '#title' => t('Pagination Speed'),
      '#type' => 'textfield',
      '#description' => t('Pagination speed in milliseconds'),
      '#default_value' => $this->options['paginationSpeed'],
    );
    $form['settings']['rewindSpeed'] = array(
      '#title' => t('Rewind Speed'),
      '#type' => 'textfield',
      '#description' => t('Rewind speed in milliseconds'),
      '#default_value' => $this->options['rewindSpeed'],
    );
    $form['settings']['autoPlay'] = array(
      '#title' => t('Auto Play'),
      '#type' => 'select',
      '#description' => t('If you set autoPlay: true default speed will be 5 seconds.'),
      '#options' => array(
        TRUE => 'Yes',
        FALSE => 'No',
      ),
      '#default_value' => $this->options['autoPlay'],
    );
    $form['settings']['stopOnHover'] = array(
      '#title' => t('Stop on Hover'),
      '#type' => 'select',
      '#description' => t('Stop autoplay on mouse hover.'),
      '#options' => array(
        TRUE => 'Yes',
        FALSE => 'No',
      ),
      '#default_value' => $this->options['stopOnHover'],
    );
    $form['controls'] = array(
      '#type' => 'fieldset',
      '#title' => t('Navigation'),
    );
    $form['controls']['navigation'] = array(
      '#title' => t('Navigation'),
      '#type' => 'select',
      '#description' => t('Display "next" and "prev" buttons.'),
      '#options' => array(
        TRUE => 'Yes',
        FALSE => 'No',
      ),
      '#default_value' => $this->options['navigation'],
    );
    /*$form['controls']['navigation_text'] = array(
      '#title' => t('Navigation Text'),
      '#type' => 'textfield',
      '#description' => t('Cusomize navigation text.'),
      '#default_value' => implode(',', $this->options['navigation_text']),
    );*/
    $form['controls']['rewindNav'] = array(
      '#title' => 'Rewind Nav',
      '#type' => 'select',
      '#description' => t('Slide to first item. Use rewindSpeed to change animation speed.'),
      '#options' => array(
        TRUE => 'Yes',
        FALSE => 'No',
      ),
      '#default_value' => $this->options['rewindNav'],
    );
    $form['controls']['scrollPerPage'] = array(
      '#title' => t('Scroll Per Page'),
      '#type' => 'select',
      '#description' => t('Scroll per page not per item.'),
      '#options' => array(
        TRUE => 'True',
        FALSE => 'False',
      ),
      '#default_value' => $this->options['scrollPerPage'],
    );
    $form['controls']['pagination'] = array(
      '#title' => t('Pagination'),
      '#type' => 'select',
      '#description' => t('Show pagination.'),
      '#options' => array(
        TRUE => 'Yes',
        FALSE => 'No',
      ),
      '#default_value' => $this->options['pagination'],
    );
    $form['controls']['paginationNumbers'] = array(
      '#title' => t('Pagination Numbers'),
      '#type' => 'select',
      '#description' => t('Show numbers inside pagination buttons.'),
      '#options' => array(
        TRUE => 'True',
        FALSE => 'No',
      ),
      '#default_value' => $this->options['paginationNumbers'],
    );
    $form['front'] = array(
      '#type' => 'fieldset',
      '#title' => t('Theme'),
    );
    $form['front']['responsive'] = array(
      '#title' => t('Responsive'),
      '#type' => 'select',
      '#description' => t('You can use Owl Carousel on desktop-only websites too! Just change that to "false" to disable resposive capabilities.'),
      '#options' => array(
        TRUE => 'Yes',
        FALSE => 'No',
      ),
      '#default_value' => $this->options['responsive'],
    );
    $form['front']['responsiveRefreshRate'] = array(
      '#title' => t('Responsive Refresh Rate'),
      '#type' => 'textfield',
      '#description' => t('Check window width changes every 200ms for responsive actions.'),
      '#default_value' => $this->options['responsiveRefreshRate'],
    );
    $form['front']['responsiveBaseWidth'] = array(
      '#title' => 'Responsive Base Width',
      '#type' => 'textfield',
      '#description' => t('Owl Carousel check window for browser width changes. You can use any other jQuery element to check width changes for example ".owl-demo". 
      Owl will change only if ".owl-demo" get new width.'),
      '#default_value' => $this->options['responsiveBaseWidth'],
    );
    $form['front']['baseClass'] = array(
      '#title' => t('Base Class'),
      '#type' => 'textfield',
      '#description' => t("Automaticly added class for base CSS styles. Best not to change it if you don't need to."),
      '#default_value' => $this->options['baseClass'],
    );
    $form['front']['theme'] = array(
      '#title' => t('Theme'),
      '#type' => 'textfield',
      '#description' => t('Default Owl CSS styles for navigation and buttons. Change it to match your own theme'),
      '#default_value' => $this->options['theme'],
    );
    $form['options'] = array(
      '#type' => 'fieldset',
      '#title' => t('Options'),
    );
    /* @todo, add required data attributes to images if lazy load is selected.
    $form['options']['lazy_load'] = array(
      '#title' => t('Lazy Load'),
      '#type' => 'select',
      '#description' => t("Delays loading of images. Images outside of viewport won't be loaded before user scrolls to them. Great for mobile devices to speed up page loadings."),
      '#default_value' => $this->options['lazy_load'],
    );
    $form['options']['lazy_follow'] = array(
      '#title' => t('Lazy Follow'),
      '#type' => 'select',
      '#description' => t('When pagination used, it skips loading the images from pages that got skipped. It only loads the images that get displayed in viewport. 
      If set to false, all images get loaded when pagination used. It is a sub setting of the lazy load function.'),
      '#options' => array(
        TRUE => 'Yes',
        FALSE => 'No',
      ),
      '#default_value' => $this->options['lazy_follow'],
    );*/
    $form['options']['autoHeight'] = array(
      '#title' => t('Auto Height'),
      '#type' => 'select',
      '#description' => t('Add height to owl-wrapper-outer so you can use diffrent heights on slides. Use it only for one item per page setting.'),
      '#options' => array(
        TRUE => 'Yes',
        FALSE => 'No',
      ),
      '#default_value' => $this->options['autoHeight'],
    );
    /* @todo, re-add with support.
    $form['options']['jsonPath'] = array(
      '#title' => t('JSON Path'),
      '#type' => 'textfield',
      '#description' => t('Allows you to load directly from a jSon file. The JSON structure you use needs to match the owl JSON structure used here. 
      To use custom JSON structure see jsonSuccess option.'),
      '#default_value' => $this->options['options']['json_path'],
    );
    $form['options']['jsonSuccess'] = array(
      '#title' => t('JSON Success'),
      '#type' => 'textfield',
      '#description' => t('Success callback for $.getJSON build in into carousel.'),
      '#default_value' => $this->options['options']['json_success'],
    );*/
    $form['options']['dragBeforeAnimFinish'] = array(
      '#title' => t('Drag Before Animation Finish'),
      '#type' => 'select',
      '#description' => t('Ignore whether a transition is done or not (only dragging).'),
      '#options' => array(
        TRUE => 'Yes',
        FALSE => 'No',
      ),
      '#default_value' => $this->options['dragBeforeAnimFinish'],
    );
    $form['options']['mouseDrag'] = array(
      '#title' => t('Mouse Drag'),
      '#type' => 'select',
      '#description' => t('Turn off/on mouse events.'),
      '#options' => array(
        TRUE => 'Yes',
        FALSE => 'No',
      ),
      '#default_value' => $this->options['mouseDrag'],
    );
    $form['options']['touchDrag'] = array(
      '#title' => t('Touch Drag'),
      '#type' => 'select',
      '#description' => t('Turn off/on touch events.'),
      '#options' => array(
        TRUE => 'Yes',
        FALSE => 'No',
      ),
      '#default_value' => $this->options['touchDrag'],
    );
    $form['options']['addClassActive'] = array(
      '#title' => t('Add Class Active'),
      '#type' => 'select',
      '#description' => t('Add "active" classes on visible items. Works with any numbers of items on screen.'),
      '#options' => array(
        TRUE => 'Yes',
        FALSE => 'No',
      ),
      '#default_value' => $this->options['addClassActive'],
    );
    /* @todo, re-add with support.
    $form['options']['transitionStyle'] = array(
      '#title' => t('Transition Style'),
      '#type' => 'textfield',
      '#description' => t('Add CSS3 transition style. Works only with one item on screen.'),
      '#default_value' => $this->options['options']['transition_style'],
    );*/
  }

  /**
   * Additionally save the view settings to a variable.
   */
  function options_submit($form, &$form_state) {
    $settings = $form_state['values']['style_options'];
    $config = array_merge($settings['settings'], $settings['controls'], $settings['front'], $settings['options']);

    // Clean up.
    unset($form_state['values']['style_options']['settings']);
    unset($form_state['values']['style_options']['controls']);
    unset($form_state['values']['style_options']['front']);
    unset($form_state['values']['style_options']['options']);

    // Keep default value structure.
    $form_state['values']['style_options'] = $config;

    $id = 'owl_carousel_' . $form_state['view']->current_display . $form_state['view']->vid;
    variable_set($id, $config);
  }

  /**
   * Render display.
   */
  function render() {
    $id = 'owl-carousel-' . $this->view->current_display . $this->view->vid;
    $this->options['id']['default'] = $id;
    // Group results.
    $rows = $this->render_grouping($this->view->result, $this->options['grouping']);

    $output = '';
    foreach ($rows as $title => $row) {
      $output .= theme($this->theme_functions(),
        array(
          'view' => $this->view,
          'options' => $this->options,
          'rows' => $row,
          'title' => $title
        )
      );
    }

    return $output;
  }
}
