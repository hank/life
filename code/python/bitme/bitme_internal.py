import datetime, time

errors = {
1000: [ 500,    "Unknown error"],
1001: [ 404,    "The requested resource was not found"],
1002: [ 400,    "Invalid request parameter value"],
1003: [ 503,    "API is temporarily unavailable"],
1100: [ 500,    "Unknown authentication error"],
1101: [ 401,    "Invalid API key"],
1102: [ 401,    "Invalid nonce"],
1103: [ 401,    "Invalid signing hash"],
1105: [ 403,    "Invalid username and/or password"],
1106: [ 403,    "Login successful, Two-factor authentication required"],
1200: [ 500,    "Unknown transaction error"],
1201: [ 403,    "Insufficient available account balance"],
1202: [ 403,    "Cannot exceed deposit limit"],
1203: [ 403,    "Cannot exceed withdrawal limit"],
1400: [ 500,    "Unknown order error"],
1401: [ 403,    "Cannot have more than 100 open orders"],
1402: [ 403,    "Cannot create an order that will execute against own order"],
1500: [ 500,    "Unknown error relating to a user"],
1501: [ 403,    "Invalid user"],
1504: [ 403,    "The given email address is already in use"],
1505: [ 403,    "Cannot use same user"],
1506: [ 403,    "User must agree to terms of use"],
1700: [ 500,    "Unknown rate limiting error"],
1701: [ 420,    "You are being rate limited, lower your request rate"]
}

def utc_mktime(utc_tuple):
    """Returns number of seconds elapsed since epoch

    Note that no timezone are taken into consideration.

    utc tuple must be: (year, month, day, hour, minute, second)

    """

    if len(utc_tuple) == 6:
        utc_tuple += (0, 0, 0)
    return time.mktime(utc_tuple) - time.mktime((1970, 1, 1, 0, 0, 0, 0, 0, 0))

def datetime_to_timestamp(dt):
    """Converts a datetime object to UTC timestamp"""

    return int(utc_mktime(dt.timetuple())) * 1000 + (dt.microsecond / 1000)

if __name__ == '__main__':
    print datetime_to_timestamp(datetime.datetime.now())
