// find
stringList[0xfc] = "HEADER_GC_TIME_SYNC";

// add before(if you changed the index in packet.h, change it in here as well)
// won't break anything, but it's good for debugging
#ifdef ENABLE_ENTITY_PRELOADING
		stringList[211] = "HEADER_GC_PRELOAD_ENTITIES";
#endif