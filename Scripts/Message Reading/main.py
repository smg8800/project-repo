from messages import *
from visualization import *
import time


def main():
    # start = time.time()
    ourchat = 86.0
    sean = user("Sean",1)
    aidan = user("Aidan",0)
    kody = user("Kody",0.25)
    users = [sean, aidan, kody]


    df_messages = get_messages()
    extract_activity(df_messages, ourchat, users)

    print_bar_chart(users)
    print_multibar_chart(users)

    for usr in users:
        print(usr.name + " has " + str(usr.points) + " points.")
    
    # end = time.time()-start
    # print('Execution time in seconds: ' + str(end))

main()