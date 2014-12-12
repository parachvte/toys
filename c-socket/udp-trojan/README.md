## udp-trojan

A lab only for Windows - -||

Implement a UDP server and a UDP client.

#### Server side:

Start a UDP server on PC A, execute commands whatever it receives (and return the results).

* Server runs automatically after PC is booted
* Server should be as concealed as possible

#### Client side:

PC B with the client installed, and sends UDP commands to PC A, trying to create a user named `Hacker`, passwd `HackerPWD`.


Add/Delete user on Windows:

```
net user [username] [password] /add
net user [username] /del
```
