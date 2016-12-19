<?php

/**
 * @function asu_brand_os_admin
 * 
 * returns ASU Brand OS's admin form
 */
function asu_brand_os_admin() {
	$form = array();
  $form['asu_brand_os'] = array(
	  '#type' => 'fieldset',
	  '#title' => t('Configure ASU Brand OS'),
	  '#collapsible' => FALSE,
	  '#collapsed' => FALSE,
    '#description' => t('Please see ASU Brand module settings. Note: this module assumes responsibility for default header settings.'),
	);

  /*
	//module mode
  $form['asu_brand_os']['asu_brand_os_api'] = array(
	  '#type' => 'textfield',
	  '#title' => t('API Key'),
	  '#required' => TRUE,
	  '#default_value' => variable_get('asu_brand_os_api', ''),
	  '#description' => t('Your MailChimp API Key.  Leaving this blank will disable automatic subscription'),
   );
   $options = _asu_brand_os_get_lists(variable_get('asu_brand_os_api', ''));
   if ($options) {
     $form['asu_brand_os']['asu_brand_os_list'] = array(
      '#type' => 'select',
      '#title' => t('Mailing List'),
      '#required' => TRUE,
      '#default_value' => variable_get('asu_brand_os_list', ''),
      '#description' => t('MailChimp list to subscribe new users to.'),
      '#options' => $options,
     );
     
     $use_field_state = array('visible' => array('input[name="asu_brand_os_use_field"]' => array('checked' => TRUE)));
     $form['asu_brand_os']['asu_brand_os_use_field'] = array(
       '#type' => 'checkbox',
       '#title' => t('Use custom field'),
       '#default_value' => variable_get('asu_brand_os_use_field', FALSE),
     );
     $form['asu_brand_os']['asu_brand_os_use_field_name'] = array(
       '#type' => 'textfield',
       '#title' => 'Field name',
       '#default_value' => variable_get('asu_brand_os_use_field_name', ''),
       '#states' => $use_field_state,
     );
     $form['asu_brand_os']['asu_brand_os_use_field_value'] = array(
       '#type' => 'textfield',
       '#title' => 'Field value',
       '#default_value' => variable_get('asu_brand_os_use_field_value', ''),
       '#states' => $use_field_state,
       '#description' => t('Mailchimp can be customized with extra fields for capturing and storing data.  
           Openscholar can be configured to use these fields when automatically subscribing users.  Enter
            the name of a field (from the merge tag column, not the field label column in Mailchimp) and 
           a value here.  (An example of how to use this would be several OpenScholar installations adding 
           users to the same mailing list.  By creating a field for each installation, you can flag where 
           each subscription originated.)'),
     );
   } else {
     $form['asu_brand_os']['api_key_error'] = array(
       '#type' => 'markup',
       '#value' => 'No mailing lists available.  Please check your API key and try again.',
     );
   }
  */
      
  return system_settings_form($form);
}