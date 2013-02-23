<?php
/**
 * @file
 * Field configuration for twitter_post module.
 */

/**
 * Implements hook_field_info()
 */
function twitter_post_field_info() {
  return array(
    'twitter_post' => array(
      'label' => t('Twitter'),
      'description' => t('Allows posting to Twitter.com.'),
      'default_widget' => 'twitter_post_widget',
      'default_formatter' => 'text_text',
    ),
  );
}

/**
 * Implement hook_field_widget_info().
 */
function twitter_post_field_widget_info() {
  return array(
    'twitter_post_widget'=> array(
      'label' => t('Post to Twitter'),
      'field types' => array('twitter_post'),
    ),
  );
}

/**
 * Implement hook_field_widget().
 */
function twitter_post_field_widget_form(&$form, &$form_state, $field, $instance, $langcode, $items, $delta = 0, $element) {
  if (!user_access('post to twitter')) {
    return $element;
  }

  $status = isset($items[$delta]['status']) ? $items[$delta]['status'] : TRUE;
  $message = isset($items[$delta]['message']) ? $items[$delta]['message'] : t('New post: !title !url-alias');
  $element += array(
    '#type' => 'fieldset',
    '#group' => 'Social networks',
    '#title' => t('Post to twitter.com'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#tree' => TRUE,
    'status' => array(
      '#type' => 'checkbox',
      '#title' => t('Announce this post on Twitter'),
      '#default_value' => $status,
      '#id' => 'twitter-toggle',
    ),
    'message' => array(
      '#type' => 'textfield',
      '#title' => t('Twiter.com status'),
      '#default_value' => $message,
      '#description' => t('The given text will be posted to twitter.com. You can use !url, !url-alias, !tinyurl, !title and !user as replacement text.'),
      '#maxlength' => 150,
      '#attached' => array(
        'js' => array(drupal_get_path('module', 'twitter_post') . '/twitter_post.js'),
      ),
      '#attributes' => array('class' => array('twitter-post-message')),
    ),
  );

  return $element;
}

/**
 * Implements hook_field_formatter_settings_summary().
 */
function twitter_post_field_formatter_settings_summary($field, $instance, $view_mode) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];


  if ($settings['type'] != 'none') {
    $summary = t('Default status: @status. Message: @message', array(
      '@status' => $settings['status'],
      '@message' => $settings['message'],
    ));
  }
  else {
    $summary = t('Twitter post field is disabled.');
  }

  return $summary;
}

/**
 * Implement hook_field_is_empty().
 */
function twitter_post_field_is_empty($item, $field) {
  return strlen($item['message']) == 0;
}

/**
 * Implements hook_field_attach_form()
 *
 * Adds a select field to choose a Twitter account.
 */
function twitter_post_field_attach_form($entity_type, $entity, &$form, &$form_state, $langcode) {
  $options = array();
  module_load_include('inc', 'twitter');
  $twitter_accounts = twitter_load_authenticated_accounts();
  foreach ($twitter_accounts as $twitter_account) {
    $options[$twitter_account->twitter_uid] = $twitter_account->screen_name;
  }
  $twitter_uid = key($options);
  $screen_name = current($options);
  foreach ($form_state['field'] as $field_name => $field) {
    if ($field[$langcode]['field']['type'] == 'twitter_post') {
      $element = array();
      if (count($options) > 1) {
        $element['account'] = array(
          '#type' => 'select',
          '#title' => t('Twitter Account'),
          '#options' => $options,
          '#id' => 'twitter-account',
        );
      }
      else {
        $element['account'] = array(
          '#type' => 'value',
          '#value' => $twitter_uid,
        );
        $element['account_name'] = array(
          '#type' => 'item',
          '#title' => t('Twitter account'),
          '#markup' => _twitter_user_profile($screen_name),
        );
      }
      $form[$field_name][$langcode][0] += $element;
    }
  }
}
