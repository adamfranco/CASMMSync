<?php
// $Id$

/**
 * @file
 * Synchronizes users and groups from a CASDirectory into Monster Menus.
 *
 * Synchronizes users and groups from a CASDirectory into Monster Menus so they
 * can be assigned permissions prior to logging in to Drupal.
 */

/**
 * Implements hook_menu().
 */
function casmmsync_menu() {
  $items = array();

  $items['admin/user/casmmsync'] = array(
    'title' => t('CAS-MM Sync settings'),
    'description' => 'Configure synchronization of users and groups from a CASDirectory into Monster Menus',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('casmmsync_admin_settings'),
    'access arguments' => array('administer site configuration'),
    'type' => MENU_NORMAL_ITEM,
  );


  return $items;
}


/**
 * Form builder. Configure CAS-MM Sync
 *
 * @ingroup forms
 * @see system_settings_form().
 */
function casmmsync_admin_settings() {
  // Server
  $form['server'] = array(
    '#type' => 'fieldset',
    '#title' => t('CASDirectory server settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['server']['cassmmsync_path'] = array(
    '#type' => 'textfield',
    '#title' => t('CASDirectory URL'),
    '#size' => 30,
    '#default_value' => variable_get('cassmmsync_path', ''),
    '#description' => 'The base URL of your CASDirectory web-service.',
  );

  $form['server']['cassmmsync_adminkey'] = array(
    '#type' => 'textfield',
    '#title' => t('Admin Access Key'),
    '#size' => 30,
    '#default_value' => variable_get('cassmmsync_adminkey', ''),
    '#description' => 'The secret key for accessing the directory service without proxy authentication.',
  );

  // Cron
  $form['cron'] = array(
    '#type' => 'fieldset',
    '#title' => t('Cron settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['cron']['casmmsync_show_debug'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show Debug'),
    '#default_value' => variable_get('casmmsync_show_debug', FALSE),
    '#description' => 'Show debugging info when running cron.',
  );

  $form['cron']['cassmmsync_maxexectime'] = array(
    '#type' => 'textfield',
    '#title' => t('Max Excecution Time'),
    '#size' => 10,
    '#default_value' => variable_get('cassmmsync_maxexectime', 300),
    '#description' => 'An override for the PHP max_execution_time setting to allow the sync to complete.',
  );

  return system_settings_form($form);
}