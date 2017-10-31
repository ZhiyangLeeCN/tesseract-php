cmake_minimum_required(VERSION 2.8.12)

# Use solution folders.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake Targets")

project(php_tesseract C CXX)

# Output directory settings
set(output_dir ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${output_dir})

if (MSVC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /MP")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

#set(CPPAN_BUILD_SHARED_LIBS ON)
add_subdirectory(.cppan)

file(GLOB PHP_TESSERACT_HDR
    src/*.h
)

file(GLOB PHP_TESSERACT_SRC
    src/*.cpp
)

include_directories(src/)

if (WIN32)

    if (NOT DEFINED PHP_SRC_DIR)
        message(FATAL_ERROR "ERROR:PHP_SRC_DIR undefined.")
    endif()

    if (NOT DEFINED PHP_LIB_DIR)
        message(FATAL_ERROR "ERROR:PHP_LIB_DIR undefined.")
    endif()

    if (NOT DEFINED PHP_TARGET_LIB_NAME)
        message(FATAL_ERROR "ERROR:PHP_TARGET_LIB_NAME undefined.")
    endif()

    add_definitions(-DZEND_WIN32 -DPHP_WIN32 -DZEND_DEBUG -DCOMPILE_DL_TESSERACT_PHP -DZEND_WIN32_KEEP_INLINE)

    link_directories(${PHP_LIB_DIR})
    include_directories(${PHP_SRC_DIR} ${PHP_SRC_DIR}/Zend ${PHP_SRC_DIR}/main ${PHP_SRC_DIR}/TSRM)

    add_library(php_tesseract SHARED ${PHP_TESSERACT_SRC} ${PHP_TESSERACT_HDR})

    target_link_libraries(php_tesseract
        ${PHP_TARGET_LIB_NAME}
        pvt.cppan.demo.google.tesseract.libtesseract
        pvt.cppan.demo.danbloomberg.leptonica
    )

else()

endif()