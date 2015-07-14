# README, last updated on :- 31st of May, 2014, in Islamabad

Argsv for Ruby.
------------------
An effort to process the command line arguments with ease and style

Example application.
-----------------------
- [Example application code] -
- [Example application code] -
- [Example application code] -




Explaining oddities in processing CLI arguments...

Case 1 of n
------------
Outcome of using same single letter command string option twice; once precedded by an hyphen(Config_Argsv::SHORT_COMMAND_SYMBOL) and once without an hyphen(Config_Argsv::SHORT_COMMAND_SYMBOL)

# Example.rb

require "argsv/argsv"
COMMANDS="h,-h(It shows an help screen)"
args=ArgsV::argsv(COMMANDS)

C:\ruby>DEBUG='true' ruby Example.rb -hh 

The output will be...

(It shows an help screen) Index into ARGV = 0 User provided command string = -hh Index into the user provided command string = 1 Command to which previous index belongs to -hh(Is short command)
(It shows an help screen) Index into ARGV = 0 User provided command string = -hh Index into the user provided command string = 1 Command to which previous index belongs to -hh(Is short command)
(It shows an help screen) Index into ARGV = 0 User provided command string = -hh Index into the user provided command string = 2 Command to which previous index belongs to -hh(Is short command)
(It shows an help screen) Index into ARGV = 0 User provided command string = -hh Index into the user provided command string = 2 Command to which previous index belongs to -hh(Is short command)




