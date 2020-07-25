const express = require('express')
var pg = require('pg')
var format = require('pg-format')
var PGUSER = 'kushkamisha'
var PGDATABASE = 'Website'

module.exports.getDataFromDatabase = function() {
  var config = {
    user: PGUSER, // name of the user account
    database: PGDATABASE, // name of the database
    max: 10, // max number of clients in the pool
    idleTimeoutMillis: 30000 // how long a client is allowed to remain idle before being closed
  }

  var pool = new pg.Pool(config)
  var myClient

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
        return '<h1>err</h1>';
      }
      console.log(result.rows[0]);
      // return "<h1>" + result.rows[0]['name'] + "</h1>";
      return "<h1>yes</h1>";
    })
  })



  // return "<h1>Something</h1>";
}