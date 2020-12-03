var express = require('express');
var router = express.Router();
var conn = require("../helpers/mysqlConnection").mysql_pool; //pool connection


/* GET home page. */
router.get('/', async function (req, res, next) {

  res.render('geolocation');
})

router.post('/', async function (req, res, next) {
  console.log(req.body)
  let query_insert = `INSERT INTO Geolocation
  (personID, dateTime, latitude, longitude) 
  VALUES ('${req.body.personID}', '${req.body.dateTime}', 
  '${req.body.latitude}', '${req.body.longitude}'); `

  conn.query(query_insert, function (err, results, fields) {
    if (err) throw err;
    console.log(results)

    res.render('geolocation');
      
  });


})

module.exports = router;


