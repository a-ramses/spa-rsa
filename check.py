import sys, random

try:
  while True:
  
    a = int(sys.stdin.readline(), base=16)
    b = int(sys.stdin.readline(), base=16)
    
    op = sys.stdin.readline().strip()
    
    c = int(sys.stdin.readline(), base=16)
    
    print()
    
    print(" a  = {0:064x}".format(a))
    print(" b  = {0:064x}".format(b))
    print(" c  = {0:064x}".format(c))
    
    if op == "a":
      res = (a+b) % (2**255 - 19)
    
    if op == "m":
      res = (a*b) % (2**255 - 19)

    # print(hex((a*b )% (2 ** 255 -19)))    

    print()
    print("res = {0:064x}".format(res))
    
    print()
    print("check", "add:" if op == 'a' else "mul:", c == res)
    print()

except ValueError: pass

