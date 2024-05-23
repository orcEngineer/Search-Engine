#include "SearchServer.h"
#include <vector>
#include <string>
#include <algorithm>
#include <utility>

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string>& queries_input) {
    std::vector<std::vector<RelativeIndex>> results;

    for (const auto& query : queries_input) {
        std::vector<int> absolute_relevance(inverted_index.docs.size(), 0);
        std::istringstream iss(query);
        std::string word;
        while (iss >> word) {
            auto word_count = inverted_index.GetWordCount(word);
            for (const auto& [doc_id, count] : word_count) {
                absolute_relevance[doc_id] += count;
            }
        }

        int max_absolute_relevance = *std::max_element(absolute_relevance.begin(), absolute_relevance.end());
        std::vector<std::pair<int, float>> relative_relevance(inverted_index.docs.size());
        for (size_t i = 0; i < absolute_relevance.size(); ++i) {
            relative_relevance[i] = {i, max_absolute_relevance == 0 ? 0 : static_cast<float>(absolute_relevance[i]) / max_absolute_relevance};
        }

        std::sort(relative_relevance.begin(), relative_relevance.end(), [](const auto& a, const auto& b) {
            return a.second > b.second;
        });

        std::vector<RelativeIndex> query_result;
        for (const auto& [doc_id, rank] : relative_relevance) {
            if (rank > 0) {
                query_result.push_back({static_cast<size_t>(doc_id), rank});
            }
        }

        results.push_back(query_result);
    }
    return results;
}