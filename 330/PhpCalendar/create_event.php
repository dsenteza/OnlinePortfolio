<?php 
	printf("got to the new event php");

	session_start();
	require "database.php";
	if(!isset($_SESSION["username"])){
		$_SESSION["logintoaddstory"] = true;
		exit();
	}

	$owner = $_SESSION["username"];
	$title = $_POST["eventTitle"];
	$eventStart = $_POST["eventStart"];
	$eventEnd = $_POST["eventEnd"];
	$description = $_POST["description"];

	printf("%s  %s  %s  %s", $owner, $title, $eventStart, $eventEnd, $description);


	$stmt = $mysqli->prepare("insert into events (owner, startTime, endTime, title, description) values (?, ?, ?, ?, ?)");
	if(!$stmt){
		printf("Query Prep Failed: %s\n", $mysqli->error);
		exit;
	}

	$stmt->bind_param('sssss', $owner, $eventStart, $eventEnd, $title, $description);
	$stmt->execute();
	$stmt->close();
?>