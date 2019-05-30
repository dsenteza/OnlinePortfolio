<html>
	<head>
		<meta charset="utf-8">
		<title>User Login</title>
	</head>

	<body>
		<?php

			session_start();

			//Credentials for database access
			$mysqli = new mysqli('localhost', 'root', 'computer', 'task_db');

			if ($mysqli->connect_errno) {
				printf("Connection Failed: %s\n", $mysqli->connect_error);
				exit;
			}
			
			if(isset($_POST['button'])){
				$button = $_POST['button'];
				if($button == 'login'){
					$username = $_POST['username'];
					$password = $_POST['password'];

					//Selects hashed and salted password from database
					$stmt = $mysqli->prepare("select hashed_password from users where username=?");
					if(!$stmt){
						printf("Query prep failed: %s\n", $mysqli->error);
						exit;
					}
					$stmt->bind_param('s', $username);
					$stmt->execute();
					//tablePass = hashed and salted
					$stmt->bind_result($tablePass);

					$stmt->fetch();
						if(password_verify($password, $tablePass)){
							$_SESSION["username"] = $username;
							$_SESSION["loggedIn"]=true;
							header("Location: create-task.php");
						}
						else{
							printf("invalid username or password");
							echo "<br><form action='login.php'><input type='submit' value='Back to Login'></form>";
						}
					$stmt->close();
				}
				else{
					$username = $_POST['username'];
					$password = $_POST['password'];

					$stmt = $mysqli->prepare("select count(*) from users where username=?");
					$stmt->bind_param('s', $username);
					$stmt->execute();
					$stmt->bind_result($count);
					$stmt->fetch();
					$stmt->close();
					//Checks if there is a user with that username
					if($count > 0){
						header("Location: login.php");
						exit;
					}

					//Salts, hashes password, stores it
					else{
						$hashed = password_hash($password, PASSWORD_BCRYPT);
						$stmt = $mysqli->prepare("insert into users (username, hashed_password) values (?, ?)");
						if (!$stmt) {
							printf("Query Prep Failed: %s\n", $mysqli->error);
							exit;
						}
						$stmt->bind_param('ss', $username, $hashed);
						$stmt->execute();
						$stmt->close();
						header("Location: create-task.php");
					}
				}
			}
		?>
		<div>
			<form id="returning" action="login.php" method="POST">
				<p>Returning User Login:</p>
				<br>
				<input type="text" name="username" placeholder="Username">
				<input type="password" name="password" placeholder="Password">
				<input type="submit" name="button" value="login">
			</form>
		</div>

		<div>
			<form id="newUser" action="login.php" method="POST">
				<p>Create Account:</p>
				<br>
				<input type="text" name="username" placeholder="Username">
				<input type="password" name="password" placeholder="Password">
				<input type="submit" name="button" value="create">
			</form>
		</div>
	</body>
	
</html>