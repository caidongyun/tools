// help/init.cc

#include "init.hh"

int help_init(const int argc, char const*const* argv, const int command, \
                     const int common_argc, char const*const* common_argv) {

   int count;	
   int ret = 0;
   
   for(count = 1; count < common_argc; count++)
      cout<<common_argv[count]<<endl;	   

   return ret;
}	
