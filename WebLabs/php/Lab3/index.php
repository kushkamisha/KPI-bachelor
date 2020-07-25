<!doctype html>
<html>
<head>
    <title>Lab 3</title>
</head>
<body>
    <h3>1. This is simple php loop. Please enter start, end value and step of cycle to start.</h3>
    <form action='loop.php' method='post'>
        Start: <input type='text' name='start' /><br>
        End: <input type='text' name='end' /><br>
        Step: <input type='text' name='step' /><br>
        <p><input type='submit'></p>
    </form>
    
    <h3>2. Automatically generated table.</h3>
    <form action='generate_table.php' method='post'>
        Number of table (1-4): <input type='text' name='table_numb' /><br>
        Number of rows: <input type='text' name='n_rows' /><br>
        Number of cols: <input type='text' name='n_cols' /><br>
        <p><input type='submit'></p>
    </form>
</body>
</html>