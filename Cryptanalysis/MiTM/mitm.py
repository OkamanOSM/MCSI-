from Crypto.Cipher import DES
from struct import pack

# Define parameters
a1 = 2
b1 = 3
a2 = 20
b2 = 53

# Convert integers to 4-byte big-endian format
a1_bytes = pack('>I', a1)
b1_bytes = pack('>I', b1)
a2_bytes = pack('>I', a2)
b2_bytes = pack('>I', b2)

# Concatenate to form 8-byte keys
key1 = a1_bytes + b1_bytes
key2 = a2_bytes + b2_bytes

# Initialize DES ciphers
enc1 = DES.new(key1, DES.MODE_ECB)
enc2 = DES.new(key2, DES.MODE_ECB)

# Define plaintext
plaintext = b'Hello world! :-)'

# Encrypt using Double DES
ciphertext = enc2.encrypt(enc1.encrypt(plaintext))

# Dictionary to store intermediate values
table = {}

# Create table for k1
print("Creating table for k1...")
for i in range(2**18):
    # Generate 8-byte key
    key = i.to_bytes(8, byteorder='big')
    test = DES.new(key, DES.MODE_ECB)
    # Encrypt plaintext to get 'middle' value
    table[test.encrypt(plaintext)] = key

# Notify about the completion of the first half of the table
print("First half of meet in the middle table created.")

# Search for k2
print("Searching for k2...")
for i in range(2**18):
    # Generate 8-byte key
    key = i.to_bytes(8, byteorder='big')
    test = DES.new(key, DES.MODE_ECB)
    # Decrypt ciphertext to get 'middle' value
    mid = test.decrypt(ciphertext)
    if mid in table:
        k1 = ' '.join([f'{byte:02x}' for byte in table[mid]])
        k2 = ' '.join([f'{byte:02x}' for byte in key])
        print(f"Match found!")
        print(f"k1: {k1}\nk2: {k2}")
        break
else:
    print("No match found in the meet in the middle attack.")
