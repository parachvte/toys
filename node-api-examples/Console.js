"use strict"

// console.log([data], [...])
console.log("logging %d %d", 2, 3)

// console.info([data], [...])
console.info("info %d %d", 2, 3)

// console.error([data], [...])
console.error("error %d %d", 2, 3)  // the same as log & info, but print to stderr

// console.warn([data], [...])
console.warn("warn %d %d", 2, 3)

// console.dir(obj)
var obj = {
    "name": "im Object"
}
console.log(obj)
console.dir(obj)    // firefox may display a different version than chrome
                    // when using console.dir, I can figure out the diffs realy
                    // it use `util.inspect` on obj.

// console.time(label) & console.timeEnd(label)
console.time("label")
var a = 0
for (var i = 0; i < 100000000; i++) {
    a = a ^ 1
}
console.timeEnd("label") // label: 81ms

// console.trace(label)
console.time("label 2")
;(function () {
    var a = 1
      , b = 2
      , c
    c = a + b
    a = b
    b = c
    console.trace("label 2")    // printed to stderr
}())

// console.assert(expression, [message])
console.assert(false, "Oh no")  // equivalent to assert.ok
