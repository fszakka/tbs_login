<?php

 class DepartmentController extends DrupalDefaultEntityController{
 
	public function save($department) {
    drupal_write_record('department', $department);
    field_attach_insert('department', $department);
    module_invoke_all('entity_insert', 'department', $department);
    return $department;
  }
 }