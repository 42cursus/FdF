cmake_minimum_required(VERSION 3.8)

project(FdF C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)

set(FT_LIB_NAME ft)
set(FT_LIB_FILENAME libft.a)
set(FT_LIB_DIR "${PROJECT_SOURCE_DIR}/lib/ft")

file(GLOB_RECURSE FT_LIB_HEADERS "${FT_LIB_DIR}/*.h")
file(GLOB_RECURSE FT_LIB_SOURCES "${FT_LIB_DIR}/*.c")

add_custom_target(${FT_LIB_NAME}_target ALL
        COMMAND make -C ${FT_LIB_DIR}
        BYPRODUCTS "${FT_LIB_DIR}/${FT_LIB_FILENAME}"
        SOURCES "${FT_LIB_HEADERS};${FT_LIB_SOURCES}"
        COMMENT "Building FT_LIB")

add_library(${FT_LIB_NAME} STATIC IMPORTED)
add_dependencies(${FT_LIB_NAME} "${FT_LIB_NAME}_target")
set_target_properties(${FT_LIB_NAME} PROPERTIES
        IMPORTED_LOCATION ${FT_LIB_DIR}/${FT_LIB_FILENAME} # Make sure to use absolute path here
        INTERFACE_COMPILE_DEFINITIONS ""
        INTERFACE_LINK_OPTIONS ""
        INTERFACE_SOURCES "${FT_LIB_HEADERS}"
        INTERFACE_INCLUDE_DIRECTORIES "${FT_LIB_DIR};${FT_LIB_DIR}/include")

set(MLX_LIB_NAME mlx)
set(MLX_LIB_FILENAME libmlx.a)
set(MLX_LIB_DIR "${PROJECT_SOURCE_DIR}/lib/mlx")

file(GLOB_RECURSE MLX_LIB_HEADERS "${MLX_LIB_DIR}/*.h")
list(FILTER MLX_LIB_HEADERS EXCLUDE REGEX "${MLX_LIB_DIR}/test/*" )
file(GLOB_RECURSE MLX_LIB_SOURCES "${MLX_LIB_DIR}/*.c")
list(FILTER MLX_LIB_SOURCES EXCLUDE REGEX "${MLX_LIB_DIR}/test/*|${MLX_LIB_DIR}/mlx_lib_xpm.c")

add_custom_target(${MLX_LIB_NAME}_target ALL
        COMMAND make -C ${MLX_LIB_DIR}
        BYPRODUCTS "${MLX_LIB_DIR}/${MLX_LIB_FILENAME}"
        SOURCES "${MLX_LIB_HEADERS};${MLX_LIB_SOURCES}"
        COMMENT "Building MLX_LIB")

add_library(${MLX_LIB_NAME} STATIC IMPORTED)
add_dependencies(${MLX_LIB_NAME} "${MLX_LIB_NAME}_target")
set_target_properties(${MLX_LIB_NAME} PROPERTIES
        IMPORTED_LOCATION "${MLX_LIB_DIR}/${MLX_LIB_FILENAME}" # Make sure to use absolute path here
        INTERFACE_COMPILE_DEFINITIONS ""
        INTERFACE_SOURCES "${MLX_LIB_HEADERS}"
        INTERFACE_INCLUDE_DIRECTORIES "${MLX_LIB_DIR}")


set(FDF_LIB_NAME fdf)
set(FDF_LIB_FILENAME libfdf.a)
set(FDF_LIB_DIR "${PROJECT_SOURCE_DIR}/lib/fdf")

file(GLOB_RECURSE FDF_LIB_HEADERS "${FDF_LIB_DIR}/*.h")
list(FILTER FDF_LIB_HEADERS EXCLUDE REGEX "${FDF_LIB_DIR}/test/*" )
file(GLOB_RECURSE FDF_LIB_SOURCES "${FDF_LIB_DIR}/*.c")
list(FILTER FDF_LIB_SOURCES EXCLUDE REGEX "${FDF_LIB_DIR}/test/*|${FDF_LIB_DIR}/mlx_lib_xpm.c")

add_custom_target(${FDF_LIB_NAME}_target ALL
        COMMAND make -C ${FDF_LIB_DIR}
        BYPRODUCTS "${FDF_LIB_DIR}/${FDF_LIB_FILENAME}"
        SOURCES "${FDF_LIB_HEADERS};${FDF_LIB_SOURCES}"
        COMMENT "Building FDF_LIB")

add_library(${FDF_LIB_NAME} STATIC IMPORTED)
add_dependencies(${FDF_LIB_NAME} "${FDF_LIB_NAME}_target")
set_target_properties(${FDF_LIB_NAME} PROPERTIES
        IMPORTED_LOCATION "${FDF_LIB_DIR}/${FDF_LIB_FILENAME}" # Make sure to use absolute path here
        INTERFACE_COMPILE_DEFINITIONS ""
        INTERFACE_SOURCES  "${FDF_LIB_HEADERS};${FDF_LIB_SOURCES}"
        INTERFACE_INCLUDE_DIRECTORIES "${FDF_LIB_DIR};${PROJECT_SOURCE_DIR}/include")

add_custom_target(fclean ALL)
add_custom_command(TARGET fclean POST_BUILD
        COMMAND make -C ${FT_LIB_DIR} fclean
        COMMAND make -C ${FDF_LIB_DIR} clean)

find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(X11 REQUIRED) # https://cmake.org/cmake/help/latest/module/FindX11.html
find_library(MATH_LIB m)

pkg_check_modules(X11 REQUIRED IMPORTED_TARGET x11)
pkg_check_modules(Xext REQUIRED IMPORTED_TARGET xext)

set(TARGET_NAME "${PROJECT_NAME}_exe")
set(TARGET_LIBRARIES
        ${FT_LIB_NAME} ${FDF_LIB_NAME} ${MLX_LIB_NAME}
        ${MATH_LIB}
        Threads::Threads)

file(GLOB_RECURSE FDF_HEADERS "${PROJECT_SOURCE_DIR}/src/*.h")
file(GLOB_RECURSE FDF_SOURCES "${PROJECT_SOURCE_DIR}/src/*.c")

add_executable(${TARGET_NAME} ${FDF_HEADERS} ${FDF_SOURCES})
set_target_properties(${TARGET_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
        OUTPUT_NAME "FdF")
target_compile_options(${TARGET_NAME} PRIVATE -Wno-error=parentheses)
target_include_directories(${TARGET_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(${TARGET_NAME}
        "${TARGET_LIBRARIES}"
        -lbsd -lX11 -lXext -lXrandr -lXpm -lm)
