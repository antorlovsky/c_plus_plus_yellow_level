#include "responses.h"

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