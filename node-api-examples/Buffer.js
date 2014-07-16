"use strict";

// Buffer
// http://nodejs.org/api/buffer.html

//require("buffer"); // require is not needed while Buffer Class is **GLOBAL**

// buf.write
var buf = new Buffer(15);
var len = buf.write("\u00bd + \u00bc = \u00be", 0);
console.log(len + " bytes: " + buf.toString("utf8", 0, len));

buf = new Buffer(0);
buf.write("x"); // can not write anything
console.log(buf.toString());

// buf.toJSON
console.log(buf.toJSON());

// Buffer.byteLength(string, [encoding])
var str = "\u00bd + \u00bc = \u00be";
console.log(str + ": " + str.length + " characters, " +
            Buffer.byteLength(str, "utf8") + " bytes");
// ½ + ¼ = ¾: 9 characters, 12 bytes

// Buffer.concat(list, [totalLength])

// buf.copy(targetBuffer, [targetStart], [sourceStart], [sourceEnd])
var buf1 = new Buffer(26);
var buf2 = new Buffer(26);
for (var i = 0; i < 26; i++) {
    buf1[i] = i + 97; // 97 is ASCII a
    buf2[i] = 33; // ASCII !
}
buf1.copy(buf2, 8, 22, 26);  // buf1[22, 26) -> buf2[8, 8 + 26 - 22)
console.log(buf2.toString("ascii", 0, 25));
// !!!!!!!!wxyz!!!!!!!!!!!!!
