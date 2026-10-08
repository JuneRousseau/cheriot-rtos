#include "service.h"
#include <debug.hh>
#include <stdlib.h> // for yield()

using Debug = ConditionalDebug<true, "Service">;

// How many times [service_incr] has been executed
int serviceCount = 0;

int __cheri_compartment("service") service_executions_count(void)
{
	return serviceCount;
}

int __cheri_compartment("service") service_incr(uint32_t *buf)
{
	Debug::log("service: incrementing the received buffer {} ongoing...", buf);
    
    // Force preemption here to make it deterministic
	yield();

	buf[0] = buf[0]+1;

    // update the counter
	serviceCount += 1;
	return 0;
}
