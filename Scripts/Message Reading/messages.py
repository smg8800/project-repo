import sqlite3
import numpy as np
import pandas as pd
# import time

class user():
    def __init__(self,name=' ', pts=0):
        self.points = pts
        self.name = name
        self.sports = dict.fromkeys(['gym','basketball','running','tennis','boxing','baseball','soccer'],0)


def get_messages():
    # start = time.time()
    connection = sqlite3.connect('/Users/sean/Coding/Projects/Scripts/Message Reading/chat.db')
    messages = pd.read_sql_query("select * from message", connection)
    user_ids = pd.read_sql_query("select * from handle", connection)
    chat_message_joins = pd.read_sql_query("select * from chat_message_join where chat_id = '86.0'", connection)

    messages.rename(columns={'ROWID' : 'message_id'}, inplace = True)
    user_ids.rename(columns={'id' : 'phone_number', 'ROWID': 'handle_id'}, inplace = True)
    temp = pd.merge(messages[['text', 'handle_id', 'date','is_sent', 'message_id']],  user_ids[['handle_id', 'phone_number']], on ='handle_id', how='left')

    frame = pd.merge(temp, chat_message_joins[['chat_id', 'message_id']], on = 'message_id', how='left')
    frame.drop(frame[frame['chat_id'] != 86.0].index, inplace=True)
    frame.index = np.arange(len(frame))
    # end = time.time()-start
    # print('Execution of get_messages in seconds: ' + str(end))
    return frame
            


def increment_user(usr_id, activity, time, users):
    if usr_id == 0:
        usr = users[0]
    elif usr_id == 23:
        usr = users[1]
    elif usr_id == 22:
        usr = users[2]
    usr.points += time
    if activity in usr.sports:
        usr.sports[activity] += time
    else:
        usr.sports[activity] = time


def extract_activity(messages, chat_id, users):
    for i in range(len(messages)):
        text = messages.loc[i][0]
        usr = messages.loc[i][1]
        chat = messages.loc[i][6]

        if chat == chat_id:
            if isinstance(text,str):
                words = text.split()
                if len(words) > 1:
                    if words[1] == 'test':
                        continue
                    if words[0].upper() == 'WORKOUT':
                        for i in range(1,len(words),2): # change start value to 2 if testing
                            if words[i].lower() in users[0].sports or words[i].lower() in users[1].sports or words[i].lower() in users[2].sports:
                                increment_user(usr, words[i].lower(), float(words[i+1]), users)
                            else:
                                increment_user(usr, words[i+1].lower(), float(words[i]), users)
