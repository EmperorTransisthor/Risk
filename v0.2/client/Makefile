CC = gcc
MAIN_DIRECTORY = ${PWD}/..
CFLAGS = -I..
OPTIONS = ${CFLAGS} ${OPTMIZATION}
FUTURE_FLAGS = -Wcast-align -Wcast-align

# TODO improve this makefile
# all: clientMulti clientTCP

# clientMulti: clientMulti.c 
# 	gcc -o clientMulti clientMulti.c
	
# clientTCP: clientTCP.c 
# 	gcc -o clientTCP clientTCP.c 	

# clean:
# 	rm clientMulti clientTCP

OPTIONS = ${CFLAGS} ${OPTMIZATION}

#TODO put files to vector
compile:
	${CC} -o clientMulti clientMulti.c ${OPTIONS}
	${CC} -o clientTCP clientTCP.c ${OPTIONS}

clean:
	rm *.o
