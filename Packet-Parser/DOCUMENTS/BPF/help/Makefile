# help/Makefile
# sohail@stupidcomputing.com

.PHONY	: clean

all	: help.o init.o

%.o	: %.cc
	g++ -c $< -o $@

clean	:
	rm -rf *.o

