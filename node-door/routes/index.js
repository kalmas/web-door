var express = require('express'),
  router = express.Router(),
  serialport = require('serialport'),
  SerialPort = serialport.SerialPort,
  serial = new SerialPort('/dev/tty.usbmodem1411', {
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
  res.render('open', { title: 'Its Open!'});
  open();
  setTimeout(close, 2000);
});

module.exports = router;
