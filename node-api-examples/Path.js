var path = require("path")

console.log(path.normalize("/foo/bar//..")) // /foo

console.log(path.join("/foo", "/bar/quux/..")) // /foo/bar

console.log(path.relative("/foo", "/to")) // ../to

// path.dirname(p)
// path.basename(p, [ext])
// path.extname(p)
// path.sep															// or \
// path.delimiter												: or ;
