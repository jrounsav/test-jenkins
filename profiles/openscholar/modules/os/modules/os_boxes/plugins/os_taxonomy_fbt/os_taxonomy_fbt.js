// Adds active class in widget links anchor tag for current active link.
Drupal.behaviors.osTaxonomyFilter = {
  attach : function(ctx) {
    jQuery('.block-boxes-os_taxonomy_fbt a').removeClass('active');
    jQuery('.block-boxes-os_taxonomy_fbt a[href="'+ location.pathname + '"]').addClass('active');
  }
};