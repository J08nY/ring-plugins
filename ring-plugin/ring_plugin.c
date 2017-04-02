//plugin.c
#include<ring_plugin.h>
#include<plugin_service_lib.h>

class CustomPlugin : public RING_Plugin {
private:
	const RING_PluginAPI* api;
	
public:
	virtual RING_Plugin(const RING_PluginAPI *api) : api(api);
	
	virtual void destroy() {
		delete this;
	}
	
	virtual void onEvent(RING_Event* event) {
		//either use api directly
		api->invokeService(api, "call", nullptr);
		//or through plugin_service_lib
		RING_Call call(api);
		call.call();
	}
}

// plugin init function
RING_PLUGIN_CREATE_STATIC(plugin_create, api) {
	return new CustomPlugin(api);
}
