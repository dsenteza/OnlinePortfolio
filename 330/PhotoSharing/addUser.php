<?php

	$data = json_decode(file_get_contents("php://input"));

	$usr = $data->bname;
	$pass = $data->pass;

	mysql_connect("localhost", "root", "computer");
	mysql_select_db("creative");

	msql_query("INSERT INTO `users`(`username`, `password`) VALUES ('".$usr."', '".$pass."')" or die(mysql_error());

	echo $usr." ".$pass;

?>