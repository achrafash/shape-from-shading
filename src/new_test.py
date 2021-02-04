#coding:utf-8
import os
import csv

def create_csv(dirname):
    path = 'src' #change to your own image path
    name = os.listdir(path)
    with open (dirname+'.csv','w') as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(['data', 'label'])
        for n in name:
            if n[-4:] == '.jpg':
                print(n)
                writer.writerow(['./dataset/'+str(dirname) +'/'+ str(n),'./dataset/' + str(dirname) + 'label/' + str(n[:-4] + '.png')])
            else:
                pass

if __name__ == "__main__":
    create_csv('src')
