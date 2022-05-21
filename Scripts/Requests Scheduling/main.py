from msg_schedule import *
import sys

# runs the msg_schedule functions;
# takes in 2 inputs, url and input_string
# if no inputs, use default values listed below
# loop forever sending requests at appropriate times

def main():
    args = sys.argv[1:]
    if len(args) > 0: # look for input args
        input_string = args[1]
        url = args[3]
    else: # use default args
        input_string = "02:11:55,9:58:20,13:45:09,13:45:09,13:45:09,17:22:00,17:22:00,18:35:05,18:35:05,19:45:10"
        url = "http://ifconfig.co" 
 
    timestamps = split_times(input_string, ',') 
    while(True): # loop 
        send_requests(timestamps, url)

main()