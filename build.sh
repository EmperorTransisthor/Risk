#!/bin/bash

#TODO create simmilar script for Windows

CURRPATH=$PWD

cd v0.2
cd server && make && cd ..
cd client && make && cd CURRPATH