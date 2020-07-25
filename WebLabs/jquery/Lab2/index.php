<!doctype html>
<html>
<head>
  <title>Lab 2</title>
  <link rel="stylesheet" type="text/css" href="style/style.css">
</head>
<body>
  <div id="text">Hello World!</div>

  <?php include 'table1.html'; ?>
  <?php include 'table2.html'; ?>
  <?php include 'table3.html'; ?>
  <?php include 'table4.html'; ?>
  
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js"></script>
  <script>
    $("#mytable1").css("background", "pink");
    $("#mytable1 tr:nth-child(2) td").css("background", "#eee");
    
    // 2.
    $("#mytable1 tr td").html("<p>some text</p>");
    $("#mytable1 tr td[colspan]").css("color", "red");
    $("#mytable1 tr td[rowspan]").css("font-size", "28px");
    
    // 3.
    $("table:eq(2) tr td").html("<div>text in cell</div>");
    $("table:eq(2)").css("background", "blue");
    $("table:eq(2)").css("color", "#fff");
    $("table:eq(2) tr:nth-child(3n) td").css("font-style", "italic");
    $("table:eq(2) tr:gt(2) td").css("text-transform", "uppercase");
  
    // 4.
    $("table:eq(3) tr:first-child td").html("<pre>text in cell</pre>");
    $("table:eq(3) tr:first-child td:nth-child(2n)").css("color", "green");
    $("table:eq(3) tr:first-child td:nth-child(3)").html("<hr>");
    
    // 5.
    $("table:eq(3) tr:eq(-2) td:first-child").html("<ul><li>1 line</li><li>2 line</li><li>3 line</li><li>4 line</li></ul>");
    var lst_length = $("table:eq(3) tr:eq(-2) td:first-child li").length;
    for (var i = 1; i <= lst_length; i++) {
      var value = $("table:eq(3) tr:eq(-2) td:first-child li:nth-child(" + i + ")").text();
      alert(value);
    }
  </script>
</body>
</html>
