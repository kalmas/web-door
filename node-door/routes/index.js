var port = '/dev/ttyACM0';
// var port = '/dev/tty.usbmodem1411';

var express = require('express');
var router = express.Router();
var serialport = require('serialport');
var SerialPort = serialport.SerialPort;
var serial = new SerialPort(port, {
  baudrate: 9600,
  parser: serialport.parsers.readline("\n")
});

var close = function() {
  serial.write(new Buffer([0x00]));
};

var open = function() {
  serial.write(new Buffer([0x01]));
};

/* GET home page. */
router.get('/', function(req, res) {
  res.render('index', { title: 'Who Dat?' });
});

router.post('/open', function(req, res) {
  res.send();
  open();
  setTimeout(close, 2000);
});

module.exports = router;
