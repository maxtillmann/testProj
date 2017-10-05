<?php

class loginDB
{
private $logindb;

public function __construct()
{
	$this->logindb = new mysqli("localhost","root","the8speed","login");

	if ($this->logindb->connect_errno != 0)
	{
		echo "Error connecting to database: ".$this->logindb->connect_error.PHP_EOL;
		exit(1);
	}
	echo "correctly connected to database".PHP_EOL;
}

public function getUsername($name)
{
	$un = $this->logindb->real_escape_string($name);
	$query = "select screenname from users where screenname = '$name';";
	$result = $this->logindb->query($query);
	if (!$result)
	{
            echo "this username does not exist!".PHP_EOL;
            return 0;
	}
	
	$user = $result->fetch_assoc();
	if (isset($user['screenname']))
	{
            return $user['screenname'];
	}
	return 0;
}

public function validateLogin($username,$password)
{
	$un = $this->logindb->real_escape_string($username);
	$pw = $this->logindb->real_escape_string($password);
	$statement = "select * from users where screenname = '$un';";
	$response = $this->logindb->query($statement);

	while ($row = $response->fetch_assoc())
	{
		echo "checking password for $username".PHP_EOL;
		if ($row["password"] == $pw)
		{
			echo "passwords match for $username".PHP_EOL;
			return 1;// password match
		}
		echo "passwords did not match for $username".PHP_EOL;
	}
	return 0;//no users matched username
}

public function addNewUser($name, $password)
{
	if($this->getUsername($name) == true)
	{
            echo "user $name already exists!".PHP_EOL;
            return false;
	}
	$addQuery = "insert into users (screenname, password) values ('$name', '$password');";
	$results = $this->logindb->query($addQuery);
	echo "user $name created";
	
	if (!$results)
	{
	echo "error: ".$this->logindb->error.PHP.EOL;
	}
}
	
	


}


?>
