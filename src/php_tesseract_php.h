/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2017 The PHP Group                                |
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

#ifndef PHP_TESSERACT_PHP_H
#define PHP_TESSERACT_PHP_H

extern zend_module_entry tesseract_php_module_entry;
#define phpext_tesseract_php_ptr &tesseract_php_module_entry

#define PHP_TESSERACT_PHP_VERSION "0.1.0"

#ifdef PHP_WIN32
#	define PHP_TESSERACT_PHP_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_TESSERACT_PHP_API __attribute__ ((visibility("default")))
#else
#	define PHP_TESSERACT_PHP_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

ZEND_BEGIN_MODULE_GLOBALS(tesseract_php)
	zend_bool    use_namespace;
ZEND_END_MODULE_GLOBALS(tesseract_php)

extern ZEND_DECLARE_MODULE_GLOBALS(tesseract_php);

#ifdef ZTS
#define TESSERACT_PHP_G(v) TSRMG(tesseract_php_globals_id, zend_tesseract_php_globals *, v)
#else
#define TESSERACT_PHP_G(v) (tesseract_php_globals.v)
#endif

#define TESS_STARTUP_FUNCTION(module)   	ZEND_MINIT_FUNCTION(tess_##module)
#define TESS_RINIT_FUNCTION(module)		ZEND_RINIT_FUNCTION(tess_##module)
#define TESS_STARTUP(module)	 		  	ZEND_MODULE_STARTUP_N(tess_##module)(INIT_FUNC_ARGS_PASSTHRU)
#define TESS_SHUTDOWN_FUNCTION(module)  	ZEND_MSHUTDOWN_FUNCTION(tess_##module)
#define TESS_SHUTDOWN(module)	 	    ZEND_MODULE_SHUTDOWN_N(tess_##module)(INIT_FUNC_ARGS_PASSTHRU)

#ifdef TESS_DEBUG
#undef TESS_DEBUG
#define TESS_DEBUG(m) fprintf(stderr, "%s\n", m);
#else
#define TESS_DEBUG(m) 
#endif

#define TESS_INIT_CLASS_ENTRY(ce, name, name_ns, methods) \
    if (TESSERACT_PHP_G(use_namespace)) { \
        INIT_CLASS_ENTRY(ce, name_ns, methods); \
    } else { \
        INIT_CLASS_ENTRY(ce, name, methods); \
    }

#define TESS_CLASS_ALIAS(name, name_ns) \
    if (TESSERACT_PHP_G(use_namespace)) { \
        zend_register_class_alias(#name, name##_class_entry_ptr);\
    } else { \
        zend_register_class_alias(name_ns, name##_class_entry_ptr);\
    }

#endif	/* PHP_TESSERACT_PHP_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
