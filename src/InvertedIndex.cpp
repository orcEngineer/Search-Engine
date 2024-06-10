#include "../include/InvertedIndex.h"
#include <iostream>
#include <thread>
#include <mutex>

void InvertedIndex::UpdateDocumentBase(std::vector<std::string> input_docs) {
    // Определяем количество потоков, которые будут использоваться
    size_t num_threads = std::thread::hardware_concurrency();
    if (num_threads == 0) {
        num_threads = 2; // По умолчанию используем 2 потока
    }

    // Вычисляем количество документов на каждый поток
    size_t docs_per_thread = input_docs.size() / num_threads;

    // Создаем вектор для хранения промежуточных результатов
    std::vector<std::vector<std::string>> temp_docs(num_threads);

    // Функция, которая будет выполняться в потоке
    auto updateDocuments = [&](size_t start, size_t end, size_t thread_index) {
        for (size_t doc_num = start; doc_num < end; doc_num++) {
            temp_docs[thread_index].push_back(input_docs[doc_num]);
        }
    };

    // Создаем вектор для хранения потоков
    std::vector<std::thread> threads;

    // Запускаем потоки
    for (size_t i = 0; i < num_threads; ++i) {
        size_t start = i * docs_per_thread;
        size_t end = (i == num_threads - 1) ? input_docs.size() : start + docs_per_thread;
        threads.emplace_back(updateDocuments, start, end, i);
    }

    // Дожидаемся завершения всех потоков
    for (auto& thread : threads) {
        thread.join();
    }

    // Объединяем результаты из всех потоков
    for (const auto& part : temp_docs) {
        docs.insert(docs.end(), part.begin(), part.end());
    }
}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word){
    std::vector<Entry> entry_for_current_word;
    for(size_t num_doc=0; num_doc<docs.size(); num_doc++) {
        std::stringstream content_current_doc(docs[num_doc]);
        std::string current_word;
        size_t count_repetitions_in_current_document = 0;
        while (content_current_doc >> current_word) {
            if (current_word == word) {
                count_repetitions_in_current_document++;
            }
        }
        if (count_repetitions_in_current_document > 0) {
            entry_for_current_word.push_back({num_doc, count_repetitions_in_current_document});
        }
    }
    return entry_for_current_word;
}





