const http = require('http');
const path = require('path');
const async = require('async');
const socketio = require('socket.io');
const express = require('express');


var pg = require('pg')
var format = require('pg-format')
var PGUSER = 'kushkamisha'
var PGDATABASE = 'Website'


var config = {
    user: PGUSER, // name of the user account
    database: PGDATABASE, // name of the database
    max: 10, // max number of clients in the pool
    idleTimeoutMillis: 30000 // how long a client is allowed to remain idle before being closed
}

var pool = new pg.Pool(config)
var myClient;
let data;

let myQuery = `
  SELECT
      "authors"."name",
      "branches"."branch",
      "articles"."title",
      "articles"."text"
  FROM "articles"
  INNER JOIN "authors"
      USING ("ID")
  INNER JOIN "branches"
      USING ("ID")
  ORDER BY
      "authors"."name";
`;

pool.connect(function (err, client, done) {
if (err) console.log(err)
myClient = client
var ageQuery = format(myQuery)
myClient.query(ageQuery, function (err, result) {
  if (err) {
    // return err;
    console.log(err);
    // return '<h1>err</h1>';
  }
  console.log(result.rows[0]);
  data = result.rows;
  // return res.end("<h1>yes</h1>");
})
});


var router = express();
var server = http.createServer(router);
var io = socketio.listen(server);

router.use(express.static(path.resolve(__dirname, 'client')));

var parser = require('./controllers/API_parser.js');

server.listen(process.env.PORT || 8000, process.env.IP || "0.0.0.0", function(){
  var addr = server.address();
  console.log("Chat server listening at", addr.address + ":" + addr.port);
});


router.get('/articles', function (req, res) {
    res.header('Content-type', 'text/html');

    let result = "";
    for (let i = 0; i < 3; i++) {
        result += "<h1>" + data[i]["name"] + "</h1>";
        result += "<h3>" + data[i]["branch"] + "</h3>";
        result += "<h2>" + data[i]["title"] + "</h2>";
        result += "<h4>" + data[i]["text"] + "</h4>";
        result += "<hr>";
    }

    // return res.end(parser.getDataFromDatabase());
    return res.end(result);
});
