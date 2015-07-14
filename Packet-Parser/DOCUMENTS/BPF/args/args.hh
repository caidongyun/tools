//args.hh
//Written by, Sohail Qayum Malik<sohail@stupidcomputing.com>

#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <string>

using namespace::std;

//If defined then this file is already included
#ifndef	EXT3GREP_ARGS_H
#define EXT3GREP_ARGS_H
#endif

//Enable it to use the init() function, read where this macro is used in 
//the source code
#define	EXT3GREP_INIT_H 

#ifdef EXT3GREP_INIT_H
typedef	int (*init_func)(const int, char const*const*, const int, const int, char const*const*);
#include "./../init.hh"
#endif

#include "iter.hh"
#include "args.h"

class args {

   class argHistory;	

   struct stacked_arg {
      int command_index;
      int index;
      int com_argc;
      vector<argHistory>::iterator it;
   };	   

   class argHistory {

      public:

         int command;	   
         int lBnd;
         int argc;

         bool operator<(const argHistory& ref) const {
            return (lBnd < ref.lBnd);     
         }

	 bool operator==(const argHistory& ref) const {
            return (command == ref.command);		 
	 }

	 bool operator*(void) const {
            return !(this==NULL);		 
         }		 
   };

   typedef		size_t		size_type;

   bool			common_flag;

   const int& argc;
   char const*const* argv;
   //Passed to the functions
   int argc_com;
   //Internally used
   int com_argc;

   stack<stacked_arg> stk_obj;

   int command_index;
   int index;
 
   class argHistory cmd;
   vector<argHistory> cmdContainer;
   vector<argHistory>::iterator it;
   	
   string cmdStr(size_t, const string&);
   int matchCmdStr(string const&, int, int);

   bool operator++(int);
   bool operator++(void);
   bool operator--(void);
   bool operator[](int);
   string operator*(void);
   size_type size(void);

#ifdef	EXT3GREP_INIT_H
   init_func funk;  
#endif   
   	   
   public:
#ifdef EXT3GREP_INIT_H   
      args(const int&, char const*const* argv, string, init_func);
#else
      args(const int&, char const*const* argv, string);
#endif      
      
      ~args();

#ifdef EXT3GREP_INIT_H
      int init(void);
#endif
      
      args* begin(void) {
	 return this;     
      }	      
      args* end(void) {
	 return this;     
      }

      //args Iterator
      typedef		iter<args>	iterator;

      bool push(void);
      bool pop(void);
      bool discard(void);


   friend class iter<args>;   

};	
