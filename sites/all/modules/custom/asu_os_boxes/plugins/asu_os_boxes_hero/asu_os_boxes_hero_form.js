(function ($) {
    Drupal.behaviors.asuOSBoxesHero = {
        attach: function (context, settings) {
            var radios = document.getElementById('edit-hero-options');
            var customChk = document.getElementById('edit-hero-options-custom');
            var uploadField = document.getElementById('edit-fid');

            // toggleDisplay(customChk, uploadField);

            radios.addEventListener('click', function(){
                // toggleDisplay(customChk, uploadField);
            });

            function toggleDisplay(clicked, target){
                if(target && clicked){
                    if(clicked.checked) {
                        target.removeAttribute('style');
                    } else {
                        target.setAttribute('style', 'display:none;');
                    }
                }
            }
        }
    };
}(jQuery));