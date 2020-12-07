var express = require('express');
var router = express.Router();
var conn = require("../helpers/mysqlConnection").mysql_pool; //pool connection


/* GET home page. */
router.get('/', async function (req, res, next) {



  res.render('news');
})

module.exports = router;
