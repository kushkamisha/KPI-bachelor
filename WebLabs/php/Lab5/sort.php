<?php
    include 'functions.php';

    // generate random array with 10 elements
    $array = array();
    for ($i=0; $i<10; $i+=1) {
        $array[$i] = rand(-10, 10);
    }
    
    $sort_method = $_POST['sort_method'];
    
    echo '<p>Array to sort: ';
    for ($i=0; $i < count($array); $i+=1) {
        echo $array[$i].'&nbsp;&nbsp;';
    }
    echo '</p><p>Your method of sort: '.$sort_method.'</p>';
    
    if ($sort_method == 'Selection') {
        $start_time = microtime();
        $sorted = selection($array);
        $end_time = microtime();
        show_array($sorted, $end_time-$start_time);
    } else if ($sort_method == 'Insertion') {
        $start_time = microtime();
        $sorted = insertion($array);
        $end_time = microtime();
        show_array($sorted, $end_time-$start_time);
    } else if ($sort_method == 'Bogosort') {
        $start_time = microtime();
        $sorted = bogosort($array);
        $end_time = microtime();
        show_array($sorted, $end_time-$start_time);
    } else if ($sort_method == 'Bubble sort') {
        $start_time = microtime();
        $sorted = bubble_sort($array);
        $end_time = microtime();
        show_array($sorted, $end_time-$start_time);
    } else if ($sort_method == 'Quicksort') {
        $start_time = microtime();
        $sorted = quicksort($array, 0, count($array));
        $end_time = microtime();
        show_array($sorted, $end_time-$start_time);
    } else if ($sort_method == 'Gnome sort') {
        $start_time = microtime();
        $sorted = gnome_sort($array);
        $end_time = microtime();
        show_array($sorted, $end_time-$start_time);
    }
?>