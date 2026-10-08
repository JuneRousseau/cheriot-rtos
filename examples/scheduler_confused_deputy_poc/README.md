# Confused deputy with malicious scheduler --- Exit-replay PoC

Proof of concept of a confused deputy attack with a malicious scheduler.
The scheduler can replay an exited thread, and the switcher will restore the
trusted stack saved at the last context switch, even if it contains stale saved registers.
This is due to the fact that the switcher does not re-spill the registers in the trusted stack
on the thread exit path, and does not check the liveness of the sealed trusted stack when resumed.

The flag `--malicious-scheduler=y` compiles with a malicious scheduler,
`--malicious-scheduler=n` compiles if the CHERIoT-RTOS well-behaved scheduler.

This example showcases how this confused deputy attack breaks integrity / no capture:
a first thread starting in `client_thread` shares a local capability, pointing to a private buffer
of `client`'s compartment, with `service` for the time of call.
Another thread starting in `client_observer_thread` simply observes the content the private buffer
after the execution of `client_thread` terminates.

`service_incr` increment the content of the shared buffer. 
If a preemption happens just before the increment happens, the switcher saves the register file in
the trusted stack, including the local capability passed as argument by `client_thread`.
With a malicious scheduler replaying the thread after it existed, 
this register file will be restored (including the local capability passed as argument by `client_thread`),
and the increment will be executed twice, using the local capability restored from the trusted stack.

## Prerequisites

```sh
docker pull ghcr.io/cheriot-platform/devcontainer:latest
```

```sh
docker run --rm -it -v "$PWD":/work -w /work/examples/scheduler_confused_deputy_poc \
    ghcr.io/cheriot-platform/devcontainer:latest bash
```

## Current well-behaved scheduler

```sh
# inside the container
xmake config --sdk=/cheriot-tools/ --malicious-scheduler=n
xmake build
xmake run
```

Trace:
```
Client: share buf_local 0x80006b30 (v:1 0x80006b30-0x80006b34 l:0x4 o:0x0 p: - RWcgm- -- ---) with the service, which currently contains 0x0.
Service: service: incrementing the received buffer 0x80006b30 (v:1 0x80006b30-0x80006b34 l:0x4 o:0x0 p: - RWcgm- -- ---) ongoing...
Client: service has executed, buf not captured, buf currently contains 0x1.
Client: [service_incr] had been executed 1 times. Expected: 1 time.
Client: [service_incr] had been executed 1 times. Expected: 1 time.
Client: buf contains 0x1. Expected: 0 or 1.
```

## Malicious scheduler
```sh
# inside the container
xmake config --sdk=/cheriot-tools/ --malicious-scheduler=y
xmake build
xmake run
```

Trace:
```
Client: share buf_local 0x80006b80 (v:1 0x80006b80-0x80006b84 l:0x4 o:0x0 p: - RWcgm- -- ---) with the service, which currently contains 0x0.
Service: service: incrementing the received buffer 0x80006b80 (v:1 0x80006b80-0x80006b84 l:0x4 o:0x0 p: - RWcgm- -- ---) ongoing...
Client: service has executed, buf not captured, buf currently contains 0x1.
Client: [service_incr] had been executed 1 times. Expected: 1 time.
Client: [service_incr] had been executed 2 times. Expected: 1 time.
Client: buf contains 0x2. Expected: 0 or 1.
Client: [service_incr] wrote into [buf] after it returned from its once call in [client_thread].
SUCCESS
```
