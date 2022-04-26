import pandas as pd

# Helper to reformats date from ex. Jan 1 2000 to 01/01/2000
def reformat_date(date):
    parts = date.split()
    month = parts[0]
    day = int(parts[1])
    year = parts[2]
    num = 0
    if month == "Jan":
        num = 1
    elif month == "Feb":
        num = 2
    elif month == "Mar":
        num = 3
    elif month == "Apr":
        num = 4
    elif month == "May":
        num = 5
    elif month == "Jun":
        num = 6
    elif month == "Jul":
        num = 7
    elif month == "Aug":
        num = 8
    elif month == "Sep":
        num = 9
    elif month == "Oct":
        num = 10
    elif month == "Nov":
        num = 11
    elif month == "Dec":
        num = 12

    if day > 9:
        return "0" + str(num) + "/" + str(day) + "/" + str(year)
    else:
        return "0" + str(num) + "/0" + str(day) + "/" + str(year)



def read_data(file):
    return pd.read_csv(file)