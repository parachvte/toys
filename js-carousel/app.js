var express = require('express')
var jade = require('jade')


var app = express()

// static
app.use(express.static('static'))

// template
var fn = jade.compileFile('view/index.jade')

// route
app.get('/', function(req, res) {
  res.send(fn())
})


console.log('Start server on (port 3000) ...')
app.listen(3000)
