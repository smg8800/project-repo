from datetime import datetime
import time
from urllib.request import Request, urlopen

## Made by Sean Geary
## 5/21/22

# send_requests(times, url) - Takes an input dictionary of timestamps and their respective counts, then
# we get the current time converted to the input string style, then check if the current
# time is a time included in the input. If it is found, we find the number of entries with that
# same time, then send a GET request for each entry. Upon completion, we get the current time again
# and wait 1 second minus the number of microseconds that have passed since the requests were sent.
# This ensures that we are waiting until the start of each new second to begin checking the input
# and sending the GET requests.
# Inputs:
#        items - a dictionary with the keys being the timestamps from the input,
#                and the value stores the number of times that timestamp shows up
#        url - url to send GET request to

def send_requests(times, url):
    now = datetime.now().strftime("%H:%M:%S") # get current time in H:M:S form
    headers = {'User-Agent': 'Mozilla/5.0'} # include headers so we aren't denied permission from website
    if now in times: # check if current time is in list
        for i in range(times[now]):
            req = Request(url,headers= headers) # GET Request
            # page = urlopen(req).read()
            # webpage = page.decode('utf-8') # would read and open webpage for use
            # do something with the webpage

    time.sleep((1000000 - datetime.now().microsecond)/1000000)

# helper function to split single input string into a list of times to be returned
def split_times(string_list, char):
    list = string_list.split(char)
    a = {}
    for item in list:
        # check if already in dictionary, add 1 if it is, else add to dictionary with value 1
        if item in a:
            a[item] += 1
        else:
            a[item] = 1
    return a



# code used to create dummy timestamps to check if the requests are being handled correctly

# allTimes = ""
# for i in range(0,24):
#     if i <= 9:
#         for j in range(0,60):
#             if j <= 9:
#                 for k in range(0,60):
#                     if k <= 9:
#                         allTimes += ("0" + str(i) + ":0" + str(j) + ":0" + str(k)) + ","
#                         # allTimes += ("0" + str(i) + ":0" + str(j) + ":0" + str(k)) + ","
#                         # allTimes += ("0" + str(i) + ":0" + str(j) + ":0" + str(k)) + ","
#                         # allTimes += ("0" + str(i) + ":0" + str(j) + ":0" + str(k)) + ","
#                         # allTimes += ("0" + str(i) + ":0" + str(j) + ":0" + str(k)) + ","
#                     else:
#                         allTimes += ("0" + str(i) + ":0" + str(j) + ":" + str(k)) + ","
#                         # allTimes += ("0" + str(i) + ":0" + str(j) + ":" + str(k)) + ","
#                         # allTimes += ("0" + str(i) + ":0" + str(j) + ":" + str(k)) + ","
#                         # allTimes += ("0" + str(i) + ":0" + str(j) + ":" + str(k)) + ","
#                         # allTimes += ("0" + str(i) + ":0" + str(j) + ":" + str(k)) + ","
#             else:
#                 for k in range(0,60):
#                     if k <= 9:
#                         allTimes += ("0" + str(i) + ":" + str(j) + ":0" + str(k)) + ","
#                         # allTimes += ("0" + str(i) + ":" + str(j) + ":0" + str(k)) + ","
#                         # allTimes += ("0" + str(i) + ":" + str(j) + ":0" + str(k)) + ","
#                         # allTimes += ("0" + str(i) + ":" + str(j) + ":0" + str(k)) + ","
#                         # allTimes += ("0" + str(i) + ":" + str(j) + ":0" + str(k)) + ","
#                     else:
#                         allTimes += ("0" + str(i) + ":" + str(j) + ":" + str(k)) + ","
#                         # allTimes += ("0" + str(i) + ":" + str(j) + ":" + str(k)) + ","
#                         # allTimes += ("0" + str(i) + ":" + str(j) + ":" + str(k)) + ","
#                         # allTimes += ("0" + str(i) + ":" + str(j) + ":" + str(k)) + ","
#                         # allTimes += ("0" + str(i) + ":" + str(j) + ":" + str(k)) + ","
#     else:
#         for j in range(0,60):
#             if j <= 9:
#                 for k in range(10,40):
#                     if k <= 9:
#                         allTimes += (str(i) + ":0" + str(j) + ":0" + str(k)) + ","
#                         # allTimes += (str(i) + ":0" + str(j) + ":0" + str(k)) + ","
#                         # allTimes += (str(i) + ":0" + str(j) + ":0" + str(k)) + ","
#                         # allTimes += (str(i) + ":0" + str(j) + ":0" + str(k)) + ","
#                         # allTimes += (str(i) + ":0" + str(j) + ":0" + str(k)) + ","
#                     else:
#                         allTimes += (str(i) + ":0" + str(j) + ":" + str(k)) + ","
#                         # allTimes += (str(i) + ":0" + str(j) + ":" + str(k)) + ","
#                         # allTimes += (str(i) + ":0" + str(j) + ":" + str(k)) + ","
#                         # allTimes += (str(i) + ":0" + str(j) + ":" + str(k)) + ","
#                         # allTimes += (str(i) + ":0" + str(j) + ":" + str(k)) + ","
#             else:
#                 for k in range(10,40):
#                     if k <= 9:
#                         allTimes += (str(i) + ":" + str(j) + ":0" + str(k)) + ","
#                         # allTimes += (str(i) + ":" + str(j) + ":0" + str(k)) + ","
#                         # allTimes += (str(i) + ":" + str(j) + ":0" + str(k)) + ","
#                         # allTimes += (str(i) + ":" + str(j) + ":0" + str(k)) + ","
#                         # allTimes += (str(i) + ":" + str(j) + ":0" + str(k)) + ","
#                     else:
#                         allTimes += (str(i) + ":" + str(j) + ":" + str(k)) + ","
#                         # allTimes += (str(i) + ":" + str(j) + ":" + str(k)) + ","
#                         # allTimes += (str(i) + ":" + str(j) + ":" + str(k)) + ","
#                         # allTimes += (str(i) + ":" + str(j) + ":" + str(k)) + ","
#                         # allTimes += (str(i) + ":" + str(j) + ":" + str(k)) + ","

