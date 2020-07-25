<?php
    $start = intval($_POST['start']);
    $end = intval($_POST['end']);
    $step = intval($_POST['step']);
    
    // Check whether it is necessary to take data from database.
    if ($start == '' && $end == '' && $step == '') {
        echo '<p>The data will be from database.</p>';
        include 'connect.php';
        
        $result = mysqli_query($connection, 'SELECT * FROM my_loop');
        while ($row = mysqli_fetch_assoc($result)) {
            $start = intval($row['start']);
            $end = intval($row['end']);
            $step = intval($row['step']);
        }
    }
    
    if (!is_int($start) || !is_int($end) || !is_int($step)) {
        echo 'All values must be int type. Please try again.';
    } else {
        echo '<h3>The cycle from '.$start.' to '.$end.' with step '.$step.' :</h3>';
        
        if ($start < $end && $step > 0) {
            for ($i=$start; $i<=$end; $i+=$step) echo $i.' ';
        }
        else if ($start > $end && $step > 0) {
            for ($i=$start; $i>=$end; $i-=$step) echo $i.' ';
        }
        else {
            echo 'Loop step must be greater than 0.';
        }
        
        // Save new start, end and step to my_loop table
        include 'connect.php';
        
        // Clear table
        $sql = "TRUNCATE TABLE my_loop";
        mysqli_query($connection, $sql) or die(mysqli_error());
    
        $sql = mysqli_query($connection, 'INSERT INTO my_loop (start, end, step) VALUES ('.$start.', '.$end.', '.$step.')') or die(mysqli_error());
        
        mysqli_close($connection);
    }
?>