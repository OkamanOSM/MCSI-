def int_to_bytes(value, length):
    return value.to_bytes(length, byteorder='big')

# Eğri 1 parametreleri
a1 = 2
b1 = 3

# Eğri 2 parametreleri
a2 = 20
b2 = 53

# Bayt uzunluğu (örneğin, 4 bayt = 32 bit)
byte_length = 4

# Eğri 1 parametrelerini bayt dizisine dönüştürme
a1_bytes = int_to_bytes(a1, byte_length)
b1_bytes = int_to_bytes(b1, byte_length)

# Eğri 2 parametrelerini bayt dizisine dönüştürme
a2_bytes = int_to_bytes(a2, byte_length)
b2_bytes = int_to_bytes(b2, byte_length)

# Bayt dizilerini ekrana yazdırma
print("Eğri 1 - a parametresi bayt dizisi:", a1_bytes)
print("Eğri 1 - b parametresi bayt dizisi:", b1_bytes)
print("Eğri 2 - a parametresi bayt dizisi:", a2_bytes)
print("Eğri 2 - b parametresi bayt dizisi:", b2_bytes)
