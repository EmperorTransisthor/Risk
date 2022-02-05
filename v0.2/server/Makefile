CC = g++
OPTMIZATION = -O0
MAIN_DIRECTORY = ${PWD}/..
CFLAGS = -I..
CPP = -std=c++1z
# CFLAGs = -I/home/emperor/Desktop/Projekciki/Risk/v0.2/
FUTURE_FLAGS = -Wcast-align -Wcast-align

OPTIONS = ${CFLAGS} ${OPTMIZATION}

#TODO put files to vector
	
compile:
	${CC} -c class_def.cpp ${OPTIONS}
	${CC} -c main.cpp ${OPTIONS}
	${CC} -c SerwerTCP.cpp ${OPTIONS}
	${CC} -c PipeCom/PipeHelper.cpp ${OPTIONS}
	${CC} -c SerwerMULTICAST.c ${OPTIONS}
	${CC} main.o class_def.o SerwerTCP.o SerwerMULTICAST.o PipeHelper.o -o RYZYKO
	rm *.o
	
