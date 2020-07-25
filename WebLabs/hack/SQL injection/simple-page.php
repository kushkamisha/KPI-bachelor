<?php include_once('connect.php'); ?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <title>SQL injection</title>
    
    <?php
        error_reporting(0);
        $x = $_GET['id'];
        $query = "SELECT * FROM users WHERE id=$x";
        $result = mysqli_query($connection, $query);
        if (!$result) {
            die('Query failed '.mysqli_error($connection));
        }
        while ($lel = mysqli_fetch_array($result)) {
            echo "<h2><pre>Hello and Welcome to our site, ".$lel['login']."</pre></h2>";
            break;
        }
    ?>
    
    <?php
        if (!mysqli_connect_errno()) {
            echo " :3 ".mysqli_error($connection);
        }
    ?>
    
</head>
<body>
</body>
</html>