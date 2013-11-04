# Drupal Drush Site Build

This Drush extension allows you to run the Drush `site-install` command using values
taken from a Drush alias file.

## Installation

Clone into `~/.drush/site-build/`.

## Setup

Create an alias file in `~/.drush`:

For example:

```
$aliases['local'] = array(
  'root' => '<path to Drupal install>',
  'uri' => 'http://<your URL>',
  'databases' => array(
    'default' => 
    array (
      'default' => 
      array (
        'database' => '',
        'username' => '',
        'password' => '',
        'host' => '',
        'port' => '',
        'driver' => 'mysql',
        'prefix' => false,
      ),
    ),
  ),
  'variables' => array(
    'profile' => '<install profile to use>',
	'site-name' => 'Your Site Name',
	'account-name' => '<account name>',
	'account-pass' => '<account password>',
    'account-mail' => '<your email>',
  ),
  'path-aliases' => 
    array (
      '%site' => 'sites/default/',
      '%files' => 'sites/default/files',
    ),
);
```

## Usage

    drush @<site alias>.local site-build

## Hooks

The site will be bootstrapped once the site-install task has been run.  This allows you 
to run Drush command hooks from within your custom modules or installation profile.

    // my_module/my_module.drush.inc
    function drush_MY_MODULE_post_site_build() {
       // run functions after the command has finished.
    }