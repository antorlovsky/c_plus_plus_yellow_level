#include <cassert>
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

istream& operator>>(istream& is, Query& q) {
    string type;
    is >> type;

    if (type == "NEW_BUS") {
        q.type = QueryType::NewBus;
        is >> q.bus;

        int stop_count;
        is >> stop_count;

        q.stops.resize(stop_count);
        for (string& stop : q.stops) {
            is >> stop;
        }
    }
    else if (type == "BUSES_FOR_STOP") {
        q.type = QueryType::BusesForStop;
        is >> q.stop;
    }
    else if (type == "STOPS_FOR_BUS") {
        q.type = QueryType::StopsForBus;
        is >> q.bus;
    }
    else if (type == "ALL_BUSES") {
        q.type = QueryType::AllBuses;
    }

    return is;
}

struct BusesForStopResponse {
    bool success;
    vector<string> buses;
};

ostream& operator<<(ostream& os, const BusesForStopResponse& r) {
    if (r.success) {
        bool first = true;
        for (const string& bus : r.buses) {
            if (!first)
                os << " ";

            os << bus;
            first = false;
        }
    }
    else {
        os << "No stop";
    }

    return os;
}

struct StopsForBusResponse {
    bool success;
    vector<vector<string>> stops;
};

ostream& operator<<(ostream& os, const StopsForBusResponse& r) {
    if (r.success) {
        bool first = true;

        for (const auto& stop : r.stops) {
            if (!first)
                os << endl;

            first = false;

            os << "Stop " << stop[0] << ":";

            if (stop.size() == 1) {
                os << " no interchange";
            }
            else {
                for (int i = 1; i < stop.size(); ++i)
                    os << " " << stop[i];
            }
        }
    }
    else {
        os << "No bus";
    }

    return os;
}

struct AllBusesResponse {
    bool success;
    map<string, vector<string>> buses;
};

ostream& operator<<(ostream& os, const AllBusesResponse& r) {
    if (r.success) {
        bool first = true;

        for (const auto& [bus, stops] : r.buses) {
            if (!first)
                os << endl;

            first = false;

            os << "Bus " << bus << ":";

            for (const string& stop : stops)
                os << " " << stop;
        }
    }
    else {
        os << "No buses";
    }

    return os;
}

class BusManager {
public:
    void AddBus(const string& bus, const vector<string>& stops) {
        buses_to_stops[bus] = stops;

        for (const string& stop : stops)
            stops_to_buses[stop].push_back(bus);
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const {
        if (stops_to_buses.count(stop) == 0)
            return {false};

        return {true, stops_to_buses.at(stop)};
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const {
        if (buses_to_stops.count(bus) == 0)
            return {false};

        vector<vector<string>> stops;
        for (const string& stop : buses_to_stops.at(bus)) {
            vector<string> buses = {stop};

            for (const string& other_bus : stops_to_buses.at(stop)) {
                if (bus != other_bus)
                    buses.push_back(other_bus);
            }

            stops.push_back(buses);
        }

        return {true, stops};
    }

    AllBusesResponse GetAllBuses() const {
        if (buses_to_stops.empty())
            return {false};

        return {true, buses_to_stops};
    }

private:
    map<string, vector<string>> buses_to_stops;
    map<string, vector<string>> stops_to_buses;
};

int main() {
    int query_count;
    Query q;

    cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
        switch (q.type) {
            case QueryType::NewBus:
                bm.AddBus(q.bus, q.stops);
                break;
            case QueryType::BusesForStop:
                cout << bm.GetBusesForStop(q.stop) << endl;
                break;
            case QueryType::StopsForBus:
                cout << bm.GetStopsForBus(q.bus) << endl;
                break;
            case QueryType::AllBuses:
                cout << bm.GetAllBuses() << endl;
                break;
        }
    }

    return 0;
}
