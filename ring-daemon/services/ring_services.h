

class CallService {
public:
	CallService(const PluginManager& manager) {
		manager.registerService("call", &call);
	}
	void call(void *c);
}
