#include "PipeHelper.h"
#include "common/ConstantValues.h"
#include "server/SerwerTCP.hpp"

#include <cstring>
#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>


int atoiChecker(char buffer[MAXLINE])
{
    std::string stringTemp;
    int temp = atoi(buffer);

    if (temp == 0)      // If atoi read buffer incorrectly, compensate
    {
        stringTemp = buffer;
        if (stringTemp.find("0") == std::string::npos)
            temp = -1;
    }
    return temp;
}

void write_Buffer2Pipe_WRITE (int writingPipe, char buffer[MAXLINE], std::string *stringTemp)
{
	int stringLength;
	strcpy(buffer, (*stringTemp).c_str());
	if (write(writingPipe, &operationWRITE, sizeof(int))        == -1) { printf("Write pipe error"); }
	stringLength = strlen(buffer);
	if (write(writingPipe, &stringLength, sizeof(int))          == -1) { printf("Write pipe error"); }
	if (write(writingPipe, buffer, stringLength * sizeof(char)) == -1) { printf("Write pipe error"); }
	(*stringTemp).clear(); // juz niepotrzebna
}

void write_Buffer2Pipe_WRITE_2ALL (int writingPipe, char buffer[MAXLINE], std::string *stringTemp)
{
	int stringLength;
	strcpy(buffer, (*stringTemp).c_str());
	if (write(writingPipe, &operationWRITE_2ALL, sizeof(int))   == -1) { printf("Write pipe error"); }
	stringLength = strlen(buffer);
	if (write(writingPipe, &stringLength, sizeof(int))          == -1) { printf("Write pipe error"); }
	if (write(writingPipe, buffer, stringLength * sizeof(char)) == -1) { printf("Write pipe error"); }
	(*stringTemp).clear();  // juz niepotrzebna
}

void write_Buffer2Pipe_READ (int writingPipe, char buffer[MAXLINE], std::string *stringTemp)
{
	int stringLength;
	strcpy(buffer, (*stringTemp).c_str());
	if (write(writingPipe, &operationREAD, sizeof(int))         == -1) { printf("Write pipe error"); }
	stringLength = strlen(buffer);
	if (write(writingPipe, &stringLength, sizeof(int))          == -1) { printf("Write pipe error"); }
	if (write(writingPipe, buffer, stringLength * sizeof(char)) == -1) { printf("Write pipe error"); }
	(*stringTemp).clear(); // juz niepotrzebna
}

void read_Buffer2Pipe (int readingPipe, char buffer[MAXLINE])
{
	int stringLength;
	if (read(readingPipe, &stringLength, 	sizeof(int)) 	    == -1) printf("Error reading buffer length from pipe\n");
    if (read(readingPipe, buffer, stringLength * sizeof(char)) == -1) printf("Error reading buffer from pipe\n");
}

// old, replaced by pipeComParent
void mutliOperationalPipe (int writingPipe, int readingPipe, int operation, char buffer[MAXLINE], std::string *stringTemp)
{
    if (operation == operationWRITE)
        write_Buffer2Pipe_WRITE (writingPipe, buffer, stringTemp);
    else if (operation == operationREAD)
    {
        write_Buffer2Pipe_READ  (writingPipe, buffer, stringTemp);
        read_Buffer2Pipe        (readingPipe, buffer);
    }
    else   
        std::cout << "Something went wrong in multiOperationalPipe\nWrong operation: " << operation << std::endl;
}

void pipeComParent(struct PipeHelper* pipeComStructure, int operation)
{
    std::string             *stringTempAddress;
    std::stringstream       *stringStreamTempAddress;
    int writingPipe         = pipeComStructure->p2cPipe[1];
    int readingPipe         = pipeComStructure->c2pPipe[0];
    stringTempAddress       = pipeComStructure->stringAddress;
    stringStreamTempAddress = pipeComStructure->stringStreamAddress;

    // zamiana stream na string
    *stringTempAddress = stringStreamTempAddress->str();
    // zamiana string na buffer

    if (operation == operationWRITE)
    {
        write_Buffer2Pipe_WRITE (writingPipe, pipeComStructure->buffer, stringTempAddress);

        // buffer flush
        memset(pipeComStructure->buffer, 0, sizeof(pipeComStructure->buffer));
    }

    else if (operation == operationREAD)
    {
        write_Buffer2Pipe_READ  (writingPipe, pipeComStructure->buffer, stringTempAddress);

        // buffer flush
        memset(pipeComStructure->buffer, 0, sizeof(pipeComStructure->buffer));
        read_Buffer2Pipe        (readingPipe, pipeComStructure->buffer);
    }

    else if (operation == operationCliChng)
    {
        if (write(writingPipe, &operationCliChng, sizeof(int))                  == -1) { printf ("Write operation to pipe error\n "); }
        if (write(writingPipe, pipeComStructure->playerID_Address, sizeof(int)) == -1) { printf ("Write client to pipe error\n"); }
    }

    else if (operation == operationWRITE_2ALL)
    {
        write_Buffer2Pipe_WRITE_2ALL (writingPipe, pipeComStructure->buffer, stringTempAddress);

        // buffer flush
        memset(pipeComStructure->buffer, 0, sizeof(pipeComStructure->buffer));
    }

    else if (operation == operationEXIT)
    {
        // ToDo
        if (write(writingPipe, &operationEXIT, sizeof(int)) == -1) { printf ("Write operation to pipe error\n"); }
    }

    else 
        std::cout << "Something went wrong in pipeComParent\nWrong operation: " << operation << std::endl;

    // clearing
    string_Flush (pipeComStructure->stringAddress);
    stringstream_Flush (pipeComStructure->stringStreamAddress);

}

void string_Flush (std::string* stringAddress)
{
    stringAddress->clear();
}

void stringstream_Flush (std::stringstream* stringStreamAddress)
{
    stringStreamAddress->str(std::string());
    stringStreamAddress->clear();
}

