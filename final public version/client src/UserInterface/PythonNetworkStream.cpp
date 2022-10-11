// find
		Set(HEADER_GC_DRAGON_SOUL_REFINE, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCDragonSoulRefine), STATIC_SIZE_PACKET));

// add after
#ifdef ENABLE_ENTITY_PRELOADING
		Set(HEADER_GC_PRELOAD_ENTITIES, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCPreloadEntities), DYNAMIC_SIZE_PACKET));
#endif
