function(enable_coverage CUR_TARGET)
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        target_compile_options(${CUR_TARGET} PRIVATE
            -fprofile-arcs
            -ftest-coverage
            )
        target_link_libraries(${CUR_TARGET} PRIVATE
            -lgcov
            )
    else()
        message("COVERAGE for compiler ${CMAKE_CXX_COMPILER_ID} is not implemented")
    endif()
endfunction()
