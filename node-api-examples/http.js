// HTTP
// Stability: Stable - 3

// http.createServer([RequestListener])

// http.Server

"use strict";
var http = require("http");

var server = http.createServer(function(req, res) {
    res.writeHead(200, {'Content-Type': 'text/plain'});
    res.end('okey');
});

server.listen('127.0.0.1', 3333);

