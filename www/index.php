<?php
// Start the session
session_start();

// Check if the form was submitted
if ($_SERVER["REQUEST_METHOD"] == "POST" && isset($_FILES["file"])) {
  // Get the uploaded file information
  $file_name = $_FILES["file"]["name"];
  $file_tmp = $_FILES["file"]["tmp_name"];

  if (is_uploaded_file($file_tmp)) {
	  echo "File is uploaded.";
  } else {
	  echo "File is not uploaded.";
  }
  // Move the file to the uploads directory
  if (move_uploaded_file($file_tmp, "uploads/" . $file_name)) {
	  echo "File uploaded successfully.";
  } else {
	  echo "File upload failed, please try again.";
  }
  
  // Set a session variable with the file name
  $_SESSION["file_name"] = $file_name;
}

if ($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST["SecretValue"])) {
	$_SESSION["posted_data"]["SecretValue"] = $_POST["SecretValue"];
}

?>

<!DOCTYPE html>
<html>
<head>
  <title>PHP Session, Cookies, Form Post, and File Upload Example</title>
</head>
<body>

  <h1>PHP Session, Cookies, Form Post, and File Upload Example</h1>
  
  <h2>Cookie Example</h2>
  <?php
  // Check if the cookie is set
  if(isset($_COOKIE["PHPSESSID"])) {
      echo "Cookie PHPSESSID value is: " . $_COOKIE["PHPSESSID"];
  } else {
      echo "Cookie is not set!";
  }
  ?>
  
  <h2>Form Post and File Upload Example</h2>
  <form method="post" enctype="multipart/form-data">
    <label for="file">Upload a file:</label>
    <input type="file" name="file" id="file">
    <br>
    <input type="submit" value="Upload">
  </form>

  <h2>Form Post Example</h2>
  <form method="post">
	<label for="SecretValue">SecretValue:</label>
	<input type="text" name="SecretValue" id="SecretValue">
	<br>
	<input type="submit" value="Submit">
  
  <?php
  // Check if the session variable is set
  if(isset($_SESSION["file_name"])) {
      echo "<h2>Session Example</h2>";
	  echo "Uploaded file name is: " . $_SESSION["file_name"];
  }
  if (isset($_SESSION["posted_data"])) {
	  echo "<h2>Form Post Example</h2>";
	  echo "SecretValue is: " . $_SESSION["posted_data"]["SecretValue"];
  }
  
  ?>

</body>
</html>

