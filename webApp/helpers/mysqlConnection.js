var mysql = require('mysql');


var config;

config = {
      mysql_pool : mysql.createPool({

      //establece limite de personas conectadas a la base de datos
      connectionLimit : 15,
      //establece basico el route donde se ouede accessar
      host     : '70.12845.69.',  //THIS IS THE SAME FOR YOUR
      user     : 'root',      //THIS IS THE SAME FOR YOUR
      password : 'covid-19',        //HERE GO YOUR PASSWORD TO ENTER IN YOUR DB
      database : 'final-project'   //HERE GO THE DATABASE THAT WE ARE GONNA USED

  })
};

module.exports = config;

