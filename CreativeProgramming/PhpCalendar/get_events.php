<?php 

	require 'database.php';
	session_start();

	$curUser = $_SESSION['username'];
	/*if(!isset($id)){
		$id = $_GET['id'];
	}*/
	$_SESSION['commentpage_id'] = $curUser;


	$stmt = $mysqli->prepare("SELECT (*) FROM events where owner=?");
	if(!$stmt){
		printf("Query Prep Failed: %s\n", $mysqli->error);
		exit;
	}

	$stmt->bind_param('s', $curUser);
	$stmt->execute();
	$stmt->bind_result($id, $owner, $start, $end, $title, $description);
	 

	$starts = array();
	$ends = array();
	$titles = array();
	$descriptions = array();
	while($stmt->fetch()){
		
		array_push($starts,$start);
		array_push($ends,$end);
		array_push($titles,$title);
		array_push($descriptions,$description);
	}

	$stmt->close();
	echo json_encode(array("starts" => $starts, "ends" => $ends, "titles" => $titles, "descriptions" => $descriptions));
?>