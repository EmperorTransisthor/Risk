# Risk v0.2 server

Server consists of 3 daemon processes:
* **TCP server** - echo select() server which is responsible for communication with clients. It is controled by game process via pipe commands. It listens most of the time.
* **UDP server** - multicast server, which allows a client to find active games. It closes when the game starts.
* **Game process** - backend. It communicates with TCP server using pipes. Basically, all operations are performed there, depending on what it recieved from TCP server.

Stdout, Stdin and Stderr streams are saved to Syslog.log .
