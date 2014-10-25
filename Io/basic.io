# Basic usage of Io programming language
# use `println` for debug

# Main namespace
Lobby

# Object
Car := Object clone  # new type
car := Car clone  # with type `Car`
Car slotNames   # see slots
Car type  # see type
car proto  # get prototype

# create method
Car drive := method(
    "Im driving!"
)
Car drive
drive := Car getSlot("drive")  # get variabla or method

# list
l := list("Hello", "World")
l size
l append("!")

# Map
m := Map clone
m atPut("name", "Ryan")
m at("name")
mObj := m asObject
mList := m asList
m keys
m size

# Boolean
if (0, "true!", "false!")  # Note that 0 has true value
true clone
false clone
nil clone  # true, false, nil are singletons

# Condition
if (true, "true", "false")
if (true) then ("true * 2") else ("false * 2")

# Loop
# loop ("forever" println)
# i := 0
# while (i < 10, i := i + 1; i println)
# for (i, 1, 10, i println)

# Operator
OperatorTable addOperator("xor", 11)
true xor := method(bool, if (bool, false, true))
false xor := method(bool, if (bool, true, false))
(true xor false) println  # ?

0
