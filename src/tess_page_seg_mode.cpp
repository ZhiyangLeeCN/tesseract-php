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
		"PSM_OSD_ONLY", sizeof("PSM_OSD_ONLY") - 1, PageSegMode::PSM_OSD_ONLY);
	zend_declare_class_constant_long(tess_page_seg_model_ce,
		"PSM_AUTO_OSD", sizeof("PSM_AUTO_OSD") - 1, PageSegMode::PSM_AUTO_OSD);
	zend_declare_class_constant_long(tess_page_seg_model_ce,
		"PSM_AUTO_ONLY", sizeof("PSM_AUTO_ONLY") - 1, PageSegMode::PSM_AUTO_ONLY);
	zend_declare_class_constant_long(tess_page_seg_model_ce,
		"PSM_AUTO", sizeof("PSM_AUTO") - 1, PageSegMode::PSM_AUTO);
	zend_declare_class_constant_long(tess_page_seg_model_ce,
		"PSM_SINGLE_COLUMN", sizeof("PSM_SINGLE_COLUMN") - 1, PageSegMode::PSM_SINGLE_COLUMN);
	zend_declare_class_constant_long(tess_page_seg_model_ce,
		"PSM_SINGLE_BLOCK_VERT_TEXT", sizeof("PSM_SINGLE_BLOCK_VERT_TEXT") - 1, PageSegMode::PSM_SINGLE_BLOCK_VERT_TEXT);
	zend_declare_class_constant_long(tess_page_seg_model_ce,
		"PSM_SINGLE_BLOCK", sizeof("PSM_SINGLE_BLOCK") - 1, PageSegMode::PSM_SINGLE_BLOCK);
	zend_declare_class_constant_long(tess_page_seg_model_ce,
		"PSM_SINGLE_LINE", sizeof("PSM_SINGLE_LINE") - 1, PageSegMode::PSM_SINGLE_LINE);
	zend_declare_class_constant_long(tess_page_seg_model_ce,
		"PSM_SINGLE_WORD", sizeof("PSM_SINGLE_WORD") - 1, PageSegMode::PSM_SINGLE_WORD);

	return SUCCESS;
}