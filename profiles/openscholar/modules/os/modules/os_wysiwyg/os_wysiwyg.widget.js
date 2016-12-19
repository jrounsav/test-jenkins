(function($) {

  /**
   * Hides the ckeditor.
   */
  Drupal.behaviors.osWysiwygInlineCKEDITOR = {
    attach: function (context) {
      CKEDITOR.on("instanceReady", function(event) {
        var editor = event.editor;
        var instance = $('#cke_' + editor.name);
        var editor_height = $('iframe').contents().find('body.cke_editable').height() + 25;

        // Adjusting the height of the wysiwyg according to the window height.
        // var editor_height = height / 2;

        if (editor_height < 100) {
          editor_height = 100;
        }

        if (editor_height > 550) {
          // The height can be more than 550.
          editor_height = 550;
        }

        instance.find('#cke_1_contents').height(editor_height);

        editor.on('doubleclick', function(evt)  {
          if (evt.data.element.is('a')) {
            evt.data.dialog = null;
          }
        }, null, null, 100);

        editor.on('selectionChange', function(evt) {
          // Verify the selected content is a link or not. In case it's a link
          // replace the text the user selected with a jQuery selector.
          if (jQuery(this.getSelectedHtml().$).is('a')) {
            jQuery.selectLink = jQuery(this.getSelectedHtml().$);
          }
        });

        event.editor.document.on('mouseup', function()  {
          // Get the text that the user selected.
          jQuery.selectLink = this.getSelection().getSelectedText();
        });
      });
    }
  };

})(jQuery);
