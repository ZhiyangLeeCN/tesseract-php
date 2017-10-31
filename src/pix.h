#ifndef PHP_TESS_PIX_H
#define PHP_TESS_PIX_H

#include <allheaders.h>

void pix_res_dtor(zend_resource *resource);
void pix_res_register(int module_number);
PIX* pix_res_fetch(zend_resource *resource);

PHP_FUNCTION(tessPixRead);
PHP_FUNCTION(tessPixDestroy);

#endif // !PHP_TESS_PIX_H
