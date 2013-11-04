<?php

/**
 * @file
 * Drush integration for site installation from alias files.
 */

/**
 * Implements hook_drush_command().
 */
function site_build_drush_command() {
  $items['site-build'] = array(
    'description' => dt('use site install to build a site using options set in an alias file.'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_ROOT,
    'aliases' => array('sb')
  );

  return $items;
}

/**
 * Get variables from the alias file.
 *
 * @return mixed
 */
function _site_build_get_vars() {

  $alias = drush_get_context('DRUSH_TARGET_SITE_ALIAS');

  if ( !$alias ) {
    return drush_set_error('DRUPAL_SITE_NOT_FOUND', dt('You need to specify an alias.'));
  }

  $alias_record = drush_sitealias_get_record($alias);
  $vars = $alias_record['variables'];

  return $vars;
}

/**
 * Command validate.
 */
function drush_site_build_validate() {

  $vars = _site_build_get_vars();

  if ( !$vars ) {
    return FALSE;
  }

  array_walk($vars, function ($value, $key) {
    drush_set_option($key, $value);
  });
}

/**
 * Run the command.
 *
 * @return bool
 */
function drush_site_build() {

  $vars = _site_build_get_vars();

  /*
   * Invoke the core site-install task
   */
  drush_invoke('site-install', array(
    $vars['profile'],
  ));

  /*
   * Bootstrap the new installation so that the hooks defined in 
   * profile and module *.drush.inc files can run full commands.
   */
  drush_bootstrap_to_phase(DRUSH_BOOTSTRAP_DRUPAL_FULL);

}

/**
 * Post site-build operations
 */
function drush_site_build_post_site_build() {
  $alias = drush_get_context('DRUSH_TARGET_SITE_ALIAS');

  drush_shell_exec('drush ' . $alias . ' uli --browser=0 | pbcopy');
}
