// market_data_set.cpp
#include "market_data_set.h"

TickerTimeseries::TickerTimeseries() = default;

TickerTimeseries::TickerTimeseries(
    const std::vector<float>& high,
    const std::vector<float>& low,
    const std::vector<float>& open,
    const std::vector<float>& close,
    const std::vector<float>& volume
)
    : high(high), low(low), open(open), close(close), volume(volume) {
    validate();
}

void TickerTimeseries::validate() {
    size_t size = high.size();
    if (low.size() != size || open.size() != size || close.size() != size || volume.size() != size) {
        throw std::invalid_argument("All time series vectors must be the same size");
    }
}

MarketDataSet::MarketDataSet(
    const std::string& date_input,
    const std::map<std::string, TickerTimeseries>& ts_input
)
    : date(date_input), ticker_timeseries(ts_input) {}
