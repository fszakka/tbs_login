<?php
//function tbs_login_department_form($form, &$form_state) 
//tbs_login_form_change_page
function tbs_login_form_change_page($form, &$form_submit){

 $default_value = variable_get('tbs_login_change_department');
 $value = $default_value['dep_name'];
 
 $form['change'] = array(
  '#type' => 'fieldset',
  '#title' => t('Department change'),
  '#collapsible' => TRUE,
  '#collapsed' => FALSE,
  '#prefix' => '<div class="change">',
  '#suffix' => '</div>',
 );
  $form['change']['tbs_login_change_departments_change'] = array(
    '#type' => 'textfield',
	'#title' => t('Enter Deparments'),
	'#default_value' => $value,
	'#description' => t('Enter the list of department separated by commas eg: Administrator, Geology, ICT'),
	
  );
  
  $form['change']['change_record'] = array(
  '#type' => 'submit',
  '#value' => 'change Record',
  '#submit' => array('tbs_login_from_change_record_submit'),
  '#validate' => array('tbs_login_form_change_record_validate'),
  );
  
 
  
  $form['change']['return_table'] = array(
  '#type' => 'submit',
  '#value' => 'return',
//'#submit' => array('tbs_login_form_return_submit'),
  
  );
  
  return $form;
}
function tbs_login_form_change_record_validate($form, &$form_state) {
     $change_data_value = $form_state['values']['tbs_login_change_departments_change'];
    
	 $data = new data();
	 $change_data = $data->tbs_login_validate_department($change_data_value);
	
}
function tbs_login_from_change_record_submit($form, &$form_state){
	
	$change_data_value = $form_state['values']['tbs_login_change_departments_change'];
	$default_value = variable_get('tbs_login_change_department');
	
	 global $user;
	 if(!empty($change_data_value))
	 {
		$num_updated = db_update('tbs_login_department') // Table name no longer needs {}
				->fields(array(
				'uid' => $user->uid,
				'dep_name' => $change_data_value,
				'entereddate' => REQUEST_TIME,
						))
				->condition('dep_id', $default_value['Key'], '=')
				->execute();
	  
		variable_set('tbs_login_change_department',$change_data_value);
	 }
	$form_state['redirect'] = array('department/more',
    array('query' => array('key' => 'value')),
    // $http_response_code
    302,
  );

}



