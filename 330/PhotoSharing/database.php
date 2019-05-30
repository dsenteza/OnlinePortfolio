<?php
//Credentials for database access
	$mysqli = new mysqli('localhost', 'root', '4Cqhb10!', 'creative');

	if ($mysqli->connect_errno) {
		printf("Connection Failed: %s\n", $mysqli->connect_error);
		exit;
	}
?>