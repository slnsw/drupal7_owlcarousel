/**
 * @file
 * Initiate Owl Carousel.
 */

(function($) {
  Drupal.behaviors.owlcarousel = {
    attach: function(context, settings) {
      // Attach settings.
      for (var carousel in settings.owlcarousel) {
        $("#" + carousel).owlCarousel(settings.owlcarousel[carousel]);
      }
    }
  };
}(jQuery));
