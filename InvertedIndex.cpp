#include "InvertedIndex.h"
#include<iostream>

void InvertedIndex::UpdateDocumentBase(std::vector<std::string> input_docs){//на входе документы с начальным содержанием
    for(int doc_num = 0; doc_num<input_docs.size(); doc_num++){
        docs=input_docs;
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










