// Allocates one big heap chunk and asks adversary whether it overlaps its
// captured capability's address.

// Give a quota big enough to for the big allocation that we need
#define MALLOC_QUOTA (0x8000 + 256)

#include <cheri.hh>
#include <compartment.h>
#include <debug.hh>
#include <stdlib.h>

#include "adversary.h"

using Debug = ConditionalDebug<true, "Main">;

constexpr size_t BigAllocationSize = 0x8000; // 32 KiB

int __cheri_compartment("main") entry()
{
	void *p = malloc(BigAllocationSize);
	Debug::Invariant(p != nullptr, "big allocation failed");

	Debug::log("big allocation {} (requested {} bytes)", p, BigAllocationSize);

	check_overlap(CHERI::Capability{p}.base(), BigAllocationSize);

	return 0;
}
