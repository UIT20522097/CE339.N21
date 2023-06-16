
var current = document.getElementById('current');
var warning_temperture = document.getElementById('over');

var gateway = `http://localhost:3000`;

window.addEventListener('load', () => {
    console.log('Trying to connect to ' + gateway + '...');
    var socket = io.connect(gateway);
    socket.on('connect', () => {
        console.log('Connected!');
        socket.emit('message', 'Hello Server!');
    });
    socket.on('message', (data) => {
        console.log('Received: ' + data);
        if (data > 50 || data < -50) {
            current.style.left = "50%";
            current.innerHTML = "OVER";
        } else {
            current.style.left = data + 50;
            current.innerHTML = data;
        }
    });
});
