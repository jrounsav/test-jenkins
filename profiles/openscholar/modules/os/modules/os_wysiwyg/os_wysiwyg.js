(function($) {
  /**
   * Hides the text format help when the wysiwyg is disabled
   */
  Drupal.behaviors.osWysiwygHideTips = {
    attach: function (context) {
      // don't do this for every thing
      function toggle (e) {
        $(e.currentTarget).parents('.text-format-wrapper').find('.filter-wrapper').toggle();
      }
      $('.filter-wrapper', context).hide();
      $('.wysiwyg-toggle-wrapper a', context).off('click', toggle).on('click', toggle);
    }
  };

  Drupal.behaviors.osWysiwygBrowserAutoSubmit = {
    attach: function (ctx) {

      Drupal.media.popups.mediaStyleSelector.mediaBrowserOnLoad = function (e) {
        var doc = $(e.currentTarget.contentDocument);
        if ($('#edit-format option', doc).length == 1) {
          $('#edit-format', doc).parent('.form-item').hide();
        }

        if ($('#media-format-form fieldset#edit-options .fieldset-wrapper *:visible', doc).length == 0) {
          e.currentTarget.contentWindow.Drupal.media.formatForm.submit.apply($('#media-format-form a.fake-ok', doc)[0]);
        }
      };
    }
  };

})(jQuery);
