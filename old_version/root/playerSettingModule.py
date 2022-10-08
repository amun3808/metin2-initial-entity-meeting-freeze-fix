# if you don't have 'background' in imports, add this
if app.ENABLE_ENTITY_PRELOADING:
	import background

# find
	loadGameDataDict={
	...
	}

# add this before
if app.ENABLE_ENTITY_PRELOADING:
	def BuildEntitiesPreloadingDict():
		try:
			lines = open("preload.txt", "r").readlines()
		except:
			import exception
			exception.Abort("Failed to read preload.txt")

		for line in lines:
			line = line.strip()
			if not line:
				continue

			try:
				[_, curMap] = line.split(":")
				constInfo.PRELOADING_ENTITIES_DICT[curMap.strip()] = []

				continue
			except:
				pass

			if curMap:
				stripped = line.strip()
				if stripped:
					constInfo.PRELOADING_ENTITIES_DICT[curMap].append(int(stripped))

	def PreloadEntities(mapName):
		for entity in constInfo.PRELOADING_ENTITIES_DICT[mapName]:
			chr.PreloadEntity(entity)

	def __LoadInitialEntities():
		if background.GetCurrentMapName() not in constInfo.PRELOADING_ENTITIES_DICT.keys():
			BuildEntitiesPreloadingDict()

		PreloadEntities(background.GetCurrentMapName())


# and add this after
if app.ENABLE_ENTITY_PRELOADING:
	loadGameDataDict["INITIAL_ENTITIES"] = __LoadInitialEntities