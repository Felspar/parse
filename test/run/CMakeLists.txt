if(TARGET felspar-check)
    add_test_run(felspar-check felspar-parse TESTS
            extract.tests.cpp
        )
endif()
