<?php

function tbs_login_department_form($form, &$form_state) {
 $form['access'] = array(
  '#type' => 'fieldset',
  '#title' => t('Department Settings'),
  '#collapsible' => TRUE,
  '#collapsed' => FALSE,
  '#prefix' => '<div class="department">',
  '#suffix' => '</div>',
 );
  $form['access']['tbs_login_departments'] = array(
    '#type' => 'textfield',
	'#title' => t('Enter Deparments'),
	'#default_value' => variable_get('tbs_login_departments'),
	'#description' => t('Enter the list of department separated by commas eg: Administrator, Geology, ICT'),
	'#autocomplete_path' => 'department/autocomplete',
  );
  
  $form['access']['submit'] = array(
  '#type' => 'submit',
  '#value' => 'Submit',
  );
  
 
  
  $form['access']['delete'] = array(
  '#type' => 'submit',
  '#value' => 'View and Delete',
  '#submit' => array('tbs_login_form_delete_submit'),
  
  );
  
  return $form;
}

function tbs_login_department_form_validate($form, &$form_state) {
     $departments = $form_state['values']['tbs_login_departments'];
    
     $login_departments = explode(", ", $departments);
	 
	 foreach($login_departments as $value)
	 {
	     if(!preg_match('/^[a-zA-Z ]+$/',$value)) {
                form_set_error('tbs_login_departments', t("Sorry, this @values is not correct try again.", array('@values' => $value)));
		 }
	 }
}

function tbs_login_department_form_submit($form, &$form_state) {

  $departments = $form_state['values']['tbs_login_departments'];
  
  variable_set('tbs_login_departments',$departments);
  $search_history = variable_get('department_search_history', array());
  $search_history[] = $departments;
  variable_set('department_search_history',$search_history);
  drupal_set_message(t("Congratulation @department, has been saved.", array('@department' => $departments)));
  tbs_login_department_add($departments);
  

}
function tbs_login_form_delete_submit($form, &$form_state) {
 $form_state['redirect'] = array('department/more',
    array('query' => array('key' => 'value')),
    // $http_response_code
    302,
  );
}
function tbs_login_department_add($departments) {

   global $user;
   
    $login_departments = array();
   
    $login_departments = explode(", ", $departments);
	$thid = array();
	
   foreach($login_departments as $value)
   {
      if(tbs_login_department_is_available($value) == false){
	  
           $thid = db_insert('tbs_login_department')
                  ->fields(array(
	                  'uid' => $user->uid,
	                  'dep_name' => $value,
                      'entereddate' => REQUEST_TIME,     
                    ))
            ->execute();
	    }
	}
	 
	return $thid;
}

function tbs_login_department_is_available($departments) {

 // $uid = 1;
    
  $department_options = array();
  $result = db_query('SELECT n.uid,n.dep_name,n.entereddate FROM {tbs_login_department} n');

   $uppercase_department = strtoupper($departments);
   foreach ($result as $record) {
     $uppercase_record = strtoupper($record->dep_name);
     if (strcmp($uppercase_record,$uppercase_department)== 0)
	    return true;
   }
  return false;
}