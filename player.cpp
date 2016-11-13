// Anne Warden
// CS375 Final Project
// player.cpp

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int main(int argc, char *argv[])
{
  int sockfd, port, len;
  struct sockaddr_in address;
  struct sockaddr *p_addr = (struct sockaddr *)&address;
  int read_count, result;
  string input;
  char buffer[1024];
  
  if (argc != 3) {
    cerr << "usage: " << argv[0] << " HOST PORT" << endl;
    exit(1);
  }
  
  port = atoi(argv[2]);
  
  // Create a client socket.
  sockfd = socket(PF_INET, SOCK_STREAM, 0);
  
  // Create the server socket address as given on the command line
  address.sin_family = AF_INET;
  address.sin_port = htons(port);
  address.sin_addr.s_addr = inet_addr(argv[1]);
  
  // Connect our socket to the server's socket
  len = sizeof(address);
  result = connect(sockfd, p_addr, len);
  
  if(result == -1) {
    cerr << "Server connection failed" << endl;
    exit(1);
  }

  cout << "Connected" << endl;
  
  // Recieve Player Info and send READY
  read_count = read(sockfd, buffer, sizeof(buffer));
  buffer[read_count] = '\0';
  cout << buffer << endl;

  write(sockfd, "READY", 6);
  
  // Recieve: GO and Start Game
  do
    {
      read_count = read(sockfd, buffer, sizeof(buffer));
      buffer[read_count] = '\0';
      cout << "Client got back: " << buffer << endl;
    }while(strcmp(buffer, "GO") != 0);

  bool stop = false;
  
  while(!stop){
    cout << endl;
    cout << "0: Exit" << endl;
    cout << "1: Rock" << endl;
    cout << "2: Paper" << endl;
    cout << "3: Scissors" << endl;
    cout << "Enter Choice: ";
    
    // Get and send player choice
    bool invalid;
    do
      {
	getline(cin, input);
	switch(input.c_str()[0])
	  {
	  case '0':
	    write(sockfd, "STOP", 5);
	    invalid = false;
	    break;
	  case '1':
	    write(sockfd, "Rock", 5);
	    invalid = false;
	    break;
	  case '2':
	    write(sockfd, "Paper", 6);
	    invalid = false;
	    break;
	  case '3':
	    write(sockfd, "Scissors", 9);
	    invalid = false;
	    break;
	  default:
	    cout << "Invalid input" << endl;
	    cout << "Enter Choice: ";
	    invalid = true;
	  }
      }while(invalid);

    // Recieve data: W/L, STOP
    read_count = read(sockfd, buffer, sizeof(buffer));
    buffer[read_count] = '\0';

    switch(buffer[0])
      {
      case 'W':
	cout << "You win!" << endl;
	break;
      case 'L':
	cout << "Sorry, you lose" << endl;
	break;
      case 'T':
	cout << "The match was a draw." << endl;
	break;
      case 'S':
	stop = true;
	break;
      default:
	cout << "Recieved invalid result" << endl;
      }
    //cout << "Client got back: " << buffer << endl;
    
    if(!stop)
      {
	read_count = read(sockfd, buffer, sizeof(buffer));
	buffer[read_count] = '\0';
	//cout << "Client got back: " << buffer << endl;
      }
  }

}
