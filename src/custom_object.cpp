#include "php.h"
#include "custom_object.h"

zend_object_handlers custom_object_handlers = std_object_handlers;

zend_object* custom_object_new(zend_class_entry *ce TSRMLS_DC) {

	custom_object *intern = (custom_object*)emalloc(
		sizeof(custom_object) + zend_object_properties_size(ce)
	);

	zend_object_std_init(&intern->std, ce);
	object_properties_init(&intern->std, ce);

	custom_object_handlers.offset = XtOffsetOf(custom_object, std);

	intern->std.handlers = &custom_object_handlers;

	return &intern->std;

}