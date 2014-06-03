<?php
// set ip and port
$host = "127.0.0.1";
$port = 2333;

// don't timeout!
set_time_limit(0);

// create socket
$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);

// bind socket to port
$result = socket_bind($socket, $host, $port);

// start listening for connections
$result = socket_listen($socket, 5);

// accept incoming connections
// spawn another socket to handle communication
while (true) {
    $spawn = socket_accept($socket) or die("Could not accept\n");
    // read client input
    $input = socket_read($spawn, 1024) or die("Could not read input\n");

    // clean up input string
    $input = trim($input);
    echo "{$spawn} -> Client Message : " . $input . "\n";

    // reverse client input and send back
    $output = strrev($input) . "\n";
    socket_write($spawn, $output, strlen($output)) or die("Could not write output\n");
}

// close sockets
//socket_close($spawn);
socket_close($socket);
