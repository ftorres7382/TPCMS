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
