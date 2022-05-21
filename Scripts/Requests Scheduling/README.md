The purpose of this script is to perform a GET request at specific times of the day, indicated
by a string passed in in the format 'HOUR:MINUTE:SECOND' at the start of the day, with entries separated by a comma.
This program can be run in the terminal with the command 'python3 .../main.py --input_string "(sample timestamps)" --URL "(sampleurl.com)"',
or default paramaters can be typed in directly where the "url" and "string" variables are declared in the else statement
of main.py (lines 15-16). --input_string= An example list of times by default,
--input_string "02:11:55,9:58:20,13:45:09,13:45:09,13:45:09,17:22:00,17:22:00,18:35:05,18:35:05,19:45:10"
--url by default is "http://ifconfig.co".