<!DOCTYPE html>
<html>

	<head>
		<meta charset="utf-8">
		<title>Task Creation</title>
		<link rel="stylesheet" type="text/css" href="task-style.css">
	</head>

	<body>
		<?php
			if($_SESSION["loggedIn"]==false){
				header("Location: list-tasks.php");
			}
			else{
				echo "
				<h1>Create a Task</h1>
				<p>Enter the deatails about your task below:</p>
				<br>
				<form action='submit.php' method='POST'>
					<input type='text' name='taskname placeholder='Task Name'>
					<input type='number' name='price' min='1' placeholder='Price'>
					<textarea name='description' placeholder='Write your task description here...''></textarea>
					<input type='submit' name='submitTask'>
				</form>
				";
			}
		?>
	</body>

</html>