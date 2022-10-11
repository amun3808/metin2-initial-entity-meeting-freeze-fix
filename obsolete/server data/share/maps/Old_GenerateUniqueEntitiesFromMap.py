import os

rectList = []


# boss.txt
# npc.txt
# regen.txt
# stone.txt
mapFiles = ["boss.txt", "npc.txt", "regen.txt", "stone.txt"]
# group, mob, regen
valid = ["g", "m", "r"]
mapName = ""

"""
mapData = {
    mapName : {
        g : [],
        m : [],
        r : [],
    }
}
"""
mapData = {}

def ParseMaps():
	for path in open("index"):
		if path[-1] == os.linesep:
			path = path[:-1]

		try:
			[_, mapName] = path.split()
		except:
			continue

		if not mapName:
			continue

		# initialize mapData dict
		mapData[mapName] = {}
		mapData[mapName]["g"] = []
		mapData[mapName]["m"] = []
		mapData[mapName]["r"] = []
		# print(mapName)

		for mapFile in mapFiles:
			lines = 0
			try:
				lines = open( mapName + "/" + mapFile)
			except:
				continue

			for line in lines:
				tokens = line.split()

				if not len(tokens):
					continue

				# tokens[0] is the marker(g,m,r)
				if tokens[0] in valid:
					try:
						stripped = tokens[len(tokens) - 1].strip()
						if stripped:
							mapData[mapName][tokens[0]].append(int(stripped))
							# print(stripped)
					except:
						pass

# the dict is now complete, let's parse the groups
"""
groups = {
	groupVnum: [leader, ...members]
}
"""
groups = {}
# g = group.txt
def ParseGroup():
	currentGroup = {"Members": [], "Vnum": 0}
	for line in open("group_old.txt"):
		line = line.strip()
		if not line:
			continue

		# when the group ends
		if line == "}":
			# append the currentGroup to our global dict
			groups[currentGroup["Vnum"]] = []
			# members
			for member in currentGroup["Members"]:
				groups[currentGroup["Vnum"]].append(member)
			# clear the currentGroup
			currentGroup = {"Members": [], "Vnum": 0}

		try:
			s = line.split()
			if len(s):
				tok = s[0].strip()
		except:
			pass
		
		if not tok:
			continue

		if tok == "Vnum":
			stripped = s[1].strip()
			if stripped:
				currentGroup["Vnum"] = int(stripped)
		#leader and members have the same structure [tok, name, vnum]
		elif len(s) == 3:
			stripped = s[2].strip()
			if stripped:
				currentGroup["Members"].append(int(stripped))

#
"""
regenGroups = {
	regenGroupVnum: [mobsVnum]
}
"""
regenGroups = {}
# r = group_group.txt
def ParseGroupGroup():
	currentGroup = {"Members": [], "Vnum": 0}
	for line in open("group_group_old.txt"):
		line = line.strip()
		if not line:
			continue

		# when the group ends
		if line == "}":
			# append the currentGroup to our global dict
			# instantiate regenGroup Vnum:[]
			regenGroups[currentGroup["Vnum"]] = []
			# members
			for member in currentGroup["Members"]:
				regenGroups[currentGroup["Vnum"]].append(member)
			# clear the currentGroup
			currentGroup = {"Members":[], "Vnum":0}

		try:
			arr = line.split()
			if not len(arr):
				continue

			# idx is always the second item
			idx = arr[1].strip()
			if not idx:
				continue

			# Vnum	x
			if arr[0] == "Vnum":
				currentGroup["Vnum"] = int(idx)
			# idx	vnum	count
			elif len(arr) == 3:
				currentGroup["Members"].append(int(idx))
		except:
			pass
			
#
def ReconstructMapDataWithUniqueIds():
	for curMap in mapData.keys():
		# groups
		mapGroups = mapData[curMap]["g"]
		for group in mapGroups:
			if group not in groups:
				continue

			for g in groups[group]:
				# add all mobs from group to mobs array
				mapData[curMap]["m"].append(int(g))

		# regen groups
		mapRegenGroups = mapData[curMap]["r"]
		for group in mapRegenGroups:
			if group not in regenGroups:
				continue
			
			for rg in regenGroups[group]:
				# add all mobs from regen group to mobs array
				mapData[curMap]["m"].append(int(rg))
		# remove duplicates from mobs array
		mapData[curMap]["m"] = list(dict.fromkeys(mapData[curMap]["m"]))
		# sort the mobs
		mapData[curMap]["m"].sort()

#
preloadingLines = []
def ConstructPreloadingDataFile():
	lines = []
	for curMap in mapData.keys():
		lines.append("Map: %s\n" % curMap)
		for mob in mapData[curMap]["m"]:
			lines.append("%d\n" % mob)

		lines.append("\n\n")#separate the maps

	f = open("preload.txt", "w+")
	f.writelines(lines)
	f.close()
#
ParseMaps()
ParseGroup()
ParseGroupGroup()
ReconstructMapDataWithUniqueIds()
ConstructPreloadingDataFile()
