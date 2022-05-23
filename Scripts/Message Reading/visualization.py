import matplotlib.pyplot as plt
import numpy as np


def print_bar_chart(users):

    objs = (users[0].name, users[1].name, users[2].name)
    y_pos = np.arange(len(objs))
    performance = [users[0].points, users[1].points, users[2].points]

    plt.bar(y_pos, performance, align='center', alpha=0.5)
    plt.xticks(y_pos, objs)
    plt.ylabel('Hours of Activity')
    plt.title('Activity')

    plt.show()

def print_multibar_chart(users):
    l = len(users[0].sports)
    t = 0
    for i in range(1,3):
        if len(users[i].sports) > l:
            l = users[i].sports
            t = i
    

    fig, ax = plt.subplots()
    idx = np.arange(l)
    width = 0.1
    opacity = 0.8
    sports = sports_dict_to_list(users[t])
    sp1 = get_sports_vals(users[0],sports)
    sp2 = get_sports_vals(users[1],sports)
    sp3 = get_sports_vals(users[2],sports)
    print(sp1)
    print(sp2)
    print(sp3)

    rects1 = plt.bar(idx, sp1, width, alpha=opacity, color='b', label=users[0].name)
    rects2 = plt.bar(idx+width, sp2, width, alpha=opacity, color='r', label=users[1].name)
    rects3 = plt.bar(idx+2*width, sp3, width, alpha=opacity, color='g', label=users[2].name)

    plt.xlabel("Sports")
    plt.ylabel("Points")
    plt.title("Points by Sport per Person")
    plt.xticks(idx+width, sports )

    plt.legend()
    plt.tight_layout()
    plt.show()


def sports_dict_to_list(user):
    s = []
    for sport in user.sports:
        s.append(sport)
    return s

def get_sports_vals(user,sports):
    s = []
    for sport in sports:
        if sport in user.sports:
            s.append(user.sports[sport])
        else:
            s.append(0)
    return s