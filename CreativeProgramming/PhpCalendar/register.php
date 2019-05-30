<!-- referenced from: MODULE 3 newUser.php -->
<?php 
	require 'database.php';
	session_start();
	$username = $_POST["username"];
	$password = $_POST["password"];
	
	printf("Logged in as: %s ", $username);

	// TODO: CHANGE QUERY
	$stmt = $mysqli->prepare("SELECT COUNT(*) FROM users WHERE username=?");
	$stmt->bind_param('s', $username);
	$stmt->execute();
	$stmt->bind_result($count);
	$stmt->fetch();
	$stmt->close();

	if($count > 0){
		// $_SESSION["userExists"] = true;
		printf("Error: User already exists. Choose a different username.");
		exit;
	}
	else {
		$hashed = password_hash($password, PASSWORD_DEFAULT);
		$stmt = $mysqli->prepare("insert into users (username, password) values (?, ?)");
		if (!$stmt){
			printf("Query Prep Failed: %s\n", $mysqli->error);
			exit;
		}
		//$stmt->bind_param('ss', $username, $hashed);
		$stmt->execute();
		$stmt->close();
	}
?>