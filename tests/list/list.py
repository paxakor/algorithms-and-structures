n = int(input())
l = []
for i in range(n):
  cmd = input()
  if cmd[0] == 'c':
    l = []
  elif cmd[0] == 's':
    print(len(l))
  elif cmd[0] == 'p':
    for x in l:
      print(x, end = ' ')
    print()
  else:
    x = int(cmd[2:])
    if cmd[0] == 'f':
      l = [x] + l
    elif cmd[0] == 'b':
      l = l + [x]
    elif cmd[0] == 'r':
      if x in l:
        l.remove(x)
