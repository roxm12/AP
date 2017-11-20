var express = require('express');
var path = require('path');
var favicon = require('serve-favicon');
var logger = require('morgan');
var cookieParser = require('cookie-parser');
var bodyParser = require('body-parser');
var name =require('./routes/name');
var index = require('./routes/index');
var users = require('./routes/users');
var pw=require('./routes/pw');
var ipurl=require('./routes/ipurl');
var blocklist=require('./routes/blocklist');
var mainpage=require('./routes/mainpage');
var fcm=require('./routes/fcm');
var app = express();

// view engine setup
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'ejs');

// uncomment after placing your favicon in /public
//app.use(favicon(path.join(__dirname, 'public', 'favicon.ico')));
app.use(logger('dev'));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/', index);
app.use('/users', users);
app.use('/name',name);
app.use('/pw',pw);
app.use('/ipurl',ipurl);
app.use('/blocklist',blocklist);
app.use('/mainpage',mainpage);
app.use('/fcm',fcm);
// catch 404 and forward to error handler
app.use(function(req, res, next) {
  var err = new Error('Not Found');
  err.status = 404;
  next(err);
});

// error handler
app.use(function(err, req, res, next) {
  // set locals, only providing error in development
  res.locals.message = err.message;
  res.locals.error = req.app.get('env') === 'development' ? err : {};

  // render the error page
  res.status(err.status || 500);
  res.render('error');
});
app.get('/route', function(req, res){
            res.send('Hello Router, <img src="/dongguk.jpg">')
            })
module.exports = app;
