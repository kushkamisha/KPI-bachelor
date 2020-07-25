<link rel='stylesheet' href='../Lab2/style/style.css' />
<?php
    $n_rows = intval($_POST['n_rows']);
    $n_cols = intval($_POST['n_cols']);
    $table_numb = intval($_POST['table_numb']);
    
    // Check whether it is necessary to take data from database.
    if ($n_rows == '' && $table_numb == '') {
        echo '<p>The data will be from database.</p>';
        include 'connect.php';
        
        $result = mysqli_query($connection, 'SELECT * FROM my_table');
        while ($row = mysqli_fetch_assoc($result)) {
            $n_rows = intval($row['rows']);
            $table_numb = intval($row['table_no']);
            if ($table_numb == 3 || $table == 4) {
                $n_cols = 7;
            }
        }
    }
    
    if (!is_int($n_rows) || !is_int($table_numb)) {
        echo 'All values must be int type. Please try again.';
    } else {
        if ($table_numb == 1) {
            if ($n_rows > 1) {
                $table = '<div>Table 2.1 with '.$n_rows.' rows.</div><table id="mytable"><tr><td colspan="'.$n_rows.'" /></tr>';
                
                while ($n_rows > 1) {
                    $n_rows -= 1;
                    $table .= '<tr><td rowspan="'.$n_rows.'" /><td colspan="'.$n_rows.'" /></tr>';
                }
                
                $table .= '</table>';
                
                echo $table;
            } else echo 'Enter bigger number for number of rows.';
        }
        else if ($table_numb == 2) {
            if ($n_rows > 2) {
                $table = '<div>Table 2.2 with '.$n_rows.' rows.</div>';
                $table .= '<table id="mytable"><tr><td rowspan="'.$n_rows.'" /><td colspan="'.($n_rows-2).'" /></tr>';
                
                while ($n_rows > 3) {
                    $n_rows -= 1;
                    $table .= '<tr><td rowspan="'.$n_rows.'" /><td colspan="'.($n_rows-2).'" /></tr>';
                }
                
                $table .= '<tr><td rowspan="2" /></tr><tr></tr></table>';
                
                echo $table;
            } else echo 'Enter bigger number for number of rows.';
        }
        else if ($table_numb == 3) {
            if ($n_rows > 1) {
                if ($n_cols > 2) {
                    $table = '<div>Table 2.3 with '.$n_rows.' rows.</div>';
                    $table .= '<table id="mytable">';
                    
                    if ($n_rows % 2 != 0) {
                        $flag = 0;
                    } else {
                        $flag = 1;
                    }
                    
                    $n_cols -= 2;
                    while ($n_rows > 0) {
                        $n = $n_cols;
                        if ($n_rows % 2 == $flag) {
                            $table .= '<tr><td /><td colspan="2" />';
                            while ($n > 0) {
                                $table .= '<td colspan="2" />';
                                $n -= 1;
                            }
                            $table .= '</tr>';
                        } else {
                            $table .= '<tr><td colspan="2" />';
                            while ($n > 0) {
                                $table .= '<td colspan="2" />';
                                $n -= 1;
                            }
                            $table .= '<td /></tr>';
                        }
                        $n_rows -= 1;
                    }
                    
                    $table .= '</table>';
                    
                    echo $table;
                } else echo 'Enter bigger number for number of cols.';
            } else echo 'Enter bigger number for number of rows.';
        }
        else if ($table_numb == 4) {
            // if (($n_rows+1) % 3) {
            //     echo 'Number of rows in the table + 1 must divide without a remiender by 3.';
            // } else {
                if ($n_rows > 2) {
                    if ($n_cols > 2) {
                        $n_cols -= 3;
                        $table = '<div>Table 2.4 with '.$n_rows.' rows.</div><table id="mytable"><tr>';
                        $table .= '<td rowspan="3" /><td  /><td rowspan="2" />';
                        $n = $n_cols;
                        $n_rows -= 1;
                        $counter = 1;
                        
                        while ($n > 0) {
                            if ($n % 3 == 2) {
                                $table .= '<td />';
                                $counter += 1;
                            } else if ($n % 3 == 0) {
                                $table .= '<td rowspan="3" />';
                            } else if ($n % 3 == 1) {
                                $table .= '<td rowspan="2" />';
                            }
                            $n -= 1;
                        }
                        $table .= '</tr>';
                        
                        $rows_counter = 1;
                        while ($n_rows > 0) {
                            $c = $counter;
                            $table .= '<tr>';
                            while ($c > 0) {
                                $table .= '<td rowspan="3" />';
                                $c -= 1;
                            }
                            if ($rows_counter % 3 == 0) {
                                $table .= '<td rowspan="3" />';
                            }
                            $table .= '</tr>';
                            $n_rows -= 1;
                            $rows_counter += 1;
                        }
                        
                        $table .= '</table>';
                        
                        echo $table;
                    } else echo 'Enter bigger number for number of cols.';
                } else echo 'Enter bigger number for number of rows.';
            // }
        }
    }
?>