#include "php.h"
#include "php_tesseract_php.h"
#include "tess_page_seg_mode.h"
#include <baseapi.h>

using tesseract::PageSegMode;

zend_class_entry *tess_page_seg_model_ce;

TESS_STARTUP_FUNCTION(tess_page_seg_mode)
{
	zend_class_entry ce;
	TESS_INIT_CLASS_ENTRY(ce, "Tess_page_seg_mode", "Tesseract\\PageSegMode", NULL);
	tess_page_seg_model_ce = zend_register_internal_class_ex(&ce, NULL);
	tess_page_seg_model_ce->ce_flags |= ZEND_ACC_FINAL;

	zend_declare_class_constant_long(tess_page_seg_model_ce,
		ZEND_STRL("PSM_OSD_ONLY"), PageSegMode::PSM_OSD_ONLY);
	zend_declare_class_constant_long(tess_page_seg_model_ce,
		ZEND_STRL("PSM_AUTO_OSD"), PageSegMode::PSM_AUTO_OSD);
	zend_declare_class_constant_long(tess_page_seg_model_ce,
		ZEND_STRL("PSM_AUTO_ONLY"), PageSegMode::PSM_AUTO_ONLY);
	zend_declare_class_constant_long(tess_page_seg_model_ce,
		ZEND_STRL("PSM_AUTO"), PageSegMode::PSM_AUTO);
	zend_declare_class_constant_long(tess_page_seg_model_ce,
		ZEND_STRL("PSM_SINGLE_COLUMN"), PageSegMode::PSM_SINGLE_COLUMN);
	zend_declare_class_constant_long(tess_page_seg_model_ce,
		ZEND_STRL("PSM_SINGLE_BLOCK_VERT_TEXT"), PageSegMode::PSM_SINGLE_BLOCK_VERT_TEXT);
	zend_declare_class_constant_long(tess_page_seg_model_ce,
		ZEND_STRL("PSM_SINGLE_BLOCK"), PageSegMode::PSM_SINGLE_BLOCK);
	zend_declare_class_constant_long(tess_page_seg_model_ce,
		ZEND_STRL("PSM_SINGLE_LINE"), PageSegMode::PSM_SINGLE_LINE);
	zend_declare_class_constant_long(tess_page_seg_model_ce,
		ZEND_STRL("PSM_SINGLE_WORD"), PageSegMode::PSM_SINGLE_WORD);

	return SUCCESS;
}