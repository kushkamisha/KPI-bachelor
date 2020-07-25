<?php
    // display array
    function show_array($array, $work_time) {
        echo '<p>Sorted array: ';
        for ($i=0; $i < count($array); $i+=1) {
            echo $array[$i].'&nbsp;&nbsp;';
        }
        echo '</p> Method\'s work time: ';
        printf('%.6f',$work_time);
        echo ' sec';
    }
    
    // swap two elements in the array
    function swap(&$array, $i, $j) {
        $temp = $array[$i];
        $array[$i] = $array[$j];
        $array[$j] = $temp;
    }
    
    // for bogosort
    function is_sorted($array) {
        for ($i=0; $i < count($array)-1; $i+=1) {
            if ($array[$i] > $array[$i+1]) {
                return 0;
            }
        }
        return 1;
    }


    function selection($array) {
        $list = $array;
        for ($i=0; $i < count($array); $i+=1) {
            $min_index = $i;
            
            for ($j=$i+1; $j<count($array); $j+=1) {
                if ($array[$j] < $array[$min_index]) {
                    $min_index = $j;
                }
            }
            
            if ($min_index != $i) {
                swap($array, $i, $min_index);
            }
        }
        
        return $array;
    }
    
    function insertion($array) {
        for ($i=0; $i < count($array); $i+=1) {
            $j = $i;
            while ($j > 0 && $array[$j] < $array[$j-1]) {
                swap($array, $j, $j-1);
                $j -= 1;
            }
        }
        
        return $array;
    }
    
    function bogosort($array) {
        while (!is_sorted($array)) {
            shuffle($array);
        }
        
        return $array;
    }
    
    function bubble_sort($array) {
        for ($i=0; $i < count($array); $i+=1) {
            for ($j=0; $j < count($array)-1; $j+=1) {
                if ($array[$j] > $array[$j+1]) {
                    swap($array, $j, $j+1);
                }
            }
        }
        
        return $array;
    }
    
    function quicksort($array) {
        if(count($array) <= 1) {
            return $array;
        }
        
        $left = $right = array();
        reset($array);
        $pivot_key  = key($array);
        $pivot  = array_shift($array);
        
        foreach($array as $k => $v) {
            if($v < $pivot)
                $left[$k] = $v;
            else
                $right[$k] = $v;
        }
        return array_merge(quicksort($left), array($pivot_key => $pivot), quicksort($right));
    }
    
    function gnome_sort($array) {
        $i = 1;
        while ($i < count($array)) {
            if (!$i || $array[$i-1] <= $array[$i]) {
                $i += 1;
            } else {
                swap($array, $i, $i-1);
                $i -= 1;
            }
        }
        
        return $array;
    }
?>