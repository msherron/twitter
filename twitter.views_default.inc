<?php
/**
 * @file
 * Default views for Twitter module.
 */
function twitter_views_default_views() {
  $view = new view();
  $view->name = 'tweets';
  $view->description = 'Displays Twitter.com status messages for users who have associated Twitter accounts.';
  $view->tag = '';
  $view->base_table = 'twitter';
  $view->human_name = 'Tweets';
  $view->core = 0;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Tweets */
  $handler = $view->new_display('default', 'Tweets', 'default');
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['grouping'] = '';
  $handler->display->display_options['style_options']['columns'] = array(
    'profile_image_url' => 'profile_image_url',
    'text' => 'text',
    'created_time' => 'text',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'profile_image_url' => array(
      'sortable' => 0,
      'separator' => '',
    ),
    'text' => array(
      'sortable' => 0,
      'separator' => ' &#8212; ',
    ),
    'created_time' => array(
      'sortable' => 0,
      'separator' => '',
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  /* Field: Twitter: Profile image */
  $handler->display->display_options['fields']['profile_image_url']['id'] = 'profile_image_url';
  $handler->display->display_options['fields']['profile_image_url']['table'] = 'twitter_account';
  $handler->display->display_options['fields']['profile_image_url']['field'] = 'profile_image_url';
  $handler->display->display_options['fields']['profile_image_url']['label'] = '';
  /* Field: Twitter: Message text */
  $handler->display->display_options['fields']['text']['id'] = 'text';
  $handler->display->display_options['fields']['text']['table'] = 'twitter';
  $handler->display->display_options['fields']['text']['field'] = 'text';
  $handler->display->display_options['fields']['text']['label'] = '';
  $handler->display->display_options['fields']['text']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['text']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['text']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['text']['alter']['external'] = 0;
  $handler->display->display_options['fields']['text']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['text']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['text']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['text']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['text']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['text']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['text']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['text']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['text']['alter']['html'] = 0;
  $handler->display->display_options['fields']['text']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['text']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['text']['hide_empty'] = 0;
  $handler->display->display_options['fields']['text']['empty_zero'] = 0;
  $handler->display->display_options['fields']['text']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['text']['link_urls'] = 1;
  $handler->display->display_options['fields']['text']['link_usernames'] = 1;
  $handler->display->display_options['fields']['text']['link_hashtags'] = 1;
  /* Field: Twitter: Created time */
  $handler->display->display_options['fields']['created_time']['id'] = 'created_time';
  $handler->display->display_options['fields']['created_time']['table'] = 'twitter';
  $handler->display->display_options['fields']['created_time']['field'] = 'created_time';
  $handler->display->display_options['fields']['created_time']['label'] = '';
  $handler->display->display_options['fields']['created_time']['date_format'] = 'time ago';
  /* Sort criterion: Twitter: Created time */
  $handler->display->display_options['sorts']['created_time']['id'] = 'created_time';
  $handler->display->display_options['sorts']['created_time']['table'] = 'twitter';
  $handler->display->display_options['sorts']['created_time']['field'] = 'created_time';
  $handler->display->display_options['sorts']['created_time']['order'] = 'DESC';
  /* Filter criterion: Twitter: Protected status */
  $handler->display->display_options['filters']['protected']['id'] = 'protected';
  $handler->display->display_options['filters']['protected']['table'] = 'twitter_account';
  $handler->display->display_options['filters']['protected']['field'] = 'protected';
  $handler->display->display_options['filters']['protected']['value'] = 0;
  $handler->display->display_options['filters']['protected']['group'] = '0';
  $handler->display->display_options['filters']['protected']['expose']['operator'] = FALSE;

  /* Display: Page */
  $handler = $view->new_display('page', 'Tweets', 'page_all_tweets');
  $handler->display->display_options['display_description'] = 'Lists unprotected tweets.';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Twitter: Login name */
  $handler->display->display_options['arguments']['screen_name']['id'] = 'screen_name';
  $handler->display->display_options['arguments']['screen_name']['table'] = 'twitter';
  $handler->display->display_options['arguments']['screen_name']['field'] = 'screen_name';
  $handler->display->display_options['arguments']['screen_name']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['screen_name']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['screen_name']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['screen_name']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['screen_name']['limit'] = '0';
  $handler->display->display_options['path'] = 'tweets';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['use_more'] = FALSE;
  $handler->display->display_options['use_more'] = TRUE;
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['style_options']['grouping'] = '';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['inline'] = array(
    'text' => 'text',
    'created_time' => 'created_time',
  );
  $handler->display->display_options['row_options']['separator'] = ' &#8212; ';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Twitter: Message text */
  $handler->display->display_options['fields']['text']['id'] = 'text';
  $handler->display->display_options['fields']['text']['table'] = 'twitter';
  $handler->display->display_options['fields']['text']['field'] = 'text';
  $handler->display->display_options['fields']['text']['label'] = '';
  $handler->display->display_options['fields']['text']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['text']['link_urls'] = 1;
  $handler->display->display_options['fields']['text']['link_usernames'] = 1;
  $handler->display->display_options['fields']['text']['link_hashtags'] = 1;
  $handler->display->display_options['fields']['text']['link_attributes'] = 1;
  /* Field: Twitter: Created time */
  $handler->display->display_options['fields']['created_time']['id'] = 'created_time';
  $handler->display->display_options['fields']['created_time']['table'] = 'twitter';
  $handler->display->display_options['fields']['created_time']['field'] = 'created_time';
  $handler->display->display_options['fields']['created_time']['label'] = '';
  $handler->display->display_options['fields']['created_time']['date_format'] = 'time ago';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $handler->display->display_options['block_description'] = 'Tweets';

  return array('tweets' => $view);
}
