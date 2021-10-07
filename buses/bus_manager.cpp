#include "bus_manager.h"

void BusManager::AddBus(const string& bus, const vector<string>& stops) {
    buses_to_stops[bus] = stops;

    for (const string& stop : stops)
        stops_to_buses[stop].push_back(bus);
}

BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
    if (stops_to_buses.count(stop) == 0)
        return {false};

    return {true, stops_to_buses.at(stop)};
}

StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
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

AllBusesResponse BusManager::GetAllBuses() const {
    if (buses_to_stops.empty())
        return {false};

    return {true, buses_to_stops};
}