import csv
import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np

generations = []
populations = []
individualsData = []
generationsno = 0

with open('blobs.csv', newline='') as csvfile:
    blobsreader = csv.reader(csvfile, delimiter=';', quotechar='|', quoting=csv.QUOTE_NONNUMERIC)
    row1 = next(blobsreader)
    generationsno = int(row1[0])
    for row in blobsreader:
        individualsData.append(row[2:-1])
        generations.append(row[0])
        populations.append(row[1])


font = {'color':  'white',
        'weight': 'normal',
        'size': 12,
        }

font2 = {'color':  'white',
        'weight': 'normal',
        'size': 24,
        }        

plt.style.use('ggplot')


fig = plt.figure(figsize=(5, 3), dpi=100, facecolor='#606060')
ax = fig.add_subplot(111)
bars = plt.bar(generations,populations,color=(0.2, 0.4, 0.6, 0.6))
plt.title("Populations", fontdict=font2)


ax.tick_params(labelcolor='white', labelsize='medium', width=3)


x_pos = [x for x in range(-1,generationsno+2)]
plt.xticks(x_pos, x_pos)
y_pos = np.arange(0, 60, 5).tolist()
plt.yticks(y_pos, y_pos)
#for bar in bars:
#    yval = bar.get_height()
#    plt.text(bar.get_x() + bar.get_width() / 4, yval/2, int(yval), fontdict=font)
plt.setp( ax.xaxis.get_majorticklabels(), rotation=90 )
#plt.show()
plt.savefig('populations.png', dpi=1000, bbox_inches='tight', facecolor=fig.get_facecolor(), edgecolor='none')