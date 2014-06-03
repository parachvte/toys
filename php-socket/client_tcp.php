<?php

//include the server.php script to start the server
//include_once('server.php');

$host    = "127.0.0.1";
$port    = 2333;

$message = "Hello Server";
echo "Message To server :".$message;

for ($i = 0; $i < 30000; $i++) {
    // create socket
    $socket = socket_create(AF_INET, SOCK_DGRAM, SOL_UDP) or die("Could not create socket\n");

    // connect to server
    $result = socket_connect($socket, $host, $port) or die("Could not connect to server\n");  

    // send string to server
    socket_write($socket, $message, strlen($message)) or die("Could not send data to server\n");

    // get server response
    $result = socket_read($socket, 1024) or die("Could not read server response\n");

    echo "Reply From Server  :".$result;

    // close socket
    socket_close($socket);
}

