#include <iostream>
#include "php.h"
#include "php_tesseract_php.h"
#include "pix.h"

int pix_res_num;

void pix_res_dtor(zend_resource *resource)
{
	PIX *pix = (PIX*)resource->ptr;
	pixDestroy(&pix);
}

void pix_res_register(int module_number)
{
	pix_res_num = zend_register_list_destructors_ex(pix_res_dtor, NULL, "pixRes", module_number);
}

PIX* pix_res_fetch(zend_resource *resource)
{
	PIX *pix = (PIX*)zend_fetch_resource(resource, "pixRes", pix_res_num);
	return pix;
}

/* {{{ public tessPixRead($filename) */
PHP_FUNCTION(tessPixRead)
{
	zend_string *filename;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "S", &filename) == FAILURE) {
		return;
	}

	PIX* pix = pixRead(filename->val);
	if (!pix) {
		RETURN_FALSE;
	}

	zend_resource *resource = zend_register_resource(pix, pix_res_num);

	RETURN_RES(resource);
}
/* }}} */

/* {{{ public tessPixDestroy($pix) */
PHP_FUNCTION(tessPixDestroy)
{
	zval *val;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "r", &val) == FAILURE) {
		return;
	}

	zend_list_close(Z_RES_P(val));
}