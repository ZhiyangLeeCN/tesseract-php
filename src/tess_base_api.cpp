#include "php.h"
#include "php_tesseract_php.h"
#include <allheaders.h>
#include "pix.h"
#include "custom_object.h"

#include <baseapi.h>

zend_class_entry *tess_base_api_ce;

ZEND_BEGIN_ARG_INFO_EX(arginfo_tess_base_api_construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tess_base_api_init, 0, 0, 2)
	ZEND_ARG_TYPE_INFO(0, "datapath", IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, "language", IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, "oem", IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tess_base_api_setpagesegmode, 0, 0, 1)
	ZEND_ARG_TYPE_INFO(0, "mode", IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tess_base_api_setvariable, 0, 0, 2)
	ZEND_ARG_TYPE_INFO(0, "name", IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, "value", IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tess_base_api_setimage, 0, 0, 1)
	ZEND_ARG_TYPE_INFO(0, "pix", IS_RESOURCE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tess_base_api_getutf8text, 0, 0, 0)
ZEND_END_ARG_INFO()

/* {{{ public Tesseract\TesseractBaseApi::__construct(void)*/
PHP_METHOD(tess_base_api, __construct)
{
	custom_object *self = Z_CUSTOM_OBJ_P(Z_OBJ_P(getThis()));
	tesseract::TessBaseAPI *tess_base_api = new tesseract::TessBaseAPI;
	self->custom_data = tess_base_api;
};

/* {{{ public Tesseract\TesseractBaseApi::__destruct(void) */
PHP_METHOD(tess_base_api, __destruct)
{
	custom_object *self = Z_CUSTOM_OBJ_P(Z_OBJ_P(getThis()));
	tesseract::TessBaseAPI *tess_base_api = (tesseract::TessBaseAPI*)self->custom_data;
	tess_base_api->Clear();
	tess_base_api->End();
	delete tess_base_api;
}
/* }}} */

/* {{{ public Tesseract\TesseractBaseApi::Init($datapath, $language, $oem = OCR_ENGINE_MODEL::OEM_DEFAULT)*/
PHP_METHOD(tess_base_api, Init)
{
	zend_string *datapath;
	zend_string *language;
	zend_long oem = tesseract::OcrEngineMode::OEM_DEFAULT;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "SS|l", &datapath, &language, &oem) == FAILURE) {
		return;
	}

	custom_object *self = Z_CUSTOM_OBJ_P(Z_OBJ_P(getThis()));
	tesseract::TessBaseAPI *tess_base_api = (tesseract::TessBaseAPI*)self->custom_data;
	int result = tess_base_api->Init(datapath->val, language->val, (tesseract::OcrEngineMode)oem);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ public Tesseract\TesseractBaseApi::SetPageSegMode($mode)*/
PHP_METHOD(tess_base_api, SetPageSegMode)
{
	zend_long mode;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "l", &mode) == FAILURE) {
		return;
	}

	custom_object *self = Z_CUSTOM_OBJ_P(Z_OBJ_P(getThis()));
	tesseract::TessBaseAPI *tess_base_api = (tesseract::TessBaseAPI*)self->custom_data;
	tess_base_api->SetPageSegMode((tesseract::PageSegMode)mode);
}
/* }}} */

/* {{{ public Tesseract\TesseractBaseApi::SetVariable($name, $value)*/
PHP_METHOD(tess_base_api, SetVariable)
{
	zend_string *name;
	zend_string *value;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "SS", &name, &value) == FAILURE) {
		return;
	}

	custom_object *self = Z_CUSTOM_OBJ_P(Z_OBJ_P(getThis()));
	tesseract::TessBaseAPI *tess_base_api = (tesseract::TessBaseAPI*)self->custom_data;
	bool result = tess_base_api->SetVariable(name->val, value->val);
	RETURN_BOOL(result);
}
/* }}} */

/* {{{ public Tesseract\TesseractBaseApi::SetImage($pix)*/
PHP_METHOD(tess_base_api, SetImage)
{
	zval *val;
	zend_resource *res;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "r", &val) == FAILURE) {
		return;
	}

	res = Z_RES_P(val);
	PIX *pix = pix_res_fetch(res);
	custom_object *self = Z_CUSTOM_OBJ_P(Z_OBJ_P(getThis()));
	tesseract::TessBaseAPI *tess_base_api = (tesseract::TessBaseAPI*)self->custom_data;
	tess_base_api->SetImage(pix);
	tess_base_api->Recognize(0);
}
/* }}} */

/* {{{ public Tesseract\TesseractBaseApi::GetUTF8Text */
PHP_METHOD(tess_base_api, GetUTF8Text)
{
	custom_object *self = Z_CUSTOM_OBJ_P(Z_OBJ_P(getThis()));
	tesseract::TessBaseAPI *tess_base_api = (tesseract::TessBaseAPI*)self->custom_data;

	char *text = tess_base_api->GetUTF8Text();
	zend_string *ret = zend_string_init(text, sizeof(text) -1, 0);
	delete[] text;

	RETURN_STR(ret);
}
/* }}} */

static const zend_function_entry tess_base_api_methods[] =
{
	PHP_ME(tess_base_api, __construct,	     arginfo_tess_base_api_construct,		ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(tess_base_api, __destruct,		 NULL,									ZEND_ACC_PUBLIC | ZEND_ACC_DTOR)
	PHP_ME(tess_base_api, Init,			     arginfo_tess_base_api_init,			ZEND_ACC_PUBLIC)
	PHP_ME(tess_base_api, SetPageSegMode,    arginfo_tess_base_api_setpagesegmode,	ZEND_ACC_PUBLIC)
	PHP_ME(tess_base_api, SetVariable,       arginfo_tess_base_api_setvariable,		ZEND_ACC_PUBLIC)
	PHP_ME(tess_base_api, SetImage,          arginfo_tess_base_api_setimage,		ZEND_ACC_PUBLIC)
	PHP_ME(tess_base_api, GetUTF8Text,       arginfo_tess_base_api_getutf8text,		ZEND_ACC_PUBLIC)
	PHP_FE_END
};

TESS_STARTUP_FUNCTION(tess_base_api)
{
	zend_class_entry ce;
	TESS_INIT_CLASS_ENTRY(ce, "Tess_base_api", "Tesseract\\TesseractBaseApi", tess_base_api_methods);

	tess_base_api_ce = zend_register_internal_class_ex(&ce, NULL);
	tess_base_api_ce->ce_flags |= ZEND_ACC_FINAL;
	tess_base_api_ce->create_object = custom_object_new;

	return SUCCESS;
}