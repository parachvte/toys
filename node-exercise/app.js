'use strict';

var express = require('express')
var app = express()

app.get('/hello', function (request, response) {
    response.send('Hello World!')
})

app.listen(3000)
console.log('App running on port 3000')
