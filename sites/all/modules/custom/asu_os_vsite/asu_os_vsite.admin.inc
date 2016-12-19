<?php

/**
 * @file
 * ASU OpenScholar vSite module settings UI.
 */

/**
 * Provides settings pages.
 */
function asu_os_vsite_admin_settings() {

  $to = variable_get('asu_os_vsite_redirect_request_emails', 'mlsamuel@asu.edu');

  $form['asu_os_vsite_redirect_request_emails'] = array(
    '#type' => 'textfield',
    '#title' => t('vSite Redirect Request Notification Emails'),
    '#default_value' => $to,
    '#size' => 60,
    '#maxlength' => 255,
    '#description' => t('Emails to receive notifications about redirect requests. Separate multiple emails with commas.'),
  );

  return system_settings_form($form);
}