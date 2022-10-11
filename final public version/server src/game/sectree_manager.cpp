// find
			pkMapSectree->Build();

// add this after
#ifdef ENABLE_ENTITY_PRELOADING
			ExtendPreloadedEntitiesMap(iIndex, pkMapSectree);
#endif


// add this at the end of the file
#ifdef ENABLE_ENTITY_PRELOADING
void SECTREE_MANAGER::ExtendPreloadedEntitiesMap(int32_t mapIndex, LPSECTREE_MAP lpMapSectree)
{
	if (m_preloadedEntities.find(mapIndex) == m_preloadedEntities.end())
	{
		m_preloadedEntities.insert({ mapIndex, {} });

		auto lmbd = [&mapIndex, this](LPENTITY ent) {
			this->m_preloadedEntities.at(mapIndex).push_back(((LPCHARACTER)ent)->GetRaceNum());
		};
		lpMapSectree->for_each(lmbd);

		{
			std::unordered_set<int32_t> s;
			for (int32_t i : m_preloadedEntities.at(mapIndex))
				s.insert(i);

			m_preloadedEntities.at(mapIndex).assign(s.begin(), s.end());
		}
	}
}

void SECTREE_MANAGER::SendPreloadEntitiesPacket(LPCHARACTER ch)
{
	LPDESC d = ch->GetDesc();
	if (!d)
		return;

	long lMapIndex = ch->GetMapIndex();

	if (m_preloadedEntities.find(lMapIndex) == m_preloadedEntities.end())
		return;
		
	std::vector<uint32_t> &vec = m_preloadedEntities.at(lMapIndex);
	if (!vec.size())
		return;

	{
		TEMP_BUFFER buf;
		TPacketGCPreloadEntities pack{};
		pack.header = HEADER_GC_PRELOAD_ENTITIES;
		pack.count = vec.size();

		for (int32_t i = 0; i != vec.size(); i++)
			buf.write(&(vec.at(i)), sizeof(uint32_t));

		pack.size = sizeof(pack) + buf.size();

		d->BufferedPacket(&pack, sizeof(TPacketGCPreloadEntities));
		d->Packet(buf.read_peek(), buf.size());
	}
}
#endif
