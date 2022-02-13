#pragma once

#include "common/ConstantValues.h"

#include <string>
#include <sstream>

// namespace pipeCom
// {

struct PipeHelper
{
    int p2cPipe[2];
    int c2pPipe[2];
    int *playerID_Address;
    std::string         *stringAddress;
    std::stringstream   *stringStreamAddress;
    char buffer[MAXLINE];
};

void write_Buffer2Pipe_WRITE(int writingPipe, char buffer[MAXLINE], std::string* stringTemp);
void write_Buffer2Pipe_WRITE_2ALL(int writingPipe, char buffer[MAXLINE], std::string* stringTemp);
void write_Buffer2Pipe_READ (int writingPipe, char buffer[MAXLINE], std::string* stringTemp);
void  read_Buffer2Pipe(int readingPipe, char buffer[MAXLINE]);
void mutliOperationalPipe (int writingPipe, int readingPipe, int operation, char buffer[MAXLINE], std::string* stringTemp);
void pipeComParent (struct PipeHelper* pipeC, int operation);
void string_Flush(std::string* stringAddress);
void stringstream_Flush(std::stringstream* stringStreamAddress);

// } // namespace pipeCom