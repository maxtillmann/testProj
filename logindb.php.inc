<?php
class loginDB
{
	private $logindb;

	public function createLogin()
	{
	       $this->logindb = new mysqli("127.0.0.1", "root","Mindswap1","login");
	       if($this->logindb->connect_errno != 0){
	              echo "Could not connect to DB" . $this->logindb->connect_error,"\n";
		      exit(1);
	       }
	       echo "Connected to DB", "\n";
	}

	public function validateLogin($username,$password,$type){

	      $user = $this->logindb->real_escape_string($username);
	      $pass = $this->logindb->real_escape_string($password);
	      $statement = "select * from users where screenname = '$user';";
	      $response = $this->logindb->query($statement);

	      while ($row = $response->fetch_assoc())
	      {	
			echo "checking password for $username","\n";
			if ($row["password"] == $pass)
			{
				echo "passwords match for $username","\n";
				return 1;// password match
			}
	      }
	      if($type == "Login"){
	       	       echo "passwords did not match for $username","\n";
	       	       return -1;//no users matched username
	     }
	     else{
	       	       $statement = "INSERT INTO users(screenname,password) VALUES('$user','$password');";
	       	       $response = $this->logindb->query($statement);
		       $statement = "select * from users where screenname = '$user';";
		       $response = $this->logindb->query($statement);
		       
		       while($row = $response->fetch_assoc()){
		       		  echo "Succesfully Registered", "\n";
				  return 2;
		       }
		       
		        echo "Registered Failed", "\n";
			return -2;
		       
	     }
	}
}

?>