#!/bin/env ruby
# boot.rb(an example application to demonstrate the use of lib/argsv/argsv.rb)
# Written by, Sohail Qayum Malik[sqm@hackers.pk]

# Set correct paths
argsv_Ruby_lib = File.expand_path(File.join(File.dirname(__FILE__), 'argsv-Ruby/lib'))
# Execute this statement if condition is meat(if argsv_Ruby_lib is part of LOAD_PATH
$LOAD_PATH.unshift(argsv_Ruby_lib) unless $LOAD_PATH.include?(argsv_Ruby_lib)
cextensions = File.expand_path(File.join(File.dirname(__FILE__), 'CExtensions'))
# Execute this statement if condition is meat(if cextensions is part of LOAD_PATH)
$LOAD_PATH.unshift(cextensions) unless $LOAD_PATH.include?(cextensions)

# A constant
COMMANDS="?,/?,h,-h,help,--help(Shows the help screen)#v,-v,version,--version(Shows the current version number)#t,-t,test,--test(To test)"

require 'argsv/argsv'
require 'argsv/wrapper'
require 'BPFCompiler/BPFCompiler'

# -----------
# Mandatetory
# -----------
argv_detail = ArgsV::argsv(COMMANDS)

# -------------------------------------------------------  
# Direct access without any abstractions(not recommended)
# -------------------------------------------------------
if ENV['DEBUG'] == 'true'
  puts "Number of common command line arguments = " + String(ArgsV::get_number_of_common_args(argv_detail))
  ArgsV::reset_argv_detail_indexes(argv_detail)
  arg = ArgsV::get_next_arg(argv_detail)
  while arg
    if arg[Config_Argsv::IS_SHORT_COMMAND]
       puts "Short Command, ARGV_COMMAND_OPTION = " + arg[Config_Argsv::ARGV_COMMAND_OPTION] + " INDEX_INTO_ARGV_INDEX = " + String(arg[Config_Argsv::INDEX_INTO_ARGV_INDEX])+ " ARGV_COMMAND_OPTION_INDEX = " + String(arg[Config_Argsv::ARGV_COMMAND_OPTION_INDEX]) + " COMMAND_OPTIONS_INDEX = " + String(arg[Config_Argsv::COMMAND_OPTIONS_INDEX]) + " INDEX_INTO_COMMAND_OPTIONS_INDEX = " + String(arg[Config_Argsv::INDEX_INTO_COMMAND_OPTIONS_INDEX]) +" ARGV_COMMAND_OPTION_ARGC = " + String(arg[Config_Argsv::ARGV_COMMAND_OPTION_ARGC]) + " HELP_TEXT_INDEX = " + arg[Config_Argsv::HELP_TEXT_INDEX]
    else
       puts "Long Command, ARGV_COMMAND_OPTION = " + arg[Config_Argsv::ARGV_COMMAND_OPTION] + " INDEX_INTO_ARGV_INDEX = " + String(arg[Config_Argsv::INDEX_INTO_ARGV_INDEX]) + " COMMAND_OPTIONS_INDEX = " + String(arg[Config_Argsv::COMMAND_OPTIONS_INDEX]) + " INDEX_INTO_COMMAND_OPTIONS_INDEX = " + String(arg[Config_Argsv::INDEX_INTO_COMMAND_OPTIONS_INDEX]) + " ARGV_COMMAND_OPTION_ARGC = " + String(arg[Config_Argsv::ARGV_COMMAND_OPTION_ARGC]) + " HELP_TEXT_INDEX = " + arg[Config_Argsv::HELP_TEXT_INDEX] 
    end
    arg = ArgsV::get_next_arg(argv_detail)
  end
# --------------------------------------------------------
# Indirect access, using abstractions. Highely recommended
# --------------------------------------------------------
else # DEBUG != true
  wrapped_args = ArgsV::Wrapper.new(argv_detail)
  common_args = wrapped_args.get_common_args()

  i = 0
  while i < common_args.size
    puts common_args[i]
    i = i + 1
  end  

  if ( (arg = wrapped_args.get_arg("?")) )
    puts "Help found, and number of instances of help are = " + String(arg.size)
  else
    puts "Help not found"
  end

  if ( ( arg = wrapped_args.get_arg("test")) )
    puts "Test found, and number of instances are = " + String(arg.size)
    i = 0
    while i < arg.size
      if wrapped_args.arg_is_short(arg[i])
        puts "It is a short command"
      end
      i = i + 1
    end
  else 
    puts "Test not found" 
  end

end

bpfcompiler = BPFCompiler.new()
args = Array.new
args[0] = "Sohail"
args[1] = "Qayum"
args[2] = "Malik"
bpfcompiler.add("Sohail", "Qayum", "Malik", "Sohail Qayum Malik")

