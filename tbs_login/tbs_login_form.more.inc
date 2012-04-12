<?php

function tbs_login_more_form($form, &$form_submit) {
 
 
  
  $header = array
  (
    'uid' => t('User ID'),
    'dep_name' => t('Department Name'),
	'entereddate' => t('Date Entered'),
  );
  $options= array();
  
  //$result = db_query('SELECT n.dep_id,n.uid,n.dep_name,n.entereddate FROM {tbs_login_department} n');
  
  $query = db_select('tbs_login_department','th')
         ->extend('PagerDefault')
		 ->orderBy('entereddate', 'DESC')
		 ->fields('th')
         ->limit(10);
		 
   // Fetch the result set.
  $result = $query->execute();
 
  $options = array();
  
  foreach ($result as $record) 
  {
  
	$options[] = array (
	   'uid' => tbs_login_department_user_fetch($record->uid),
	   'dep_name' => $record->dep_name,
	   'entereddate' => date("m/j/Y", $record->entereddate),
	   'Key' => $record->dep_id,
	   );
    }
  variable_set('tbs_login_options_array', $options);
  
  $form['table'] = array
  (
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $options,
    '#empty' => t('No users found'),
  	'#multiple' => FALSE,
  );
  //$form['pager'] = array('#value' => theme('pager'));
  // $output = theme('table', array('header' => $header, 'rows' => $options)) . theme('pager');
  $form['pager_pager'] = array('#theme' => 'pager');

  $form['submit'] = array
  (
    '#type' => 'submit',
    '#value' => t('Delete Selected'),
  );
  
  $form['change'] = array 
  (
     '#type' => 'submit',
     '#value' => t('Update Selected'),
	 '#submit' => array('tbs_login_form_change'),
  );
  
  
  return $form;


}
function tbs_login_department_user_fetch($getuser) {

  global $user;
  
  $found_user = array();
  
  foreach ($user as $users) {
  
      if($users == $getuser)
	    return $found_user[]= $user->name;
  }
  return $found_user;
}
function tbs_login_more_form_validate($form, &$form_state)
{
  // $value = $form_state['values']['table'];
  // dsm($value);
   //dsm(_form_test_tableselect_form_builder($form, $form_state, $element_properties));
  // dsm($form_state['values']);
}
function tbs_login_more_form_submit($form, &$form_state)
{
   $value = $form_state['values']['table'];
   $options= variable_get('tbs_login_options_array');
   
   variable_set('tbs_login_department_delete',$options[$value]);
   
    $form_state['redirect'] = array('department/department-delete',
    array('query' => array('key' => 'value')),
    // $http_response_code
    302,
  );
}

function tbs_login_form_change($form, &$form_state)
{
   $value = $form_state['values']['table'];
   $options= variable_get('tbs_login_options_array');
   //dsm($options);
   //$val = new data();
   //$clsvalue = $val->tbs_login_test ($options);
   
   
   variable_set('tbs_login_change_department',$options[$value]);
   $form_state['redirect'] = array('department/departmentupdate',
    array('query' => array('key' => 'value')),
    // $http_response_code
    302,
  );
}