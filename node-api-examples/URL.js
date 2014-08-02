"use strict"

var url = require("url")

var a = url.parse("http://www.baidu.com:80/on/x/x/x/x/x?q=22u381u2#div")

console.log(a)

//{ protocol: 'http:',
//  slashes: true,
//  auth: null,
//  host: 'www.baidu.com:80',
//  port: '80',
//  hostname: 'www.baidu.com',
//  hash: '#div',
//  search: '?q=22u381u2',
//  query: 'q=22u381u2',
//  pathname: '/on/x/x/x/x/x',
//  path: '/on/x/x/x/x/x?q=22u381u2',
//  href: 'http://www.baidu.com:80/on/x/x/x/x/x?q=22u381u2#div' }

console.log(url.format(a))
