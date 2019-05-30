<?php
	//delete files by unlinking the path
	session_start();
	$username = $_SESSION['username'];
	$file = $_POST['delete'];

	$full_path = sprintf("/img/%s/%s", $username, $file);
	unlink($full_path);

	header("Location: files.php");

?>