// bindings.cpp
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <string>
#include <map>
#include "market_data_set.h"

namespace py = pybind11;





py::dict process_dict(const py::dict& input_dict) {
    std::string date = input_dict["date"].cast<std::string>();
    py::dict data_dict = input_dict["data"].cast<py::dict>();

    std::map<std::string, TickerTimeseries> ts_map;

    for (const auto& item : data_dict) {
        std::string ticker = item.first.cast<std::string>();
        py::dict ticker_data = item.second.cast<py::dict>();

        std::vector<float> high = ticker_data["High"].cast<std::vector<float>>();
        std::vector<float> low = ticker_data["Low"].cast<std::vector<float>>();
        std::vector<float> open = ticker_data["Open"].cast<std::vector<float>>();
        std::vector<float> close = ticker_data["Close"].cast<std::vector<float>>();
        std::vector<float> volume = ticker_data["Volume"].cast<std::vector<float>>();

        TickerTimeseries ts(high, low, open, close, volume);
        ts_map[ticker] = ts;
    }

    MarketDataSet mds(date, ts_map);

    py::dict output;
    output["date"] = mds.date;
    output["ticker_count"] = 69;

    return output;
}

PYBIND11_MODULE(results_dict, m) {
    // m.doc() = "MarketDataSet processor module";
    m.def("process_dict", &process_dict, "Parse and process a dict into MarketDataSet");
}