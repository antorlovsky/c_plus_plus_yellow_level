#pragma once

#include "date.h"

#include <vector>
#include <string>
#include <map>
#include <set>
#include <utility>
#include <sstream>
#include <iostream>
#include <algorithm>

class Database {
public:
    void Add(const Date& date, const string& event);

    void Print(ostream& os) const;

    template <typename Predicate>
    size_t RemoveIf(Predicate predicate) {
        int remove_count = 0;

        for (auto doc_it = begin(documents); doc_it != end(documents); ) {
            const Date& date = doc_it->first;
            vector<string>& events = doc_it->second;

            int size_before = events.size();

            auto it = stable_partition(begin(events), end(events), [date, predicate](const string& event) {
                return !predicate(date, event);
            });

            auto remove_it = end(events);

            while (remove_it != it) {
                --remove_it;
                unique_documents.erase(make_pair(date, *remove_it));
            }

            events.erase(it, end(events));
            remove_count += size_before - events.size();

            if (events.empty())
                doc_it = documents.erase(doc_it);
            else
                ++doc_it;
        }

        return remove_count;
    }

    template <typename Predicate>
    vector<string> FindIf(Predicate predicate) const {
        vector<string> result;

        for (const auto& [date, events] : documents) {
            for (auto it = begin(events); it != end(events); ++it) {
                if (predicate(date, *it)) {
                    ostringstream record;

                    record << date << " " << *it;
                    result.push_back(record.str());
                }
            }
        }

        return result;
    }

    string Last(const Date& date) const;

private:
    map<Date, vector<string>> documents;
    set<pair<Date, string>> unique_documents;
};