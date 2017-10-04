<?php
ini_set('display_errors', 'On');
error_reporting(E_ALL | E_STRICT);

require_once __DIR__ . '/vendor/autoload.php';
use PhpAmqpLib\Connection\AMQPStreamConnection;
use PhpAmqpLib\Message\AMQPMessage;

class amqpCreate
{
	private $connection;
	private $channel;
	
	public function amqpConstruct($hostip,$port,$user,$pass){

	       $this->connection = new AMQPStreamConnection($hostip,$port,$user,$pass);

	       if($this->connection){
			echo "Established a connection to the broker\n";
	       }
	       else{
			echo "Connect Connect to broker\n";
	       }

	}
	
	public function amqpSend($qname,$msg){
	       $this->channel = $this->connection->channel();
	       $this->channel->queue_declare($qname, false, false, false, false);
	       $this->msg = new AMQPMessage($msg);
	       $this->channel->basic_publish($this->msg, '', $qname);
	       //echo " [x] Sent " . $msg . "\n";
	       $this->channel->close();
	       $this->connection->close();
	}
}
?>