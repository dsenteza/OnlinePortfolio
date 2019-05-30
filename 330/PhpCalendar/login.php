<?php 

	require 'database.php';
	session_start();

	$username = $_POST["username"];
	$password = $_POST["password"];

	printf("Logged in as: %s", $username);
 
 	// referenced from: MODULE 3 userCheck.php
	$stmt = $mysqli->prepare("select password from users where username=?");
	if(!$stmt){
		printf("Query prep failed: %s\n", $mysqli->error);
		exit;
	}

 	$stmt->bind_param('s', $username);
	$stmt->execute();
	$stmt->bind_result($pwd_hash);
	$stmt->fetch();

	if(password_verify($password, $pwd_hash)){
		$_SESSION["username"] = $username;
		$_SESSION["loggedIn"] = true;
		printf("\nWelcome to your personal calendar, %s!", $_SESSION["username"]);
	}
	else{
		printf("Error: Invalid username or password");
	}

	$stmt->close();
?>