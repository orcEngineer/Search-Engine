#include "../include/ConverterJSON.h"

class ConfigFileIsMissingException:public std::exception{
    const char* what() const noexcept override{
        return "Config file is missing!";
    }
};
class ConfigFileIsEmptyExcpetion:public std::exception{
    const char* what() const noexcept override{
        return "Config file is empty!";
    }
};
class IncorrectVersionException:public std::exception{
    const char* what() const noexcept override{
        return "config.json has incorrect file version!";
    }
};

void ConverterJSON::GetTextDocuments() {
    try {
        std::ifstream i_file_config(".\\config\\config.json");
        if (!i_file_config.is_open()) {
            throw ConfigFileIsMissingException();
        }
        nlohmann::json config_content_json;
        i_file_config >> config_content_json;

        try {
            if (config_content_json["config"].size() == 0) {
                throw ConfigFileIsEmptyExcpetion();
            }

            files_name = config_content_json["files"];
            i_file_config.close();

            for (int num_file = 0; num_file < files_name.size(); ++num_file) {

                std::string current_text = "";
                std::ifstream current_file(files_name[num_file]);

                if(!current_file.is_open()){
                    std::cout<<"\nError. Could not find the file at: "<<files_name[num_file]<<"\n";
                }else {
                    std::string current_all_text="";
                    while (!current_file.eof()) {
                        std::getline(current_file, current_text);
                        current_all_text+=current_text;
                    }
                    files_contents.push_back(current_all_text);
                    current_file.close();
                }
            }
        }
        catch (const std::exception& x) {
            std::cerr << x.what();
        }
    }
    catch (const std::exception& x){
        std::cerr<<x.what();
    }
}

void ConverterJSON::CheckingVersionCompatibility(int versionProgram){
    std::ifstream i_file_config(".\\config\\config.json");
    nlohmann::json config_content_json;
    i_file_config >> config_content_json;
    i_file_config.close();
    try {
        if (config_content_json["config"]["version"] != versionProgram) {
            throw IncorrectVersionException();
        }
    }
    catch (const std::exception& x){
        std::cerr<<x.what();
    }
}

int ConverterJSON::GetResponsesLimit(){
    std::ifstream i_file_config(".\\config\\config.json");
    nlohmann::json config_content_json;
    i_file_config>>config_content_json;
    i_file_config.close();
    return config_content_json["config"]["max_responses"];
}

std::vector<std::string> ConverterJSON::GetRequests(){
    std::ifstream i_file_requests(".\\config\\requests.json");
    nlohmann::json requests_content_json;
    i_file_requests>>requests_content_json;
    requests = requests_content_json["requests"];
    i_file_requests.close();

    if (requests.size() > GetResponsesLimit()) {
        requests.resize(GetResponsesLimit());
    }
    return requests;
}

void ConverterJSON::putAnswers(const std::vector<std::vector<RelativeIndex>> &answers) {
    // Создаем JSON объект для хранения ответов
    nlohmann::json j;

    // Создаем базовое поле answers
    j["answers"] = nlohmann::json::object();

    // Перебираем все ответы
    for (size_t i = 0; i < answers.size(); ++i) {
        std::string request_id = "request" + std::to_string(i + 1);

        // Создаем объект для текущего запроса
        nlohmann::json request_result;
        if (answers[i].empty()) {
            // Если нет релевантных документов, result = false
            request_result["result"] = false;
        } else {
            // Если есть релевантные документы, result = true
            request_result["result"] = true;
            nlohmann::json relevance_array = nlohmann::json::array();
            for (const auto& answer : answers[i]) {
                relevance_array.push_back({{"docid", answer.doc_id}, {"rank", answer.rank}});
            }
            request_result["relevance"] = relevance_array;
        }

        // Добавляем результат текущего запроса в основной JSON объект
        j["answers"][request_id] = request_result;
    }

    // Открываем файл answers.json и стираем его содержимое, если файл уже существует
    std::ofstream ofs(".\\config\\answers.json", std::ofstream::out | std::ofstream::trunc);
    if (!ofs.is_open()) {
        throw std::runtime_error("Cannot open answers.json file for writing");
    }

    // Записываем JSON объект в файл
    ofs << j.dump(4); // 4 - это количество пробелов для форматирования JSON
    ofs.close();
}
