from sys import argv
import random
from numpy import random
import numpy as np

def randomValue():
  if random.random() < 0.3:
    return 0
  return np.random.normal(scale=15)

def printMatrix(m, l, c, file=None):
  aux = [(i, j, m[i][j]) 
          for i in range(l) 
          for j in range(c) 
          if abs(m[i][j]) > 0]
 
  if file is None:
    print(l, c)
    for el in aux:
      print(el[0], el[1], el[2])
  else:
    file.write("{} {}\n".format(l, c))
    for el in aux:
      file.write("{} {} {}\n".format(el[0], el[1], el[2]))


if __name__ == '__main__':
  M, P, N = [int(float(arg)) for arg in argv[1:4]]
  fileA, fileB, fileC = argv[4:7]

  ## compute and print
  a = np.array([[randomValue() for j in range(P)] for i in range(M)])

  with open(fileA, 'w+') as f:
    printMatrix(a, M, P, f)
  f.closed


  ## compute and print
  b = np.array([[randomValue() for j in range(N)] for i in range(P)])

  with open(fileB, 'w+') as f:
    printMatrix(b, P, N, f)
  f.closed


  ## compute and print
  c = np.matmul(a, b)

  with open(fileC, 'w+') as f:
    printMatrix(c, M, N, f)
  f.closed

