dnl $Id$
dnl config.m4 for extension otama

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(otama, for otama support,
dnl Make sure that the comment is aligned:
dnl [  --with-otama             Include otama support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(otama, whether to enable otama support,
Make sure that the comment is aligned:
[  --enable-otama           Enable otama support])

if test "$PHP_OTAMA" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-otama -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/otama.h"  # you most likely want to change this
  dnl if test -r $PHP_OTAMA/$SEARCH_FOR; then # path given as parameter
  dnl   OTAMA_DIR=$PHP_OTAMA
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for otama files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       OTAMA_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$OTAMA_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the otama distribution])
  dnl fi

  dnl # --with-otama -> add include path
  dnl PHP_ADD_INCLUDE($OTAMA_DIR/include)

  dnl # --with-otama -> check for lib and symbol presence
  dnl LIBNAME=otama # you may want to change this
  dnl LIBSYMBOL=otama # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $OTAMA_DIR/lib, OTAMA_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_OTAMALIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong otama lib version or lib not found])
  dnl ],[
  dnl   -L$OTAMA_DIR/lib -lm
  dnl ])
  dnl
  dnl PHP_SUBST(OTAMA_SHARED_LIBADD)

  PHP_NEW_EXTENSION(otama, otama.c, $ext_shared)
  PHP_ADD_LIBRARY(otama, , OTAMA_SHARED_LIBADD)
  PHP_SUBST(OTAMA_SHARED_LIBADD)
fi
