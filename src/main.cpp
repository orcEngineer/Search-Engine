#include"../include/SearchServer.h"

int main(){

    ConverterJSON converter_json;
    converter_json.GetTextDocuments();
    converter_json.CheckingVersionCompatibility(1);

    InvertedIndex inverted_index;
    inverted_index.UpdateDocumentBase(converter_json.files_contents);

    for(int i = 0; i<converter_json.files_contents.size(); i++){
            std::stringstream content_current_doc(converter_json.files_contents[i]);
            std::string current_word;
            while (content_current_doc >> current_word) {
                inverted_index.freq_dictionary[current_word] = inverted_index.GetWordCount(current_word);
        }
    }

    SearchServer search_server(inverted_index);
    converter_json.putAnswers(search_server.search(converter_json.GetRequests(), converter_json.GetResponsesLimit()));

    return 0;
}