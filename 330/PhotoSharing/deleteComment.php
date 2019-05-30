<?php

	session_start();
	require 'database.php';

	if (!isset($_SESSION["username"])) {
		$_SESSION["loggedIn"] = false;
		Header("Location: photoblog.html.php");
		exit();
	}

	$username = $_SESSION['username'];
	$id = $_SESSION['comm_id'];

		$stmt = $mysqli->prepare("DELETE FROM comments WHERE comm_id like '%" . $id . "%' AND username = '$username'");
		if (!$stmt) {
			printf("Query Prep Failed: %s\n", $mysqli->error);
			exit;
		}
		$stmt->bind_param('ssss', $username, $img_id, $comm_id, $comm_text, $comm_like);
		$stmt->execute();
		$stmt->close();
		header("Location: comment.php");
?>