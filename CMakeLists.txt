cmake_minimum_required(VERSION 3.27)
project(file_search_engine)

set(CMAKE_CXX_STANDARD 17)

# Отключаем тесты для библиотеки nlohmann_json
set(JSON_BuildTests OFF CACHE INTERNAL "")

# Добавляем подкаталог для nlohmann_json
add_subdirectory(nlohmann.json)

# Определяем цель для исполняемого файла file_search_engine
add_executable(file_search_engine
        src/main.cpp
        src/ConverterJSON.cpp
        src/InvertedIndex.cpp
        src/SearchServer.cpp
        include/ConverterJSON.h
        include/InvertedIndex.h
        include/SearchServer.h
)

# Подключаем библиотеку nlohmann_json
target_link_libraries(file_search_engine nlohmann_json::nlohmann_json)

# Используем FetchContent для подключения googletest
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)
FetchContent_MakeAvailable(googletest)

# Настраиваем GoogleTest
enable_testing()

# Определяем цель для исполняемого файла с тестами
add_executable(file_search_engine_tests
        src/inverted_index_tests.cpp
        src/search_server_tests.cpp
        src/ConverterJSON.cpp
        src/InvertedIndex.cpp
        src/SearchServer.cpp
        include/ConverterJSON.h
        include/InvertedIndex.h
        include/SearchServer.h
)

# Подключаем библиотеку Google Test к исполняемому файлу с тестами
target_link_libraries(file_search_engine_tests gtest gtest_main nlohmann_json::nlohmann_json)

# Добавляем тесты
include(GoogleTest)
gtest_discover_tests(file_search_engine_tests)