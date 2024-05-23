cmake_minimum_required(VERSION 3.27)
project(file_search_engine)

set(CMAKE_CXX_STANDARD 17)

# Отключаем тесты для библиотеки nlohmann_json
set(JSON_BuildTests OFF CACHE INTERNAL "")

# Добавляем подкаталог для nlohmann_json
add_subdirectory(nlohmann.json)

# Создаем исполняемый файл
add_executable(file_search_engine
        main.cpp
        ConverterJSON.cpp
        ConverterJSON.h
        InvertedIndex.h
        InvertedIndex.cpp
        SearchServer.cpp
        SearchServer.h
)

# Подключаем библиотеку nlohmann_json
target_link_libraries(file_search_engine PRIVATE nlohmann_json::nlohmann_json)

# Используем FetchContent для подключения googletest
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)
FetchContent_MakeAvailable(googletest)

# Настраиваем GoogleTest
enable_testing()

# Добавляем библиотеку gtest и gtest_main к целевому файлу file_search_engine
target_link_libraries(file_search_engine PRIVATE gtest_main)

# Добавляем тесты
include(GoogleTest)
gtest_discover_tests(file_search_engine)