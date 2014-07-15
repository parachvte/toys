"use strict";
var assert = require("assert");

//------------------------------------------------------------------------------
// Test functions
//------------------------------------------------------------------------------

// assert.fail(actual, expected, message, operator)
function failTest1() {
    assert.fail(23, 42, "Message", "###");  // 'Message'
}
function failTest2() {
    assert.fail(23, 42, undefined, "###"); // '23 ### 42'
}
function failTest3() {
    assert.fail(23, 23, "they are equal... but we will raise error either", "###");
}
// assert(value, message), assert.ok(value, [message])
function okTest1() {
    assert(true, "assert true");
}
function okTest2() {
    assert(false, "assert false");
}
function okTest3() {
    assert.ok(true, "assert.ok true");
}
function okTest4() {
    assert(false, "assert.ok false");
}
// assert.equal(actual, expected, [message])
function equealTest1() {
    assert.equal(23, 23, "equal!");
}
function equealTest2() {
    assert.equal(23, 24, "not equal!");
}
// assert.notEqual(actual, expected, [message])
function notEqualTest() {
    assert.notEqual(1, 1, "equal!");
}
// assert.deepEqual(actual, expected, [message])
function MyObject(id) {
    this.id = id;
}
function deepEqualTest() {
    assert.deepEqual(new MyObject(4), new MyObject(5), "not equal!");
}
// assert.notDeepEqual(actual, expected, [message])
function notDeepEqualTest() {
    assert.notDeepEqual(new MyObject(4), new MyObject(4), "equal!");
}
// assert.strictEqual(actual, expected, [message])

// assert.throws(block, [error], [message])
function throwsTest() {
    assert.throws(
        function() {
            throw new Error("Wrong value");
        },
        function(err) {
            if ((err instanceof Error) && /value/.test(err)) {
                console.log("Error occur");
                return true;
            }
        },
        "unexpected error"
    );
}
// assert.doesNotThrow(block, [message])
function doesNotThrowTest() {
    assert.doesNotThrow(
        function() {
            throw new Error("unexpected error");
        },
        "oh no!" // message is useless
    );
}
// assert.ifError(value)
function ifErrorTest() {
    assert.ifError(true); // if value is a true value, throw it! I cant understand what document says...
}


//------------------------------------------------------------------------------
// Call test functions
//------------------------------------------------------------------------------

// The config object is ugly, is there AOP in JavaScript?
// Or shall I 
var config = {
    TEST_FAIL1: false,
    TEST_FAIL2: false,
    TEST_FAIL3: false,
    TEST_OK1: true,
    TEST_OK2: false,
    TEST_OK3: true,
    TEST_OK4: false,
    TEST_EQUAL1: true,
    TEST_EQUAL2: false,
    TEST_NOTEQUAL: false,
    TEST_DEEPEQUAL: false,
    TEST_NOTDEEPEQUAL: false,
    TEST_THROWS: true,
    TEST_DOESNOTTHROWS: false,
    TEST_IFERROR: true
};

if (config.TEST_FAIL1) { failTest1(); } // error
if (config.TEST_FAIL2) { failTest2(); } // error
if (config.TEST_FAIL3) { failTest3(); } // error

if (config.TEST_OK1) { okTest1(); } // passed
if (config.TEST_OK2) { okTest2(); } // error
if (config.TEST_OK3) { okTest3(); } // passed
if (config.TEST_OK4) { okTest4(); } // error

if (config.TEST_EQUAL1) { equealTest1(); } // passed
if (config.TEST_EQUAL2) { equealTest2(); } // error

if (config.TEST_NOTEQUAL) { notEqualTest(); } // error

if (config.TEST_DEEPEQUAL) { deepEqualTest(); } // error

if (config.TEST_NOTDEEPEQUAL) { notDeepEqualTest(); } // error

if (config.TEST_THROWS) { throwsTest(); } // "Error occur"

if (config.TEST_DOESNOTTHROWS) { doesNotThrowTest(); } // error

if (config.TEST_IFERROR) { ifErrorTest(); } // error
