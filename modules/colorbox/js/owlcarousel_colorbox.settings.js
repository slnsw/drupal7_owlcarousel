
/**
 * @file
 * Owl Carousel Colorbox integration.
 */

(function($) {

  Drupal.behaviors.owlcarousel_colorbox = {
    attach: function(context, settings) {

      for (var carousel in settings.owlcarousel_colorbox) {
        // Update image path.
        // @todo, remove this in favor of theme override.
        var links = $('.' + carousel + '.owl-carousel a.colorbox');
        if (links.length) {
          links.each(function(index, link) {
            var image = $(link).find('img');
            $(link).attr('href', image[0].src);
          });

          // Pass global colorbox settings.
          if (settings.colorbox) {
            links.colorbox(settings.colorbox);
          }
        }
      }
    }
  };

}(jQuery));
