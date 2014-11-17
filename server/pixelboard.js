var restify = require('restify');

// State
var next_user_id = 0;
var users = {};

// Serialport
var port="/dev/ttyACM0";
var SerialPort = require("serialport").SerialPort;
var serialPort = new SerialPort(port, { baudrate: 38400 });

serialPort.on("open", function () {
  console.log(port+' opened');
  setTimeout(function() {
    console.log('pixelboard ready');
  }, 5000);
});

function sendSerial(data) {
  serialPort.write(new Buffer(data+'\r','ascii'));
}

var fs = require('fs');
var user_token = JSON.parse(fs.readFileSync('/usr/local/src/pixelboard/server/user_token.json', 'utf8'));

// Setup some https server options
var https_options = {
  key: fs.readFileSync('/etc/ssl/self-signed/server.key'),
  certificate: fs.readFileSync('/etc/ssl/self-signed/server.crt'),
  name: 'pixelboardserver',
  version: '1.0.0'
};

var server = restify.createServer(https_options);

server.use(restify.acceptParser(server.acceptable));
server.use(restify.queryParser());
server.use(restify.bodyParser());

server.use(function consoleDebug(req, res, next) {
  console.log('URL: '+JSON.stringify(req.url));
  console.log('METHOD:'+JSON.stringify(req.method));
  console.log('PARAMS:'+JSON.stringify(req.params));
  console.log('');
  next();
});

//server.use(function authenticate(req, res, next) {
function authenticate(req, res, next) {
  // validate custom headers x-auth-token and x-auth-user 
  if ( ( user_token[req.headers['x-auth-user']]) && ( user_token[req.headers['x-auth-user']] == req.headers['x-auth-token'] ) ) {
    next();
  } else {
    next(new restify.NotAuthorizedError('Authentication Error'));
  }
}

server.get(/\/?.*/, restify.serveStatic({
  directory: './pages',
  default: 'pixelboard.html'
}));

server.post('/', function (req, res, next) {
  authenticate(req, res, next);
  var data = req.params.data;
  res.writeHead(200, {'Content-Type': 'application/json; charset=utf-8'});
  res.end(JSON.stringify(true));
  sendSerial(data);
  return next();
});

server.listen(88, function () {
  console.log('%s listening at %s', server.name, server.url);
});

