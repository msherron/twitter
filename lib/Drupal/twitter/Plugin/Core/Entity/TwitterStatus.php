<?php

/**
 * @file
 * Definition of Drupal\twitter\Plugin\Core\Entity\TwitterStatus.
 */

namespace Drupal\twitter\Plugin\Core\Entity;

use Drupal\Core\Entity\Entity;
use Drupal\Core\Entity\Annotation\EntityType;
use Drupal\Core\Annotation\Translation;
use Drupal\Core\Language\Language;
use Drupal\user\UserInterface;

/**
 * Defines the twitter status entity class.
 *
 * @EntityType(
 *   id = "twitter_status",
 *   label = @Translation("Individual Twitter statuses"),
 *   module = "twitter",
 *   controllers = {
 *     "storage" = "Drupal\twitter\TwitterStatusStorageController",
 *     "access" = "Drupal\twitter\TwitterStatusAccessController",
 *     "render" = "Drupal\Core\Entity\EntityRenderController",
 *     "form" = {
 *       "default" = "Drupal\twitter\TwitterStatusFormController",
 *     },
 *     "translation" = "Drupal\twitter\TwitterStatusTranslationController"
 *   },
 *   base_table = "twitter",
 *   uri_callback = "twitter_status_uri",
 *   label_callback = "twitter_status_label",
 *   fieldable = TRUE,
 *   translatable = TRUE,
 *   entity_keys = {
 *     "id" = "twitter_id",
 *     "uuid" = "uuid"
 *   }
 * )
 */
class TwitterStatus extends EntityNG {
  /**
   * @var created_at
   */
  public $createdAt;

  public $id;

  public $text;

  public $source;

  public $truncated;

  public $favorited;

  public $inReplyToStatusId;

  public $inReplyToUserId;

  public $inReplyToScreenName;

  public $user;

  /**
   * Constructor for TwitterStatus
   */
  public function __construct($values = array()) {
    if (isset($values['user'])) {
      $this->user = new TwitterAccount($values['user']);
      unset($values['user']);
    }
    parent::__construct($values, 'twitter_status');
  }
}
