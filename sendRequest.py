import requests
import Filter


def get_request(address):
    # print(address)

    # Try except structure for error handling
    try:
        r = requests.get(address)
        print('connected to Pi: ' + address)
        Filter.filter_content(str(r.content))
    except:
        print('unable to connect to Pi: ' + address)
