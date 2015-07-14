# sniff/Makefile
# sohail@stupidcomputing.com

.PHONY	: clean

all	: sniff.o init.o

%.o	: %.cc
	g++ -c $< -o $@ -D$(DEBUG)

clean	:
	rm -rf *.o

