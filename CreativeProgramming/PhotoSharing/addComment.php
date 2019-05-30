<!DOCTYPE html>
<html lang="en">
	<head>	
		<title>Leave a Comment</title>
	
	</head>
	<body>
		<a href="logout.php">  Logout</a><br>
		<a href="photoblog.php">Back to Photoblog</a>
		<br>
		<h1>Simple News Website</h1>
		<br><br>

		<?php
			
			session_start();
			require 'database.php';

			if (!isset($_SESSION["username"])) {
				$_SESSION["loggedIn"] = false;
				Header("Location: newsfeed.php");
				exit();
			}

			$username = $_SESSION['username'];
			// $title = $_POST['title'];
			// $text = $_POST['articleText'];
			// $url = $_POST['url'];

		?>

		<!-- Submit a new comment -->
		<form action="addComment.php" method="POST">
			<textarea name="commentText"></textarea>
			<input type="submit" value="Submit Comment">
		</form>

		<?php
		//Display comments
			$stmt = $mysqli->prepare("select username, comment_text, comment_id from comments where comment_id=?");
			if (!$stmt) {
				echo "first query failed";
				printf("Query Prep Failed: %s\n", $mysqli->error);
				exit;
			}
			$stmt->bind_param('i', $id);
			$stmt->execute();
			$stmt->bind_result($username, $comment_text, $comment_id);
		 
			echo "<ul>\n";
			while ($stmt->fetch()) {
				printf("\t<li>%s says: %s </li>",
			    htmlspecialchars($username),   
				htmlspecialchars($comment_text));
			}
			echo "</ul>\n";

			//Insert into database
			if (isset($_POST['commentText'])) {

				$comment_val = $_POST['commentText'];
				$stmt = $mysqli->prepare("insert into comments (username, comment_text, comment_id) values (?, ?, ?)");
				if (!$stmt) {
					echo "second query failed";
					printf("Query Prep failed: %s \n", $mysqli->error);
					exit;
				}
				$stmt->bind_param('ssi', $currentUser, $comment_text, $id);
				$stmt->execute();
				$stmt->close();
				header("Location: addComment.php");
			}
		?>

	</body>

	</html>