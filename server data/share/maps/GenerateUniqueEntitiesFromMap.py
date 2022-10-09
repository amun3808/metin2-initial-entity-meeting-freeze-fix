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
		print(mapName)

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
	groupVnum: [leaderVnum, mobsVnum]
}
"""
groups = {}
# g = group.txt
def ParseGroup():
	groupVnum = 0
	
	for line in open("group.txt"):
		line = line.strip()
		if ((not line) or (line=="{") or (line=="}")):
			continue

		try:
			[tok, vnum] = line.split()
			if(tok == "Group"):
				groupVnum = int(vnum)
				groups[groupVnum] = []

				# move to next line
				continue
		except:
			pass

		if(groupVnum and groupVnum in groups):
			[k, v] = line.split(":")
			# print(k)

			# parse leader
			if k == "Leader":
				stripped = v.strip()
				if stripped:
					groups[groupVnum].append(int(stripped))
					# print(stripped)

			# parse members
			elif k == "Members":
				members = v.split(",")
				# remove spaces and append to mobs list
				for member in members:
					stripped = member.strip()
					if stripped:
						groups[groupVnum].append(int(stripped))
						# print(stripped)
#
"""
regenGroups = {
	regenGroupVnum: [mobsVnum]
}
"""
regenGroups = {}
# r = group_group.txt
def ParseGroupGroup():
	regenGroupVnum = 0
	
	for line in open("group_group.txt"):
		line = line.strip()
		if ((not line) or (line=="{") or (line=="}")):
			continue

		try:
			[tok, gName] = line.split()
			if(tok == "Group"):
				# move to next line, we don't care about group name anymore
				continue
		except:
			pass

		[k, v] = line.split(":")
		# print(k)

		# parse vnum
		if k == "Vnum":
			stripped = v.strip()
			if stripped:
				regenGroupVnum = int(stripped)
				regenGroups[regenGroupVnum] = []
				# print(stripped)

		# parse members
		elif k == "Members":
			members = v.split(",")
			if not len(members):
				if regenGroupVnum in regenGroups:
					del regenGroups[regenGroupVnum]
	
				continue

			# remove spaces and append to mobs list
			for member in members:
				stripped = member.strip()
				if stripped:
					regenGroups[regenGroupVnum].append(int(stripped))
					# print(stripped)
			
#
def ReconstructMapDataWithUniqueIds():
	for curMap in mapData.keys():
		print(curMap)
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
