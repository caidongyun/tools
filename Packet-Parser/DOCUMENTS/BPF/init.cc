//init.cc
//Written by, Sohail Qayum Malik[sqm@hackers.pk]

#include "init.hh"

int init(const int argc, char const*const* argv, const int command, \
		     const int common_argc, char const*const* common_argv) {
   
   int ret = 0;	

   switch(command) {

      case HELP: 

         ret = help(argc, argv, common_argc, common_argv); 	      
      break;

      case SNIFF:

         ret = sniff(argc, argv, common_argc, common_argv);  
      break;
   }	  

   return ret;	
}	
