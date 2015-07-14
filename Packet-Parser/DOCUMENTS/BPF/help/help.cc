// help/help.cc

#include "help.hh"

int help(const int argc, char const*const* argv, \
		    const int common_argc, char const*const* common_argv) {
   
   int count;

#ifdef	EXT3GREP_INIT_H
   args arg(argc, argv, COMMANDS, help_init);
#else

   args arg(argc, argv, COMMANDS);
#endif   

   //At index 0, the name of the programm is 
   for(count=1; count < common_argc; count++)
      cout<<common_argv[count]<<endl;

#ifdef	EXT3GREP_INIT_H
   arg.init();
#endif   
 
   return 0;	 
}	
