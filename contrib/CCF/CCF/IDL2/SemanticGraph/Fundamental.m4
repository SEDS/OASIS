# file      : CCF/IDL2/SemanticGraph/Fundamental.m4
# author    : Boris Kolpackov <boris@dre.vanderbilt.edu>
# cvs-id    : $Id: Fundamental.m4 54723 2003-12-22 22:26:40Z boris $

define(`upcase', `translit(`$*', `a-z', `A-Z')')


define(`capitalize_word',
  `regexp(`$1', `^\(.\)\(.*\)', `upcase(`\1')`\2'')')


define(`capitalize',
  `patsubst(`$1', `\w+', `capitalize_word(`\&')')')

define(`make_class_name', `patsubst(capitalize(`$1'), ` ')')

define(`make_var_name', `patsubst(`$1', ` ', `_')')
