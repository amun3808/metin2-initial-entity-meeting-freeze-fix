# find
self.__SetProgress(0)

# add this before
		if app.ENABLE_ENTITY_PRELOADING:
			self.loadStepList.append((100, ui.__mem_func__(self.__LoadInitialEntities)))


# find
	def __LoadNPC(self):
		playerSettingModule.LoadGameData("NPC")


# add this after
	if app.ENABLE_ENTITY_PRELOADING:
		def __LoadInitialEntities(self):
			playerSettingModule.LoadGameData("INITIAL_ENTITIES")
