// find
		case HEADER_GC_DRAGON_SOUL_REFINE:
			ret = RecvDragonSoulRefine();
			break;

// add after(or before, whatever)
#ifdef ENABLE_ENTITY_PRELOADING
		case HEADER_GC_PRELOAD_ENTITIES:
			ret = RecvPreloadEntitiesPacket();
			break;
#endif

// add at the end of the file
#ifdef ENABLE_ENTITY_PRELOADING
bool CPythonNetworkStream::RecvPreloadEntitiesPacket()
{
	TPacketGCPreloadEntities pack;
	if (!Recv(sizeof(pack), &pack))
		return false;

	assert(int32_t(pack.size) - sizeof(pack) == pack.count * sizeof(uint32_t) && "HEADER_GC_PRELOAD_ENTITIES");

	CRaceData* pRaceData = nullptr;
	CRaceManager& rkRaceMgr = CRaceManager::Instance();
	for (int32_t i = 0; i < pack.count; i++)
	{
		uint32_t dwEntityRace;
		if (!Recv(sizeof(uint32_t), &dwEntityRace))
			return false;

#ifdef _DEBUG
		 TraceError("Preloading %d", dwEntityRace);
#endif
		 if (!rkRaceMgr.GetRaceDataPointer(dwEntityRace, &pRaceData))
			 TraceError("Failed to preload race %d", dwEntityRace);
	}

	return true;
}
#endif