add_library(parse-headers-tests STATIC EXCLUDE_FROM_ALL
        extract.cpp
        parse.binary.cpp
    )
target_link_libraries(parse-headers-tests PUBLIC felspar-parse)
add_dependencies(felspar-check parse-headers-tests)
