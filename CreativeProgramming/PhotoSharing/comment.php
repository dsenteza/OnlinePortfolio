<!DOCTYPE html>
<html lang="en">
	<head>	
		<title>Simple News Website</title>
	</head>
	<body>

		<a href="logout.php"> Logout</a><br>
		<a href="photoblog.php">Back to Photoblog</a>
		<br>
		<h1>Comments for the Image:</h1>
		<br><br>

		<?php
			
			session_start();
			require 'database.php';
			$username = $_SESSION['username'];
			$img_id = $_POST['comment'];
		?>

		<!-- Submit a new comment -->
		<form action="comment.php" method="POST">
			<textarea name="commentText" placeholder="Leave a comment here..."></textarea>
			<input type="submit" value="Submit Comment">
		</form>

		<?php
		//Display comments
			$stmt = $mysqli->prepare("select username, comm_id, img_id, comm_text from comments where img_id=".$img_id."");
			if (!$stmt) {
				echo "first query failed";
				printf("Query Prep Failed: %s\n", $mysqli->error);
				exit;
			}
			// $stmt->bind_param('i', $id);
			$stmt->execute();
			$stmt->bind_result($username, $comm_id, $img_id, $comm_text);
		 
			echo "<ul>\n";
			while ($stmt->fetch()) {
				printf("\t<li>%s says: %s </li>",
			    htmlspecialchars($username),   
				htmlspecialchars($comm_text));
				// echo "<a href='deleteComment.php' method='POST'>Delete</a>";
			}
			echo "</ul>\n";

			//Insert into database
			if (isset($_POST['commentText'])) {

				$comment_val = $_POST['commentText'];
				$stmt = $mysqli->prepare("insert into comments (username, comm_id, img_id, comm_text) values (?, ?, ?, ?)");
				if (!$stmt) {
					echo "second query failed";
					printf("Query Prep failed: %s \n", $mysqli->error);
					exit;
				}
				$stmt->bind_param('siis', $username, $id, $img_id, $comment_val);
				$stmt->execute();
				$stmt->close();
				header("Location: photoblog.php");
			}
		?>

	</body>
</html>