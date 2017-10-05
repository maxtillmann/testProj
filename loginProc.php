<?php
//require_once __DIR__ . '/vendor/autoload.php';
require 'amqpCreate.php.inc';
require 'logindb.php.inc';
	echo "Hello", "\n";
	$hostinfo = parse_ini_file("amqpCreate.ini");
	$amqp = new amqpCreate();
	$amqp->amqpConstruct($hostinfo['HOST'],$hostinfo['PORT'],$hostinfo['USER'],$hostinfo['PASS']);
	echo "Hello2", "\n";	
	$amqp->amqpAuthenticate('Login');
?>