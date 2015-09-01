<?php
/**
 * @file
 * Contains \Drupal\twitter\Form\TwitterSettingsForm.
 */

namespace Drupal\twitter\Form;

use Drupal\Core\Url;
use Drupal\Core\Form\ConfigFormBase;
use Drupal\Core\Form\FormStateInterface;
use Drupal\Component\Utility\MapArray;

/**
 * Configure twitter settings for this site.
 */
class TwitterSettingsForm extends ConfigFormBase {


  /**
   * {@inheritdoc}
   */
  protected function getEditableConfigNames() {
    return [
      'twitter.settings'
    ];
  }

  /**
   * {@inheritdoc}
   */
  public function getFormId() {
    return 'twitter_settings_form';
  }

  /**
   * {@inheritdoc}
   */
  public function buildForm(array $form, FormStateInterface $form_state) {
    $twitter_config = $this->configFactory->get('twitter.settings');
    $form['import'] = array(
      '#type' => 'checkbox',
      '#title' => t('Import and display the Twitter statuses of site users who have entered their Twitter account information.'),
      '#default_value' => $twitter_config->get('import'),
    );
    $intervals = array(604800, 2592000, 7776000, 31536000);
    $options = array_merge(array(0 => t('Never')), array_map('format_interval', array_combine($intervals, $intervals)));
    $form['expire'] = array(
      '#type' => 'select',
      '#title' => t('Delete old statuses'),
      '#default_value' => $twitter_config->get('expire'),
      '#options' => $options,
      '#states' => array(
         'visible' => array(
           ':input[name=twitter_import]' => array('checked' => TRUE),
         ),
      ),
    );
    $form['oauth'] = array(
      '#type' => 'fieldset',
      '#title' => t('OAuth Settings'),
      '#description' => t('To enable OAuth based access for twitter, you must <a href="@url">register your application</a> with Twitter and add the provided keys here.', array('@url' => 'https://dev.twitter.com/apps/new')),
    );
    $form['oauth']['callback_url'] = array(
      '#type' => 'item',
      '#title' => t('Callback URL'),
      '#markup' => new Url('twitter/oauth', array('absolute' => TRUE)),
    );
    $form['oauth']['consumer_key'] = array(
      '#type' => 'textfield',
      '#title' => t('OAuth Consumer key'),
      '#default_value' => $twitter_config->get('consumer_key'),
    );
    $form['oauth']['consumer_secret'] = array(
      '#type' => 'textfield',
      '#title' => t('OAuth Consumer secret'),
      '#default_value' => $twitter_config->get('consumer_secret'),
    );
    // Twitter external APIs settings.
    $form['twitter'] = array(
      '#type' => 'fieldset',
      '#title' => t('Twitter Settings'),
      '#description' => t('The following settings connect Twitter module with external APIs. ' .
        'Change them if, for example, you want to use Identi.ca.'),
    );
    $form['twitter']['host'] = array(
      '#type' => 'textfield',
      '#title' => t('Twitter host'),
      '#default_value' => $twitter_config->get('host'),
    );
    $form['twitter']['api'] = array(
      '#type' => 'textfield',
      '#title' => t('Twitter API'),
      '#default_value' => $twitter_config->get('api'),
    );
    $form['twitter']['search'] = array(
      '#type' => 'textfield',
      '#title' => t('Twitter search'),
      '#default_value' => $twitter_config->get('search'),
    );
    $form['twitter']['tinyurl'] = array(
      '#type' => 'textfield',
      '#title' => t('TinyURL'),
      '#default_value' => $twitter_config->get('tinyurl'),
    );

    return parent::buildForm($form, $form_state);
  }

  /**
   * {@inheritdoc}
   */
  public function submitForm(array &$form, FormStateInterface $form_state) {
    $twitter_config = $this->configFactory->get('twitter.settings');
    $twitter_config
      ->set('import', $form_state['values']['import'])
      ->set('expire', $form_state['values']['expire'])
      ->set('consumer_key', $form_state['values']['consumer_key'])
      ->set('consumer_secret', $form_state['values']['consumer_secret'])
      ->set('host', $form_state['values']['host'])
      ->set('api', $form_state['values']['api'])
      ->set('search', $form_state['values']['search'])
      ->set('tinyurl', $form_state['values']['tinyurl'])
      ->save();
    parent::submitForm($form, $form_state);
  }

}
