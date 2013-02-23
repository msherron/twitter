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
      'label' => t('Post to Twitter'),
      'description' => t('Allows posting to Twitter.com.'),
      'instance_settings' => array(
        'status' => 1,
        'format' => 'New post: !title !url-alias',
      ),
      'default_widget' => 'twitter_post_widget',
    ),
  );
}

/**
 * Implements hook_field_settings_form().
 */
function twitter_post_field_settings_form($field, $instance) {
  $defaults = field_info_field_settings($field['type']);
  $settings = array_merge($defaults, $field['settings']);

  $form['test'] = array(
    '#type' => 'textfield',
    '#title' => t('Upload destination'),
    '#default_value' => $settings['test'],
    '#description' => t('Select where the final files should be stored. Private file storage has significantly more overhead than public files, but allows restricted access to files within this field.'),
  );

  return $form;
}

/**
 * Implements hook_field_instance_settings_form().
 */
function twitter_post_field_instance_settings_form($field, $instance) {
  $settings = $instance['settings'];
  $form = array();

  $form['format'] = array(
    '#type' => 'textfield',
    '#title' => t('Default format string'),
    '#maxlength' => 140,
    '#description' => t('The given text will be used as a template for posting to Twitter.com. ' .
                        'The following token replacements are available: !url, !url-alias, !tinyurl, !title, and !user'),
    '#default_value' => $settings['format'],
    '#required' => TRUE,
  );

  $form['status'] = array(
    '#type' => 'checkbox',
    '#description' => t('When active, tweets will be automatically published.'),
    '#title' => t('Post to twitter by default'),
    '#default_value' => $settings['status'],
  );

  return $form;
}

/**
 * Implement hook_field_widget_info().
 */
function twitter_post_field_widget_info() {
  return array(
    'twitter_post_widget'=> array(
      'label' => t('Default Twitter field'),
      'field types' => array('twitter_post'),
    ),
  );
}

/**
 * Implements hook_field_widget_settings_form().
 */
function twitter_post_field_widget_settings_form($field, $instance) {
  $widget = $instance['widget'];
  $settings = $widget['settings'];

  $form['preview'] = array(
    '#title' => t('Preview image style'),
    '#type' => 'textfield',
    '#default_value' => $settings['preview'],
    '#description' => t('The preview image will be shown while editing the content.'),
  );

  return $form;
}

/**
 * Implement hook_field_widget().
 */
function twitter_post_field_widget_form(&$form, &$form_state, $field, $instance, $langcode, $items, $delta = 0, $element) {
  if (!user_access('post to twitter')) {
    return $element;
  }

  $format = isset($items[$delta]['format']) ? $items[$delta]['format'] : 0;
  $status = isset($items[$delta]['status']) ? $items[$delta]['status'] : TRUE;
  $element += array(
    '#type' => 'fieldset',
    '#group' => 'Social networks',
    '#title' => t('Post to twitter.com'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#tree' => TRUE,
    'post' => array(
      '#type' => 'checkbox',
      '#title' => t('Announce this post on Twitter'),
      '#default_value' => $status,
      '#id' => 'twitter-toggle',
    ),
    'status' => array(
      '#default_value' => $format,
      '#description' => t('The given text will be posted to twitter.com. You can use !url, !url-alias, !tinyurl, !title and !user as replacement text.'),
      '#maxlength' => 150,
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
    $summary = t('Default status: @status. Format: @format', array(
      '@status' => $settings['status'],
      '@format' => $settings['format'],
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
  return strlen($item['twitter_post_field']) == 0;
}
