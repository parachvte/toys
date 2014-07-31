"use strict"

var os = require("os")


console.log(os.tmpdir()) // /var/xxx

console.log(os.endianness()) // LE

console.log(os.hostname()) // Ryan

console.log(os.type()) // Darwin

console.log(os.platform()) // darwin

console.log(os.release()) // 13.3.0

console.log(os.uptime()) // 1223277

console.log(os.loadavg()) // [ 1.990234375, 2.2138671875, 1.88671875 ]

console.log(os.totalmem()) // 8589934592

console.log(os.freemem()) // 3411714048

console.log(os.cpus()) 
/* (My Macbook Air)
  [ { model: 'Intel(R) Core(TM) i5-4250U CPU @ 1.30GHz',
    speed: 1300,
    times: { user: 52446630, nice: 0, sys: 55895270, idle: 395667180, irq: 0 } },
  { model: 'Intel(R) Core(TM) i5-4250U CPU @ 1.30GHz',
    speed: 1300,
    times: { user: 25735410, nice: 0, sys: 20844910, idle: 457396410, irq: 0 } },
  { model: 'Intel(R) Core(TM) i5-4250U CPU @ 1.30GHz',
    speed: 1300,
    times: { user: 46791560, nice: 0, sys: 48118570, idle: 409066730, irq: 0 } },
  { model: 'Intel(R) Core(TM) i5-4250U CPU @ 1.30GHz',
    speed: 1300,
    times: { user: 24056590, nice: 0, sys: 20199890, idle: 459720090, irq: 0 } } ]
*/

console.log(os.networkInterfaces()) // get l0, eth0, IPv4, IPv6 infos

console.log(os.EOL)
