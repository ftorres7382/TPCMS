var express = require('express');
var router = express.Router();
var conn = require("../helpers/mysqlConnection").mysql_pool; //pool connection


/* GET home page. */
router.get('/', async function (req, res, next) {

  res.render('visit');
})

router.post('/', async function (req, res, next) {
  console.log(req.body)
  let query_insert = `INSERT INTO HealthCareVisit 
  (personID, doctorID, dateTime, medicine, quantity) 
  VALUES ('${req.body.personID}', '${req.body.doctorID}', 
  '${req.body.dateTime}', '${req.body.medicine}', '${req.body.quantity}');`

  conn.query(query_insert, function (err, results, fields) {
    if (err) throw err;
    console.log(results)

    res.render('visit');
      
  });


})

module.exports = router;

