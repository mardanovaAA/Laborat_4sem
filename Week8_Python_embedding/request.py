from requests import get

def price(pair):
    r = get('https://api.binance.com/api/v3/ticker/price').json()
    for item in r:
        if item['symbol'] == pair:
            return float(item['price'])
    return 0.