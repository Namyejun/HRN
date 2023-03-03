import plotly.figure_factory as ff
import pandas as pd
import os

pathdir = './data/gantt'
files = os.listdir(pathdir)

RED = 'rgb(255, 0, 0)'
GREEN = 'rgb(0, 255, 0)'
BLUE = 'rgb(0, 0, 255)'
BLACK = 'rgb(100, 100, 100)'
DARKGREEN = 'rgb(50, 100, 50)'
DARKBLUE = 'rgb(100, 50, 50)'
DARKRED = 'rgb(50, 50, 100)'

RIGHTBLUE = 'rgb(46,196,181)'
REDORANGE = 'rgb(232,54,30)'
RED = 'rgb(231,19,117)'
WHITE = 'rgb(230,255,235)'
BLACK = 'rgb(1,22,39)'
PURPLE = 'rgb(113,0,218)'
GREEN = 'rgb(153,241,158)'

color_preset = [RIGHTBLUE, REDORANGE, RED, WHITE, BLACK, PURPLE, GREEN]

colors = {'IDLE':'rgb(249,213,35)'}

for filename in files:
    if filename.rfind('txt') < 0:
        continue
    f = open(pathdir + '/' + filename,'r')
    data = f.read()
    f.close()

    #data = data.replace(' ',',')
    data = data.split()

    print(data)
    gantt_dict = []
    i = 0
    start = 0
    finish = 0
    timer = 0
    pid = ''

    process_num = 0

    for i in range(0,len(data)-1):
        # pid = data[i]
        if data[i] == '0':
            pid = 'IDLE'
            pidnum = int(data[i])
        else:
            pid = 'P' + data[i]
            pidnum = int(data[i])

        if data[i] != data[i+1]:
            finish = timer+1
            colors[pid] = color_preset[process_num % len(color_preset)]
            process_num += 1
            gantt_dict.append(dict(Task=pid, Start=start, Finish=finish, Resource=pidnum))
            start = finish

        if i == len(data)-2:
            finish = timer+2
            colors[pid] = color_preset[process_num % len(color_preset)]
            process_num += 1
            gantt_dict.append(dict(Task=pid, Start=start, Finish=finish, Resource=pidnum))

        timer+=1
        i+=1
    df = pd.DataFrame(gantt_dict)
    df.sort_values(by=['Resource'])
    print(df)
    print(colors)

    #fig = ff.create_gantt(df, colors=colors, index_col='Task', show_colorbar=True, group_tasks=True, bar_width=0.45)
    fig = ff.create_gantt(df, colors=colors, index_col='Task', group_tasks=True, bar_width=0.45)
    # fig.update_yaxes(autorange="reversed")
    fig.update_layout(title_text=filename, xaxis_type='linear')

    # update layout by process number
    layout_height = 1200
    fontsize = 10
    if process_num < 10:
        layout_height = 400 + process_num * 7
        fontsize = 20
    elif process_num < 50:
        layout_height = 400 + process_num * 9
        fontsize = 14
    else:
        layout_height = 400 + process_num * 11
        fontsize = 10

    fig.update_layout(
        height=layout_height,
        title=dict(
            font=dict(
                size=30,
                color='#000000'
            )
        ),
        font=dict(
            size=fontsize,
            color='#000000'
        )
    )
    fig.show()
    # print(gantt_dict)