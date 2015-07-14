# BPF/Makefile
# Sohail Qayum Malik[sqm@hackers.pk, http://hackers.pk/sohail, http://github.com/sohail, http://sohail.github.com/resume]

.PHONY	: clean

all	: bpf.o

bpf.o	: bpf.h bpf.c
	gcc -c $< -o $@

clean	:
	rm -rf *.o

