<?php

	$data = json_decode(file_get_contents("php://input"));
	$username = mysql_real_escape_string($data->username);
	$password = mysql_real_escape_string($data->password);
	mysql_connect("localhost", "root", "computer");
	mysql_select_db("creative");
	mysql_query("INSERT INTO users(`username`, `password`)VALUES('".$username"', '".$password"')");

?>