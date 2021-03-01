#pragma once

// Server constants
#define MAXLINE 1024

#define SA struct sockaddr

#define LISTENQ		2
#define	MAXFD		64
#define NICKMAXLEN	24
#define NICKMINLEN   4
#define MAXPLAYERS	 6

const int operationREAD 		= 0;		// Server to client without response
const int operationWRITE 		= 1;		// Server to client with    response
const int operationCliChng  	= 2;		// Game to server (which player turn)
const int operationWRITE_2ALL	= 3;
const int operationEXIT			= 4;
//const int operationACK			= 1;		// Pipe content accepted


struct PlayerInit {
	bool handshake = false;
	bool nickAccepted = false;
};

struct PlayerServ {
	char nickChar[NICKMAXLEN+1] = "NULL";
	std::string nick;
	bool implemented = false;
	struct PlayerInit init;
	int sockfd;
};

int daemon_init(const char* pname, int facility, uid_t uid);
char* nickCheck(char buf[MAXLINE], int* n, int* currentClient, int numberOfClients, bool* sendSuccess, struct PlayerServ* player, char* nickChar[MAXPLAYERS]);
char* handshakeResponse(struct PlayerServ* player, bool *sendSuccess);
char* Check(char buf[MAXLINE], int* n, int* currentClient, int numberOfClients, bool* sendSuccess);
const char* Wait(int* n);
void sig_pipe(int signo);
static ssize_t my_read(int fd, char* ptr);
ssize_t readline(int fd, char* vptr, size_t maxlen);
ssize_t Readline(int fd, char* ptr, size_t maxlen);
ssize_t	writen(int fd, const char* vptr, size_t n);
void Writen(int fd, char* ptr, size_t nbytes);
ssize_t Read(int fd, void* ptr, size_t nbytes);
int servTCP(int* p2c_pipe, int* c2p_pipe);
// void write_Buffer2Pipe(int w2p, char buffer[MAXLINE], std::string *stringTemp);
// void  read_Buffer2Pipe(int r2p, char buffer[MAXLINE]);
