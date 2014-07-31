"use strict"
var assert = require("assert")

// My solution
function sortGiftCode(code) {
  var charSet = [], ret = ""
  for (var i = 0; i < code.length; i++) {
		if (!(code[i] in charSet)) {
			charSet.push(code[i])
		}
	}
	charSet.sort()
	charSet.forEach(function (c) {
		ret += c
	})
	return ret
}

assert.equal(sortGiftCode("abcdef"), "abcdef")
assert.equal(sortGiftCode("pqksuvy"), "kpqsuvy")
assert.equal(sortGiftCode("zyxwvutsrqponmlkjihgfedcba"), "abcdefghijklmnopqrstuvwxyz")

// Best practice solution
function sortGiftCode2(code) {
  return code.split("").sort().join("")
}

assert.equal(sortGiftCode2("abcdef"), "abcdef")
assert.equal(sortGiftCode2("pqksuvy"), "kpqsuvy")
assert.equal(sortGiftCode2("zyxwvutsrqponmlkjihgfedcba"), "abcdefghijklmnopqrstuvwxyz")
