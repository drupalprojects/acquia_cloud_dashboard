<?php

/**
 * @file
 * Contains Drupal\acquia_cloud_dashboard\Form\DomainForm.
 */

namespace Drupal\acquia_cloud_dashboard\Form;

use Drupal\Core\Form\ConfigFormBase;
use Drupal\acquia_cloud_dashboard\CloudAPIHelper;

class DomainForm extends ConfigFormBase {

  protected $site;
  protected $environment;

  /**
   * {@inheritdoc}
   */
  public function getFormID() {
    return 'acquia_cloud_dashboard_domain';
  }

  /**
   * {@inheritdoc}
   */
  public function buildForm(array $form, array &$form_state, $site_name = NULL, $env = NULL) {
    $this->site = $site_name;
    $this->environment = $env;

    $form['site'] = array(
      '#type' => 'textfield',
      '#title' => t('Acquia Cloud Site'),
      '#default_value' => $this->site,
      '#size' => '40',
      '#required' => TRUE,
      '#disabled' => TRUE,
    );
    $form['environment'] = array(
      '#type' => 'textfield',
      '#title' => t('Acquia Cloud Environment'),
      '#default_value' => $this->environment,
      '#size' => '40',
      '#required' => TRUE,
      '#disabled' => TRUE,
    );
    $form['domain'] = array(
      '#type' => 'textfield',
      '#title' => t('Domain Name to be added'),
      '#size' => '40',
      '#required' => TRUE,
    );

    return parent::buildForm($form, $form_state);
  }

  /**
   * {@inheritdoc}
   */
  public function submitForm(array &$form, array &$form_state) {
    $api = new CloudAPIHelper();
    $api->postMethod('sites/' . $this->site . '/envs/' . $this->environment . '/domains/' . $form_state['values']['domain']);
    $form_state['redirect'] = 'admin/config/cloud-api/view';
    parent::submitForm($form, $form_state);
  }

}