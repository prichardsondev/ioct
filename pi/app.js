var express = require('express');
var app = express();
var http = require('http').createServer(app);
var io = require('socket.io')(http);

var SerialPort = require("serialport")
var xbee_api = require('xbee-api');

var path = require('path');

app.use(express.static(path.join(__dirname, 'public')));
app.use('/js', express.static(path.join(__dirname, '/node_modules/socket.io-client/dist')));

app.get('/', (req, res) => {
  res.sendFile('index.html');
});

/*
    pin mapping
    arduino    xbee
       7       DIO0
       8       DIO1
*/

io.on('connection', (socket) => {
    //send (just to new client)
    socket.emit('updateClient', pinState)
    //receive
    socket.on('updateServer', pin => {
        togglePin(pin);
    });
});

function togglePin(pin){
    let data;

    switch(pin) {
        case 7:
            data = [0x7E,0x00,0x0F,0x10,0x01,0x00,0x13,0xA2,0x00,0x40,0xF7,0x43,0xDD,0xFF,0xFE,0x00,0x00,0x37,0xAE];
            break;
        case 8:
            console.log('8');
            break;
    }

    xbeeSerial.write(new Buffer.from(data));
}

http.listen(3000, () => {
  console.log('listening on *:3000');
});

//ls /dev/tty*
var xbeeSerial = new SerialPort("/dev/ttyUSB0", {
    baudRate: 9600
});

var xbeeAPI = new xbee_api.XBeeAPI({ api_mode: 1 });
xbeeSerial.pipe(xbeeAPI.parser);

xbeeSerial.on('open', () => console.log("Xbee Port Open"));

let pinState = {
    office:{}
}

xbeeAPI.parser.on("data", function (frame) {
    if (typeof frame != 'undefined'){
        console.log("frame: ", frame);
        //146 - IO Sample - radio sent
        //144 - Zigbee packet - we sent
        if (frame.type == 146){
            console.log("frame: ", frame);
            if (frame.remote64 == '0013a20040f743dd') {
                if (frame.digitalSamples != pinState.office) {
                    pinState.office = frame.digitalSamples;
                    console.log(pinState.office);
                    //send update to all clients
                    io.sockets.emit('updateClient', pinState);
                  }
            }

            
        }
    }
});