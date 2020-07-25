<?php
    $start = $_POST['start'];
    $step = $_POST['step'];
    $end = $_POST['end'];

    if ($start == '') {
        echo 'Please fill "start" field.<br>';
    }
    if ($step == '') {
        echo 'Please fill "step" field.<br>';
    }
    if ($end == '') {
        echo 'Please fill "end" field.<br>';
    }
    
    $start = intval($start);
    $step = intval($step);
    $end = intval($end);
    
    if ($start == 200 || $start == 150 || $start == 120) {
        if ($step == 1 || $step == 2 || $step == 3) {
            if ($end == 1 || $end == -1 || $end == 0) {
                if ($start < $end) {
                    for ($i=$start; $i<=$end; $i+=$step) echo $i.' ';
                } else {
                    for ($i=$start; $i>=$end; $i-=$step) echo $i.' ';
                }
            }
        }
    }
    
    if ($start == 0 || $start == 1 || $start == 2) {
        if ($step == 1 || $step == 10 || $step == 100) {
            if ($end == 99 || $end == 199 || $end == 999) {
                if ($start < $end) {
                    for ($i=$start; $i<=$end; $i+=$step) echo $i.' ';
                } else {
                    for ($i=$start; $i>=$end; $i-=$step) echo $i.' ';
                }
            }
        }
    }
    
    if ($start == 1 || $start == 0 || $start == -1) {
        if ($step == 1 || $step == 2) {
            if ($end == -99 || $end == 99 || $end == 0) {
                if ($start < $end) {
                    for ($i=$start; $i<=$end; $i+=$step) echo $i.' ';
                } else {
                    for ($i=$start; $i>=$end; $i-=$step) echo $i.' ';
                }
            }
        }
    }
    
    if ($start == -100 || $start == 0 || $start == 100) {
        if ($step == 4 || $step == 2 || $step == 3) {
            if ($end == 2 || $end == -2 || $end == 0) {
                if ($start < $end) {
                    for ($i=$start; $i<=$end; $i+=$step) echo $i.' ';
                } else {
                    for ($i=$start; $i>=$end; $i-=$step) echo $i.' ';
                }
            }
        }
    }
?>