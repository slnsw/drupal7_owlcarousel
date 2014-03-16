/**
 * @file
 * Initiate Owl Carousel.
 */

(function($) {

  Drupal.behaviors.owlcarousel = {
    attach: function(context, settings) {

      for (var carousel in settings.owlcarousel) {
        // Carousel instance.
        var owl = $('#' + carousel);

        // lazyLoad support.
        if (settings.owlcarousel[carousel].lazyLoad) {
          var images = owl.children('img');

          $.each(images, function(i, image) {
            $(image).attr('data-src', $(image).attr('src'));
          });

          images.addClass('lazyOwl');
        }

        // Attach instance settings.
        owl.owlCarousel(settings.owlcarousel[carousel]);
      }
    }
  };

}(jQuery));
