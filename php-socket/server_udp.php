<?php
// set ip and port
$host = "127.0.0.1";
$port = 2333;

// don't timeout!
set_time_limit(0);

// create socket
$socket = socket_create(AF_INET, SOCK_DGRAM, SOL_UDP);

socket_bind($socket, $host, $port) or die('Could not bind socket');

// accept incoming connections
// spawn another socket to handle communication
while (true) {
    $buffer = '';
    $ret    = '';
    do {
        // $buffer and $port both come back with information for the ack
        socket_recvfrom($socket, $buffer, 512, 0, $host, $port);
        echo "Recieve: " . $buffer . "\n";

        // add the block number from the data packet to the ack packet
        $packet = strrev($buffer);

        // send ack
        socket_sendto($socket, $packet, strlen($packet), 0, $host, $port);

        // append the data to the return variable
        // for large files this function should take a file handle as an arg
        $ret .= $buffer;
    } while (strlen($buffer) == 516);
    echo "Final Result: " . $ret . "\n";
}

// close socket
socket_close($socket);
