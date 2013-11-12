/**
 * Simple test application which loads the libraries specified by commandline
 * Example:
 * libloader /usr/include/libfoo.so ./libbar.so
 */

#include <iostream>
#include <dlfcn.h>

int main (int argc, char * argv [])
{
  for (int i = 1; i < argc ; ++i)
  {
    std::cout << "Loading library: " << argv[i] << std::endl;
    void * handle = 0;
    handle = dlopen (argv[i], RTLD_NOW);
    if (handle == 0)
      std::cout << "Failed to load library: " << argv[i] << std::endl;
  }

  return 0; 
}

