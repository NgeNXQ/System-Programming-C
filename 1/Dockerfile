FROM gcc:latest

COPY main.cpp Employee.cpp Database.cpp Employee.h Database.h Flags.h Makefile /usr/src/bin/

WORKDIR /usr/src/bin

RUN make

CMD [ "./labwork1" ]