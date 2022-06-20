file(GLOB FUNDB_TEST_SOURCES "${PROJECT_SOURCE_DIR}/test/*/*test.cpp")

######################################################################################################################
# DEPENDENCIES
######################################################################################################################

# valgrind
find_program(VALGRIND_BIN valgrind)
if ("${VALGRIND_BIN}" STREQUAL "VALGRIND_BIN-NOTFOUND")
    message(WARNING "fundb/test couldn't find valgrind.")
else()
    message(STATUS "fundb/test found valgrind at ${VALGRIND_BIN}")
endif()

set(VALGRIND_OPTIONS
        --error-exitcode=1                      # if leaks are detected, return nonzero value
        # --gen-suppressions=all  # uncomment for leak suppression syntax
        --leak-check=full                       # detailed leak information
        --soname-synonyms=somalloc=*jemalloc*   # also intercept jemalloc
        --trace-children=yes                    # trace child processes
        --track-origins=yes                     # track origin of uninitialized values
        )
set(VALGRIND_SUPPRESSIONS_FILE "${PROJECT_SOURCE_DIR}/build-deps/valgrind.supp")

##########################################
# "make check-tests"
##########################################
add_custom_target(build-tests COMMAND ${CMAKE_CTEST_COMMAND} --show-only)
add_custom_target(check-tests COMMAND ${CMAKE_CTEST_COMMAND} --verbose)

##########################################
# "make XYZ_test"
##########################################
foreach (fundb_test_source ${FUNDB_TEST_SOURCES})
    # Create a human readable name.
    get_filename_component(bustub_test_filename ${fundb_test_source} NAME)
    string(REPLACE ".cpp" "" fundb_test_name ${bustub_test_filename})

    # Add the test target separately and as part of "make check-tests".
    add_executable(${fundb_test_name} EXCLUDE_FROM_ALL ${fundb_test_source})
    add_dependencies(build-tests ${fundb_test_name})
    add_dependencies(check-tests ${fundb_test_name})

    target_link_libraries(${fundb_test_name} fundb_shared gtest gmock_main)

    # Set test target properties and dependencies.
    set_target_properties(${fundb_test_name}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test"
        COMMAND ${fundb_test_name}
    )

    # Add the test under CTest.
    add_test(${fundb_test_name} ${VALGRIND_BIN} ${VALGRIND_OPTIONS}
    --suppressions=${VALGRIND_SUPPRESSIONS_FILE} ${CMAKE_BINARY_DIR}/test/${fundb_test_name}
    --gtest_color=yes --gtest_output=xml:${CMAKE_BINARY_DIR}/test/unit_${test_name}.xml)
    add_test(${fundb_test_name} ${CMAKE_BINARY_DIR}/test/${fundb_test_name} --gtest_color=yes
            --gtest_output=xml:${CMAKE_BINARY_DIR}/test/${fundb_test_name}.xml)
endforeach(fundb_test_source ${FUNDB_TEST_SOURCES})