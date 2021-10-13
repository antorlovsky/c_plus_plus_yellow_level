#include "database.h"

void Database::Add(const Date& date, const string& event) {
    if (unique_documents.count(make_pair(date, event)) == 1)
        return;

    documents[date].push_back(event);
    unique_documents.insert(make_pair(date, event));
}

void Database::Print(ostream& os) const {
    for (const auto& [date, events] : documents) {
        for (const auto& event : events) {
            os << date << " " << event << endl;
        }
    }
}

string Database::Last(const Date& date) const {
    if (documents.empty())
        return "No entries";

    auto it = documents.upper_bound(date);

    bool found = false;
    while (it != begin(documents) && !found) {
        it = prev(it);

        if (!it->second.empty())
            found = true;
    }

    if (!found)
        return "No entries";

    ostringstream record;
    record << it->first << " " << it->second.back();

    return record.str();
}
