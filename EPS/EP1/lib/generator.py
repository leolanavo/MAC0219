import random
from numpy import random
import numpy as np

def randomValue():
  if random.random() < 0.3:
    return 0
  return np.random.normal(scale=15)


class Matrix:
  def __init__(self, N, M, randFn=randomValue):
    self.lines, self.cols = int(N), int(M)
    self.data = np.array([
      [randFn() for j in range(self.cols)] 
          for i in range(self.lines)
    ])

  def __str__(self):
    aux = [(i, j, self.data[i][j]) 
        for i in range(self.lines)
        for j in range(self.cols)
        if abs(self.data[i][j]) > 0]

    s = "{} {}\n".format(self.lines, self.cols)
    for el in aux:
      s += "{} {} {}\n".format(el[0], el[1], el[2])

    return s

m = Matrix(10, 20)

print(m)
