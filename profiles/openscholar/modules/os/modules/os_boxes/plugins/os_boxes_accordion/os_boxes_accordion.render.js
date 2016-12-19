/**
 * Starts up accordion widgets according to their settings
 */
(function ($) {
  Drupal.behaviors.osBoxesAccordion = {
    attach: function (ctx) {
      $.each(Drupal.settings.os_boxes.accordion, function (delta, data) {
        $('#boxes-box-' + data.delta + ' > .boxes-box-content > .accordion', ctx).accordion({
          collapsible: true,
          heightStyle: 'content',
          active: data.active
        })
      });
    }
  }
})(jQuery);
