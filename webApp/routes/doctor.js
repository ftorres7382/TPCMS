var express = require('express');
var router = express.Router();
var conn = require("../helpers/mysqlConnection").mysql_pool; //pool connection


/* GET home page. */
router.get('/', async function (req, res, next) {

  res.render('doctor');

})

  router.post('/', async function (req, res, next) {
    console.log(req.body)
    let query_insert = `INSERT INTO Doctor (name, speciality) 
    VALUES ('${req.body.name}', '${req.body.speciality}');`
  
    conn.query(query_insert, function (err, results, fields) {
      if (err) throw err;
      console.log(results)
  
      res.render('doctor');
        
    });

})

module.exports = router;



