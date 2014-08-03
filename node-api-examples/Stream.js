
// Stream
// http://nodejs.org/api/stream.html
//
// This module looks like funny :)
//
// All stream are instances of EventEmitter
//
// Tree parts:
// 1. APIs need to be aware of
// 2. APIs when you need to implement your own custom streams
// 3. How stream works


var http = require("http")

var server = http.createServer(function (req, res) {
  var body = ""
  req.setEncoding("utf8")
  req.on("data", function (chunk) {
		body += chunk
  })
  
  req.on("end", function () {
		try {
			var data = JSON.parse(body)
		} catch (er) {
			res.statusCode = 400
			return res.end("error: " + er.message)
		}

		res.write(typeof data)
		res.end()
	})
})

server.listen(8888)

// curl localhost:8888 -d "{}"
