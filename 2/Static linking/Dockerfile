FROM gcc:latest

COPY main.cpp Employee.cpp Database.cpp Employee.h Database.h Flags.h DatabaseIO.h DatabaseIO.cpp Makefile /usr/src/bin/

WORKDIR /usr/src/bin

RUN make
