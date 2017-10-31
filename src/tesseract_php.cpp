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

#include "php.h"
#include "php_ini.h"
#include "main/SAPI.h"
#include "Zend/zend_alloc.h"
#include "ext/standard/info.h"
#include "ext/standard/php_string.h"

#include "php_tesseract_php.h"
#include "tess_page_seg_mode.h"
#include "tess_orc_engine_mode.h"
#include "tess_base_api.h"
#include "pix.h"

#include <iostream>
#include <allheaders.h>
#include <baseapi.h>

ZEND_DECLARE_MODULE_GLOBALS(tesseract_php)

/* True global resources - no need for thread safety here */
static int le_tesseract_php;

/* {{{ PHP_INI
 */
PHP_INI_BEGIN()
	STD_PHP_INI_BOOLEAN("tesseract_php.use_namespace", "1", PHP_INI_SYSTEM, OnUpdateBool, use_namespace, zend_tesseract_php_globals, tesseract_php_globals)
PHP_INI_END()

/* }}} */

/** {{{ PHP_GINIT_FUNCTION
*/
PHP_GINIT_FUNCTION(tesseract_php)
{
	memset(tesseract_php_globals, 0, sizeof(*tesseract_php_globals));
}
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(tesseract_php)
{
	REGISTER_INI_ENTRIES();

	pix_res_register(module_number);

	TESS_STARTUP(tess_page_seg_mode);
	TESS_STARTUP(tess_ocr_engine_mode);
	TESS_STARTUP(tess_base_api);

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(tesseract_php)
{
	UNREGISTER_INI_ENTRIES();

	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(tesseract_php)
{
#if defined(COMPILE_DL_TESSERACT_PHP) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(tesseract_php)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(tesseract_php)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "tesseract_php support", "enabled");

	php_info_print_table_end();

	DISPLAY_INI_ENTRIES();
}
/* }}} */

/* {{{ tesseract_php_functions[]
 *
 * Every user visible function must have an entry in tesseract_php_functions[].
 */
const zend_function_entry tesseract_php_functions[] = {
	PHP_FE(tessPixRead, NULL)
	PHP_FE(tessPixDestroy, NULL)
	PHP_FE_END	/* Must be the last line in tesseract_php_functions[] */
};
/* }}} */

/* {{{ tesseract_php_module_entry
 */
zend_module_entry tesseract_php_module_entry = {
	STANDARD_MODULE_HEADER,
	"tesseract_php",
	tesseract_php_functions,
	PHP_MINIT(tesseract_php),
	PHP_MSHUTDOWN(tesseract_php),
	PHP_RINIT(tesseract_php),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(tesseract_php),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(tesseract_php),
	PHP_TESSERACT_PHP_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_TESSERACT_PHP
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(tesseract_php)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
