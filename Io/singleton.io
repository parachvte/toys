# Test for Io singleton

Singleton := Object clone

Singleton clone := Singleton

a := Singleton clone
b := Singleton clone
(a == b) println
