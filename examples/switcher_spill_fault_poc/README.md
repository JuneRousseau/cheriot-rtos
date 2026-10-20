# Switcher spill fault after the first spill

Proof of concept: in cross-compartment call,
it is possible for the first register spill to pass, but for the others to fail.

It is possible when the current address of the stack capability goes 
past the top, just enough for the first spill to be in our stack frame,
but the next ones to be in the caller's stack frame.

`poc.cc` showcases this behaviour.

## Running

1. Build the example
``` sh
xmake config --sdk=/cheriot-tools
xmake
```

2. Generate the trace

```sh
/cheriot-tools/bin/cheriot_sim --trace build/cheriot/cheriot/release/switcher_spill_fault_poc > trace.txt
```

Search for the only CHERI `BoundsViolation` in the trace: 
it corresponds to the bounds violation in the cross-compartment call 
register spilling.

Here is an excerpt of the trace:


```
[101741] [M]: 0x80000288 (0x2A039163) bne t2, zero, 0x2a2
mem[X,0x8000028C] -> 0x3023
mem[X,0x8000028E] -> 0xFE81
[101742] [M]: 0x8000028C (0xFE813023) sc cfp, 0xfe0(sp)
MSHWM <- 0x80005440
tag[0x80005440] <- 0
mem[0x80005440] <- 0x0000000000000000
mem[X,0x80000290] -> 0x713D
[101743] [M]: 0x80000290 (0x713D) c.cincaddr16csp 0x3e0
x2 <- 0x80005440 (v:1 0x80005250-0x080005450 l:0x000000200 o:0x0 p:- RWcmgl -- ---)
mem[X,0x80000292] -> 0xE426
[101744] [M]: 0x80000292 (0xE426) c.cscsp cs1, 0x8
tag[0x80005448] <- 0
mem[0x80005448] <- 0x0000000000000000
mem[X,0x80000294] -> 0xE80E
[101745] [M]: 0x80000294 (0xE80E) c.cscsp cgp, 0x10
CHERI BoundsViolation Reg=c2/csp PC=0x80000294
```

The first register spilling `sc cfp, 0xfe0(sp)` goes through: it lands in our stack frame.
The second register spilling `c.cscsp cs1, 0x8` barely goes through as well: it still lands in our stack frame, at the limit.
The third register spilling `c.cscsp cgp, 0x10` traps: it lands in the caller's stack frame, past the capability top.
