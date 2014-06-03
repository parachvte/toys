<?php

//include the server.php script to start the server
//include_once('server.php');

$host    = "127.0.0.1";
$port    = 2333;


for ($i = 0; $i < 3; $i++) {
    // create socket
    $socket = socket_create(AF_INET, SOCK_DGRAM, SOL_UDP) or die("Could not create socket\n");

    $message = "Hello Server";
    echo "Message To Server: " . $message . "\n";
    $packet = $message;
    socket_sendto($socket, $packet, strlen($packet), 0, $host, $port);

    socket_recvfrom($socket, $buffer, 512, 0, $host, $port);
    echo "Reply From Server: " . $buffer . "\n";

    // close socket
    socket_close($socket);
}

