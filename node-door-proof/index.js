var serialport = require('serialport'),
  SerialPort = serialport.SerialPort,
  keypress = require('keypress'),
  isOpen = false;

keypress(process.stdin);
process.stdin.setRawMode(true);
process.stdin.resume();


var serial = new SerialPort('/dev/tty.usbmodem1411', {
  baudrate: 9600,
  parser: serialport.parsers.readline("\n")
});

serial.on("data", function (data) {
  console.log("here: " + data);
});

process.stdin.on('keypress', function (ch, key) {
  if (key && key.name == 'space') {
    open_close();
  } else if (key && key.ctrl && key.name == 'c') {
    process.stdin.pause();
  }
});

var open_close = function(){
  if (isOpen) {
  	console.log('Closing');
  	serial.write(new Buffer([0x00]));
  	isOpen = false;
  } else {
  	console.log('Opening');
  	serial.write(new Buffer([0x01]));
  	isOpen = true;
  }
};


process.stdin.setRawMode(true);
process.stdin.resume();