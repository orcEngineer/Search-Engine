#include<vector>
#include<iostream>
#include<string>
#include"nlohmann/json.hpp"
#include<fstream>
#include<ostream>
#include<exception>

struct RelativeIndex{
    size_t doc_id;
    float rank;
    bool operator ==(const RelativeIndex& other) const {
        return (doc_id == other.doc_id && rank == other.rank);
    }
};


class ConverterJSON {
public:
    std::vector<std::string> files_name;
    std::vector<std::string> files_contents;
    std::vector<std::string> requests;
public:
    ConverterJSON() = default;
    void GetTextDocuments();//получение содержимого файлов, перечисленных в config.json
    int GetResponsesLimit();//считывание max_responses
    std::vector<std::string> GetRequests();//получение запросов из requests.json
    void putAnswers(const std::vector<std::vector<RelativeIndex>>& answers);//запись ответов
    void CheckingVersionCompatibility(int versionProgram);
};