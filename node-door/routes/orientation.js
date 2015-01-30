// var port = '/dev/ttyACM0';
var port = '/dev/tty.usbmodem1451';

var express = require('express');
var router = express.Router();
var serialport = require('serialport');
var SerialPort = serialport.SerialPort;
var serial = new SerialPort(port, {
  baudrate: 9600,
  parser: serialport.parsers.readline("\n")
});

function send() {
  serial.write(new Buffer([127, x, y]));
};

router.get('/', function(req, res) {
  console.log('here');
  res.render('orientation', { title: 'Device Orientation' });
});

router.get('/coord', function(req, res) {
  res.send();
  send(10, 10);
});

module.exports = router;
