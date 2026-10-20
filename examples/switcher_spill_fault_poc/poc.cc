#include <compartment.h>

__cheri_callback void callee() {}

// We call callee(), but we move the stack pointer past the top address (ie. in the caller's stack frame),
// but just enough so that so that the first spill
// ` csc               cs0, (SPILL_SLOT_cs0-SPILL_SLOT_SIZE)(csp) `
// of the switcher does not trap (it lands in our stack frame),
// but moving the address back lands past the top address
// (ie. we are the caller's stack frame)
void __cheri_compartment("poc") entry()
{
	register auto fn asm("ct1") = callee;
	__asm__ volatile(
	  "cgettop   t2, csp\n"
	  "addi      t2, t2, 16\n"
	  "csetaddr  csp, csp, t2\n" // csp = top + 16: still tagged and 16-aligned
                                 // so the alignment check in .Lswitch_csp_check passes
	  "1:\n"
	  "auipcc    ct2, %%cheriot_compartment_hi(.compartment_switcher)\n"
	  "clc       ct2, %%cheriot_compartment_lo_i(1b)(ct2)\n"
	  "cjalr     ct2\n" ::"C"(fn));
    return;
}
