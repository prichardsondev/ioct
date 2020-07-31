var express = require('express');
var app = express();
var http = require('http').createServer(app);
var io = require('socket.io')(http);
const Gpio = require('onoff').Gpio;
const relay = new Gpio(17,'out');

var path = require('path');

app.use(express.static(path.join(__dirname, 'public')));
app.use('/js', express.static(path.join(__dirname, '/node_modules/socket.io-client/dist')));

app.get('/', (req, res) => {
  res.sendFile('index.html');
});

io.on('connection', (socket) => {
    //send (just to new client)
    socket.emit('updateClient', relay.readSync())
    //receive
    socket.on('updateServer', pin => {
        togglePin();
    });
});

function togglePin(){
    relay.writeSync(1-relay.readSync());
    io.sockets.emit('updateClient', relay.readSync());
}

http.listen(3000, () => {
  console.log('listening on *:3000');
});