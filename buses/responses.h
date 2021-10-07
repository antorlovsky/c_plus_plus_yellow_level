#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

struct BusesForStopResponse {
    bool success;
    vector<string> buses;
};

ostream& operator<<(ostream& os, const BusesForStopResponse& r);

struct StopsForBusResponse {
    bool success;
    vector<vector<string>> stops;
};

ostream& operator<<(ostream& os, const StopsForBusResponse& r);

struct AllBusesResponse {
    bool success;
    map<string, vector<string>> buses;
};

ostream& operator<<(ostream& os, const AllBusesResponse& r);