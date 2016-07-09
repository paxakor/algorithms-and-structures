from random import randint

f = open("test", 'w')
n = 1000
print(n, file = f)
for i in range(n):
  k = randint(0, 400)
  if k == 0:
    print("c", file = f)
  elif k < 5:
    print("s", file = f)
  elif k < 10:
    print("p", file = f)
  else:
    t = randint(-40, 40)
    if k < 220:
      print("f", t, file = f)
    elif k < 340:
      print("b", t, file = f)
    else:
      print("r", t, file = f)
