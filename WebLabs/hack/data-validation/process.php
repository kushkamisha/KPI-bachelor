<?php
echo "<pre>";
    $name = $_POST["name"];
    $email = $_POST["email"];

    // $name = strip_tags($name);
    // $name = htmlspecialchars($name);
    // $name = mysql_escape_string($name);
    
    // $email = strip_tags($email);
    // $email = htmlspecialchars($email);
    // $email = mysql_escape_string($email);
    
    // <script>alert(1)</script>
    // <style>body{background-color:blue;}</style>
    
    echo "Name: ".$name."\n";
    echo "Email: ".$email;
echo "</pre>";
?>