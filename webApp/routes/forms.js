var express = require('express');
var router = express.Router();
var conn = require("../helpers/mysqlConnection").mysql_pool; //pool connection


/* GET home page. */
router.get('/', async function (req, res, next) {

  res.render('forms');
})

router.post('/', async function (req, res, next) {
  console.log(req.body)
  let query_insert = `INSERT INTO Person
  (name, age, race, ethnicity, gender, martialStatus, income, education , employmentStatus)
  VALUES ('${req.body.name}', '${req.body.age}', '${req.body.race}', '${req.body.ethnicity}', '${req.body.gender}',
  '${req.body.martialStatus}', '${req.body.income}','${req.body.education}', '${req.body.employmentStatus}');`

  conn.query(query_insert, function (err, results, fields) {
    if (err) throw err;
    console.log(results)

    res.render('forms');
      
  });


})

module.exports = router;
