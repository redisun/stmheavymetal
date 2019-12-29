cmake_minimum_required(VERSION 3.16)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${CMAKE_SOURCE_DIR}/cmake/modules")

find_package(openocd)

project(stmbare LANGUAGES CXX ASM)

set(APP stmbare)
set(PATH_APP src)
set(GCC_TOOLCHAIN_PREFIX "arm-none-eabi-")

set(LINKER_DEFINITION_FILE ${CMAKE_CURRENT_SOURCE_DIR}/stm32.ld)

set(CMAKE_EXECUTABLE_SUFFIX .elf)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AR ${GCC_TOOLCHAIN_PREFIX}ar)
set(CMAKE_ASM_COMPILER ${GCC_TOOLCHAIN_PREFIX}g++)
set(CMAKE_CXX_COMPILER ${GCC_TOOLCHAIN_PREFIX}g++)

set(NM ${GCC_TOOLCHAIN_PREFIX}nm)
set(OBJDUMP ${GCC_TOOLCHAIN_PREFIX}objdump)
set(OBJCOPY ${GCC_TOOLCHAIN_PREFIX}objcopy)
set(READELF ${GCC_TOOLCHAIN_PREFIX}readelf)
set(SIZE ${GCC_TOOLCHAIN_PREFIX}size)
set(CPPFILT ${GCC_TOOLCHAIN_PREFIX}c++filt)

set(GCCFLAGS
    -g
    -Wall
    -Wextra
    -pedantic
    -Wmain
    -Wundef
    -Wsign-conversion
    -Wunused-parameter
    -Wuninitialized
    -Wmissing-declarations
    -Wshadow
    -Wunreachable-code
    -Wswitch-default
    -Wswitch-enum
    -Wcast-align
    -Wmissing-include-dirs
    -Winit-self
    -Wfloat-equal
    -Wdouble-promotion
    -gdwarf-2
    -fno-exceptions
    -ffunction-sections
    -fdata-sections
)

set(_CPPFLAGS ${GCCFLAGS}
    -x c++
    -fno-rtti
    -fstrict-enums
    -fno-use-cxa-atexit
    -fno-use-cxa-get-exception-ptr
    -fno-nonansi-builtins
    -fno-threadsafe-statics
    -fno-enforce-eh-specs
    -ftemplate-depth=32
    -Wzero-as-null-pointer-constant
    -finline-functions
    -finline-limit=32
    -mcpu=cortex-m3
    -mtune=cortex-m3
    -mthumb
    -mfloat-abi=soft
    -mno-unaligned-access
    -mno-long-calls
)

set(_AFLAGS ${GCCFLAGS}
    -x assembler
)

set(_LDFLAGS ${GCCFLAGS}
    -x none
    -nostdlib
    -nostartfiles
    -T ${LINKER_DEFINITION_FILE}
    -Wl,--gc-sections
    -Wl,-Map,${APP}.map
)

string(REPLACE ";" " " CPPFLAGS "${_CPPFLAGS}")
string(REPLACE ";" " " AFLAGS "${_AFLAGS}")
string(REPLACE ";" " " LDFLAGS "${_LDFLAGS}")

set(POSTBUILD_GEN_SYMBOL_LISTING ${READELF} --syms ${APP}${CMAKE_EXECUTABLE_SUFFIX} > ${APP}_readelf.txt)
set(POSTBUILD_GEN_HEX ${OBJCOPY} -O ihex ${APP}${CMAKE_EXECUTABLE_SUFFIX} ${APP}.hex)
set(POSTBUILD_GEN_BIN ${OBJCOPY} -S -O binary ${APP}${CMAKE_EXECUTABLE_SUFFIX} ${APP}.bin)

set(MAP_FILE ${CMAKE_BINARY_DIR}/${APP}.map)
set(SYMBOL_LISTING_FILE ${CMAKE_BINARY_DIR}/${APP}_readelf.txt)
set(HEX_FILE ${CMAKE_BINARY_DIR}/${APP}.hex)
set(BIN_FILE ${CMAKE_BINARY_DIR}/${APP}.bin)

set(CMAKE_CXX_FLAGS "${CPPFLAGS}" CACHE STRING "" FORCE)
set(CMAKE_ASM_FLAGS "${AFLAGS}" CACHE STRING "" FORCE)
set(CMAKE_EXE_LINKER_FLAGS "${LDFLAGS}" CACHE STRING "" FORCE)

set(app_src
    ${PATH_APP}/init_ctor
    ${PATH_APP}/init_ram
    ${PATH_APP}/reset_vector
    ${PATH_APP}/reset_handler
    ${PATH_APP}/syscalls
    ${PATH_APP}/main
)

add_executable(stmbare
    ${app_src}
)

set(PARSE_SYMBOL_OPTIONS --print-size)

add_custom_command(TARGET stmbare POST_BUILD
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    
    COMMENT "Generating post build artifacts"

    COMMAND ${OBJDUMP} -h -S ${APP}${CMAKE_EXECUTABLE_SUFFIX} > ${APP}.lss

    COMMAND ${NM} --numeric-sort ${PARSE_SYMBOL_OPTIONS} ${APP}${CMAKE_EXECUTABLE_SUFFIX} > ${APP}_nm.txt

    COMMAND ${NM} --numeric-sort ${PARSE_SYMBOL_OPTIONS} ${APP}${CMAKE_EXECUTABLE_SUFFIX} | ${CPPFILT} > ${APP}_cppfilt.txt

    COMMAND ${SIZE} -A -t ${APP}${CMAKE_EXECUTABLE_SUFFIX} > ${APP}_size.txt

    COMMAND ${POSTBUILD_GEN_SYMBOL_LISTING}

    COMMAND ${POSTBUILD_GEN_HEX}

    COMMAND ${POSTBUILD_GEN_BIN}
)

install(FILES

    ${CMAKE_BINARY_DIR}/${APP}${CMAKE_EXECUTABLE_SUFFIX}
    ${CMAKE_BINARY_DIR}/${APP}.lss
    ${CMAKE_BINARY_DIR}/${APP}_cppfilt.txt
    ${CMAKE_BINARY_DIR}/${APP}_size.txt
    ${MAP_FILE}
    ${SYMBOL_LISTING_FILE}
    ${HEX_FILE}
    ${BIN_FILE}

    DESTINATION

    ${CMAKE_CURRENT_SOURCE_DIR}/bin/${APP}
)

get_filename_component(OPENOCD_CONFIG openocd.cfg ABSOLUTE)

add_custom_target(flash COMMAND ${OPENOCD_EXECUTABLE}
  -f ${OPENOCD_CONFIG}
  --command "program ${BIN_FILE} reset exit")