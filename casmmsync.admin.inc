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
    'access arguments' => array('administer'),
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
  $form['cassmmsync_path'] = array(
    '#type' => 'textfield',
    '#title' => t('CASDirectory URL'),
    '#size' => 30,
    '#description' => 'The base URL of your CASDirectory web-service.',
  );

  return system_settings_form($form);
}