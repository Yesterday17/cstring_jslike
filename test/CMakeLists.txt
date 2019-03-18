if(BUILD_TEST)
    set(unit_tests
            test_string_base
            test_utf8_method)

    foreach(unit_test ${unit_tests})
        add_executable("${unit_test}" "${unit_test}.c")
        target_link_libraries("${unit_test}" cstring_jslike unity)
        add_test(NAME "${unit_test}"
                COMMAND "./${unit_test}")
        add_coverage("${unit_test}")
    endforeach()
endif()