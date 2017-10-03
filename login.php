<?php
	ini_set('display_errors', 'On');
	error_reporting(E_ALL | E_STRICT);
	
	require 'vendor/autoload.php';
	use GuzzleHttp\Psr7\Request;
	use GuzzleHttp\Client;
	
	$ini_arr = parse_ini_file("amqpCreate.ini");
	$url = $ini_arr['URL'];
	//echo $url;
	
	//var_dump($_POST);

	if (!isset($_POST))
	{
		$msg = "Empty Form Submitted";
		echo json_encode($msg);
		exit(0);
	}
	
	$credentials = json_encode($_POST);

	//echo  $credentials;

	/**************************************************************************
	$ch = curl_init($url);
	curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "POST");
	curl_setopt($ch, CURLOPT_POSTFIELDS, $credentials);
	curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
	curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, false);

	//curl_close($ch);
	
	// echo curl_getinfo($ch) . '<br/>';
	//echo curl_errno($ch) . '<br/>';
	//echo curl_error($ch) . '<br/>';
	//$output = curl_exec($ch);
	***************************************************************************/
		
	//$client = new Client(['debug'=>true,'exceptions'=>false,'verify' => false]);
	$client = new Client(['verify' => false]);

	//$output = $client->request('POST', 'http://httpbin.org/post', [ 'json' => $credentials]);
	$output = $client->post($url, [ 'json' => $credentials]);
	//$output = $client->post($url, [ 'json' => json_encode(['a' => 'b'])]);
	//$output = $client->post('https://httpbin.org/post', [ 'json' => $credentials]);

	
	//echo "Output: " . $output->getBody()->getContents() . "<br />";
	var_dump($output->getBody()->getContents());
	var_dump($output->getBody()->getContents());
	
?>