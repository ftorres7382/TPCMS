//To enter, put localhost:3000
//To enter in Cell phone, use (Local IP Address):3000
//For Francisco: 192.168.0.103:3000 with house internet


require('dotenv').config();

var createError = require('http-errors');
var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');
var hbs = require("hbs");
var methodOverride = require("method-override");
var bodyParser = require('body-parser'); //recuperar datos a traves de URL

//==================================ROUTES====================================
// ===== Index Route =====
var indexRouter = require('./routes/index');

/*
// ===== Doctor Section =====
var doctorRouter = require('./routes/doctor');
// ===== Forms Term Section =====
var formsRouter = require('./routes/forms');
// ===== Geolocation Section =====
var geolocationRouter = require('./routes/geolocation');
// ===== iframes Section =====
var iframesRouter = require('./routes/iframes');
// ===== News Section =====
var newsRouter = require('./routes/news');
// ===== Visit Section =====
var visitRouter = require('./routes/visit');

*/


//==================================ROUTES====================================

var app = express();

const port = process.env.PORT || 3000;
app.use(express.static(__dirname + "public"));

// view engine setup
app.set('views', path.join(__dirname, 'views'));
hbs.registerPartials(__dirname + '/views/partials/')

app.set('view engine', 'hbs');

app.use(methodOverride("_method"));

app.use(logger('dev'));
app.use(express.json());
app.use(bodyParser.urlencoded({
  extended: true
}));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

// ========================== USING ROUTES ==========================
// Index route & authorize
app.use('/', indexRouter);

/*
// ===== Doctor Section =====
app.use('/doctor', doctorRouter);
// ===== forms Section =====
app.use('/forms', formsRouter);
// ===== Geolocations Section =====
app.use('/geolocation', geolocationRouter);
// ===== iframes Section =====
app.use('/iframes', iframesRouter);
// ===== News Section =====
app.use('/news', newsRouter);
// ===== Visit Section =====
app.use('/visit', visitRouter);
*/

//TODO: catch error page, or create one
// catch 404 and forward to error handler
app.use(function (req, res, next) {
  next(createError(404));
});

// error handler
app.use(function (err, req, res, next) {
  // set locals, only providing error in development
  res.locals.message = err.message;
  res.locals.error = req.app.get('env') === 'development' ? err : {};

  // render the error page
  res.status(err.status || 500);
  res.render('error');
});

app.listen(port, function () {
  console.log(`Server ${port} is online!`);
});
