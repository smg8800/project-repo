from messages import *
from visualization import *


def main():
    ourchat = 86.0
    sean = user("Sean")
    aidan = user("Aidan")
    kody = user("Kody")
    users = [sean, aidan, kody]


    df_messages = get_messages()
    extract_activity(df_messages, ourchat, users)

    print_bar_chart(users)

    print(sean.points)
    print(aidan.points)
    print(kody.points)

main()