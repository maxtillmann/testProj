<?php
//require_once __DIR__ . '/vendor/autoload.php';
require 'amqpCreate.php.inc';

	$hostinfo = parse_ini_file("amqpCreate.ini");
	$amqp = new amqpCreate();
	$amqp->amqpConstruct($hostinfo['HOST'],$hostinfo['PORT'],$hostinfo['USER'],$hostinfo['PASS']);
	$request = $amqp->amqpRecieve('Login');
	
		
?>