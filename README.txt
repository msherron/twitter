Introduction
============
Twitter module allows listing tweets in blocks or pages. Its integration with Views opens the
door to all sorts of formatting (ie. as an automatic slideshow with views_slideshow). Other
submodules allow posting to twitter, executing actions when tweeting or login with a Twitter
account.

OAuth
=====
Except for just listing tweets, OAuth module is required to authenticate against Twitter. If you 
just want to list tweets in a block, follow the steps at http://drupal.org/node/1253026.

If you download the OAuth module, get the latest development version as the stable one has a
bug when cancelling an account. You can find it here: http://drupal.org/node/1167740

Once OAuth has been enabled, go to admin/config/services/twitter and follow instructions.

How to add a Twitter account to a Drupal user account
=====================================================
Read http://drupal.org/node/1253026 for details.

How to post to Twitter
======================
1. Read the OAuth section to install and configure OAuth.
2. Once OAuth has been configured, go to admin/config/services/twitter/post and select from which
   node types a user may post to Twitter and the default message.
3. Verify permissions at admin/people/permissions.
4. Add a Twitter account and try to edit or post content.
