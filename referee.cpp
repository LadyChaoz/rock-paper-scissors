// Anne Warden
// CS375 Final Project
// referee.cpp

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int play(char p1[], char p2[]);

int main()
{
  int server_sockfd, client1_sockfd, client2_sockfd;
  socklen_t server_len, client1_len, client2_len;
  struct sockaddr_in server_address;
  struct sockaddr_in client1_address;
  struct sockaddr_in client2_address;
  struct sockaddr *p_sadd = (struct sockaddr *)(&server_address);
  struct sockaddr *p_c1add = (struct sockaddr *)(&client1_address);
  struct sockaddr *p_c2add = (struct sockaddr *)(&client2_address);

  //string sockname = "server_socket";
  //const char *sockname_cstr = sockname.c_str();

  // Create a socket and name it
  server_sockfd = socket(PF_INET, SOCK_STREAM, 0);

  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(0);
  server_address.sin_addr.s_addr = htonl(INADDR_ANY);
  server_len = sizeof(server_address);
  bind(server_sockfd, p_sadd, server_len);
  
  // Find assigned port
  getsockname(server_sockfd, p_sadd, &server_len);
  cout << "Referee is using port " << ntohs(server_address.sin_port) << endl;
  
  // Game variables
  int read_count;
  char p1_choice[16], p2_choice[16];
  
  // Create a connection queue and wait
  listen(server_sockfd, 5);
  
  while(true){
    cout << "Referee is waiting for players" << endl;
    
    // Accept connections
    bool client1_connected = false, client2_connected = false;
    if(!client1_connected)
      {
	client1_len = sizeof(client1_address);
	client1_sockfd = accept(server_sockfd, p_c1add, &client1_len);
	write(client1_sockfd, "You are Player 1.\n", 20);
	
	cout << "Player 1 has connected" << endl;
	client1_connected = true;
      }
    if(!client2_connected)
      {
	client2_len = sizeof(client2_address);
	client2_sockfd = accept(server_sockfd, p_c2add, &client2_len);
	write(client2_sockfd, "You are Player 2.\n", 20);

	cout << "Player 2 has connected" << endl;
	client2_connected = true;
      }

    // Interact with Clients, Run Game
    bool done = false;
    int rounds = 0, p1_wins = 0, p2_wins = 0;
    while(!done){
      // Recieve Player Choices: READY, CHOICE, STOP
      read_count = read(client1_sockfd, p1_choice, sizeof(p1_choice));
      p1_choice[read_count] = '\0';
      read_count = read(client2_sockfd, p2_choice, sizeof(p2_choice));
      p2_choice[read_count] = '\0';

      // Begin or play game
      if (strcmp(p1_choice, "READY") == 0 && strcmp(p2_choice, "READY") == 0)
	{
	  write(client1_sockfd, "GO", 3);
	  write(client2_sockfd, "GO", 3);
	}
      else
	{
	  // Display user choice and winner
	  rounds++;
	  cout << "Round " << rounds << " :" << endl;
	  cout << "P1 choice: " << p1_choice << endl;
	  cout << "P2 choice: " << p2_choice << endl;
	  if (strcmp(p1_choice, "STOP" ) == 0 || strcmp(p2_choice, "STOP") == 0)
	    {
	      cout << "Game has ended" << endl;
	      // Stop games
	      write(client1_sockfd, "STOP #Rounds P1WinsCount P2WinCount", 4);
	      write(client2_sockfd, "STOP Summary", 4);
	      // Close Sockets
	      close(client1_sockfd);
	      close(client2_sockfd);
	      done = true;
	    }
	  else
	    {
	      // Decide Winner
	      switch(play(p1_choice, p2_choice))
		{
		case 1:
		  cout << "P1 wins" << endl;
		  write(client1_sockfd, "W P1Choice P2Choice", 2);
		  write(client2_sockfd, "L P1Choice P2Choice", 2);
		  p1_wins++;
		  break;
		case 2:
		  cout << "P2 wins" << endl;
		  write(client1_sockfd, "L", 2);
		  write(client2_sockfd, "W", 2);
		  p2_wins++;
		  break;
		case 3:
		  cout << "The round is a draw" << endl;
		  write(client1_sockfd, "T", 2);
		  write(client2_sockfd, "T", 2);
		  break;
		default:
		  cout << "Error: Cannot determine winner" << endl;
		}
	      
	      // Have client continue operations
	      write(client1_sockfd, "OK", 3);
	      write(client2_sockfd, "OK", 3);
	    }
	}
    }
  }
}

int play(char p1[], char p2[])
{
  if (strcmp(p1, "Paper") == 0)
    {
      if (strcmp(p2, "Paper") == 0)
	return 3;
      else if (strcmp(p2, "Rock") == 0)
	return 1;
      else 
	return 2;
    }
  else if (strcmp(p1, "Rock") == 0)
    {
      if (strcmp(p2, "Paper") == 0)
	return 2;
      else if (strcmp(p2, "Rock") == 0)
	return 3;
      else
	return 1;
    }
  else 
    {
      if (strcmp(p2, "Paper") == 0)
	return 1;
      if (strcmp(p2, "Rock") == 0)
	return 2;
      else
	return 3;
    }
}
