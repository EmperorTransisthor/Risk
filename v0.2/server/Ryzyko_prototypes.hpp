#pragma once

// Structures
struct PipeHelper
{
    int p2cPipe[2];
    int c2pPipe[2];
    int *playerID_Address;
    std::string         *stringAddress;
    std::stringstream   *stringStreamAddress;
    char buffer[MAXLINE];
};

// Function prototypes
int mainMenu();
int choice();
int atoiChecker(char buffer[MAXLINE]);
Sector loadWorld();         // yet to be developed
void write_Buffer2Pipe_WRITE(int writingPipe, char buffer[MAXLINE], std::string *stringTemp);
void write_Buffer2Pipe_WRITE_2ALL(int writingPipe, char buffer[MAXLINE], std::string *stringTemp);
void write_Buffer2Pipe_READ (int writingPipe, char buffer[MAXLINE], std::string *stringTemp);
void  read_Buffer2Pipe(int readingPipe, char buffer[MAXLINE]);
void mutliOperationalPipe (int writingPipe, int readingPipe, int operation, char buffer[MAXLINE], std::string *stringTemp);
void pipeComParent (struct PipeHelper* pipeC, int operation);
void string_Flush(std::string* stringAddress);
void stringstream_Flush(std::stringstream* stringStreamAddress);
