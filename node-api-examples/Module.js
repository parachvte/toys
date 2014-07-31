"use strict"

// Modules
// Stability: 5 - Locked
// http://nodejs.org/api/modules.html

// exports
exports.area = function (r) {
  var PI = Math.PI
  return PI * r * r
}

// module.exports
module.exports = function () {
}

// Folders as Modules
// write a package.json for your directory
// just like { "name": "npm", "main": "./lib/npm.js" }
// then require("npm") will try to load `npm/lib/npm.js`

// module object
// module.exports object
var EventEmitter = require("events").EventEmitter
module.exports = new EventEmitter()

// Modules all together
// http://nodejs.org/api/modules.html#modules_all_together

console.log(require.main)
