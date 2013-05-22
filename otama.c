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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_otama.h"

ZEND_DECLARE_MODULE_GLOBALS(otama)

/* True global resources - no need for thread safety here */
static int le_otama;

/* {{{ otama_functions[]
 *
 * Every user visible function must have an entry in otama_functions[].
 */
const zend_function_entry otama_functions[] = {
    PHP_ME(otama, open, NULL, 0)
    PHP_ME(otama, similarity, NULL, 0)
    PHP_FE_END  /* Must be the last line in otama_functions[] */
};
/* }}} */

/* {{{ otama_module_entry
 */
zend_module_entry otama_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    "otama",
    otama_functions,
    PHP_MINIT(otama),
    PHP_MSHUTDOWN(otama),
    PHP_RINIT(otama),       /* Replace with NULL if there's nothing to do at request start */
    PHP_RSHUTDOWN(otama),   /* Replace with NULL if there's nothing to do at request end */
    PHP_MINFO(otama),
#if ZEND_MODULE_API_NO >= 20010901
    "0.1", /* Replace with version number for your extension */
#endif
    STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_OTAMA
ZEND_GET_MODULE(otama)
#endif

/* {{{ PHP_INI
 */
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("otama._otama", "0", PHP_INI_ALL, OnUpdateLong, _otama, zend_otama_globals, otama_globals)
PHP_INI_END()
/* }}} */

/* {{{ php_otama_init_globals
 */
static void php_otama_init_globals(zend_otama_globals *otama_globals)
{
    otama_globals->_otama = NULL;
}
/* }}} */

ZEND_BEGIN_ARG_INFO_EX(arginfo_otama_open, 0, 0, 1)
    ZEND_ARG_INFO(0, config)
    ZEND_END_ARG_INFO()
PHP_METHOD(otama, open)
{
    otama_t *o;
    otama_status_t ret = OTAMA_STATUS_OK;
    char *config_string;
    int config_string_len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &config_string, &config_string_len) == FAILURE) {
        return;
    }

    ret = otama_open(&OTAMA_G(_otama), config_string);

    RETURN_TRUE;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_otama_similarity, 0, 0, 1)
    ZEND_ARG_INFO(0, filename1)
    ZEND_ARG_INFO(0, filename2)
    ZEND_END_ARG_INFO()
PHP_METHOD(otama, similarity)
{
    otama_t *o = OTAMA_G(_otama);
    otama_variant_pool_t *pool;
    otama_variant_t *var1, *var2;
    otama_status_t ret = OTAMA_STATUS_OK;
    char *filename1, *filename2;
    int strlen1, strlen2;
    float similarity = 0.0f;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
                              "ss", &filename1, &strlen1, &filename2, &strlen2) == FAILURE) {
        return;
    }

    pool = otama_variant_pool_alloc();
    var1 = otama_variant_new(pool);
    var2 = otama_variant_new(pool);

    otama_variant_set_string(var1, filename1);
    otama_variant_set_string(var2, filename2);

    //ret = otama_similarity(o, &similarity, var1, var2);
    ret = otama_similarity_file(o, &similarity, filename1, filename2);
    if (ret != OTAMA_STATUS_OK) {
        otama_variant_pool_free(&pool);
        //otamapy_raise(ret);
        return;
    }

    otama_variant_pool_free(&pool);

    RETURN_DOUBLE(similarity);
}

static zend_function_entry php_otama_methods[] = {
    {NULL, NULL, NULL}
};

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(otama)
{
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "Otama", otama_functions);
    otama_ce = zend_register_internal_class(&ce TSRMLS_CC);

    ZEND_INIT_MODULE_GLOBALS(otama, php_otama_init_globals, NULL);

    //REGISTER_INI_ENTRIES();

    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(otama)
{
    //UNREGISTER_INI_ENTRIES();
    return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(otama)
{
    return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(otama)
{
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(otama)
{
    php_info_print_table_start();
    php_info_print_table_header(2, "otama support", "enabled");
    php_info_print_table_end();
}
/* }}} */
