import math

points = [
  (-10, -5),
  (-6, 6),
  (-3, 12),
  (2, 12),
  (3, 17),
  (3, 4),
  (4, 6),
  (7, 13),
  (8, 4),
  (13, 7)
]

cmPoints = [(float(x)/10, float(y)/10) for x, y in points]

N = 10

X_o = math.fsum([x for x, y in cmPoints]) / N
Y_o = math.fsum([y for x, y in cmPoints]) / N

M1 = math.fsum(
      [ pow(x - X_o, 2) for x, y in cmPoints ]
    ) / N

M2 = math.fsum(
      [ (x - X_o) * (y - Y_o) for x, y in cmPoints ]
    ) / N

M3 = math.fsum(
      [ (y - Y_o) * (x - X_o) for x, y in cmPoints ]
    ) / N

M4 = math.fsum(
      [ pow(y - Y_o, 2) for x, y in cmPoints ]
    ) / N


matrix = [
  [M1, M2],
  [M3, M4]
]

print matrix
