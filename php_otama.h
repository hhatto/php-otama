/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2013 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef PHP_OTAMA_H
#define PHP_OTAMA_H

#include "otama.h"

extern zend_module_entry otama_module_entry;
#define phpext_otama_ptr &otama_module_entry

#ifdef PHP_WIN32
#   define PHP_OTAMA_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#   define PHP_OTAMA_API __attribute__ ((visibility("default")))
#else
#   define PHP_OTAMA_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(otama);
PHP_MSHUTDOWN_FUNCTION(otama);
PHP_RINIT_FUNCTION(otama);
PHP_RSHUTDOWN_FUNCTION(otama);
PHP_MINFO_FUNCTION(otama);

PHPAPI zend_class_entry *otama_ce;

PHP_METHOD(otama, open);
PHP_METHOD(otama, similarity);

ZEND_BEGIN_MODULE_GLOBALS(otama)
    otama_t  *_otama;
ZEND_END_MODULE_GLOBALS(otama)

/* In every utility function you add that needs to use variables 
   in php_otama_globals, call TSRMLS_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as OTAMA_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define OTAMA_G(v) TSRMG(otama_globals_id, zend_otama_globals *, v)
#else
#define OTAMA_G(v) (otama_globals.v)
#endif

#endif  /* PHP_OTAMA_H */
