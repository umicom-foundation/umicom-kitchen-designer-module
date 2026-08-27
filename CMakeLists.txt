#-----------------------------------------------------------------------------
# Umicom Kitchen Designer Module
# File: CMakeLists.txt
#
# PURPOSE:
#   Build a thin C23 product composition over Framework-owned application
#   experience, runtime and workbench contracts.
#
# Created by: Sammy Hegab
# Organisation: Umicom Foundation
# Licence: MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.24)

project(
    KitchenDesignerModule
    VERSION 0.1.0
    DESCRIPTION "Thin Umicom Kitchen Designer composition over Umicom Framework"
    LANGUAGES C
)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

option(UMICOM_KITCHEN_DESIGNER_BUILD_CONSOLE
       "Build the native Umicom Kitchen Designer verification console"
       ON)

include(CTest)
include(GNUInstallDirs)

if(NOT TARGET Umicom::Framework)
    find_package(UmicomFramework CONFIG REQUIRED)
endif()

if(NOT TARGET Umicom::application)
    message(FATAL_ERROR
        "Umicom Kitchen Designer requires Framework target Umicom::application")
endif()

if(NOT COMMAND umicom_apply_warnings)
    function(umicom_apply_warnings target)
        if(MSVC)
            target_compile_options(${target} PRIVATE /W4)
        else()
            target_compile_options(${target} PRIVATE
                -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
        endif()
    endfunction()
endif()

if(NOT COMMAND umicom_apply_sanitizers)
    function(umicom_apply_sanitizers target)
    endfunction()
endif()

add_library(umicom_kitchen_designer_module STATIC
    src/application.c
    src/workspace.c
)
add_library(Umicom::kitchen_designer_module ALIAS umicom_kitchen_designer_module)

target_include_directories(umicom_kitchen_designer_module PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_link_libraries(umicom_kitchen_designer_module PUBLIC
    Umicom::Framework
    Umicom::application
)
umicom_apply_warnings(umicom_kitchen_designer_module)
umicom_apply_sanitizers(umicom_kitchen_designer_module)

if(UMICOM_KITCHEN_DESIGNER_BUILD_CONSOLE)
    add_executable(umicom-kitchen-designer-console
        src/console/main.c)
    target_link_libraries(umicom-kitchen-designer-console PRIVATE Umicom::kitchen_designer_module)
    umicom_apply_warnings(umicom-kitchen-designer-console)
    umicom_apply_sanitizers(umicom-kitchen-designer-console)
endif()

if(BUILD_TESTING)
    add_executable(kitchen-application-test
        tests/test_application.c)
    target_link_libraries(kitchen-application-test PRIVATE Umicom::kitchen_designer_module)
    umicom_apply_warnings(kitchen-application-test)
    umicom_apply_sanitizers(kitchen-application-test)
    add_test(NAME kitchen.module.application
             COMMAND kitchen-application-test)

    add_executable(kitchen-workspace-test
        tests/test_workspace.c)
    target_link_libraries(kitchen-workspace-test PRIVATE Umicom::kitchen_designer_module)
    umicom_apply_warnings(kitchen-workspace-test)
    umicom_apply_sanitizers(kitchen-workspace-test)
    add_test(NAME kitchen.module.workspace
             COMMAND kitchen-workspace-test)
endif()

install(TARGETS umicom_kitchen_designer_module
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
if(TARGET umicom-kitchen-designer-console)
    install(TARGETS umicom-kitchen-designer-console
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
endif()
install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES application.umicom.yaml
    DESTINATION ${CMAKE_INSTALL_DATADIR}/umicom/applications/kitchen)
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
    install(FILES LICENSE
        DESTINATION ${CMAKE_INSTALL_DATADIR}/licenses/kitchen)
endif()

message(STATUS "Umicom Kitchen Designer Module version: ${PROJECT_VERSION}")
message(STATUS "Umicom Kitchen Designer uses Framework-owned application experience")

include(
    "${CMAKE_CURRENT_SOURCE_DIR}/../../framework/cmake/UmicomApplicationProductisationContribution.cmake")
umicom_add_application_productisation_contribution(
    NAME "kitchen"
    TARGET umicom_kitchen_productisation
    SOURCE "src/productisation_contribution.c"
    TEST_SOURCE "tests/test_productisation_contribution.c")
