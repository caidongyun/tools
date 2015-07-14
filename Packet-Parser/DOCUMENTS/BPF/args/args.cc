/*
 *
 * args.cc --- Provides lots of container specific definitions
 * Copyright (C) 2009 Sohail Qayum Malik<sohail@stupidcomputing.com>
 * This file may be redistributed under the terms of the GNU Public License
 *
 * For the latest version of this file visit...
 *                   http://www.stupidcomputing.com/page.php?id=alf
 *
 */

#include "args.hh"

#ifdef EXT3GREP_INIT_H
args::args(const int& argc, char const*const* argv, string commands, init_func func)\
		: argc(argc), argv(argv) {
#else
args::args(const int& argc, char const*const* argv, string commands)\
	        : argc(argc), argv(argv) {
#endif		
   
   int rBnd = 0, lBnd = 0;	
   int count = 1;
   size_t size = 1;

   cmd.command = 0;
   argc_com = 0;

#ifdef	EXT3GREP_INIT_H
   funk = func;
#endif   

   index = 0;
   common_flag = 0;
   command_index = COMMON;

   while(count<argc) {

         if(!lBnd)	   
            lBnd = matchCmdStr(commands, count, argc - count - 1);

         if(lBnd) {
	    if((count + 1) < argc) {	 
               rBnd = matchCmdStr(commands, count + 1, argc - count - 2);
	       if(rBnd)
	          rBnd--;
	    }   
	    else 
	       rBnd = argc - 1;	    
         }	      

         if(lBnd && rBnd) {
           		             
	    cmd.lBnd = lBnd;
	    cmd.argc = rBnd - lBnd + 1;
	       
	    lBnd = 0;
	    cmdContainer.push_back(cmd);
	    cmd.command = 0;
         }
      count++;
   }
  
   if(!cmdContainer.empty()) {

      vector<argHistory> cmds = cmdContainer;
      vector<argHistory>::iterator iter = cmds.begin();

      sort(iter, cmds.end());

      if(iter->lBnd > 1) 
	 argc_com = iter->lBnd;     
      else
	 argc_com = 0;     
   }
   else 
      if(argc) 
         argc_com = argc;

}

args::~args() {

   if(!cmdContainer.empty())
      cmdContainer.clear();

   //There must be some other nice way of doing this
   while(pop());
}	

int args::matchCmdStr(string const& commands, int argIdx, int argc) {

   size_t i_pos = 0, o_pos = 0, size;
   string i_str, o_str;

   int ret = 0, cmdI = 1;
   
   while((size = (o_str=cmdStr(o_pos, commands)).size())) {
      o_pos+=(size + SIZE_OF_COMMAND_DELIMITER);
      while((size = (i_str=cmdStr(i_pos, o_str)).size())) {
	 i_pos+=(size + SIZE_OF_SAME_COMMAND_DELIMITER);
	 if(!i_str.compare(argv[argIdx])) {
	    if(!cmd.command)	 
	       cmd.command = cmdI;	 
            ret = argIdx;
	    break;
	 }	 
      }

      if(ret) 
	 break;

      i_pos = 0;
      cmdI++;
   }

   return ret;
}	

string args::cmdStr(size_t b_pos, const string& commands) {

   size_t e_pos;
   string ret;

   e_pos = commands.find(COMMAND_DELIMITER, 0);
   if(e_pos == string::npos)
      e_pos = commands.find(SAME_COMMAND_DELIMITER, b_pos);
   else
      e_pos = commands.find(COMMAND_DELIMITER, b_pos);

   if(e_pos != string::npos) 
      ret = commands.substr(b_pos, e_pos - b_pos);  
   else if(b_pos < commands.size())
      ret = commands.substr(b_pos, commands.size() - b_pos);
   else
      ret = "";	   
       
   return ret;	
}

#ifdef EXT3GREP_INIT_H
int args::init(void) {

   vector<argHistory>::iterator iter;

   for(iter=cmdContainer.begin(); iter<cmdContainer.end(); iter++)
      funk(iter->argc, (argv + iter->lBnd), \
		      iter->command, argc_com, argv);
//      ::init(iter->argc, (argv + iter->lBnd),\
		      iter->command, argc_com, argv);
      
}
#endif

//
//Lots of container specific detail goes here
//

//Post increment operator
bool args::operator++(int) {

   bool ret = 0;
    
   // At index 0 the name of the command is
   // The behavior here is as same as the behavior of argc and argv 
   // in the main function
   // So index begins at origin 0 since at origin 0 the name of
   // the command is so it is incremented first
   // The side effect 
   // After finding the command, you'll increment to get to the
   // first command argument

   if(index < com_argc - 1) {

      index++;
      ret = 1;
   }	   

   return ret;
}

bool args::operator--(void) {

   bool ret = false;

   if ( index > 0 ) {
    
      index = index - 1;
      ret = true;
   }

   return ret;
}

//Pre increment operator
bool args::operator++(void) {

   bool ret = 0;

   if(index < com_argc - 1) {

      index++;
      ret = 1;
   }	   

   return ret;
}

//Sybscript operator
bool args::operator[](int command) {
	
   bool ret = 0;  

   // In either cases index is initialized at the origin 0
   // The first argument to the selected command is at the 
   // origin 1. Side effect, apply the increment operator to the
   // iterator before extarcting the first argument

   if(argc_com && command == COMMON) {
      
      if(common_flag == 0) {	   
       	   
         command_index = COMMON;	
         index = 0;
         com_argc = argc_com;

         common_flag = 1;
         ret = 1;
      }
      else {

      	 common_flag = 0;
	 ret = 0;
      }	 
   }	   
   else if(!cmdContainer.empty()) {
      
      //The find() needs it	   
      args::argHistory obj;
      obj.command = command;

      vector<args::argHistory>::iterator iter_begin;

      if((**it) && it->command==command)  
         iter_begin = it + 1;
      else
	 iter_begin = cmdContainer.begin();
      	      
      iter_begin = find(iter_begin, cmdContainer.end(), obj);
      if(iter_begin->command == command) {
         command_index = command;
         index = 0;
	 it = iter_begin;
	 com_argc = it->argc;
         ret = 1;
      }
   }

   return ret; 	
}

string args::operator*(void) {
 
   int i; 

   command_index == COMMON ? i = index : i = it->lBnd + index; 

   return string(argv[i]);
}

args::size_type args::size(void) {
   
   args::size_type size_size = 0;

   vector<argHistory>::iterator lit;
   lit = cmdContainer.begin();
   for(;lit<cmdContainer.end();) {

      size_size+=lit->argc;
      lit++;
   }

   if(argc_com > 1) 	   
      size_size+=argc_com - 1;
      
   return size_size;	
}	

bool args::push(void) {

   stacked_arg obj;
   obj.command_index = command_index;
   obj.index = index;
   obj.it = it;
   obj.com_argc = com_argc;

   stk_obj.push(obj);

   return 1;
}

bool args::pop(void) {
 
   bool ret = 0; 	

   stacked_arg obj;
   
   if(stk_obj.size()) {
      obj = stk_obj.top();
      command_index = obj.command_index;
      index = obj.index;
      it = obj.it;
      com_argc = obj.com_argc;
      stk_obj.pop(); 
      ret = 1;
   }   

   return ret;
}

bool args::discard(void) {

   bool ret = 0;

   if (stk_obj.size()) {

      stk_obj.pop();

      ret = 1;
   }

   return ret;
}
