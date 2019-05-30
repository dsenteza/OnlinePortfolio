<?php

	require 'database.php';
	session_start();
	$username = $_POST['username'];
	$password = $_POST['password'];

	$stmt = $mysqli->prepare("select count(*) from users where username=?");
	$stmt->bind_param('s', $username);
	$stmt->execute();
	$stmt->bind_result($count);
	$stmt->fetch();
	$stmt->close();
	//Checks if there is a user with that username
	if($count > 0){
		header("Location: login.html");
		exit;
	}

	//Puts username and password into table
	else{
		$hashed = password_hash($password, PASSWORD_BCRYPT);
		$stmt = $mysqli->prepare("insert into users (username, password) values (?, ?)");
		if (!$stmt) {
			printf("Query Prep Failed: %s\n", $mysqli->error);
			exit;
		}
		$stmt->bind_param('ss', $username, $hashed);
		mkdir('./img/'.$username);
		$stmt->execute();
		$stmt->close();
		header("Location: login.html");
	}

?>