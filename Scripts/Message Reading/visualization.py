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