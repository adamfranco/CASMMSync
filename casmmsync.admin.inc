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

  $items['casmmsync/update_group'] = array(
    'page callback' => '_casmmsync_receive_group_update',
    'access callback' => true,
    'type' => MENU_CALLBACK,
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

  $form['server']['casmmsync_path'] = array(
    '#type' => 'textfield',
    '#title' => t('CASDirectory URL'),
    '#size' => 30,
    '#default_value' => variable_get('casmmsync_path', ''),
    '#description' => 'The base URL of your CASDirectory web-service.',
  );

  $form['server']['casmmsync_adminkey'] = array(
    '#type' => 'textfield',
    '#title' => t('Admin Access Key'),
    '#size' => 30,
    '#default_value' => variable_get('casmmsync_adminkey', ''),
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

  $form['cron']['casmmsync_maxexectime'] = array(
    '#type' => 'textfield',
    '#title' => t('Max Excecution Time'),
    '#size' => 10,
    '#default_value' => variable_get('casmmsync_maxexectime', 300),
    '#description' => 'An override for the PHP max_execution_time setting to allow the sync to complete.',
  );

  $form['cron']['casmmsync_always_sync_users'] = array(
    '#type' => 'checkbox',
    '#title' => t('Always sync users'),
    '#default_value' => variable_get('casmmsync_always_sync_users', TRUE),
    '#description' => t('If checked, users and groups will be synced on every cron run. <br/> If not checked, they will only be synced on cron runs that include <code>casmmsync_sync_users=true</code> in the request. This can be passed to cron web-requests as GET or POST variables such as in this example URL: <br/>&nbsp; &nbsp; <code>http://www.example.com/cron.php?casmmsync_sync_users=true</code> <br/><a href="!url">Run cron manually with user sync</a>. ', array(
      '!url' => url('admin/reports/status/run-cron', array('query' => array('casmmsync_sync_users' => 'true'), 'absolute' => true,)),

    )),
  );

  // Update Notification
  $form['update_notify'] = array(
    '#type' => 'fieldset',
    '#title' => t('Update notification settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['update_notify']['casmmsync_update_passkey'] = array(
    '#type' => 'textfield',
    '#title' => t('Group update notification passkey'),
    '#size' => 30,
    '#default_value' => variable_get('casmmsync_update_passkey', ''),
    '#description' => t('Enter a passkey here to allow CAS-MM Sync to recieve ping-back updates when groups are changed. This passkey should be configured in ping-back requests in the group-management system. The group-management system should make GET requests to the URL, <br/> &nbsp; &nbsp; @url <br/>where XXXXX is the passkey above and YYYYY is the group id.', array(
      '@url' => url('casmmsync/update_group', array(
        'query' => array(
          'passkey' => 'XXXXX',
          'group_id' => 'YYYYY',
        ),
        'absolute' => true,
      )))
    ),
  );

  return system_settings_form($form);
}