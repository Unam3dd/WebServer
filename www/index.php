<?php
session_start();
?>
<!DOCTYPE HTML>
<html>
<head>
	<title>PHP POST Example</title>
</head>
<body>
<?php
if (isset($_GET['phpinfo'])) {
	phpinfo();
}
if (isset($_POST['secretvalue'])){
	$_SESSION['secretvalue'] = $_POST['secretvalue'];
}
if (isset($_SESSION['secretvalue'])){
	echo("<h1>A Secret Value has been set by POST!</h1><br><h2>Here it is: </h2>" . $_SESSION['secretvalue']);
} else {
	echo("<h1>No Secret Value has been set by POST! You can set one here:</h1>");
	echo("<form action='index.php' method='post'>");
	echo("<input type='text' name='secretvalue'>");
	echo("<input type='submit' value='Submit'>");
	echo("</form>");
}
?>
</body>
</html>
