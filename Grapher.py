import csv
import matplotlib as mpl
import matplotlib.pyplot as plt
from matplotlib import animation
import numpy as np
import pandas as pd
import statistics as st

populations = []
df = pd.DataFrame(columns=['Generation','sd','sz','st'])
generationsno = 0

with open('blobs.csv', newline='') as csvfile:
    blobsreader = csv.reader(csvfile, delimiter=';', quotechar='|', quoting=csv.QUOTE_NONNUMERIC)
    generationsno = int(next(blobsreader)[0])
    for row in blobsreader:
        populations.append(row[1])
        speedArr = np.array(row[2:-1][0::3],dtype=float)
        sizeArr = np.array(row[2:-1][1::3],dtype=float)
        sightArr = np.array(row[2:-1][2::3],dtype=float)
        df_sub = pd.DataFrame({'Generation':row[0], 'sd':[speedArr], 'sz':[sizeArr], 'st':[sightArr]})
        df = df.append(df_sub)

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
title = ax.set_title('3D Test')

def update_graph(num):
    data=df[df['Generation']==num]
    graph._offsets3d = (data.sd[0], data.sz[0], data.st[0])
    title.set_text('Generation={}, Population={}'.format(num,populations[num]))

plt.ylim(0,5)
plt.xlim(0,5)
ax.set_zlim(0,5)
ax.set_xlabel('Speed')
ax.set_ylabel('Size')
ax.set_zlabel('Sight')

data=df[df['Generation']==0]
graph = ax.scatter(data.sd[0], data.sz[0], data.st[0])

ani = mpl.animation.FuncAnimation(fig, update_graph, generationsno+1, 
                               interval=200, blit=False)




simple_list=[]

for i in range(len(df)):
    avg_sd = st.fmean(df.sd.iloc[i])
    dev_sd = st.stdev(df.sd.iloc[i])

    avg_sz = st.fmean(df.sz.iloc[i])
    dev_sz = st.stdev(df.sz.iloc[i])

    avg_st = st.fmean(df.st.iloc[i])
    dev_st = st.stdev(df.st.iloc[i])

    simple_list.append([i,populations[i],avg_sd,dev_sd,avg_sz,dev_sz,avg_st,dev_st])
    
df2=pd.DataFrame(simple_list,columns=['Generation', 'Population', 'avg_sd', 'dev_sd', 'avg_sz', 'dev_sz', 'avg_st', 'dev_st'])

fig2 = plt.figure()
ax2 = plt.axes()
rolling_mean = df2.Population.rolling(window=5).mean()
ax2.bar(df2.Generation, df2.Population)
ax2.plot(df2.Generation, rolling_mean, label='SMA(5)', color='orange')
ax2.legend(loc='upper right')
ax2.set_xlabel("Generation")
ax2.set_ylabel("Population")

fig3 = plt.figure()
ax3 = plt.axes()

color = 'tab:red'
ax3.plot( 'Generation', 'avg_sd', data=df2, color=color, linewidth=2, label="Average speed")
ax3.plot( 'Generation', 'avg_sz', data=df2, color=color, linewidth=2, lineStyle = 'dotted', label="Average size")
ax3.plot( 'Generation', 'avg_st', data=df2, color=color, linewidth=2, lineStyle = 'dashed', label="Average sight")
ax3.set_ylabel('Parameters average', color=color)
ax3.tick_params(axis='y', labelcolor=color)
ax3.legend(loc='upper left')
ax3.set_xlabel("Generation")
ax4 = ax3.twinx()  # instantiate a second axes that shares the same x-axis

color = 'tab:blue'
ax4.set_ylabel('Parameters devation', color=color)  # we already handled the x-label with ax1
ax4.plot( 'Generation', 'dev_sd', data=df2, color=color, linewidth=2, label="Speed")
ax4.plot('Generation', 'dev_sz', data=df2, color=color, linewidth=2, lineStyle = 'dotted', label="Size")
ax4.plot( 'Generation', 'dev_st', data=df2, color=color, linewidth=2, lineStyle = 'dashed', label="Sight")
ax4.tick_params(axis='y', labelcolor=color)
ax4.legend(loc='lower right')

fig.tight_layout()  # otherwise the right y-label is slightly clipped
plt.show()