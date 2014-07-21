"use strict"

// Global Objects
// http://nodejs.org/api/globals.html

// `var something;`  in Node is local to this module, but not global
global.xx = "x" // use global namespace object instead

// process
// console
// Class: Buffer
// require()
// require.resolve() ?
// require.cache        // caches all required modules
// __filename
console.log(__filename) // only the name of this file, so actually it is rather
                        // local to each module
// __dirname

// module               // A reference to current module.
                        // module.exports is used for defining what a module
                        // exports and makes available through require().

// exports              // shortcut for module.exports

// setTimeout(cb, ms)
var timer = setTimeout(function () { console.log("Hello, World!") }, 1000)
// clearTimeout(t)
clearTimeout(timer)
// setInterval(cb, ms)
var timer2 = setInterval(function () { console.log("Hello, World!") }, 1000)
// clearInterval(t)
clearInterval(timer2)
