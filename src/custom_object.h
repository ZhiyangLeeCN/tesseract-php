#ifndef PHP_TESS_CUSTOM_OBJECT_H
#define PHP_TESS_CUSTOM_OBJECT_H

#include "php_tesseract_php.h"

typedef struct _custom_object
{
	void		*custom_data;
	zend_object	std;
} custom_object;

static inline custom_object * php_custom_object_fetch_object(zend_object *obj) {
	return (custom_object *)((char *)obj - XtOffsetOf(custom_object, std));
}

#define Z_CUSTOM_OBJ_P(zv) php_custom_object_fetch_object(zv);

zend_object* custom_object_new(zend_class_entry *ce TSRMLS_DC);

#endif // !PHP_TESS_CUSTOM_OBJECT_H
