<?php

function tbs_login_form_delete_page() {
     return drupal_get_form('tbs_login_form_delete_confirm');
}

function tbs_login_form_delete_confirm($form, &$form_state) {

  $options = variable_get('tbs_login_department_delete');
  
 

  $caption = '<p>' . t('This action cannot be undone.') . '</p>';
  $heading = t('Are you sure you want to delete @department', array('@department' => $options['dep_name']));
  $cancel_path = 'department/more';
  $yes = t('Delete @delete', array('@delete' => $options['dep_name']));
  $no = t('Cancel');
  
  return confirm_form($form, $heading, $cancel_path, $caption, $yes, $no);
}

/**
 * Submit function for the confirm deletion form.
 */
function tbs_login_form_delete_confirm_submit($form, &$form_state) {
  
  $options= variable_get('tbs_login_department_delete');
  
  $num_deleted = db_delete('tbs_login_department')
  ->condition('dep_id', $options['Key'])
  ->execute();
  
  //variable_del('input_search_history');
  drupal_set_message(t('The Department @department has been deleted.',array('@department' => $options['dep_name'])));
  variable_del('tbs_login_department_delete');
  $form_state['redirect'] = array('department/more',
    array('query' => array('key' => 'value')),
    // $http_response_code
    302,
  );
  
}
