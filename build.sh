#!/bin/bash

#TODO create simmilar script for Windows

CURRPATH=$PWD
GREEN='\033[0;32m'
NOCOLOR='\033[0m'
DELIMITER='---------------------------------------------'

cd v0.2
cd server && make && cd ..
cd client && make && cd CURRPATH

echo -e " ${DELIMITER}${GREEN} Build done ${NOCOLOR}${DELIMITER}"
