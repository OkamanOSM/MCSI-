from elliptic import EllipticCurve
from time import time
from algorithm import naive_bsgs, polhig_hellman

# Eliptik Eğri Parametrelerini Belirleyin
# p: prime modulus, a, b: eliptik eğri denklemi için parametreler
# Bu parametreleri verilen genel anahtar ve başlangıç eğrisi ile belirleyeceksiniz.

p = 7919  # Prime modulus
a = 2     # Eliptik eğrinin a parametresi
b = 3     # Eliptik eğrinin b parametresi

# Eliptik Eğriyi Oluşturun
curve = EllipticCurve(p, a, b)

# Başlangıç Noktası P ve Q

# Gruptaki Elemanların Sayısını (n) Belirleyin
n = 7889  # Gruptaki eleman sayısı

# Pohlig-Hellman Algoritmasını Kullanarak Ayrık Logaritmayı Hesaplayın
result = polhig_hellman(4023, 6036,4135,3169,curve, n)

print("Discrete Logarithm:", result)
