<?php

/**
 * @file
 * Definition of Drupal\twitter\Tests\TwitterCore.
 */

namespace Drupal\twitter\Tests;

use Drupal\simpletest\WebTestBase;

/**
 * Tests the Twitter module functionality.
 */
class TwitterCore extends WebTestBase {

  /**
   * Modules to enable.
   *
   * @var array
   */
  public static $modules = array('twitter', 'views', 'twitter_mock');

  protected $user;

  public static function getInfo() {
    return array(
      'name' => 'Main tests',
      'description' => 'Tests main module features such as adding accounts or loading tweets.',
      'group' => 'Twitter',
    );
  }

  /**
   * Tests account addition without Oauth module activated
   */
  public function testAccountAdditionNoOauth() {
    // Create user
    $this->user = $this->drupalCreateUser(array(
      'add twitter accounts',
      'import own tweets',
    ));
    $this->drupalLogin($this->user);

    // Add a Twitter account
    $edit = array(
      'screen_name' => 'drupal',
    );
    $this->drupalPost('user/' . $this->user->uid . '/edit/twitter',
                      $edit, t('Add account'));
    $this->assertLink('drupal', 0,
      t('Twitter account was added successfully'));

    // Load tweets
    twitter_cron();
    $this->drupalGet('user/' . $this->user->uid . '/tweets');
    $elements = $this->xpath('//div[contains(@class, "view-tweets")]/div/table');
    $this->assertTrue(count($elements), 'Tweets were loaded successfully.');
    // Delete the Twitter account
    $edit = array(
      'accounts[0][delete]' => 1,
    );
    $this->drupalPost('user/' . $this->user->uid . '/edit/twitter',
                      $edit, t('Save changes'));
    $this->assertText(t('The Twitter account was deleted.'));
  }
}
