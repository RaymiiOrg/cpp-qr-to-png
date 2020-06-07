set(BINARY qr-to-png)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)

add_executable(${BINARY} ${SOURCES})
target_include_directories(${BINARY} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${BINARY}
        stdc++fs
        tinypngoutput
        qr-code-generator)

