CC=gcc
CFLAG=-g -Wall -W
OBJGROUP=main.o calc.o 

all: program

program: $(OBJGROUP)
	$(CC) -o calc_app.exe $(OBJGROUP)

clean: 
	\rm *.o
