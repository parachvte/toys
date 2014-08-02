
var util = require("util")
var events = require("events")

// util.format
var r = util.format("%s: %j", "PHPCon", {"foo": "bar"})
console.log(r)

// util.insepect
console.log(util.inspect(util, { showHidden: true, depth: 2, colors: true }))

console.log(util.isArray(r))
var a = ["color", "foo", "bar"]
console.log(util.isArray(a))

console.log(util.isRegExp(/[0-9]+/))

console.log(util.isDate(new Date()))

console.log(util.isError(new TypeError()))


// util.inherits(constructor, superConstructor)
// RyStream inherits from superConstrutor
function RyStream() {
	"use strict"
	events.EventEmitter.call(this)
}
util.inherits(RyStream, events.EventEmitter)

RyStream.prototype.write = function(data) {
	this.emit("data", data)
}

var rs = new RyStream()
rs.on("data", function (data) {
	console.log("data :", data)
})

console.log("rs instance: ", rs instanceof events.EventEmitter)
rs.write("Blablabla")
