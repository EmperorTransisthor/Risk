#include        <sys/types.h>   /* basic system data types */
#include        <sys/socket.h>  /* basic socket definitions */
#include        <sys/time.h>    /* timeval{} for select() */
#include        <time.h>                /* timespec{} for pselect() */
#include        <netinet/in.h>  /* sockaddr_in{} and other Internet defns */
#include        <arpa/inet.h>   /* inet(3) functions */
#include        <errno.h>
#include        <fcntl.h>               /* for nonblocking */
#include        <netdb.h>
#include        <signal.h>
#include        <stdio.h>
#include        <stdlib.h>
#include        <string.h>
#include 		<unistd.h>
#include 		<stdbool.h>
#include		<syslog.h>
#include		<string.h>
#include 		<string>
#include		<vector>
#include 		<iostream>
#include 		"SerwerTCP.hpp"


static int	read_cnt;
static char* read_ptr;
static char	read_buf[MAXLINE];





int daemon_init(const char* pname, int facility, uid_t uid)
{
	int		i, p;
	pid_t	pid;

	if ((pid = fork()) < 0)
		return (-1);
	else if (pid)
		exit(0);			//skasowanie rodzica

	//dziecko 1 kontynuuje

	if (setsid() < 0)			//stanie sie leaderem sesji
		return (-1);

	signal(SIGHUP, SIG_IGN);
	if ((pid = fork()) < 0)
		return (-1);
	else if (pid)
		exit(0);			//kasowanie dziecka pierwszego

	//dziecko drugie kontynuuje

	chdir("/tmp");				//zmiana folderu
//	chroot("/tmp");


	//zamkniecie deskryptora plikow
	for (i = 0; i < MAXFD; i++) {
		close(i);
	}


	//przekierowanie stdin, stdout i stderr do /dev/null
	p = open("/dev/null", O_RDONLY);
	open("/dev/null", O_RDWR);
	open("/dev/null", O_RDWR);

	openlog(pname, LOG_PID, facility);

	setuid(uid); //zmiana uzwytkownika
	syslog(LOG_NOTICE, "Daemon started!");
	return (0);				//sukces
}

/* void write_Buffer2Pipe (int writingPipe, char buffer[MAXLINE], std::string *stringTemp) // zmienic w2p na wp
{
	int stringLength;
	strcpy(buffer, (*stringTemp).c_str());
	if (write(writingPipe, &operationREAD, sizeof(int))    == -1) { printf("Write pipe error"); }
	stringLength = strlen(buffer);
	if (write(writingPipe, &stringLength, sizeof(int))    == -1) { printf("Write pipe error"); }
	if (write(writingPipe, &buffer, stringLength * sizeof(char)) == -1) { printf("Write pipe error"); }
	else
		std::cout << "Well well well..." << std::endl;
	(*stringTemp).clear();
}

void read_Buffer2Pipe (int readingPipe, char buffer[MAXLINE])
{
	int stringLength;
	if (read(readingPipe, &stringLength, 	sizeof(int)) 	== -1) printf("Error reading buffer length from pipe\n");
    if (read(readingPipe, &buffer, 			sizeof(buffer)) == -1) printf("Error reading buffer from pipe\n");
} */

char* nickCheck(char buf[MAXLINE], int* n, int* currentClient, int numberOfClients, bool* sendSuccess, struct PlayerServ* player, PlayerServ vectorOfPlayers[MAXPLAYERS])
{
	char nick_temp[*n];
	// Client ID ++
	(*currentClient)++;
	if ((*currentClient) == numberOfClients)
		*currentClient %= numberOfClients;

	snprintf(nick_temp, *n, "%s", buf);
	
	// Checking, if nick is correct (not NULL, not more than 24 chars, less than 4 and not used by anyone)
	if (*n > (NICKMAXLEN + 1))
	{
		*sendSuccess = false;
		return "Your nick has to be at least 4 characters and no more, than 24";
	}

	if (*n < (NICKMINLEN + 1))
	{
		*sendSuccess = false;
		return "Your nick has to be at least 4 characters and no more, than 24";
	}

	//if (!(strcmp(nick_temp, "NULL") == 0))
	if (strcmp(nick_temp, "NULL") == 0)
	{
		*sendSuccess = false;
		return "Your nick can't be 'NULL'";
	}

	/* for (int i = 0; i < (numberOfClients-1); i++)
	{
		char nick_temp2[strlen(nickChar[i])];
		strcpy(nick_temp2, nickChar[i]);
		printf("nick_temp = %s\nnick[%d] = %s\n", nick_temp, i, nick_temp2);
		if (strcmp(nick_temp2, nick_temp) == 0)
		{
			//printf("YES\n");
			*sendSuccess = false;
			sprintf(buf, "Nick '%s' is already in use", nick_temp);
			return buf;
		}
	} */
	std::string nickStrTemp = nick_temp;
	for (int i = 0; i < (numberOfClients - 1); i++)
	{
		if (vectorOfPlayers[i].nick == nickStrTemp)
		{
			std::cout << "Matching string has been found in vectorOfPlayers!!" << std::endl;
			*sendSuccess = false;
			sprintf(buf, "Nick '%s' is already in use", nick_temp);
			return buf;
		}
	}
	
	// If the nick went through verification successfully, place nick in structure and inform user, that it is correct
	//player->nick = nick_temp;
	// std::cout << "Current client: " << *currentClient << std::endl;
	// char* nickTemp3 = {nick_temp};
	// strcpy(nickChar[*currentClient], nickTemp3); // ta linijka crashuje program
	strcpy(player->nickChar, nick_temp);
	player->nick = nick_temp;
	player->init.nickAccepted = true;
	*sendSuccess = true;
	*n = 21;
	std::cout << "Nick string: " << player->nick << std::endl;
	printf("Nick Assigned: %s", player->nickChar);
	return "You've join the game!";
}

char* handshakeResponse(struct PlayerServ* player, bool *sendSuccess)
{
	player->init.handshake = true;
	*sendSuccess = true;
	return "You've successfully connected to the server.\nPlease enter your nick";
}

char*
Check(char buf[MAXLINE], int* n, int* currentClient, int numberOfClients, bool* sendSuccess)
{
	// Client ID ++
	(*currentClient)++;
	if ((*currentClient) == numberOfClients)
		*currentClient %= numberOfClients;

	int val = atoi(buf);
	if (val == 1)
	{
		*n = 4;
		*sendSuccess = true;
		return "Done";
	}
	else
	{
		*n = 6;
		*sendSuccess = false;
		return "Undone";
	}
}

const char*
Wait(int* n)
{
	char temp[] = "It's not your turn";
	*n = strlen(temp);
	return "It's not your turn";
}

void
sig_pipe(int signo)
{
	printf("Server received SIGPIPE - Default action is exit \n");
	exit(1);
}

static ssize_t
my_read(int fd, char* ptr)
{

	if (read_cnt <= 0) {
	again:
		if ((read_cnt = read(fd, read_buf, sizeof(read_buf))) < 0) {
			if (errno == EINTR)
				goto again;
			return(-1);
		}
		else if (read_cnt == 0)
			return(0);
		read_ptr = read_buf;
	}

	read_cnt--;
	*ptr = *read_ptr++;
	return(1);
}

ssize_t
readline(int fd, char* vptr, size_t maxlen)
{
	ssize_t	n, rc;
	char	c, * ptr;

	ptr = vptr;
	for (n = 1; n < maxlen; n++) {
		if ((rc = my_read(fd, &c)) == 1) {
			*ptr++ = c;
			if (c == '\n')
				break;	/* newline is stored, like fgets() */
		}
		else if (rc == 0) {
			*ptr = 0;
			return(n - 1);	/* EOF, n - 1 bytes were read */
		}
		else
			return(-1);		/* error, errno set by read() */
	}

	*ptr = 0;	/* null terminate like fgets() */
	return(n);
}

/* end readline */

ssize_t
Readline(int fd, char* ptr, size_t maxlen)
{
	ssize_t		n;

	if ((n = readline(fd, ptr, maxlen)) < 0)
		perror("readline error");
	return(n);
}



ssize_t						/* Write "n" bytes to a descriptor. */
writen(int fd, const char* vptr, size_t n)
{
	size_t		nleft;
	ssize_t		nwritten;
	const char* ptr;

	ptr = vptr;
	nleft = n;
	while (nleft > 0) {
		if ((nwritten = write(fd, ptr, nleft)) <= 0) {
			if (nwritten < 0 && errno == EINTR)
				nwritten = 0;		/* and call write() again */
			else
				return(-1);			/* error */
		}

		nleft -= nwritten;
		ptr += nwritten;
	}
	return(n);
}
/* end writen */

void
Writen(int fd, char* ptr, size_t nbytes)
{
	if (writen(fd, ptr, nbytes) != nbytes)
		perror("writen error");
}


ssize_t
Read(int fd, void* ptr, size_t nbytes)
{
	ssize_t		n;

	if ((n = read(fd, ptr, nbytes)) == -1) {
		perror("read error");
		exit(1);
	}
	return(n);
}

int
servTCP(int* p2c_pipe, int* c2p_pipe)
{
	int			listenfd, connfd, sockfd, currentClient = 0, numberOfClients = 0;
	pid_t			childpid;
	socklen_t		clilen;
	struct sockaddr_in	cliaddr, servaddr;
	struct timeval  delay;
	void			sig_chld(int);
	int			i, maxi, maxfd, n;
	int			nready, client[FD_SETSIZE];
	fd_set			rset, allset;
	char 			buf[MAXLINE], addr_buf[INET_ADDRSTRLEN + 1], response[MAXLINE];
	bool packetAccept = false, sendSuccess = false;
	PlayerServ player[6];
	bool gameInitServ = true, gameCanStart = false, test = true, gameEnd = false;
	int operation;

	std::vector <PlayerServ> vectorOfPlayers_Serv;
	
	
	//Write((c2pPipe[1], &vectorOfPlayers_Serv ,sizeof(vector0fPlayers)) == -1) { printf("Write pipe error");}
/*
	setlogmask(LOG_UPTO(LOG_INFO));
	daemon_init(argv[0], LOG_LOCAL1, 1000);
*/
	signal(SIGPIPE, sig_pipe);

	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		fprintf(stderr, "socket error : %s\n", strerror(errno));
		return 1;
	}


	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	//servaddr.sin_addr   = inaddr_any;
	servaddr.sin_port = htons(2000);	/* echo server */

	if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
		fprintf(stderr, "bind error : %s\n", strerror(errno));
		// return 1;
		exit(9001);
	}

	delay.tv_sec = 10;
	delay.tv_usec = 0;
	if (setsockopt(listenfd, SOL_SOCKET, SO_RCVTIMEO, &delay, sizeof(delay)) == -1) {
		fprintf(stderr, "SO_RCVTIMEO error : %s\n", strerror(errno));
		return 1;
	}
	int enable = 1;
	if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(delay)) < 0) {
		fprintf(stderr, "SO_REUSEADDR error : %s\n", strerror(errno));
		return 1;
	}

	if (listen(listenfd, LISTENQ) < 0) {
		fprintf(stderr, "listen error : %s\n", strerror(errno));
		return 1;
	}

	fprintf(stderr, "Waiting for clients ... \n");

	maxfd = listenfd;			/* initialize */
	maxi = -1;					/* index into client[] array */
	for (i = 0; i < FD_SETSIZE; i++)
		client[i] = -1;			/* -1 indicates available entry */
	FD_ZERO(&allset);
	FD_SET(listenfd, &allset);



	//////////////////////////			INIT LOOP			/////////////////////////////
	while(gameInitServ){
		rset = allset;		/* structure assignment */

		if ((nready = select(maxfd + 1, &rset, NULL, NULL, NULL)) < 0) {
			perror("select error");
			exit(1);
		}


		if (FD_ISSET(listenfd, &rset)) {	/* new client connection */
			clilen = sizeof(cliaddr);
			if ((connfd = accept(listenfd, (SA*)&cliaddr, &clilen)) < 0) {
				perror("accept error");
				exit(1);
			}

			bzero(addr_buf, sizeof(addr_buf));
			inet_ntop(AF_INET, (struct sockaddr*)&cliaddr.sin_addr, addr_buf, sizeof(addr_buf));

			printf("New client: %s, port %d\n",
				addr_buf, ntohs(cliaddr.sin_port));
			numberOfClients++;
			/*if ((sockfd = client[numberOfClients-1]) < 0)
			{
				char response[MAXLINE];
				strcpy(response, handshakeResponse(&player[numberOfClients-1], &sendSuccess));
				sendSuccess = false;
				n = strlen(response);
				Writen(sockfd, response, n);
			}*/
			
			for (i = 0; i < FD_SETSIZE; i++)
				if (client[i] < 0) {
					client[i] = connfd;	/* save descriptor */
					break;
				}
			if (i == FD_SETSIZE) {
				fprintf(stderr, "too many clients");
				continue;
			}
			printf("1\n");
			FD_SET(connfd, &allset);	/* add new descriptor to set */
			if (connfd > maxfd)
				maxfd = connfd;			/* for select */
			if (i > maxi)
				maxi = i;				/* max index in client[] array */
			printf("if\n");
			

			strcpy(response, handshakeResponse(&player[numberOfClients-1], &sendSuccess));
			sendSuccess = false;
			/* 
			if (numberOfClients < 2)
				sprintf(response, "%s\n You've been accepted, please wait\n You can start the game when there will be from 2 to 6 players\nCurrent number of players: %d\n", response, numberOfClients);
			else
				sprintf(response, "%s\n You've been accepted\n You can start the game now. Write 'start' to start\nCurrent number of players: %d\n", response, numberOfClients);
			*/
			n = strlen(response);
			//Writen(sockfd, response, n);// co to kurwa jest?
			Writen(client[numberOfClients-1], response, strlen(response));		// co to kurwa jest?
			//n = client[numberOfClients-1];
			//printf("n = %d\nresponse = %s\n", n, response);
			
			//Writen(client[numberOfClients-1], response, strlen(response));		// co to kurwa jest?
			//printf("Wysyp\n");
			if (--nready <= 0)
				continue;				/* no more readable descriptors */
				
			printf("3\n");
			//if ((sockfd = client[numberOfClients-1]) < 0)
			//{
			
			//}
		}

		for (i = 0; i <= maxi; i++) {	/* check all clients for data */

			if ((sockfd = client[i]) < 0)
				continue;
			if (FD_ISSET(sockfd, &rset)) {
				if ((n = Readline(sockfd, buf, MAXLINE)) == 0) {
					/* connection closed by client */
					numberOfClients--;
					close(sockfd);
					FD_CLR(sockfd, &allset);
					client[i] = -1;
				}
				else
				{

					//if (i == currentClient)
					//	packetAccept = true;
					if (!player[i].init.nickAccepted)
					{
						if (n < 0) {
							close(sockfd);
							FD_CLR(sockfd, &allset);
							client[i];
							continue;
						}
						//sleep(1); //processing delay simulation
						char response[MAXLINE];
						printf("i = %d\nsockfd = %d\n", i, sockfd);
						std::cout << "Buffer: " << buf << std::endl;
						//strcpy(response, Check(buf, &n, &currentClient, numberOfClients, &sendSuccess));
						if (player[i].init.handshake)
							strcpy(response, nickCheck(buf, &n, &currentClient, numberOfClients, &sendSuccess, &player[i], player));
						else
							strcpy(response, handshakeResponse(&player[i], &sendSuccess));
						//printf("%d\n", currentClient);
						std::cout << "Buffer: " << buf << std::endl;
						n = strlen(response);
						Writen(sockfd, response, n);

						if (player[i].init.nickAccepted)
						{
							if (numberOfClients < 2)
								sprintf(response, "You've been accepted, please wait\n You can start the game when there will be from 2 to 6 players\nCurrent number of players: %d\n", numberOfClients);
							else
								sprintf(response, "You've been accepted\n You can start the game now. Write 'start' to start\nCurrent number of players: %d\n", numberOfClients);
							n = strlen(response);
							Writen(sockfd, response, n);
						}
				
						//if (sendSuccess)
						//	packetAccept = false;
					}
					else if (player[i].init.nickAccepted)
					{
						/* It's not your turn, player X */
						if (n < 0) {
							close(sockfd);
							FD_CLR(sockfd, &allset);
							client[i];
							continue;
						}
						//sleep(1); //processing delay simulation
						char response[MAXLINE];
						sprintf(response, "You've been accepted, please wait\n You can start the game when there will be from 2 to 6 players\nCurrent number of players: %d\n", numberOfClients);
						//strcpy(response, "You've been accepted, please wait\n You can start the game when there will be from 2 to 6 players\n");
						n = strlen(response);
						Writen(sockfd, response, n);
						if ( (numberOfClients >= 2) && (numberOfClients < 7) )
						{
							if (!gameCanStart)
							{
								//sprintf(response, "You've been accepted, please wait\n You can start the game when there will be from 2 to 6 players\nCurrent number of players: %d\n", numberOfClients);
								strcpy(response, "You can start the game now. Write 'start' to start");
								n = strlen(response);
								Writen(sockfd, response, n);
								gameCanStart = true;
							}
							/*
							//strcpy(buf," ");
							//checking response to know if we start game
							if ((n = read(sockfd, buf, MAXLINE)) == 0) {
								perror("str_cli: server terminated prematurely");
								exit(0);
							}
							//sprintf(buf, "%s\0", buf);
							snprintf(buf, 5, "%s", buf);
							printf("buf = %s\n", buf);
							printf("buflen = %ld\nstartlen = %ld\n", strlen(buf), strlen("start"));*/
							else {
								buf[strlen(buf)-1] = '\0';
								if (strcmp(buf, "start") == 0)
								{
									bool canStart = true;
									for (int initV = 0; initV < numberOfClients; initV++)
									{
										if (player[initV].nick.empty())
										{
											canStart = false;
											break;
										}
									}

									if (canStart)
									{
										printf("dziala\n");
										gameInitServ = false;
										
										std::cout << "sockfd[0] = " << client[0] << std::endl;
										std::cout << "sockfd[1] = " << client[1] << std::endl;
										break;
									}

									else
									{
										strcpy(buf, "Can't start the game. Someone is typing nick\n");
										Writen(sockfd, buf, sizeof(buf));
									}
								}

								else if (gameInitServ)
								{
									strcpy(response, "Write 'start' to start");
									n = strlen(response);
									Writen(sockfd, response, n);
								}
								else
									break;
							}

						}
					}
					else
					{
						/* It's not your turn, player X */
						if (n < 0) {
							close(sockfd);
							FD_CLR(sockfd, &allset);
							client[i];
							continue;
						}
						//sleep(1); //processing delay simulation
						//char response[MAXLINE];
						//strcpy(response, Wait(&n));
						strcpy(response, "Error, please try again");
						n = strlen(response);
						Writen(sockfd, response, n);
					}
					
				}
				if (--nready <= 0)
					break;				/* no more readable descriptors */
				

			}
		}
		
	}

	/*printf("Deleting unnecessary players\n");
	for (int temp = MAXPLAYERS; temp != numberOfClients; temp--)
		vectorOfPlayers_Serv.pop_back();*/
	// for (int temp = 0; temp < numberOfClients; temp++)
	// 	vectorOfPlayers_Serv.push_back(player[temp]);
	char arrayOfChars[150];
	memset(arrayOfChars, 0, sizeof(arrayOfChars));
	strcpy (arrayOfChars, player[0].nickChar);
	for (int temp = 1; temp < numberOfClients; temp++){
		strcat (arrayOfChars, " ");
		strcat (arrayOfChars, player[temp].nickChar);
	}
	printf("Wyszlo\n");

	unsigned int data;

	data = numberOfClients;
	// strlen for
	std::cout << "Server sending nicks!" << std::endl;
	if (write(*c2p_pipe, &data, sizeof(data)) == -1) printf("Write server init data to pipe failed\n");
	std::cout << "Server prog(1/4)" <<std::endl;
	// if (read (*p2c_pipe, &operation, sizeof(int)) == -1) printf("ACK Server error\n");
	// std::cout << "Server prog(2/4)" <<std::endl;


	// if(write(*c2p_pipe, &vectorOfPlayers_Serv, 6* sizeof(std::vector <PlayerServ>)) == -1) printf("Write pipe error");
	if (write(*c2p_pipe, arrayOfChars, sizeof(arrayOfChars)) == -1) printf("Write pipe error");
	std::cout << "Server prog(3/4)" <<std::endl;

	int startingPlayer;
	if(read(*p2c_pipe , &startingPlayer, sizeof(int)) == -1) printf("Read pipe error");
	std::cout << "Server prog(4/4)" <<std::endl;
	std::cout << "sending nicks end" << std::endl;
	std::cout << "Starting player: " << player[startingPlayer].nick << " (" << startingPlayer << ")"<< std::endl;

	currentClient = startingPlayer;

	// Informing all players, who is starting
	sprintf(buf, "Starting player is %s\nPlease wait for your turn", player[startingPlayer].nickChar);
	printf("%s\n", buf);
	// Dlaczego to dociera takze do rozpoczynajajacegi gracza ??
	for (int initClient = 0; initClient < numberOfClients; initClient++)
	{
		sockfd = client[initClient];
		std::cout << "sockfd[" << sockfd << "]" << std::endl;
		if (initClient != startingPlayer)
			Writen(sockfd, buf, sizeof(buf));
	}

///////////////////////// 			MAIN LOOP			///////////////////////////////
#ifndef mainLoop

	while (!gameEnd)
	{
		// rset = allset;		/* structure assignment */
		/* mozna tu dodac funkcje do obslugi innych klientow */

		currentClient %= numberOfClients;
		if (read (*p2c_pipe, &operation, sizeof(int)) == -1) { printf("Error reading from pipe\n"); }
		if (operation == operationWRITE)
		{
			memset(buf, 0, sizeof(buf));
			std::cout << "operationWRITE\n";
			int stringLength;
			if (read (*p2c_pipe, &stringLength, sizeof(int)) == -1) { printf("Error reading from pipe\n"); }
			if (read (*p2c_pipe, &buf, stringLength * sizeof(char)) == -1) { printf("Error reading from pipe\n"); }
			std::cout << "buf:\n" << buf << std::endl;
			Writen(client[currentClient], buf, sizeof(buf));
			std::cout << "currentClient: " << player[currentClient].nick << " (" << currentClient << ")" << std::endl;
			std::cout << "sockfd = " << client[currentClient] << std::endl;
		}

		else if (operation == operationREAD)
		{
			memset(buf, 0, sizeof(buf));
			std::cout << "operationREAD" << std::endl;
			int stringLength;
			if (read (*p2c_pipe, &stringLength, sizeof(int)) == -1) { printf("Error reading from pipe\n"); }
			if (read (*p2c_pipe, &buf, stringLength * sizeof(char)) == -1) { printf("Error reading from pipe\n"); }
			std::cout << "currentClient = " << currentClient << std::endl;
			std::cout << "client[currentClient] = " << client[currentClient] << std::endl;
			Writen(client[currentClient], buf, sizeof(buf));

			bool innerLoop = true;
			while(innerLoop)
			{
				rset = allset;
				if ((nready = select(maxfd + 1, &rset, NULL, NULL, NULL)) < 0) {
					//perror("select error\n");
					printf("select error\n");
					exit(1);
				}
				printf("Post If\n");
				for (i = 0; i <= maxi; i++) 
				{	/* check all clients for data */
					if ((sockfd = client[i]) < 0)
						continue;

					
					if (FD_ISSET(sockfd, &rset)) 
					{
						if ((n = Readline(sockfd, buf, MAXLINE)) == 0) {
							/*4connection closed by client */
							close(sockfd);
							FD_CLR(sockfd, &allset);
							client[i] = -1;
						}


						else
						{
							
							std::cout << "(server) buf: " << buf << std::endl;
							if (i == currentClient)
								packetAccept = true;
							if (packetAccept)
							{
								if (n < 0) {
									close(sockfd);
									FD_CLR(sockfd, &allset);
									client[i];
									continue;
								}
								
								stringLength = strlen(buf);
								if (write(*c2p_pipe, &stringLength, sizeof(int)) == -1)			printf("Error writing string length to buffer\n"); 
								if (write(*c2p_pipe, &buf, stringLength * sizeof(char)) == -1) 	printf("Error writing buffer to pipe\n");
								
								printf("Response accepted (server)\n");
								/* if (read(*p2c_pipe, &buf, sizeof(buf)) == -1) printf("Read pipe error");
								// if strtok(buf, ^) buf == READ
								//		pipe (read)	+ Writen
								// else if buf == Write
								//		Writen, Readline + pipe(write)
								

								//printf("i = %d\nsockfd = %d\ncurrentClient  = %d\n", i, sockfd, currentClient);
								//char response[MAXLINE];
								//if (write(*c2p_pipe, &buf, sizeof(buf)) == -1) { printf("Write pipe error"); }
								n = strlen(buf);
								Writen(sockfd, buf, n); */

								if (sendSuccess)
								{
									packetAccept = false;
									innerLoop = false;
								}
								
							}
							else
							{
								/* It's not your turn, player X */
								if (n < 0) {
									close(sockfd);
									FD_CLR(sockfd, &allset);
									client[i];
									continue;
								}
								//sleep(1); //processing delay simulation
								char response[MAXLINE];
								strcpy(response, Wait(&n));
								Writen(sockfd, response, n);
							}
						}
						if (--nready <= 0)
							break;				/* no more readable descriptors */
					}
				}
			}
		}
		
		else if (operation == operationCliChng)
		{
			int pastPlayer = currentClient;
			
			if (read(*p2c_pipe, &currentClient, sizeof(int)) == -1) 
				printf("Something went wrong when readig current player from pipe\n"); 
			sprintf(buf, "Your turn has ended %s. Please wait for other players. Next player: %s\n", player[pastPlayer].nickChar, player[currentClient].nickChar);
			// strcpy(buf, "Your turn has ended. Please wait for other players\n");
			Writen(client[pastPlayer], buf, sizeof(buf));
		}

		else if (operation == operationWRITE_2ALL)
		{
			memset(buf, 0, sizeof(buf));
			std::cout << "operationWRITE_2ALL\n";
			int stringLength;
			if (read (*p2c_pipe, &stringLength, sizeof(int)) 		== -1) { printf("Error reading from pipe\n"); }
			if (read (*p2c_pipe, &buf, stringLength * sizeof(char)) == -1) { printf("Error reading from pipe\n"); }
			for (int j = 0; j < numberOfClients; j++)
				Writen(client[j], buf, sizeof(buf));
		}

		else if (operation == operationEXIT)
		{
			// ToDo
			memset(buf, 0, sizeof(buf));
			sprintf(buf, "Game was closed by %s", player[currentClient].nickChar);
			for (int j = 0; j < numberOfClients; j++)
				Writen(client[j], buf, sizeof(buf));
			exit(0);
		}

		else
			printf("Something went wrong when reading operation\n");
	}
#endif	/* mainLoop*/
	exit(500);
	
}

