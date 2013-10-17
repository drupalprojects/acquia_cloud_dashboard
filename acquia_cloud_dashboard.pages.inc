<?php

/**
 * @file
 * The configuration and report pages of Acquia Cloud API
 */

/**
 * Acquia Cloud API settings form.
 */
function acquia_cloud_dashboard_configure_form() {
  $form = array();

  $form['acquia_cloud_username'] = array(
    '#type' => 'textfield',
    '#title' => t('Acquia Cloud Username'),
    '#default_value' => variable_get('acquia_cloud_username', ''),
    '#description' => t('Enter your cloud username as shown on http://network.acquia.com'),
    '#size' => '40',
    '#required' => TRUE,
  );

  $form['acquia_cloud_password'] = array(
    '#type' => 'textfield',
    '#title' => t('Acquia Cloud Password'),
    '#default_value' => variable_get('acquia_cloud_password', ''),
    '#description' => t('Enter your cloud password as shown on http://network.acquia.com'),
    '#size' => '40',
    '#required' => TRUE,
  );

  $form['acquia_cloud_refresh_interval'] = array(
    '#type' => 'textfield',
    '#title' => t('Report Refresh Interval (seconds)'),
    '#default_value' => variable_get('acquia_cloud_refresh_interval', 3600),
    '#description' => t('Enter the time interval at which the report should be refreshed.'),
    '#size' => '5',
    '#required' => TRUE,
  );

  $form['acquia_cloud_no_of_tasks'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of recent tasks from tasklist to show'),
    '#default_value' => variable_get('acquia_cloud_no_of_tasks', 25),
    '#description' => t('Show the latest tasks from Task List, as seen on your Workflow page on Dashboard'),
    '#size' => '5',
    '#required' => TRUE,
  );

  return system_settings_form($form);
}

/**
 * Domain addition form function.
 */
function acquia_cloud_dashboard_configure_add_domain_form($form_state, $form, $site_name, $env) {
  $form = array();
  $form['acquia_cloud_domain_site'] = array(
    '#type' => 'textfield',
    '#title' => t('Acquia Cloud Site'),
    '#default_value' => $site_name,
    '#size' => '40',
    '#required' => TRUE,
    '#disabled' => TRUE,
  );
  $form['acquia_cloud_domain_env'] = array(
    '#type' => 'textfield',
    '#title' => t('Acquia Cloud Environment'),
    '#default_value' => $env,
    '#size' => '40',
    '#required' => TRUE,
    '#disabled' => TRUE,
  );
  $form['acquia_cloud_domain_domain'] = array(
    '#type' => 'textfield',
    '#title' => t('Domain Name to be added'),
    '#size' => '40',
    '#required' => TRUE,
  );

  $form['acquia_cloud_domain_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add Domain'),
  );

  return $form;
}

/**
 * SSH Key addition form function.
 */
function acquia_cloud_dashboard_configure_add_key_form($form_state, $form, $site_name) {
  $form = array();
  $form['acquia_cloud_key_site'] = array(
    '#type' => 'textfield',
    '#title' => t('Acquia Cloud Site'),
    '#default_value' => $site_name,
    '#size' => '40',
    '#required' => TRUE,
    '#disabled' => TRUE,
  );
  $form['acquia_cloud_key_nick'] = array(
    '#type' => 'textfield',
    '#title' => t('Nickname for the Key'),
    '#size' => '40',
    '#required' => TRUE,
  );
  $form['acquia_cloud_key_key'] = array(
    '#type' => 'textarea',
    '#title' => t('Key to be added'),
    '#required' => TRUE,
  );

  $form['acquia_cloud_domain_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add Domain'),
  );

  return $form;
}

/**
 * Submit handler to add ssh-key form.
 */
function acquia_cloud_dashboard_configure_add_key_form_submit($form, &$form_state) {
  $site_name = $form_state['values']['acquia_cloud_key_site'];
  $key_nick = $form_state['values']['acquia_cloud_key_nick'];
  $key_key = $form_state['values']['acquia_cloud_key_key'];

  acquia_cloud_dashboard_curl_caller_post("sites/$site_name/sshkeys", "POST", TRUE, array('ssh_pub_key' => $key_key), array('nickname' => $key_nick));
  drupal_goto('admin/config/cloud-api/view');
}

/**
 * Delete Domain Form function.
 */
function acquia_cloud_dashboard_configure_delete_domain_form($form_state, $form, $site_name, $env, $domain) {
  $form = array();
  $form['acquia_cloud_domain_site'] = array(
    '#type' => 'textfield',
    '#title' => t('Acquia Cloud Site'),
    '#default_value' => $site_name,
    '#size' => '40',
    '#required' => TRUE,
    '#disabled' => TRUE,
  );
  $form['acquia_cloud_domain_env'] = array(
    '#type' => 'textfield',
    '#title' => t('Acquia Cloud Environment'),
    '#default_value' => $env,
    '#size' => '40',
    '#required' => TRUE,
    '#disabled' => TRUE,
  );
  $form['acquia_cloud_domain_domain'] = array(
    '#type' => 'textfield',
    '#title' => t('Domain Name to be added'),
    '#size' => '40',
    '#default_value' => $domain,
    '#required' => TRUE,
    '#disabled' => TRUE,
  );

  $form['acquia_cloud_domain_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Confirm Deletion of Domain'),
  );

  return $form;
}

/**
 * Purge Cache form function.
 */
function acquia_cloud_dashboard_configure_purge_varnish_form($form_state, $form, $site_name, $env, $domain) {
  $form = array();
  $form['acquia_cloud_purge_domain_site'] = array(
    '#type' => 'textfield',
    '#title' => t('Acquia Cloud Site'),
    '#default_value' => $site_name,
    '#size' => '40',
    '#required' => TRUE,
    '#disabled' => TRUE,
  );
  $form['acquia_cloud_purge_domain_env'] = array(
    '#type' => 'textfield',
    '#title' => t('Acquia Cloud Environment'),
    '#default_value' => $env,
    '#size' => '40',
    '#required' => TRUE,
    '#disabled' => TRUE,
  );
  $form['acquia_cloud_purge_domain_domain'] = array(
    '#type' => 'textfield',
    '#title' => t('Domain Name to be added'),
    '#size' => '40',
    '#default_value' => $domain,
    '#required' => TRUE,
    '#disabled' => TRUE,
  );

  $form['acquia_cloud_purge_domain_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Confirm Purging Varnish Cache for this domain'),
  );

  return $form;
}

/**
 * Delete SSH Key form function.
 */
function acquia_cloud_dashboard_configure_delete_key_form($form_state, $form, $site_name, $keyid, $key_nick) {
  $form = array();
  $form['acquia_cloud_key_site'] = array(
    '#type' => 'textfield',
    '#title' => t('Acquia Cloud Site'),
    '#default_value' => $site_name,
    '#size' => '40',
    '#required' => TRUE,
    '#disabled' => TRUE,
  );
  $form['acquia_cloud_key_nick'] = array(
    '#type' => 'textfield',
    '#title' => t('Name of the key to be deleted'),
    '#default_value' => $key_nick,
    '#size' => '40',
    '#required' => TRUE,
    '#disabled' => TRUE,
  );

  $form['acquia_cloud_key_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Id of the key to be deleted'),
    '#default_value' => $keyid,
    '#size' => '40',
    '#required' => TRUE,
    '#disabled' => TRUE,
  );

  $form['acquia_cloud_domain_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Confirm Deletion of SSH Key'),
  );

  return $form;
}

/**
 * Submit handler for deleting SSH Key.
 */
function acquia_cloud_dashboard_configure_delete_key_form_submit($form, &$form_state) {
  $site_name = $form_state['values']['acquia_cloud_key_site'];
  $key_id = $form_state['values']['acquia_cloud_key_id'];

  acquia_cloud_dashboard_curl_caller_post("sites/$site_name/sshkeys/$key_id", "DELETE");
  drupal_goto('admin/config/cloud-api/view');
}

/**
 * Submit handler for adding domain.
 */
function acquia_cloud_dashboard_configure_add_domain_form_submit($form, &$form_state) {
  $site_name = $form_state['values']['acquia_cloud_domain_site'];
  $env = $form_state['values']['acquia_cloud_domain_env'];
  $domain_name = $form_state['values']['acquia_cloud_domain_domain'];

  acquia_cloud_dashboard_curl_caller_post("sites/$site_name/envs/$env/domains/$domain_name");
  drupal_goto('admin/config/cloud-api/view');
}

/**
 * Submit handler for delete domain form.
 */
function acquia_cloud_dashboard_configure_delete_domain_form_submit($form, &$form_state) {
  $site_name = $form_state['values']['acquia_cloud_domain_site'];
  $env = $form_state['values']['acquia_cloud_domain_env'];
  $domain_name = $form_state['values']['acquia_cloud_domain_domain'];

  acquia_cloud_dashboard_curl_caller_post("sites/$site_name/envs/$env/domains/$domain_name", "DELETE");
  drupal_goto('admin/config/cloud-api/view');
}

/**
 * Submit handler for purge domain cache form.
 */
function acquia_cloud_dashboard_configure_purge_varnish_form_submit($form, &$form_state) {
  $site_name = $form_state['values']['acquia_cloud_purge_domain_site'];
  $env = $form_state['values']['acquia_cloud_purge_domain_env'];
  $domain_name = $form_state['values']['acquia_cloud_purge_domain_domain'];

  acquia_cloud_dashboard_curl_caller_post("sites/$site_name/envs/$env/domains/$domain_name/cache", "DELETE");
  drupal_goto('admin/config/cloud-api/view');
}

/**
 * Helper function to manually refresh api report page.
 */
function acquia_cloud_dashboard_report_refresh() {
  acquia_cloud_dashboard_get_html_report();
  drupal_set_message(t('Cloud Status Report has been refreshed'), 'warning');
  drupal_goto('admin/config/cloud-api/view');
}

/**
 * Page call back that returns the report markup.
 */
function acquia_cloud_dashboard_report() {
  if (variable_get('acquia_cloud_username', "") != "") {
    $report_html = t('<b>Report was last updated !time_ago ago</b><br/>', array('!time_ago' => format_interval(REQUEST_TIME - variable_get('acquia_cloud_last_report_generated_time'))));
    $report_html .= l(t('Refresh Report'), 'admin/config/cloud-api/refresh');

    $time_last_run = variable_get('acquia_cloud_last_report_generated_time', 0);
    if (time() - $time_last_run > variable_get('acquia_cloud_refresh_interval', 3600)) {
      $report_html .= acquia_cloud_dashboard_get_html_report();
    }
    else {
      $report_html .= variable_get('acquia_cloud_report_html', t('Report Not Generated Yet'));
    }
    return $report_html;
  }
  else {
    drupal_set_message(t('Please configure your Cloud API credentials.'), 'warning');
    drupal_goto('admin/config/cloud-api/configure');
  }
}

/**
 * Helper function that builds the report markup.
 */
function acquia_cloud_dashboard_get_html_report() {
  $report_html = '';
  /*
   * Show Sites info
   */
  $sites_data = acquia_cloud_dashboard_curl_caller("sites");
  $header = array();
  $rows = array();
  $header[] = array("data" => "Site Name");
  $header[] = array("data" => "Site Information");
  foreach ($sites_data as $key => $value) {
    $site_raw_name = explode(':', $value);
    $site_name = $site_raw_name[1];
    $row = array();
    $row[] = $value;
    /*
     * Get the site info
     */
    $site_info_array = acquia_cloud_dashboard_curl_caller("sites/$site_name");
    $site_rows = array();
    foreach ($site_info_array as $key => $value) {
      $site_row = array();
      $site_row[] = $key;
      $site_row[] = $value;
      $site_rows[] = $site_row;
    }
    $site_info_table_html = theme('table', array(
      'header' => array('Parameter', 'Value'),
      'rows' => $site_rows,
        ));

    /*
     * Get the Site SSH Keys.
     */
    $site_ssh_table_html = l(t('Add SSH Key to this site'), "admin/config/cloud-api/add/key/$site_name");
    $site_ssh_keys_array = acquia_cloud_dashboard_curl_caller("sites/$site_name/sshkeys");
    $site_ssh_keys = array();
    foreach ($site_ssh_keys_array as $key => $value) {
      $site_ssh_row = array();
      $site_ssh_row[] = $value['nickname'];
      $site_ssh_row[] = drupal_substr($value['ssh_pub_key'], 0, 10) . ".....";
      $key_id = $value['id'];
      $key_nick = $value['nickname'];
      $site_ssh_row[] = l(t('Delete Key'), "admin/config/cloud-api/delete/key/$site_name/$key_id/$key_nick");
      $site_ssh_keys[] = $site_ssh_row;
    }
    $site_ssh_table_html .= theme('table', array(
      'header' => array('SSH Key Nick Name', 'SSH Key', 'Delete'),
      'rows' => $site_ssh_keys,
        ));

    /*
     * Get the Site DBs
     */
    $site_databases_array = acquia_cloud_dashboard_curl_caller("sites/$site_name/dbs");
    $site_dbs = array();
    foreach ($site_databases_array as $key => $value) {
      $site_db_row = array();
      $site_db_row[] = $value['name'];
      $site_dbs[] = $site_db_row;
    }
    $site_dbs_table_html = theme('table', array(
      'header' => array('Databases'),
      'rows' => $site_dbs,
        ));

    /*
     * Get the Environments
     */
    $site_envs_array = acquia_cloud_dashboard_curl_caller("sites/$site_name/envs");
    $site_envs = array();
    foreach ($site_envs_array as $key => $value) {
      $site_env_row = array();
      $env = $value['name'];
      $site_env_row[] = $env;
      /*
       * For each Env, get the domains
       */
      $env_domains_table_html = l(t('Add Domain to this Environment'), "admin/config/cloud-api/add/domain/$site_name/$env");
      $env_domains_array = acquia_cloud_dashboard_curl_caller("sites/$site_name/envs/$env/domains");
      $env_domains = array();
      foreach ($env_domains_array as $key => $value) {
        $env_domain_row = array();
        $domain_name = $value['name'];
        $env_domain_row[] = $domain_name;
        $env_domain_row[] = l(t('Delete Domain'), "admin/config/cloud-api/delete/domain/$site_name/$env/$domain_name");
        $env_domain_row[] = l(t('Purge Varnish Cache'), "admin/config/cloud-api/purge/domain/$site_name/$env/$domain_name");
        $env_domains[] = $env_domain_row;
      }
      $env_domains_table_html .= theme('table', array(
        'header' => array('Domain', 'Delete', 'Purge Varnish'),
        'rows' => $env_domains,
          ));

      /*
       * For each Env, get the servers
       */
      $env_servers_array = acquia_cloud_dashboard_curl_caller("sites/$site_name/envs/$env/servers");
      $env_servers = array();
      foreach ($env_servers_array as $key => $value) {
        $env_server_row = array();
        $server_name = $value['name'];
        $env_server_row[] = $server_name;

        /*
         * Get the server info
         */
        $server_info_array = acquia_cloud_dashboard_curl_caller("sites/$site_name/envs/$env/servers/$server_name");
        $server_rows = array();
        foreach ($server_info_array as $key => $value) {
          $server_row = array();
          $server_row[] = $key;
          $server_row[] = $value;
          $server_rows[] = $server_row;
        }
        $server_info_table_html = theme('table', array(
          'header' => array('Parameter', 'Value'),
          'rows' => $server_rows,
            ));


        $env_server_row[] = $server_info_table_html;
        $env_servers[] = $env_server_row;
      }
      $env_servers_table_html = theme('table', array('header' => array('Server', 'Server Info'),
        'rows' => $env_servers));


      $site_env_row[] = $env_domains_table_html . $env_servers_table_html;
      $site_envs[] = $site_env_row;
    }
    $site_envs_table_html = theme('table', array('header' => array('Environment', 'Environment Details'),
      'rows' => $site_envs));



    /*
     * Get Task List for Site
     */
    $task_list_raw = acquia_cloud_dashboard_curl_caller("sites/$site_name/tasks");
    $no_of_tasks = variable_get('acquia_cloud_no_of_tasks', 25);
    $tasks_array_trimmed = array_reverse(array_slice($task_list_raw, -$no_of_tasks));
    $task_rows = array();
    foreach ($tasks_array_trimmed as $key => $value) {
      $task_row = array();
      $task_row[] = date('l jS \of F Y h:i:s A', $value['started']);
      $task_row[] = $value['state'];
      $task_row[] = $value['description'];
      $task_rows[] = $task_row;
    }
    $site_tasks_table_html = theme('table', array(
      'header' => array('Time Started', 'Status', 'Task Details'),
      'rows' => $task_rows,
        ));

    /*
     * Join the report
     */
    $row[] = $site_info_table_html . $site_ssh_table_html . $site_dbs_table_html . $site_envs_table_html . $site_tasks_table_html;

    $rows[] = $row;
  }

  $report_html .= theme('table', array('header' => $header, 'rows' => $rows));
  variable_set('acquia_cloud_last_report_generated_time', REQUEST_TIME);
  variable_set('acquia_cloud_report_html', $report_html);

  return $report_html;
}

/**
 * Helper method that makes the Curl Calls (GET).
 */
function acquia_cloud_dashboard_curl_caller($method) {
  $url = "https://cloudapi.acquia.com/v1/" . $method . ".json";
  //  dsm($url);
  $username = variable_get('acquia_cloud_username', "");
  $password = variable_get('acquia_cloud_password', "");
  $ch = curl_init($url);
  curl_setopt($ch, CURLOPT_USERPWD, "$username:$password");
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
  $server_output = curl_exec($ch);
  curl_close($ch);
  $decoded_output = drupal_json_decode($server_output);
  return $decoded_output;
}

/**
 * Helper function that makes the curl calls (POST).
 */
function acquia_cloud_dashboard_curl_caller_post($method, $request = "POST", $binary = FALSE, $post_data = array(), $params = array()) {
  $url = "https://cloudapi.acquia.com/v1/" . $method . ".json";

  if (count($params)) {
    $url .= "?";
    foreach ($params as $key => $value) {
      $en_key = urlencode($key);
      $en_val = urlencode($value);
      $url .= ("$en_key=$en_val&");
    }
  }
  $username = variable_get('acquia_cloud_username', "");
  $password = variable_get('acquia_cloud_password', "");
  $ch = curl_init();

  curl_setopt($ch, CURLOPT_USERPWD, "$username:$password");

  //set the url, number of POST vars, POST data
  curl_setopt($ch, CURLOPT_URL, $url);
  curl_setopt($ch, CURLOPT_POST, 0);
  curl_setopt($ch, CURLOPT_POSTFIELDS, drupal_json_encode($post_data));
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($ch, CURLOPT_CUSTOMREQUEST, $request);
  if ($binary) {
    curl_setopt($ch, CURLOPT_BINARYTRANSFER, TRUE);
  }

  $result = curl_exec($ch);
  curl_close($ch);
  drupal_set_message(t('Command Sent to Cloud API'));
}
