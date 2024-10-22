cmake_minimum_required(VERSION 2.8.12)

# Use solution folders.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake Targets")

project(php_tesseract C CXX)
set(CMAKE_BUILD_TYPE Debug)  

# Output directory settings
set(output_dir ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${output_dir})

#set compiler flags
if (MSVC)
	add_definitions(-D__SSE4_1__)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /arch:AVX")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -mavx -msse4.1")
endif()
set(CPPAN_USE_CACHE 0)

#thread safe else not thread safe
option(PHP_TS "enable zend TS" OFF)
if (PHP_TS)
	add_definitions(-DZTS)
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

	#debug on or off
	option(ENABLE_DEBUG "enable debug" OFF)
	if(ENABLE_DEBUG)
		message("debug:on")
		add_definitions(-DZEND_DEBUG=1 -DTESS_DEBUG)
	else()
		message("debug:off")
		add_definitions(-DZEND_DEBUG=0)
	endif()

    if (NOT DEFINED PHP_SRC_DIR)
        message(FATAL_ERROR "ERROR:PHP_SRC_DIR undefined.")
    endif()

    if (NOT DEFINED PHP_LIB_DIR)
        message(FATAL_ERROR "ERROR:PHP_LIB_DIR undefined.")
    endif()

    if (NOT DEFINED PHP_TARGET_LIB_NAME)
        message(FATAL_ERROR "ERROR:PHP_TARGET_LIB_NAME undefined.")
    endif()

    add_definitions(-DZEND_WIN32 -DPHP_WIN32 -DZEND_WIN32_KEEP_INLINE)

    link_directories(${PHP_LIB_DIR})
    include_directories(${PHP_SRC_DIR} ${PHP_SRC_DIR}/Zend ${PHP_SRC_DIR}/main ${PHP_SRC_DIR}/TSRM)

    add_library(php_tesseract SHARED ${PHP_TESSERACT_SRC} ${PHP_TESSERACT_HDR})

    target_link_libraries(php_tesseract
        ${PHP_TARGET_LIB_NAME}
        pvt.cppan.demo.google.tesseract.libtesseract
        pvt.cppan.demo.danbloomberg.leptonica
    )

else()

	if (DEFINED PHP_CONFIG_DIR)
	  set(PHP_CONFIG_DIR "${PHP_CONFIG_DIR}/")
	else()
	  set(PHP_CONFIG_DIR "")
	endif()

	execute_process(COMMAND ${PHP_CONFIG_DIR}php-config --include-dir
        OUTPUT_VARIABLE PHP_INCLUDE_DIR
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

	execute_process(COMMAND ${PHP_CONFIG_DIR}php-config --libs
        OUTPUT_VARIABLE PHP_LIBS
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
	execute_process(COMMAND ${PHP_CONFIG_DIR}php-config --ldflags
        OUTPUT_VARIABLE ${PHP_LDFLAGS}
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

	message("PHP_INCLUDE_DIR: ${PHP_INCLUDE_DIR}")

	link_directories(${PHP_LDFLAGS})
	include_directories(BEFORE ${PHP_INCLUDE_DIR} ${PHP_INCLUDE_DIR}/Zend ${PHP_INCLUDE_DIR}/main ${PHP_INCLUDE_DIR}/TSRM)

	if (APPLE)
		SET(CMAKE_SHARED_LINKER_FLAGS  "${CMAKE_SHARED_LINKER_FLAGS} -undefined dynamic_lookup")
		message(${CMAKE_SHARED_LINKER_FLAGS})
	endif ()

	add_library(php_tesseract SHARED ${PHP_TESSERACT_SRC} ${PHP_TESSERACT_HDR})

    target_link_libraries(php_tesseract
        pvt.cppan.demo.google.tesseract.libtesseract
        pvt.cppan.demo.danbloomberg.leptonica
    )

endif()