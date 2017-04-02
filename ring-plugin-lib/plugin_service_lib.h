//plugin_service_lib.h
#include<ring_plugin.h>
#include<plugin_service_interface.h>

class RING_Call {
private:
	const RING_PluginAPI* api;
	std::unique_ptr<ring_call_t> c;

public:
	RING_Call(const RING_PluginAPI* api) : api(api) {
	}
	void call();
}



