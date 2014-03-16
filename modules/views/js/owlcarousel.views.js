/**
 * @file
 * owlcarousel.views.js
 *
 * Override or extend upon default views JavaScript functionality.
 */

(function($) {

  /**
   * Modified attach ajax behavior to a singe link.
   */
  Drupal.views.ajaxView.prototype.attachPagerLinkAjax = function(id, link) {
    var $link = $(link);
    var viewData = {};
    var href = $link.attr('href');

    $.extend(viewData, this.settings, Drupal.Views.parseQueryString(href), Drupal.Views.parseViewArgs(href, this.settings.view_base_path));
    $.extend(viewData, Drupal.Views.parseViewArgs(href, this.settings.view_base_path));

    this.element_settings.submit = viewData;
    var owl = $(this.element_settings.selector).find('.owl-carousel');
    var view = owl.parent().parent();

    if (owl.length) {
      this.element_settings.url = Drupal.settings.basePath + 'owlcarousel/views/ajax';
      this.element_settings.success = onSuccess;

      // @todo, move ajax removal to onComplete?
      // this.element_settings.complete = onComplete;
    }

    function onSuccess(content) {
      owl.data('owlCarousel').addItem(content);
      view.find('.ajax-progress-throbber').remove();

      this.element_settings.submit.page++;
    }

    this.pagerAjax = new Drupal.ajax(false, $link, this.element_settings);
  };

}(jQuery));
