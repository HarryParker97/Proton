import yfinance as yf
import json
import sys
import results_dict  # This is your compiled C++ module
import pandas as pd


def get_data(ticker: str) -> dict[str, list[str | float]]:
    
    sp500_data: pd.DataFrame = yf.download(ticker, period="10y").reset_index()
    sp500_data['Date'] = sp500_data['Date'].dt.strftime('%Y-%m-%d')

    sp500_data: pd.DataFrame = sp500_data.where(pd.notnull(sp500_data), None)

    return {
            col: sp500_data[col].tolist()
            for col in sp500_data.columns
        }       


ticker = "^GSPC"
payload: dict[str, dict[str, list[str | float]]] = {
    'date': '2025-05-19',
    'ticker': ticker,
    "strategy": {
        'strategy': 'BuyWhenUpFiveDays',
        'metrics': ['profit', 'total_cost'] 
    },
    "data": get_data(ticker=ticker)
}

# c++ engine
returned_json = results_dict.process_dict(payload)


df_back = pd.read_json(returned_json)
print(df_back.head())
