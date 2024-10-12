import random

for i in range(5):

  a = random.randint(0, 2**255 - 19 - 1)
  b = random.randint(0, 2**255 - 19 - 1)
  
  # a = 2**255 - 19 - 1
  # b = 2**255 - 19 - 1
  
  print("{0:064x}".format(a))
  print("{0:064x}".format(b))

  print(random.choice(["a", "m"]))

