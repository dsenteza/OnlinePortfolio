<!DOCTYPE html>
<html>
	<head>
		<meta charset="utf-8">
		<title>Available Tasks</title>
		<link rel="stylesheet" type="text/css" href="task-style.css">
	</head>
	<body>
		<h1>Open Tasks</h1>

		<?php
			session_start();

			//Credentials for database access
			$mysqli = new mysqli('localhost', 'root', 'computer', 'task_db');

			if ($mysqli->connect_errno) {
				printf("Connection Failed: %s\n", $mysqli->connect_error);
				exit;
			}

			//grabbing task info from tasks
			$stmt = $mysqli->prepare("select * from tasks");
			if (!$stmt) {
				printf("Query Prep Failed: %s\n", $mysqli->error);
				exit;
			}
			$stmt->execute();
			$stmt->bind_result($id, $username, $taskname, $price, $description);

			while ($stmt->fetch()) {
				$price = htmlspecialchars("$" . $price);
				echo "<div><h1 id='taskName'> " . $taskname . "</h1>";
				echo "posted by <i>" . htmlspecialchars($username) . "</i>";
				echo "<ul><li> price: " . $price . "</li>";
				echo "<li> description" . $description  ."</li></ul></div>";
			}
			$stmt->close();

			if(isset($_SESSION["loggedIn"])){

				if($_SESSION["loggedIn"] == true){
					echo "<a href='create-task.php'>Create Task</a>";
				}

				else if($_SESSION["loggedIn"] == false){
					echo "<a href='login.php'>Login</a>";
				}
			}

		?>

	</body>
</html>