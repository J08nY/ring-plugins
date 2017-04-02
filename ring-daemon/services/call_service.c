#include<plugin_service_interface.h>
#include<ring_services.h>

void CallService::call(void *c) {
	auto call = reinterpret_cast<ring_call_t*>(c);
	// do whatever to actually make the call with the data from ring_call_t
}
