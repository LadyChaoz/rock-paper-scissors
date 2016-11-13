# rock-paper-scissors
A terminal-based networking application which allows two users to play rock, paper, scissors.  
Programmer: Anne Warden

##Welcome to Rock, Paper, Scissors!

The referee program creates a server and displays a port number. Two clients can connect to the server at a time. These clients will run the game Rock, Paper, Scissors and the referee will judge the winners and losers and keep score. When either of the clients sends a signal to exit, both clients will end the game, and the server will continue running. There are two types of clients that can connect to the referee program.

Text-Only  
----
The text-only client connects to the server program using the IP address and port number of the machine running the server. The user will be prompted to input a choice, which will then send the users selection to the server program. The server will judge the selections and return a win/lose status to the client. Ending the game will close the client.

GUI  
----
There are three buttons. One for each choice. **The GUI does not currently connect to the server program.** It mearely displays the option you chose.

