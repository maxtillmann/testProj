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
	private $callback_queue;
	private $response;
	private $corr_id;
	
	public function amqpConstruct($hostip,$port,$user,$pass){
	       $this->connection = new AMQPStreamConnection($hostip,$port,$user,$pass);
	       $this->channel = $this->connection->channel();
	       
	       if($this->connection){
			//echo "Established a connection to the broker\n";
	       }
	       else{
			//echo "Connect Connect to broker\n";
			exit(-1);
	       }

	       list($this->callback_queue, ,) = $this->channel->queue_declare(
	               "", false, false, true, false);
	       $this->channel->basic_consume(
			$this->callback_queue, '',false,false,false,false,
			array($this, 'on_response'));

	}

	public function on_response($rep){
	       if($rep->get('correlation_id') == $this->corr_id){
	       		$this->response = $rep->body;
	       }
	}

	public function amqpSend($qname,$msg){
	       $this->response = null;
	       $this->corr_id = uniqid();
	       
	       $this->msg = new AMQPMessage($msg,array('correlation_id' => $this->corr_id, 'reply_to' => $this->callback_queue));
	       
	       $this->channel->basic_publish($this->msg,'',$qname);
	       //echo "[x] Sent", $msg, "\n";
	       while(!$this->response){
			$this->channel->wait();
	       }
	       //echo "[x] Got Response", $msg, "\n";
	       $this->channel->close();
	       $this->connection->close();
	       
	       return intval($this->response);      
	}
	
	public function amqpAuthenticate($qname){
	       $this->channel->queue_declare($qname,false,false,false,false);
	       
	       function authenticate($username,$password,$type){
	       		$login = new loginDB();
			$login->createLogin();
			$authenticate_results = $login->validateLogin($username,$password,$type);
			return $authenticate_results;
	       }
	       
	       echo ' [*] Waiting for Messages. To exit press CTRL+C', "\n";
	       $callback = function($req){
	       		  echo "I reached the callback", "\n";
			  $login_info = json_decode($req->body);
			  $username = $login_info->username;
			  $pass = $login_info->password;
			  $type = $login_info->type;
			  //echo "Username: ". $username,"\n";
			  $this->msg = new AMQPMessage(
			   (string)authenticate($username,$pass,$type),
			   array('correlation_id' => $req->get('correlation_id')));
			   $req->delivery_info['channel']->basic_publish($this->msg, '', $req->get('reply_to'));
			   $req->delivery_info['channel']->basic_ack(
			   $req->delivery_info['delivery_tag']);
		};
	        
		$this->channel->basic_qos(null,1,null);
		$this->channel->basic_consume($qname,'',false,false,false,false,$callback);
		
		while(count($this->channel->callbacks)){
			$this->channel->wait();
		}
		$channel->close();
		$connection->close();
	}
}
?>