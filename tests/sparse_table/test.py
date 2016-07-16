from random import randint

f = open('test', 'w')
a = open('ans', 'w')
n = 1000
print(n, file = f)
v = list()
for i in range(n):
  x = randint(-100, 100)
  v.append(x)
  print(x, file = f)
print(file = f)

# m = randint(10, 1000)
m = 1000000
print(m, file = f)
for i in range(m):
  l = randint(0, n - 1)
  r = randint(0, n - 1)
  l, r = min(l, r), max(l, r)
  print(l, r, file = f)
  print(l, r, file = a)
  print(min(v[l:r+1]), file = a)
