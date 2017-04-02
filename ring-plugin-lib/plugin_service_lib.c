//plugin_service_lib.c

#include<plugin_service_lib.h>
#include<plugin_service_interface.h>


RING_Call::call() {
	api->invokeService(api, "call", c);
}
