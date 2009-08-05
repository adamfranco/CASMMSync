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

  $form['server']['casmmsync_show_debug'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show Debug'),
    '#size' => 30,
    '#default_value' => variable_get('casmmsync_show_debug', FALSE),
    '#description' => 'Show debugging info when running cron.',
  );

  // Attribute Mapping
  $form['attributes'] = array(
    '#type' => 'fieldset',
    '#title' => t('User attribute settings'),
    '#description' => t('If multiple fields should be concatenated, list fields in order, separated by commas.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['attributes']['cassmmsync_attributes_concat'] = array(
      '#type' => 'textfield',
      '#title' => t('Concatenation string'),
      '#default_value' => variable_get('cassmmsync_attributes_concat', ' '),
      '#size' => 30,
      '#description' => t('String to use when concatenating attributes (a space by default).'),
    );

    $form['attributes']['cassmmsync_attributes_uid'] = array(
      '#type' => 'textfield',
      '#title' => t('UID'),
      '#default_value' => variable_get('cassmmsync_attributes_uid', ''),
      '#size' => 30,
      '#description' => t('Field to map to Drupal\'s internal user id. If blank, the CAS netid (&lt;cas:user&gt; element) value will be used.'),
    );

    $form['attributes']['cassmmsync_attributes_name'] = array(
      '#type' => 'textfield',
      '#title' => t('Name'),
      '#default_value' => variable_get('cassmmsync_attributes_name', ''),
      '#size' => 30,
      '#description' => t('A display name for the user. E.g. FirstName,LastName'),
    );

    $form['attributes']['cassmmsync_attributes_mail'] = array(
      '#type' => 'textfield',
      '#title' => t('EMail'),
      '#default_value' => variable_get('cassmmsync_attributes_mail', ''),
      '#size' => 30,
      '#description' => t('The user\'s email address field.'),
    );

    $form['attributes']['cassmmsync_attributes_groups'] = array(
      '#type' => 'textfield',
      '#title' => t('Groups'),
      '#default_value' => variable_get('cassmmsync_attributes_groups', ''),
      '#size' => 30,
      '#description' => t('The group-membership field.'),
    );

  return system_settings_form($form);
}