[tesseract-php - for php extension](https://github.com/ZhiyangLeeCN/tesseract-php)
===

# About

tesseract-php is a php extension based on [tesseract-ocr](https://github.com/tesseract-ocr/tesseract).

More details about tesseract-ocr can be found on their github project homepage.

# Compilation guide for various platforms

## Requirement

* PHP7+

## Dependencies

According to your platform to choose the corresponding version

* [CMake](https://cmake.org/download/)
* [Cppan client](https://cppan.org/client/)
* A compiler for C and C++: GCC or Clang

## Linux

1. Get latest tesseract-php source code to local.

2. Run
    ```
    cd tesseract-php
    cppan
    mkdir build && cd build
    cmake .. -DPHP_CONFIG_DIR=php-config where the path
    make
    ```
3. Copy `libphp_tesseract.so` to php extensions directory and changed php.ini `extension=libphp_tesseract.so`.

4. Run `php -m` to check if tesseract-php is already installed

## Windows

You have to build php-src first, php-src build in win32 system reference `http://wiki.php.net/internals/windows/stepbystepbuild`

1. Get latest tesseract-php source code to local.

2. Run
    ```
    cd tesseract-php
    cppan
    mkdir build_x32 && cd build_x32
    cmake .. -DENABLE_DEBUG=ON 
    -DPHP_SRC_DIR=D:\Projet\php-7.1.10 
    -DPHP_LIB_DIR=D:\Projet\php-7.1.10\x32\Debug 
    -DPHP_TARGET_LIB_NAME=php7_debug
    ```
3. Open `php_tesseract.sln` in Visual Stuido

If your php-src build is not debug type, chang `-DENABLE_DEBUG=OFF` and `-DPHP_TARGET_LIB_NAME=php(depending on the lib file name generated after build php-src)`. if you php-src build is TS(Thread safe) type, you must add `-DPHP-TS=ON`.

## Building for x64 platform

The other steps are the same as building 32 bits, so here omitted.

1. Run
    ```
    cd tesseract-php
    cppan
    mkdir build_x64 && cd build_x64
    cmake .. -DENABLE_DEBUG=ON 
    -DPHP_SRC_DIR=D:\Projet\php-7.1.10 
    -DPHP_LIB_DIR=D:\Projet\php-7.1.10\x32\Debug 
    -DPHP_TARGET_LIB_NAME=php7_debug 
    -G "Visual Studio 15 2017 Win64"
    ```
2. Open `php_tesseract.sln` in Visual Stuido

If your php-src build is not debug type,chang `-DENABLE_DEBUG=OFF` and `-DPHP_TARGET_LIB_NAME=php(depending on the lib file name generated after build php-src)`. if you php-src build is TS(Thread safe) type,you must add `-DPHP-TS=ON`.
