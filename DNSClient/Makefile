#------------------------------------786--------------------------------------
#*
#Makefile for dnsCli.
#dnsCli, the source code and the binary is covered by, GPL license.
#Written by, sonimalik@users.sf.net
#***********
#I've tested the dnsCli over 2.4.x and 2.6.x Linux kernel by using the DNS
#servers of my ISP and other servers which I could access. 
#***********
#This software is being distributed in the hope that you'll use it only for 
#the study and reserch purposes.
#Please ristrict your self, use this software in the off-peak hours 
#of the DNS server that you'll use/engage in your study and reserch.
#***********
#*
#-----------------------------------------------------------------------------

.PHONY		: clean	help 	
.DEFAULT	: all

all	:  dnsCli

dnsCli : dnsCli.o libA.o libB.o libC.o libD.o libE.o
	gcc -o dnsCli dnsCli.o libA.o libB.o libC.o libD.o libE.o	

dnsCli.o : dnsCli.c dnsCli.h cliServ.h
	gcc -o dnsCli.o dnsCli.c -c 

libA.o : libA.c dnsCli.h cliServ.h
	gcc -o libA.o libA.c -c 

libB.o : libB.c dnsCli.h cliServ.h
	gcc -o libB.o libB.c -c 

libC.o : libC.c dnsCli.h cliServ.h
	gcc -o libC.o libC.c -c 

libD.o : libD.c dnsCli.h cliServ.h
	gcc -o libD.o libD.c -c 

libE.o : libE.c dnsCli.h cliServ.h
	gcc -o libE.o libE.c -c 

#Be very careful, make sure only the object and the binary image get deleted -
#not the C source files.

clean  :
	rm dnsCli -f
	rm dnsCli.o -f
	rm libA.o -f
	rm libB.o -f
	rm libC.o -f
	rm libD.o -f
	rm libE.o -f

help	:
	@echo "help!";
	
