#include "php.h"
#include "custom_object.h"

zend_object_handlers custom_object_handlers = std_object_handlers;

void custom_object_free(zend_object *object)
{
	custom_object *custom_obj = Z_CUSTOM_OBJ_P(object);
	zend_object_std_dtor(object);
	efree(custom_obj);
}

zend_object* custom_object_new(zend_class_entry *ce TSRMLS_DC) {

	custom_object *intern = (custom_object*)emalloc(
		sizeof(custom_object) + zend_object_properties_size(ce)
	);
	intern->custom_data = NULL;

	zend_object_std_init(&intern->std, ce);
	object_properties_init(&intern->std, ce);

	custom_object_handlers.offset = XtOffsetOf(custom_object, std);
	custom_object_handlers.free_obj = custom_object_free;

	intern->std.handlers = &custom_object_handlers;

	return &intern->std;

}