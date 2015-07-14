# Makefile
# [sqm@hackers.pk]

ifeq ($(DEBUG),)
   DEBUG="SNIFF_DEBUG_NOT"
endif

.PHONY	: clean	all

all		: main.o args.o init.o help.o bpf.o sniff.o 
		g++ main.o init.o args/args.o help/help.o help/init.o BPF/bpf.o sniff/sniff.o sniff/init.o -o sniffer

main.o		: main.cc main.hh main.h
		g++ -c main.cc -o main.o

args.o		:
		make -C args

help.o		:
		make -C help

sniff.o		:
		make -C sniff DEBUG=$(DEBUG)

bpf.o		:
		make -C BPF

init.o		: init.cc init.hh init.h
		g++ -c init.cc -o init.o
	
clean		:
		make -C args clean
		make -C help clean
		make -C sniff clean
		make -C BPF clean
		rm -rf *.o
		rm -rf sniffer
