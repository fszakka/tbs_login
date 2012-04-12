<?php

/**
 * Implements hook_views_data()
 */
 function tbs_login_views_data() {
      $table = array(
	     'tbs_login_department' => array(
		     'table' => array(
			    'group' => 'tbslogin',
				   'base' => array(
				      'field' => 'dep_id',
					  'title' => 'tbs login',
					  'help'  => 'Tbs login Department database table'
					)
				),
				'dep_id' => array(
					'title' => t('tbs login Key'),
					'help' => t('TBS login department Key field'),
					'field' => array(
						'click sortable' => TRUE,
					),
					'filter' => array(
						'handler' => 'views_handler_filter_numeric'
						),
					'sort' => array(
						'handler' => 'views_handler_sort'
						)
					),
				'uid' => array(
					'title' => t('TBS Login User ID'),
					'help' => t('TBS Login User ID field'),
					'relationship' => array(
						'base' => 'users',
						'field' => 'uid',
						'handler' => 'views_handler_relationship',
						'label' => t('user id'),
						),
					'field' => array(
						'click sortable' => TRUE,
					),
					'filter' => array(
						'handler' => 'views_handler_filter_user_name'
						),
					'sort' => array(
						'handler' => 'views_handler_sort'
						)
					),
				'dep_name' => array(
					'title' => t('TBS Login Department Name.'),
					'help' => t('TBS login Department Name Field.'),
					'field' => array(
						'click sortable' => TRUE,
					),
					'filter' => array(
						'handler' => 'views_handler_string'
						),
					'sort' => array(
						'handler' => 'views_handler_sort'
						)
					),
				'entereddate' => array(
					'title' => t('TBS Login entered date'),
					'help' => t('TBS login entered Date Field.'),
					'field' => array(
					    'handler' => 'views_handler_field_date',
						'click sortable' => TRUE,
					),
					'filter' => array(
						'handler' => 'views_handler_filter_date'
						),
					'sort' => array(
						'handler' => 'views_handler_sort_date'
						)
					)
				)
			);
	$table['tbs_login_department']['table']['join'] = array(
    // Index this array by the table name to which this table refers.
    // 'left_field' is the primary key in the referenced table.
    // 'field' is the foreign key in this table.
    'users' => array(
      'left_field' => 'uid',
      'field' => 'uid',
    ),
  );

		return $table;
 }