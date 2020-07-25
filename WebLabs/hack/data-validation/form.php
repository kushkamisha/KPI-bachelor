<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <title>Bad form</title>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/2.2.0/jquery.min.js"></script>
</head>
<body>
    <form method="POST" id="formx" action="javascript:void(null);" onsubmit="call()">
        <h2>Test From</h2>
        <label for="name">Name:</label><input id="name" name="name" value="" type="text">
        <label for="email">Email:</label><input id="email" name="email" value="" type="text">
        <input value="Send" type="submit">
    </form>
    
    <div id="results"></div>
    
    <script type="text/javascript" language="javascript">
     	function call() {
     	  var msg   = $('#formx').serialize();
            $.ajax({
              type: 'POST',
              url: 'process.php',
              data: msg,
              success: function(data) {
                $('#results').html(data);
              },
              error:  function(xhr, str){
    	    alert('Возникла ошибка: ' + xhr.responseCode);
              }
            });
     
        }
    </script>
</body>
</html>