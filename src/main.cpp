#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <iostream>
#include <string>
#include <map>
#include <vector>

namespace py = pybind11;

class TickerTimeseries {
public:
    std::vector<int> high;
    std::vector<int> low;
    std::vector<int> open;
    std::vector<int> close;
    std::vector<int> volume;

    TickerTimeseries(
        std::vector<int> high,
        std::vector<int> low,
        std::vector<int> open,
        std::vector<int> close,
        std::vector<int> volume
    ) {
        this->high = high;
        this->low = low;
        this->open = open;
        this->close = close;
        this->volume = volume;
    }

    TickerTimeseries() = default; // Default constructor if needed
};


struct TickerTimeSeries {

    std::vector<float> high;
    std::vector<float> low;
    std::vector<float> open;
    std::vector<float> close;
    std::vector<float> volume;

    TickerTimeSeries(
        const std::vector<float>& high,
        const std::vector<float>& low,
        const std::vector<float>& open,
        const std::vector<float>& close,
        const std::vector<float>& volume
    ) {
        this->high = high;
        this->low = low;
        this->open = open;
        this->close = close;
        this->volume = volume;

        _ticker_time_series_validation();
    }

    void _ticker_time_series_validation() {

    }

}

class MarketDataSet {
public:
    std::string date;
    std::map<std::string, TickerTimeseries> ticker_timeseries;

    MarketDataSet(
        const std::string& date_input,
        const std::map<std::string, TickerTimeseries>& ts_input
    ) {
        date = date_input;
        ticker_timeseries = ts_input;
    }
};

py::dict process_dict(const py::dict& input_dict) {
    
    std::string date = input_dict["date"].cast<std::string>();
    std::string ticker = input_dict["ticker"].cast<std::string>();

    std::vector<float> high = input_dict["high"].cast<std::vector<float>>();
    std::vector<float> low = input_dict["low"].cast<std::vector<float>>();
    std::vector<float> open = input_dict["open"].cast<std::vector<float>>();
    std::vector<float> close = input_dict["close"].cast<std::vector<float>>();
    std::vector<float> volume = input_dict["volume"].cast<std::vector<float>>();

    TickerTimeseries ts(high, low, open, close, volume);

    std::map<std::string, TickerTimeseries> ts_map;
    ts_map[ticker] = ts;

    MarketDataSet mds(date, ts_map);

    py::dict output;
    output["date"] = mds.date;
    output["ticker_count"] = mds.ticker_timeseries.size();

    return output;
}

PYBIND11_MODULE(results_dict, m) {
    m.doc() = "MarketDataSet processor module";
    m.def("process_dict", &process_dict, "Parse and process a dict into MarketDataSet");
}
