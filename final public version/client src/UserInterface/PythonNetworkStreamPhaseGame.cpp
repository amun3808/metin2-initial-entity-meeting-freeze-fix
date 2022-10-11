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

	/*
	@Amun:
		We can't instantiate the entities here, because the path to their files isn't registered yet.
		The path is registered after calling "__LoadGameNPC()" in root(playerSettingModule),
			so we'll save the ids to CPythonCharacterManager::m_vecPreloadedEntities and
			call CPythonCharacterManager::PreloadEntities() from CPythonNetworkStream::StartGame(),
			to load them right before we show the "world"(before setting m_isStartGame to TRUE).

		My initial idea was to create a new game phase, but ..yeah, fuck that. 
	*/

	std::vector<uint32_t>* entVec = CPythonCharacterManager::Instance().GetPreloadedEntitiesVectorPtr();
	entVec->clear();

	for (int32_t i = 0; i < pack.count; i++)
	{
		uint32_t dwEntityRace;
		if (!Recv(sizeof(uint32_t), &dwEntityRace))
			return false;

		entVec->emplace_back(dwEntityRace);
	}

	return true;
}
#endif
