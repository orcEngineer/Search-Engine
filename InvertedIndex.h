#include<vector>
#include<string>
#include<map>
#include<fstream>
#include<string>
#include<sstream>

struct Entry {
    //int doc_id, count;
    size_t doc_id, count;
// Данный оператор необходим для проведения тестовых сценариев
    bool operator ==(const Entry& other) const {
        return (doc_id == other.doc_id &&
                count == other.count);
    }
};

class InvertedIndex {

public:
    std::vector<std::string> docs; // список содержимого документов
    std::map<std::string, std::vector<Entry>> freq_dictionary; // частотный словарь

    InvertedIndex() = default;

    void UpdateDocumentBase(std::vector<std::string> input_docs);// Обновить или заполнить базу документов, по которой будем совершать поиск
    // @param texts_input содержимое документов

    std::vector<Entry> GetWordCount(const std::string& word); //Метод определяет количество вхождений слова word
    // в загруженной базе документов @param word слово, частоту вхождений которого необходимо определить
    // @return возвращает подготовленный список с частотой слов
};
