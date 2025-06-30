#ifndef MARKET_DATA_SET_H
#define MARKET_DATA_SET_H

#include <string>
#include <vector>
#include <map>
#include <stdexcept>

class TickerTimeseries {
public:
    std::vector<float> high;
    std::vector<float> low;
    std::vector<float> open;
    std::vector<float> close;
    std::vector<float> volume;

    TickerTimeseries();
    TickerTimeseries(
        const std::vector<float>& high,
        const std::vector<float>& low,
        const std::vector<float>& open,
        const std::vector<float>& close,
        const std::vector<float>& volume
    );

    void validate();
};

class MarketDataSet {
public:
    std::string date;
    std::map<std::string, TickerTimeseries> ticker_timeseries;

    MarketDataSet(
        const std::string& date_input,
        const std::map<std::string, TickerTimeseries>& ts_input
    );
};

#endif
