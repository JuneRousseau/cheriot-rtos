# Dumping the scheduler's initial stack

Debug log of the execution:

``` text
Running file scheduler_boot_stack.
ELF Entry @ 0x80000000
tohost located at 0x800077c8
Scheduler: scheduler stack 0x80007490 (v:1 0x800071a0-0x80007560 l:0x3c0 o:0x0 p: - RWcgml -- ---)
Scheduler: dump of the snapshot (ie. the scheduler's stack content, handed out by the loader):
Scheduler: 	[0x80007558] 0x800000aa (v:1 0x0-0xffffffff l:0xffffffff o:0x4 p: G R-cgm- Xa ---)
Scheduler: 	[0x80007550] 0x24 (v:0 0x0-0x0 l:0x0 o:0x0 p: - ------ -- ---)
Scheduler: 	[0x80007548] 0x800003a8 (v:0 0x80000248-0x800007d0 l:0x588 o:0x4 p: - R-cgm- Xa ---)
Scheduler: 	[0x80007540] 0x0 (v:0 0x0-0x0 l:0x0 o:0x0 p: - ------ -- ---)
Scheduler: 	[0x80007538] 0x0 (v:0 0x0-0x0 l:0x0 o:0x0 p: - ------ -- ---)
Scheduler: 	[0x80007530] 0x80006de8 (v:0 0x80006de8-0x80006df0 l:0x8 o:0x0 p: - RWcgml -- ---)
Scheduler: 	[0x80007528] 0x800085de (v:0 0x800085de-0x80008656 l:0x78 o:0x0 p: - R----- -- ---)
Scheduler: 	[0x80007520] 0x8000a93c (v:1 0x8000a93c-0x8000a96c l:0x30 o:0x0 p: G R-cgm- Xa ---)
Scheduler: 	[0x80007518] 0x800077c0 (v:1 0x800077c0-0x80008498 l:0xcd8 o:0x0 p: G RWcgm- -- ---)
Scheduler: 	[0x80007510] 0x8000a9b0 (v:0 0x8000a9b0-0x8000a9d8 l:0x28 o:0x0 p: - RWcgml -- ---)
Scheduler: 	[0x80007508] 0x800085c8 (v:0 0x800085c8-0x80008788 l:0x1c0 o:0x0 p: - R----- -- ---)
Scheduler: 	[0x80007500] 0x800084e8 (v:0 0x800084e8-0x800084f8 l:0x10 o:0x0 p: - -Wc--- -- ---)
Scheduler: 	[0x800074f8] 0x80007580 (v:0 0x80007580-0x80007590 l:0x10 o:0x0 p: - RWcgml -- ---)
Scheduler: 	[0x800074f0] 0x800003a8 (v:0 0x80000248-0x800007d0 l:0x588 o:0x4 p: - R-cgm- Xa ---)
Scheduler: 	[0x800074e8] 0x80008664 (v:0 0x80008664-0x80008788 l:0x124 o:0x0 p: - R----- -- ---)
Scheduler: 	[0x800074e0] 0x80007580 (v:0 0x80007580-0x80007590 l:0x10 o:0x0 p: - RWcgml -- ---)
Scheduler: 	[0x800074d8] 0xa (v:1 0xa-0xb l:0x1 o:0x0 p: G ------ -- SU-)
Scheduler: 	^ We found the trusted stack unsealing capability, let's keep it to reuse later. ^
Scheduler: 	[0x800074d0] 0x1800 (v:0 0x1778-0x1838 l:0xc0 o:0x0 p: - RWcgml -- ---)
Scheduler: 	[0x800074c8] 0xe01 (v:0 0xde8-0xdf0 l:0x8 o:0x0 p: - RWcgml -- ---)
Scheduler: 	[0x800074c0] 0x80007490 (v:0 0x800071a0-0x80007560 l:0x3c0 o:0x0 p: - RWcgml -- ---)
Scheduler: 	[0x800074b8] 0x8000a9a0 (v:0 0x8000a9a0-0x8000a9e8 l:0x48 o:0x0 p: - RWcgml -- ---)
Scheduler: 	[0x800074b0] 0x800085fc (v:0 0x800085fc-0x8000861a l:0x1e o:0x0 p: - R----- -- ---)
Scheduler: 	[0x800074a8] 0x80000270 (v:0 0x80000248-0x800007d0 l:0x588 o:0x2 p: - R-cgm- Xa ---)
Scheduler: 	[0x800074a0] 0x80008774 (v:0 0x80008774-0x80008788 l:0x14 o:0x0 p: - R----- -- ---)
Scheduler: 	[0x80007498] 0x80007530 (v:0 0x80007530-0x80007538 l:0x8 o:0x0 p: - RWcgml -- ---)
Scheduler: 	[0x80007490] 0x80007560 (v:0 0x80007560-0x80007580 l:0x20 o:0x0 p: - RWcgml -- ---)
Scheduler: 	=========================================================================================
Scheduler: 	========== sp 0x80007490 ========== (live frames below, uncleared dead frame above) =====
Scheduler: 	=========================================================================================
Scheduler: 	[0x80007488] 0x8000a9a8 (v:0 0x8000a9a0-0x8000a9e8 l:0x48 o:0x0 p: - RWcgml -- ---)
Scheduler: 	[0x80007480] 0x0 (v:0 0x0-0x0 l:0x0 o:0x0 p: - ------ -- ---)
[...]
Scheduler: 	[0x800071a0] 0x0 (v:0 0x0-0x0 l:0x0 o:0x0 p: - ------ -- ---)
Scheduler: Created thread for trusted stack 0x800070d0 (v:1 0x800070d0-0x800071a0 l:0xd0 o:0xa p: G RWcgml -- ---)
Scheduler: exception_entry: 0x80007000 (v:1 0x80007000-0x800070d0 l:0xd0 o:0xa p: G RWcgml -- ---) 	(sealed trusted stack handle)
Scheduler: exception_entry: 0xa (v:1 0xa-0xb l:0x1 o:0x0 p: G ------ -- SU-) 				(trusted stack sealing key)
Scheduler: exception_entry: 0x80007000 (v:1 0x80007000-0x800070d0 l:0xd0 o:0x0 p: G RWcgml -- ---) 	(UNSEALED trusted stack handle)
Scheduler: exception_entry: 0x800070d0 (v:1 0x800070d0-0x800071a0 l:0xd0 o:0xa p: G RWcgml -- ---) 	(sealed trusted stack handle)
Scheduler: exception_entry: 0xa (v:1 0xa-0xb l:0x1 o:0x0 p: G ------ -- SU-) 				(trusted stack sealing key)
Scheduler: exception_entry: 0x800070d0 (v:1 0x800070d0-0x800071a0 l:0xd0 o:0x0 p: G RWcgml -- ---) 	(UNSEALED trusted stack handle)
Scheduler: Thread exited, 0 threads remaining
SUCCESS
```

It shows that the dead frames are not cleared properly at boot, and that the trusted stack unsealing
key is left in the initial scheduler's stack, which a malicious scheduler can store and re-use later.
