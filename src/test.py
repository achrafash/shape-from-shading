from PIL import Image
import numpy as np 
img = np.array(Image.open("dragon.jpeg"))

import csv

def csvWriter(fil_name, nparray):
  example = nparray.tolist()
  with open(fil_name+'.csv', 'w', newline='') as csvfile:
    writer = csv.writer(csvfile, delimiter=',')
    writer.writerows(example)

csvWriter("myfilename", img)

import ast

def csvReader(fil_name):
  with open(fil_name+'.csv', 'r') as f:
    reader = csv.reader(f)
    examples = list(reader)
    examples = np.array(examples)
  t1=[]
  for x in examples:
    t2=[]
    for y in x:
      z= ast.literal_eval(y)
      t2.append(np.array(z))
    t1.append(np.array(t2))
  ex = np.array(t1)
  return ex

backToNumpyArray = csvReader("myfilename")