/**
 * @file
 * Initiate Owl Carousel.
 */

 (function($) {

  Drupal.owlCarousel = Drupal.owlCarousel || {};

  Drupal.owlCarousel.init = function(context, settings){
    for (var carousel in settings.owlcarousel) {
      // Carousel instance.
      var owl = $('.' + carousel);

      // lazyLoad support.
      if (settings.owlcarousel[carousel].settings.lazyLoad) {
        var images = owl.find('img');

        $.each(images, function(i, image) {
          $(image).attr('data-src', $(image).attr('src'));
        });

        images.addClass('lazyOwl');
      }

      var owlSettings = settings.owlcarousel[carousel].settings;

      // Merge OwlCarousel accessibility settings with existing settings
      owlSettings = owlAccess.events.mergeProps(owlSettings);

      // Attach instance settings.
      if (!owl.hasClass('disabled')) {
        owl.owlCarousel(owlSettings);
      }

      // Set an inline height if custom AJAX pagination is enabled;
      // otherwise replacement of carousel element causes scrolling effect.
      if (settings.owlcarousel[carousel].views.ajax_pagination) {
        var owlnav = $('.' + carousel);
        owlnav.parent().css('height', owlnav.height());

        var view = owlnav.parent().parent();
        var next = $(view).find('.pager-next a', context);
        var prev = $(view).find('.pager-previous a', context);

        // Attach Owl Carousel behaviors to pager elements.
        $(next).once('ajax', function() {
          $(next, context).click(function() {
            owlnav.trigger('owl.next');
          });
        });
        $(prev).once('ajax', function() {
          $(prev, context).click(function() {
            owlnav.trigger('owl.prev');
          });
        });
      }
    }
  };

  Drupal.behaviors.owlcarousel = {
    attach: function(context, settings) {
      var init = true;

      if (!!settings.owlcarousel_a11y) {
        if (!!settings.owlcarousel_a11y.csscheck) {
          var testElem = $('<div>', {
            'class': 'owlcarousel-a11y-csscheck'
          });
          $('body').append(testElem);
          var bgColor = $('.owlcarousel-a11y-csscheck').css('backgroundColor');
          init = (!!bgColor && bgColor != 'transparent');
          testElem.remove();
        }
      }

      if (init) {
        Drupal.owlCarousel.init(context, settings);
      }
    }
  };

}(jQuery));
