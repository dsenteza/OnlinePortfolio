<?php
	
	require 'database.php';

	//grabbing variables from form and session
	$taskname = $_POST['taskname'];
	$price = $_POST['price'];
	$description = $_POST['description'];
	$username = $_SESSION['username'];

	//exit if variable does not exist
	if(!$taskname || !$price || !$description){
		printf("Query Prep Failed: %s\n", $mysqli->error);
		exit;
	}

	//Credentials for database access
	$mysqli = new mysqli('localhost', 'root', 'computer', 'task_db');

	if ($mysqli->connect_errno) {
		printf("Connection Failed: %s\n", $mysqli->connect_error);
		exit;
	}

	//adding new row to tasks table 
	$stmt = $mysqli->prepare("insert into tasks (username, taskname, price, description) values (?, ?, ?, ?)");
	if (!$stmt) {
		printf("Query Prep Failed: %s\n", $mysqli->error);
		exit;
	}
	$stmt->bind_param('ssss', $username, $taskname, $price, $description);
	$stmt->execute();
	$stmt->close();
	header("Location: list-tasks.php");

?>