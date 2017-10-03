<?php

	require_once __DIR__ . '/vendor/autoload.php';
	use PhpAmqpLib\Connection\AMQPStreamConnection;
   	use PhpAmqpLib\Message\AMQPMessage;
	

	ini_set('display_errors', 'On');
	error_reporting(E_ALL | E_STRICT);

	$data = file_get_contents("php://input");

	//echo json_decode($data);
	//echo file_get_contents("php://input");
	
	
	
	
?>