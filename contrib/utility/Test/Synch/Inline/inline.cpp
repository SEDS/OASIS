// file      : Test/Synch/Inline/inline.cpp
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2002-2003 Boris Kolpackov
// license   : http://kolpackov.net/license.html

//
// This is a link-time test to detect any problems with inline functions
// (notably missing inline specifier).
//

/* FUZZ: disable check_for_improper_main_declaration */

#include "Utility/Synch/Policy/Null.hpp"

int
main ()
{
}

//$Id: inline.cpp 80826 2008-03-04 14:51:23Z wotte $
