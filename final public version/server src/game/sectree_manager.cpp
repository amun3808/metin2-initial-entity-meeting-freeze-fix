// find
			pkMapSectree->Build();

// add this after
#ifdef ENABLE_ENTITY_PRELOADING
			GeneratePreloadedEntitiesMap(iIndex, pkMapSectree);
#endif


// add this at the end of the file
#ifdef ENABLE_ENTITY_PRELOADING
void SECTREE_MANAGER::GeneratePreloadedEntitiesMap(int32_t mapIndex, LPSECTREE_MAP lpMapSectree)
{
	if (m_preloadedEntities.find(mapIndex) == m_preloadedEntities.end())
	{
		m_preloadedEntities.insert({ mapIndex, {} });

		auto lmbd = [&mapIndex, this](LPENTITY ent) {
			this->m_preloadedEntities.at(mapIndex).emplace((((LPCHARACTER)ent)->GetRaceNum()));
		};
		lpMapSectree->for_each(lmbd);

		// log unique races
		for(int32_t i: m_preloadedEntities.at(mapIndex))
			sys_log(0, "ENTITY_PRELOADING: [map: %d], [entity race: %d]", mapIndex, i);
	}
}

void SECTREE_MANAGER::ExtendPreloadedEntitiesMap(int32_t mapIndex, uint32_t mob_race)
{
	auto it = m_preloadedEntities.find(mapIndex);
	if (it == m_preloadedEntities.end())// don't create new maps if they're not available from the beginning
		return;

	if ((it->second.emplace(mob_race)).second)
		sys_log(0, "ENTITY_PRELOADING: extended [map: %d], with [entity race: %d]", mapIndex, mob_race);
}

void SECTREE_MANAGER::SendPreloadEntitiesPacket(LPCHARACTER ch)
{
	LPDESC d = ch->GetDesc();
	if (!d)
		return;

	long lMapIndex = ch->GetMapIndex();

	if (m_preloadedEntities.find(lMapIndex) == m_preloadedEntities.end())
		return;
		
	std::unordered_set<uint32_t>& s = m_preloadedEntities.at(lMapIndex);

	if (s.empty())
		return;

	{
		TEMP_BUFFER buf;
		TPacketGCPreloadEntities pack{};
		pack.header = HEADER_GC_PRELOAD_ENTITIES;
		pack.count = s.size();

		for (const auto& it : s)
			buf.write(&it, sizeof(uint32_t));

		pack.size = sizeof(pack) + buf.size();

		d->BufferedPacket(&pack, sizeof(TPacketGCPreloadEntities));
		d->Packet(buf.read_peek(), buf.size());
	}
}
#endif