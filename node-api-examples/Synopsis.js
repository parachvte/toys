var http = require('http');
http.createServer(function (req, res) {
    res.writeHead(200, {'Content-Type': 'text/plain'});
    res.end('Hello, World!\n');
}).listen(2333, '127.0.0.1');

console.log('Running web server on http://127.0.0.1:2333');
