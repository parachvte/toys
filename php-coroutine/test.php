<?php

require_once 'Task.php';
require_once 'Scheduler.php';
require_once 'SystemCall.php';

function task() {
    try {
        yield killTask(500);
    } catch (Exception $e) {
        echo 'Tried to kill task 500 but failed: ', $e->getMessage(), "\n";
    }
}

$scheduler = new Scheduler;
$scheduler->newTask(task());
$scheduler->run();
