<?php

	require 'database.php';

	session_start();

	$username = $_POST['username'];
	$password = $_POST['password'];

	//Selects hashed and salted password from database
	$stmt = $mysqli->prepare("select password from users where username=?");
	if(!$stmt){
		printf("Query prep failed: %s\n", $mysqli->error);
		exit;
	}
	$stmt->bind_param('s', $username);
	$stmt->execute();
	//tablePass = hashed and salted
	$stmt->bind_result($tablePass);

		if(strcmp($password, $tablePass)){
			$_SESSION["username"] = $username;
			$_SESSION["loggedIn"] = true;
			header("Location: photoblog.php");
		}
		else{
			echo $username . "<br>";
			echo $password . "<br>";
			echo $tablePass;
			printf("invalid username or password");
			echo "<br><form action='login.php'><input type='submit' value='Back to Login'></form>";
		}

	$stmt->close();
?>