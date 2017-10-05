<?php

ini_set('display_errors', 'On');
error_reporting(E_ALL | E_STRICT);

//require 'vendor/autoload.php';
require_once __DIR__ . '/vendor/autoload.php';
require 'amqpCreate.php.inc';
use PhpAmqpLib\Connection\AMQPStreamConnection;
use PhpAmqpLib\Message\AMQPMessage;
	
	if (!isset($_POST))
	{
		$msg = "Empty Form Submitted";
		echo json_encode($msg);
		exit(0);
	}

	//$qname = $_POST["type"];
	$qname = "Login";
	//var_dump($_POST);
	$credentials = json_encode($_POST);
	$hostinfo = parse_ini_file("amqpCreate.ini");
	

	$amqp = new amqpCreate();
	
	$amqp->amqpConstruct($hostinfo['HOST'],$hostinfo['PORT'],$hostinfo['USER'],$hostinfo['PASS']);	

	$result = $amqp->amqpSend($qname,$credentials);


	if($result == 1){
		   echo "Login Authenticated", "\n";
        }

	elseif($result == -1){
		echo "Login Failed, Invalid Username or Pass", "\n";	
	}
	
	elseif($result == 2){
		echo "Sucessfully Registered", "\n";	
	}
	else{
		echo "Failed to Register", "\n";	
	}
?>