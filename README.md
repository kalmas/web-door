micro_door
----------

```micro_door.ino``` contains an arduino sketch that does two things.

1. It listens for incoming passcodes from an RFID reader, comparing them to a list of allowed passcodes and turns on Pin 2 (opening the lock) if there's a match.
2. It listens for an "open" signal on the the usb port and turns on Pin 2 when it's received.

node-door
---------

This directory holds a simple express.js web app that can pass a request to open the lock from an html page to an arduino listening over usb.

node-door-proof
---------------

Similar to functionality of node-door app except it just runs on the terminal (no website). A proof of concept.