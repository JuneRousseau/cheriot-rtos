// Thread 1: client-service
// [client_thread] shares a local capability to [buf] with [service_incr].
// After the service returns, because the capability was local, it is not expected
// for [service] to have access to [buf] anymore.
// [service_incr] simply increment the counter in [buf]
//
// Thread 2: observer
// [client_observer_thread] just starts with sleeping for letting time to the client-thread thread
// to execute. We expect to see either 0 or 1:
// (0 at initialisation or 1 after [service_incr] executed).
// If we see another value, something wrong happened.

// Under a malicious scheduler:
// 



#include "service.h"
#include <cheri.hh>
#include <debug.hh>
#include <thread.h>
#include <timeout.hh>

using Debug = ConditionalDebug<true, "Client">;

/// The client's own buffer.
static uint32_t buf[1] = {0};

int __cheri_compartment("client") client_thread()
{
    // Copy the [buf] capability and strip its Global locality bit.
	CHERI::Capability buf_local{static_cast<uint32_t *>(buf)};
	buf_local.permissions() &= buf_local.permissions().without(CHERI::Permission::Global);

	Debug::log("share buf_local {} with the service, which currently contains {}.", buf_local, buf[0]);
	service_incr(buf_local);

	Debug::log("service has executed, buf not captured, buf currently contains {}.", buf[0]);

    // Display how many times the [service_incr] has been executed
	Debug::log("[service_incr] had been executed {} times. Expected: 1 time.", service_executions_count());

	// Thread 1 exits here.
	return 0;
}

int __cheri_compartment("client") client_observer_thread()
{
	// Sleep so the client exits before we inspect the buffer.
	Timeout t{20};
	thread_sleep(&t, ThreadSleepNoEarlyWake);

    // Display how many times the [service_incr] has been executed
	Debug::log("[service_incr] had been executed {} times. Expected: 1 time.", service_executions_count());

	uint32_t observed = buf[0];
	Debug::log("buf contains {}. Expected: 0 or 1.", observed);
	if (observed > 1)
	{
		Debug::log("[service_incr] wrote into [buf] after it returned from its once call in [client_thread].");
	}

	return 0;
}
