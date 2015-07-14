//main.cc
//Written by, Sohail Qayum Malik[sqm@hackers.pk]

#include "main.hh"

int main(int argc, char *argv[]) { 

   int ret = 0;	
	
#ifdef	EXT3GREP_INIT_H 
   args arg(argc, argv, COMMANDS, init);	
#else
   args arg(argc, argv, COMMANDS);
#endif   
   
#ifdef	EXT3GREP_INIT_H
   ret = arg.init();
#endif   

   return ret; 	
}	
