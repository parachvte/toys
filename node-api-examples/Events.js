"use strict"

// All objects which emit events are instances of events.EventEmitter.
//
// Functions can then be attached to objects, to be executed when an event
// is emitted. These functions are called listeners. Inside a listener 
// function, `this` refers to the EventEmitter that the listener was attached to.
//
// 就是说在listener里面，this指的是那个发出event的对象

// Requirement
var events = require("events")
  , EventEmitter = require("events").EventEmitter
  , net = require("net")

console.log(events)
console.log(EventEmitter)

// Listener
var listener = function () {
    console.log("someone connected!")   // Why always logging **two** "someone connected!"?
}

// emitter.addListener(event, listener)
// emitter.on(event, listener)
var server = net.createServer(function (c) {
    c.write("Hello, World!\n")
}).listen(10001, "127.0.0.1")
server.on("connection", listener)

// emitter.removeListener(event, listener)
var server2 = net.createServer(function (c) {
    c.write("Hello, World!\n")
}).listen(10002, "127.0.0.1")
server2.on("connection", listener).removeListener("connection", listener)   // yeah calls can be chained

// emitter.removeAllListeners([event])
// let's forget about it :)

// emitter.setMaxListeners(n)

// emitter.listeners(event)
var server3 = net.createServer(function (c) {
    c.write("Hello, World!\n")
}).listen(10003, "127.0.0.1")
server3.on("connection", listener)
console.dir(server3.listeners("connection"))    // [ [Function], [Function] ]


// emitter.emit(event, [arg1], [arg2], [...])
var server4 = net.createServer().listen(10004, "127.0.0.1")
server4.on("connection", listener)
server4.emit("connection")  // emit the event itself

// EventEmitter.listenerCount(emitter, event)
console.log(EventEmitter.listenerCount(server4, "connection"))  // 1
