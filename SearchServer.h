#include<vector>
#include"InvertedIndex.h"
#include<vector>
#include<iostream>
#include"ConverterJSON.h"

//для сортировки вектора с частотой встречаемости запрошенных слов
#include <algorithm>
// Определение функции сравнения
inline bool compareBySecond(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
    return a.second < b.second;
}

class SearchServer {
private:
    InvertedIndex inverted_index;

    std::vector<std::pair<std::string, int>> request_frequncy;
public:
    SearchServer(InvertedIndex& inv_index) : inverted_index(inv_index){ };
    //в конструктор класса передается ссылка
    // на класс invertedIndex
    //чтобы SearchServer мог узнать частоту слов встречаемых в запросе

    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& queries_input);
    //метод обработки поисковых запросов.
    // queries_input поисковые запросы взятые из файла requests.json
    // возвращает отсортированный список релевантных ответов для заданных запросов
};