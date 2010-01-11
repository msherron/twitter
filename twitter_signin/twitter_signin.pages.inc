<?php
// $Id$

function twitter_signin_admin_settings() {
  $form = array();

  $img_path = drupal_get_path('module', 'twitter_signin') . '/images';
  $results = file_scan_directory($img_path, '.png');
  
  $options = array();
  foreach ($results as $image) {
    $options[$image->basename] = theme('image', $image->filename);
  }
  

  $form['twitter_signin_button'] = array(
    '#type' =>  'radios',
    '#title' => t('Select sign-in button'),
    '#options' => $options,
    '#default_value' => variable_get('twitter_signin_button', 'Sign-in-with-Twitter-lighter-small.png'),
  );
  
  return system_settings_form($form);
}