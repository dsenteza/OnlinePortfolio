<?php  
$mysqli = new mysqli('localhost', 'root', '4Cqhb10!', 'mod5');
 
if($mysqli->connect_error) {
	printf("Connection Failed: %s\n", $mysqli->connect_error);
	exit;
}
?>