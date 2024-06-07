#include "../include/SearchServer.h"

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string>& queries_input,
                                                             int responses_limit) {
    std::vector<std::vector<RelativeIndex>> results(queries_input.size());
    std::mutex results_mutex;

    auto searchQuery = [&](const std::string& query, size_t index) {
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
            relative_relevance[i] = {static_cast<int>(i), max_absolute_relevance == 0 ? 0.0f : static_cast<float>(absolute_relevance[i]) / max_absolute_relevance};
        }

        std::sort(relative_relevance.begin(), relative_relevance.end(), [](const auto& a, const auto& b) {
            return a.second > b.second || (a.second == b.second && a.first < b.first);
        });


        std::vector<RelativeIndex> query_result;

        for (const auto& [doc_id, rank] : relative_relevance) {
            if (rank > 0) {

                query_result.push_back({static_cast<size_t>(doc_id), rank});
            }
        }

        if (query_result.size() > responses_limit) {
            query_result.resize(responses_limit);
        }

        std::lock_guard<std::mutex> guard(results_mutex);
        results[index] = std::move(query_result);
    };

    std::vector<std::future<void>> futures;
    for (size_t i = 0; i < queries_input.size(); ++i) {
        futures.emplace_back(std::async(std::launch::async, searchQuery, queries_input[i], i));
    }

    for (auto& future : futures) {
        future.get();
    }

    return results;
}