FROM gcc:latest

#COPY * /usr/src/bin
COPY main.cpp Employee.cpp Database.cpp Employee.h Database.h Flags.h /usr/src/bin/

WORKDIR /usr/src/bin

RUN make

CMD [ "./labwork1" ]