import sys
sys.set_int_max_str_digits(10**9) # for large integer string conversion
sys.stdout.flush() # IO 交互
import math
print(math.comb(10, 5), math.factorial(10))
print(math.gcd(3, 6, 9), math.gcd(16, 12))
print(math.lcm(4, 6, 9), math.lcm(4, 8))
print(math.isqrt(5))
from decimal import*
getcontext().prec = 100 #default=28
a, b = Decimal(114), Decimal('514')
print(a/b,(a/b)**3)
import sys
input=lambda:sys.stdin.readline().rstrip() # 快读
print('haha', flush=True) # 交互用
sys.stdout.flush() # 或者用这个
