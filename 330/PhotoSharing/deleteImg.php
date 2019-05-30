<?php

	session_start();
	require 'database.php';

	if (!isset($_SESSION["username"])) {
		$_SESSION["loggedIn"] = false;
		Header("Location: photoblog.php");
		exit();
	}

	$username = $_SESSION['username'];
	$title = $_POST["delete"];

		$stmt = $mysqli->prepare("DELETE FROM images WHERE img_title like '%" . $title . "%' AND username = '$username'");
		if (!$stmt) {
			printf("Query Prep Failed: %s\n", $mysqli->error);
			exit;
		}
		// $stmt->bind_param('ssss', $username, $article_url, $article_text, $article_title);
		$stmt->execute();
		$stmt->close();
		header("Location: photoblog.php");
?>