<?php
	//processes file uploads
	session_start();

	// Get the filename and make sure it is valid
	$filename = basename($_FILES['uploadedfile']['name']);
	if( !preg_match('/^[\w_\.\-]+$/', $filename) ){
		echo $filename;
		header("Location: uploadFailure.html");
		exit;
	}

	// Get the username and make sure it is valid
	$username = $_SESSION['username'];
	if( !preg_match('/^[\w_\-]+$/', $username) ){
		echo "Invalid username";
		exit;
	}

	//path for the file
	$full_path = sprintf("./img/%s/%s", $username, $filename);

	if( move_uploaded_file($_FILES['uploadedfile']['tmp_name'], $full_path) ){
		header("Location: photoblog.php");
		exit;
	}else{
		echo $full_path;
		header("Location: uploadFailure.html");
		exit;
	}

?>