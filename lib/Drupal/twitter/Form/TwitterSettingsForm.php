<?php
/**
 * @file
 * Contains \Drupal\twitter\Form\TwitterSettingsForm.
 */

namespace Drupal\twitter\Form;

use Drupal\system\SystemConfigFormBase;

/**
 * Configure twitter settings for this site.
 */
class TwitterSettingsForm extends SystemConfigFormBase {

  /**
   * Implements \Drupal\Core\Form\FormInterface::getFormID().
   */
  public function getFormID() {
    return 'twitter_settings_form';
  }

  /**
   * Implements \Drupal\Core\Form\FormInterface::buildForm().
   */
  public function buildForm(array $form, array &$form_state) {
    $form['twitter_import'] = array(
      '#type' => 'checkbox',
      '#title' => t('Import and display the Twitter statuses of site users who have entered their Twitter account information.'),
      '#default_value' => variable_get('twitter_import', 1),
    );
    $form['twitter_expire'] = array(
      '#type' => 'select',
      '#title' => t('Delete old statuses'),
      '#default_value' => variable_get('twitter_expire', 0),
      '#options' => array(0 => t('Never')) + drupal_map_assoc(array(604800, 2592000, 7776000, 31536000), 'format_interval'),
      '#states' => array(
         'visible' => array(
           ':input[name=twitter_import]' => array('checked' => TRUE),
         ),
      ),
    );
    $form['oauth'] = array(
      '#type' => 'fieldset',
      '#title' => t('OAuth Settings'),
      '#access' => module_exists('oauth_common'),
      '#description' => t('To enable OAuth based access for twitter, you must <a href="@url">register your application</a> with Twitter and add the provided keys here.', array('@url' => 'https://dev.twitter.com/apps/new')),
    );
    $form['oauth']['callback_url'] = array(
      '#type' => 'item',
      '#title' => t('Callback URL'),
      '#markup' => url('twitter/oauth', array('absolute' => TRUE)),
    );
    $form['oauth']['twitter_consumer_key'] = array(
      '#type' => 'textfield',
      '#title' => t('OAuth Consumer key'),
      '#default_value' => variable_get('twitter_consumer_key', NULL),
    );
    $form['oauth']['twitter_consumer_secret'] = array(
      '#type' => 'textfield',
      '#title' => t('OAuth Consumer secret'),
      '#default_value' => variable_get('twitter_consumer_secret', NULL),
    );
    // Twitter external APIs settings.
    $form['twitter'] = array(
      '#type' => 'fieldset',
      '#title' => t('Twitter Settings'),
      '#description' => t('The following settings connect Twitter module with external APIs. ' .
        'Change them if, for example, you want to use Identi.ca.'),
    );
    $form['twitter']['twitter_host'] = array(
      '#type' => 'textfield',
      '#title' => t('Twitter host'),
      '#default_value' => variable_get('twitter_host', TWITTER_HOST),
    );
    $form['twitter']['twitter_api'] = array(
      '#type' => 'textfield',
      '#title' => t('Twitter API'),
      '#default_value' => variable_get('twitter_api', TWITTER_API),
    );
    $form['twitter']['twitter_search'] = array(
      '#type' => 'textfield',
      '#title' => t('Twitter search'),
      '#default_value' => variable_get('twitter_search', TWITTER_SEARCH),
    );
    $form['twitter']['twitter_tinyurl'] = array(
      '#type' => 'textfield',
      '#title' => t('TinyURL'),
      '#default_value' => variable_get('twitter_tinyurl', TWITTER_TINYURL),
    );

    return parent::buildForm($form, $form_state);
  }

  /**
   * Implements \Drupal\Core\Form\FormInterface::submitForm().
   */
  public function submitForm(array &$form, array &$form_state) {

    parent::submitForm($form, $form_state);
  }

}
