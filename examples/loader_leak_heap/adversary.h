#pragma once

#include <compartment.h>
#include <stddef.h>

/// Checks whether the capability captured by adversary's initialiser falls
/// within [base, base + length), and prints the result.
void __cheri_compartment("adversary")
  check_overlap(ptraddr_t base, size_t length);
