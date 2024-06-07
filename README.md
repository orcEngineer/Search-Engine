# Search Engine

Search Engine - это простой и эффективный поисковый движок для текстовых документов. Он поддерживает индексацию документов и поиск по запросам, возвращая релевантные результаты.

## Установка

1. Склонируйте репозиторий на свой компьютер:
    ```bash
    git clone https://github.com/orcEngineer/file_search_engine.git(https://github.com/orcEngineer/Search-Engine)
    ```

2. Перейдите в директорию проекта:
    ```bash
    cd file_search_engine
    ```

3. Создайте директорию сборки и перейдите в нее:
    ```bash
    mkdir build
    cd build
    ```

4. Запустите CMake для генерации Makefile:
    ```bash
    cmake ..
    ```

5. Соберите проект:
    ```bash
    make
    ```

## Использование

1. Поместите ваши текстовые документы в файл `config.json` в следующем формате:
    ```json
    {
        "files": [
            "path/to/document1.txt",
            "path/to/document2.txt"
        ]
    }
    ```

2. Добавьте ваши поисковые запросы в `requests.json` в следующем формате:
    ```json
    {
        "requests": [
            "query1",
            "query2"
        ]
    }
    ```

3. Запустите исполняемый файл:
    ```bash
    ./file_search_engine
    ```

4. Результаты поиска будут записаны в файл `answers.json`.

## Структура проекта

- `main.cpp`: Основной файл с точкой входа.
- `ConverterJSON.h` и `ConverterJSON.cpp`: Классы для работы с JSON файлами.
- `InvertedIndex.h` и `InvertedIndex.cpp`: Классы для создания и работы с инвертированным индексом.
- `SearchServer.h` и `SearchServer.cpp`: Классы для выполнения поисковых запросов с использованием инвертированного индекса.

## Тестирование

1. В проекте используется Google Test для тестирования. Тесты находятся в файле `tests.cpp`.

2. Для запуска тестов выполните следующие команды из директории сборки:
    ```bash
    make test
    ```

## Зависимости

- [nlohmann/json](https://github.com/nlohmann/json) для работы с JSON.
- [Google Test](https://github.com/google/googletest) для тестирования.



Пример команд для выполнения всех шагов:

# Склонируйте репозиторий
git clone https://github.com/orcEngineer/file_search_engine.git

# Перейдите в директорию проекта
cd file_search_engine

# Создайте директорию сборки и перейдите в нее
mkdir build
cd build

# Запустите CMake для генерации Makefile
cmake ..

# Соберите проект
make

# Вернитесь в корневую директорию проекта
cd ..

# Создайте файл config.json и добавьте пути к документам
echo '{
    "files": [
        "path/to/document1.txt",
        "path/to/document2.txt"
    ]
}' > config.json

# Создайте файл requests.json и добавьте поисковые запросы
echo '{
    "requests": [
        "query1",
        "query2"
    ]
}' > requests.json

# Запустите исполняемый файл
./build/file_search_engine

# Результаты будут записаны в файл answers.json
Следуя этим шагам, вы сможете успешно установить и использовать проект для поиска в ваших текстовых документах.
