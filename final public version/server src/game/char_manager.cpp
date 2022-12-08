in
LPCHARACTER CHARACTER_MANAGER::SpawnMob(uint32_t dwVnum, long lMapIndex, long x, long y, long z, bool bSpawnMotion, int iRot, bool bShow)


before

	return (ch);
}

add
#ifdef ENABLE_ENTITY_PRELOADING
	//@Amun: or be specific, like if(ch->ispet, mount, whatever)
	if (!ch->IsPC() && !ch->IsGoto() && !ch->IsWarp() && !ch->IsDoor())
		SECTREE_MANAGER::Instance().ExtendPreloadedEntitiesMap(lMapIndex, pkMob->m_table.dwVnum);
#endif


like this

LPCHARACTER CHARACTER_MANAGER::SpawnMob(uint32_t dwVnum, long lMapIndex, long x, long y, long z, bool bSpawnMotion, int iRot, bool bShow)
{
	[...]

#ifdef ENABLE_ENTITY_PRELOADING
	//@Amun: or be specific, like if(ch->ispet, mount, whatever)
	if (!ch->IsPC() && !ch->IsGoto() && !ch->IsWarp() && !ch->IsDoor())
		SECTREE_MANAGER::Instance().ExtendPreloadedEntitiesMap(lMapIndex, pkMob->m_table.dwVnum);
#endif

	return (ch);
}