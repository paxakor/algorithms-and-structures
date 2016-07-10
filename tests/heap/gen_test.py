from random import randint

f = open("test", 'w')
n = 100000
s = 0
for i in range(n):
  k = randint(0, 5)
  if k == 0 and s > 0:
    print("t", file = f)
  elif k < 4:
    s += 1
    t = randint(-40, 40)
    print("i", t, file = f)
  elif s > 0:
    print("e", file = f)
    s -= 1
