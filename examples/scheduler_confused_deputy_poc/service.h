// Copyright CHERIoT Contributors.
// SPDX-License-Identifier: MIT

#include <compartment.h>
#include <stdint.h>

int __cheri_compartment("service") service_incr(uint32_t *buf);

int __cheri_compartment("service") service_executions_count(void);
