/**
 * @file
 * Initiate Owl Carousel.
 */

(function($) {

  Drupal.behaviors.owlcarousel = {
    attach: function(context, settings) {
      for (var carousel in settings.owlcarousel) {
        settings.owlcarousel.instance = carousel;
        this.attachInit(carousel, settings.owlcarousel);

        if (settings.owlcarousel[carousel].views.ajax_pagination) {
          this.attachAjaxPagination(element, context);
        }
      }
    },

    /**
     * Find and select carousel element.
     *
     * @param carousel htmlSelector
     * @param settings object
     */
    attachInit(carousel, settings) {
      var element = $('.' + carousel);
      this.attachOwlCarousel(element, settings[settings.instance].settings);
    },

    /**
     * Attaches each individual carousel instance
     * to the provided HTML selector.
     *
     * @param element htmlElement
     * @param settings object
     */
    attachOwlCarousel: function(element, settings) {
      // Provide settings alter before init.
      $(document).trigger('owlcarousel.alterSettings', settings);

      // lazyLoad support.
      if (settings.lazyLoad) {
        var images = element.find('img');

        $.each(images, function(i, image) {
          $(image).attr('data-src', $(image).attr('src'));
        });

        images.addClass('owl-lazy');
      }

      if (element.hasClass('disabled') || settings.forceDisplay) {
        element.show();
      }
      else {
        // Attach instance settings & provide alter.
        $(document).trigger('owlcarousel.alterInstance', [element.owlCarousel(settings)]);
      }
    },

    /**
     * Attaches the AJAX pagination.
     *
     * @param element htmlElement
     * @param context object
     */
    attachAjaxPagination: function(element, context) {
      // Set an inline height if custom AJAX pagination is enabled;
      // otherwise replacement of carousel element causes scrolling effect.
      element.parent().css('height', element.height());

      var view = element.parent().parent();
      var next = $(view).find('.pager-next a', context);
      var prev = $(view).find('.pager-previous a', context);

      // Attach Owl Carousel behaviors to pager elements.
      $(next, context).once('ajax', function() {
        $(next).click(function() {
          owlnav.trigger('owl.next');
        });
      });
      $(prev, context).once('ajax', function() {
        $(prev).click(function() {
          owlnav.trigger('owl.prev');
        });
      });
    }

  };

}(jQuery));