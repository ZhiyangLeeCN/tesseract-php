#include "php.h"
#include "php_tesseract_php.h"
#include "tess_orc_engine_mode.h"
#include <baseapi.h>

using tesseract::OcrEngineMode;

zend_class_entry *tess_ocr_engine_mode_ce;

TESS_STARTUP_FUNCTION(tess_ocr_engine_mode)
{
	zend_class_entry ce;
	TESS_INIT_CLASS_ENTRY(ce, "Tess_ocr_engine_mode", "Tesseract\\OcrEngineMode", NULL);

	tess_ocr_engine_mode_ce = zend_register_internal_class_ex(&ce, NULL);
	tess_ocr_engine_mode_ce->ce_flags |= ZEND_ACC_FINAL;

	zend_declare_class_constant_long(tess_ocr_engine_mode_ce,
		"OEM_TESSERACT_ONLY", sizeof("OEM_TESSERACT_ONLY") - 1, OcrEngineMode::OEM_TESSERACT_ONLY);
	zend_declare_class_constant_long(tess_ocr_engine_mode_ce,
		"OEM_LSTM_ONLY", sizeof("OEM_LSTM_ONLY") - 1, OcrEngineMode::OEM_LSTM_ONLY);
	zend_declare_class_constant_long(tess_ocr_engine_mode_ce,
		"OEM_TESSERACT_LSTM_COMBINED", sizeof("OEM_TESSERACT_LSTM_COMBINED") - 1, OcrEngineMode::OEM_TESSERACT_LSTM_COMBINED);
	zend_declare_class_constant_long(tess_ocr_engine_mode_ce,
		"OEM_DEFAULT", sizeof("OEM_DEFAULT") - 1, OcrEngineMode::OEM_DEFAULT);
	zend_declare_class_constant_long(tess_ocr_engine_mode_ce,
		"OEM_CUBE_ONLY", sizeof("OEM_CUBE_ONLY") - 1, OcrEngineMode::OEM_CUBE_ONLY);
	zend_declare_class_constant_long(tess_ocr_engine_mode_ce,
		"OEM_TESSERACT_CUBE_COMBINED", sizeof("OEM_TESSERACT_CUBE_COMBINED") - 1, OcrEngineMode::OEM_TESSERACT_CUBE_COMBINED);

	return SUCCESS;
}