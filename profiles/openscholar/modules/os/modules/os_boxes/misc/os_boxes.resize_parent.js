(function () {
  //if (typeof window.webWidgetsIframeHasRun != 'undefined') return;
  //window.webWidgetsIframeHasRun = true;

  // an exception is most likely caused by the DOM  not being ready
  if (window.addEventListener) {
    window.addEventListener('message', receiveMessage, false);
  }
  else if (window.attachEvent) {
    window.attachEvent('onmessage', receiveMessage);
  }

  function receiveMessage(e) {
    var data = JSON.parse(e.data);

    if (typeof data.url == 'undefined') return;

    var iframes = document.querySelectorAll('iframe[src="'+data.url+'"]');

    for (i=0; i<iframes.length; i++) {
      var delta = jQuery(iframes[i]).closest('.boxes-box').attr('id');
      if (typeof Drupal.settings.widget_max_width != 'undefined' && typeof Drupal.settings.widget_max_width[delta] != 'undefined' && Drupal.settings.widget_max_width[delta] != '' && data.width > Drupal.settings.widget_max_width[delta]) {
        if (!iframes[i].resized) {
          iframes[i].width = Drupal.settings.widget_max_width[delta];
          jQuery(iframes[i]).attr("scrolling", "auto");
          jQuery(iframes[i]).attr("src", jQuery(iframes[i]).attr("src"));
          iframes[i].resized = true;
        }
      } else if (typeof data.width != 'undefined') {
        iframes[i].width = data.width;
      }
      if (typeof data.height != 'undefined') {
        iframes[i].height = data.height;
      }
    }
  }

})();
