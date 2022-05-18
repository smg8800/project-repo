import sqlite3
import pandas as pd


class user():
    def __init__(self,name):
        self.points = 0.0
        self.name = name
        self.sports = {}


def get_messages():
    connection = sqlite3.connect('/Users/sean/Coding/Projects/Scripts/Message Reading/chat.db')
    messages = pd.read_sql_query("select * from message order by date asc", connection)
    print(messages.loc[0])
    print(messages)
    print()
    user_ids = pd.read_sql_query("select * from handle", connection)
    print(user_ids.loc[0])
    print()
    chat_message_joins = pd.read_sql_query("select * from chat_message_join", connection)
    print(chat_message_joins.loc[0])
    print()
    messages.rename(columns={'ROWID' : 'message_id'}, inplace = True)
    user_ids.rename(columns={'id' : 'phone_number', 'ROWID': 'handle_id'}, inplace = True)
    temp = pd.merge(messages[['text', 'handle_id', 'date','is_sent', 'message_id']],  user_ids[['handle_id', 'phone_number']], on ='handle_id', how='left')
    r = pd.merge(temp, chat_message_joins[['chat_id', 'message_id']], on = 'message_id', how='left')
    print(r)
    print(r['chat_id'][1])
    # r = r.loc[r['chat_id'][1] == '86.0']
    print(r)
    # for i in range(100):
    #     print(i)
    #     if r.loc[i][6] != '86.0':
    #         r.drop(i)
    print("Done dropping")
    # print(r)
    return r
            


def increment_user(usr_id, activity, time, users):
    if usr_id == 0:
        usr = users[0]
    elif usr_id == 21:
        usr = users[1]
    elif usr_id == 22:
        usr = users[2]
    usr.points += time
    if activity in usr.sports:
        usr.sports[activity] += time
    else:
        usr.sports[activity] = time


def extract_activity(messages, chat_id, users):
    for i in range(len(messages)-1):
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
                        print("Workout found")
                        for i in range(1,len(words),2): # change start value to 2 if testing
                            print(usr)
                            print("Time: " + words[i])
                            print("Activity: " + words[i+1])
                            increment_user(usr, words[i+1], float(words[i]), users)
