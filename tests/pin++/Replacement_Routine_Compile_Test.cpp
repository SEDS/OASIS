// $Id$

#include "pin++/Replacement_Routine.h"
#include "pin++/Pintool.h"
#include <iostream>

/////////////////////////////////////////////////////////////////////////////////////////////
//

void function0 (void) { }
void function1 (int) { }
void function2 (int, int) { }
void function3 (int, int, int) { }
void function4 (int, int, int, int) { }
void function5 (int, int, int, int, int) { }
void function6 (int, int, int, int, int, int) { }

class function0_obj : public OASIS::Pin::Replacement_Routine <function0_obj, void (void)> { };
class function1_obj : public OASIS::Pin::Replacement_Routine <function1_obj, void (int)> { };
class function2_obj : public OASIS::Pin::Replacement_Routine <function2_obj, void (int, int)> { };
class function3_obj : public OASIS::Pin::Replacement_Routine <function3_obj, void (int, int, int)> { };
class function4_obj : public OASIS::Pin::Replacement_Routine <function4_obj, void (int, int, int, int)> { };
class function5_obj : public OASIS::Pin::Replacement_Routine <function5_obj, void (int, int, int, int, int)> { };
class function6_obj : public OASIS::Pin::Replacement_Routine <function6_obj, void (int, int, int, int, int, int)> { };

/////////////////////////////////////////////////////////////////////////////////////////////
//

void malloc1_func (int n)
{
  std::cerr << "n = " << n << std::endl;
}

void malloc2_func (int m)
{
  std::cerr << "m = " << m << std::endl;
}

class malloc1 : public OASIS::Pin::Replacement_Routine <malloc1, void (int)>
{
public:
  static return_type execute (param1_type n)
  {
    return call_original (n);
  }
};

class malloc2 : public OASIS::Pin::Replacement_Routine <malloc2, void (int)>
{
public:
  static return_type execute (param1_type n)
  {
    return call_original (n);
  }
};

template <typename T>
void CHECK_EQUALS (T expected, T actual, const char * msg)
{
  std::cerr << msg << " : " << (expected == actual ? "PASSED" : "FAILED") << std::endl;
}

template <typename T>
void CHECK_NOT_EQUALS (T expected, T actual, const char * msg)
{
  std::cerr << msg << " : " << (expected != actual ? "PASSED" : "FAILED") << std::endl;
}

int main (int argc, char * argv [])
{
  malloc1::original_funcptr (&malloc1_func);
  CHECK_EQUALS (&malloc1_func, malloc1::original_funcptr (), "checking setter/getter method");

  malloc2::original_funcptr (&malloc2_func);
  CHECK_NOT_EQUALS (malloc1::original_funcptr (), malloc2::original_funcptr (), "checking different types with same signatures");

  return 0;
}
