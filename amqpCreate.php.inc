<?php

	require_once __DIR__ . '/vendor/autoload.php';
	use PhpAmqpLib\Connection\AMQPStreamConnection;
   	use PhpAmqpLib\Message\AMQPMessage;
	

	ini_set('display_errors', 'On');
	error_reporting(E_ALL | E_STRICT);

	$connection = new AMQPStreamConnection('192.168.1.9', 5672, 'test','test');
	$channel = $connection->channel();
	$channel->queue_declare('hello', false, false, false, false);
	$msg = new AMQPMessage('Hello World!');
	$channel->basic_publish($msg, '', 'hello');
	echo " [x] Sent 'Hello World!'\n";
	$channel->close();
	$connection->close();

	
	//$data = file_get_contents("php://input");
	//echo json_decode($data);
	//echo file_get_contents("php://input");
	
?>