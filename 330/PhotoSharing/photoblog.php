<!-- referenced: https://www.youtube.com/watch?v=4ZpqQ3j1o2w -->

<?php
//lists out file names accompanied by view and delete buttons per file
session_start();
	if(! $_SESSION['username']){
		header("Location: filesharing.html");
	}
	$username = $_SESSION['username'];
	//opens text directory 
	$dir = sprintf("/text");
	//$file = "users.txt";
	//opens directory with text files that are owned by $username
	if($handle = opendir('./img/'.$username)){
		while(false !==($entry=readdir($handle))){
			if($entry == "." || $entry == ".."){
				//do nothing for the "." and ".." directories
			}
			//for every file in the directory, echo the name of the file and a button for viewing the file and deleting the file
			else{
				echo "<h1>Welcome to your Photoblog!</h1>";
				echo "<div>$entry</div><br>"."\n";
				$fileContents = file_get_contents('./img/'.$username.'/'.$entry);
        		echo $fileContents;
			}
		}
		closedir($handle);
	}
?>

<!DOCTYPE html>
<html lang="en">
	<head>
		<title>AngularJS Photoblog</title>
		<meta charset="utf-8">
		<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/font-awesome/4.4.0/css/font-awesome.min.css">
		<script src="https://ajax.googleapis.com/ajax/libs/angularjs/1.5.6/angular.min.js"></script>
		<script src="https://ajax.googleapis.com/ajax/libs/jquery/2.1.3/jquery.min.js"></script>
		<style>
			body {
				margin-left: 50px;
				margin-right: 50px;
				margin-top: 20px;
			}
		</style>
	</head>

	<body>
		<!-- uploading text files-->
		<form enctype="multipart/form-data"  action="uploadText.php" method="POST"><br>
			<p><strong>Upload text:</strong></p><br>
			<input type="hidden" name="MAX_FILE_SIZE" value="20000000" />
			<label for="uploadfile_input">Choose a file to upload:</label> <input name="uploadedfile" type="file" id="uploadfile_input" />
			<br><br>
			<input type="submit" name="sumitt" value="Upload Text">
			<br>
		</form>

		<!--form for uploading a file, taken from wiki pages-->
		<form enctype="multipart/form-data" method="POST"><br>
			<p><strong>Upload image: </strong></p><input type="file" name="image" /><br>
			<p>Title:</p>
			<input type="text" placeholder="Title" name="title" />
			<p>Description:</p>
			<textarea name="img_desc" placeholder="Optional image description."></textarea>
			<br><br>
			<input type="submit" name="sumit" value="Upload Image">
			<br>
		</form>

		<h1 style="text-align: center">Your Uploaded Photos:</h1>

		<?php

		// for images
			if(isset($_POST['sumit'])) {
				if(getimagesize($_FILES['image']['tmp_name']) == FALSE) {
					echo "Please select an image!";
				}
				else {
					$image = addslashes($_FILES['image']['tmp_name']);
					$name = addslashes($_FILES['image']['name']);
					$image = file_get_contents($image);
					$image = base64_encode($image);
					$title = $_POST['title'];
					$description = $_POST['img_desc'];
					$username = $_SESSION['username'];
					saveimage($name, $image, $title, $description, $username);
				}
			}
			displayimage($username);
		// // for text files
		// 	else if(isset($_POST['sumitt'])) {
		// 		$text = addslashes($_FILES['text']['tmp_name']);
		// 		$name = addslashes($_FILES['text']['name']);
		// 		$text = file_get_contents($text);
		// 		$text = base64_encode($text);
		// 		$title = $_POST['title'];
		// 		$description = $_POST['img_desc'];
		// 	}
			
			function saveimage($name, $image, $title, $description, $username) {
				$con = mysql_connect('localhost', 'root', '4Cqhb10!');
				mysql_select_db("creative", $con);
				$qry = "insert into images (name, image, username, img_title, img_desc) values ('$name','$image','".$username."','".$title."','".$description."')";

				$result = mysql_query($qry, $con);

				if($result) {
					echo "<br>Image upload successfully!";
				}
				else {
					echo $qry;
					echo "<br>Image upload unsuccessful :(";
				}
			}

			function saveComm($name, $text) {
				$con = mysql_connect('localhost', 'root', '4Cqhb10!');
				mysql_select_db("creative", $con);
				$qry = "insert into comments (username, comm_text) values ('$name','$image','".$username."','".$_POST['commentText']."')";

				$result = mysql_query($qry, $con);

				if($result) {
					echo "<br>Comment Added";
				}
				else {
					echo $qry;
					echo "<br>Comment unsuccessful :(";
				}
			}

			function displayimage($username) {
				$con = mysql_connect('localhost', 'root', '4Cqhb10!');
				mysql_select_db("creative", $con);
				$qry = "select * from images where username = '".$username."'";
				$result = mysql_query($qry, $con);
				// array numbers correspond to table rows in DB
				while ($row = mysql_fetch_array($result)) {
					echo '<div><h3>'
					.$row[4].
					'</h3><img height="300" width="300" src="data:image;base64,'
					.$row[3].
					' " ><p>'
					.$row[5].
					'</p></div>
					<form action="deleteImg.php" method="POST">
						<input type="hidden" name="delete" value='.$row[4].'>
						<button>Delete Image</button>
					</form>
					<form action="editImg.php" method="POST">
						<p>Edit the title or Description of your image:</p>
						<input type="hidden" name="edit" value='.$row[4].'>
						<button>Edit Image</button>
					</form>
					<form action="comment.php" method="POST">
						<input type="hidden" name="comment" value='.$row[1].'>
						<button>Comment</button>
					</form>';
					$qry = "select * from comments where article_id = '".$row[1]."'";
					$comm_result = mysql_query($qry, $con);
					while ($comm_row = mysql_fetch_array($comm_result)){
						echo '<div><p>comments:</p><br>
								<p>Username: '.$row[0].'</p>
								<p>'.$row[3].'</p></div>';
					}
				}
				mysql_close($con);
			}
		?>
		<br><br>
		<form id="logout" action="logout.php">
			<input type="submit" value="Logout" name="logout">
		</form>

		<script>
			$('#heart i').click(function(){
			    $(this).find('i').toggleClass('fa fa-heart')
			});
		</script>

	</body>
</html>