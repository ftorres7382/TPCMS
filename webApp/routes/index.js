var express = require('express');
var router = express.Router();
const { spawn } = require('child_process');


/* GET home page. */
router.get('/', async function (req, res, next){

  res.render('index/index');

})
router.post('/', async function (req, res, next) {
// console.log(req.body);

var prints;
const python = spawn('python', ['./pythonScripts/loadSchedule.py', JSON.stringify(req.body)]);
python.stdout.on('data', function (data) {
  console.log(`${data}`);
 });
 python.on('close', (code) => {
   console.log(`child process exited with code ${code}`);
 });

res.render('index/index');

})

module.exports = router;
