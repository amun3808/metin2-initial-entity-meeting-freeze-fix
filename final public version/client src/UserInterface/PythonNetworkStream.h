// find
bool RecvWarpPacket();

// add
#ifdef ENABLE_ENTITY_PRELOADING
	bool RecvPreloadEntitiesPacket();
#endif