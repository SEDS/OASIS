// $Id: follow_child_tool.cpp 2274 2013-09-11 18:39:11Z dfeiock $

#include "pin++/Callback.h"
#include "pin++/Tool.h"
#include "pin++/Pintool.h"

#include <iostream>

/**
 * @class pid_print
 *
 * Callback that prints the pid of the child process
 */
class pid_print : public OASIS::Pin::Callback0 <pid_print>
{
public:
  pid_print (void) { }

  bool handle_analyze_follow_child_process (CHILD_PROCESS child)
  {
    std::cout << "before child: "
      << OASIS::Pin::Tool::current ()->get_pid () << std::endl;
    return true;
  }
};

/**
 * @class follow_child_tool
 *
 * Pin tool that counts the number of instructions in a program.
 */
class follow_child_tool : public OASIS::Pin::Tool
{
public:
  void handle_init (int argc, char * argv [])
  {
    this->add_follow_child_process_function (&this->callback_);
  }

private:
  pid_print callback_;
};

//
// main
//
int main (int argc, char * argv [])
{
  OASIS::Pin::Pintool <follow_child_tool> (argc, argv).start_program ();
}
