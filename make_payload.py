payload = b"A" * 136

with open("test.bin", "wb") as f:
    f.write(payload)

print("Created test.bin with 136 bytes.")
