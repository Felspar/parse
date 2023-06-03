add_library(parse-headers-tests STATIC EXCLUDE_FROM_ALL
        extract.be.cpp
        extract.le.cpp
        extract.native.cpp
        insert.be.cpp
        insert.le.cpp
        insert.native.cpp
        parse.binary.cpp
    )
target_link_libraries(parse-headers-tests PUBLIC felspar-parse)
add_dependencies(felspar-check parse-headers-tests)
