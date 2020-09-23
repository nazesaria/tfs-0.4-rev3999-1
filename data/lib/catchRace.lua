if not CatchRace then
  CatchRace = {
      members = {},
      points = {},
      rank = {}
  }
end

CatchRace.storages = {status = 1007701, join = 1007702}
CatchRace.positions = {from = Position(493, 505, 7), to = Position(504, 513, 7), join = Position(498, 507, 7), exit = Position(499, 503, 7)}
CatchRace.config = {pokeball = 2150, count = 100}
CatchRace.pokeScore = {["bug"] = 1, ["troll"] = 2, ["orc"] = 3, ["cyclops"] = 5}

function CatchRace:joinEvent(player)
  doTeleportThing(player, self.positions.join)
  doPlayerAddItem(player, self.config.pokeball, self.config.count)
  setPlayerStorageValue(player, self.storages.join, 1)
end

function CatchRace:catchPokemon(player, pokemon)
  print(self:getPoints(player))
  print(self.pokeScore[getCreatureName(pokemon)])
  if self:inEvent(player) then
   -- self.points[player] = self:getPoints(player) + self.pokeScore[getCreatureName(pokemon)]
  end
end

function CatchRace:getPoints(player)
    return self.points[player] or 0
end

function CatchRace:getMembers()
  return self.members
end

function CatchRace:setMember(player)
	if #self:getMembers() > 0 then
		for list, members in ipairs(self:getMembers()) do
			if player == members then
				return
			end
		end
	end
	table.insert(self.members, player)
end

function CatchRace:removeMember(player)
	for list, members in ipairs(self:getMembers()) do
		if player == members then
			table.remove(self.members, list)
		end
	end
end

function CatchRace:isOpen()
  return getGlobalStorageValue(self.storages.status) > 0 and true or false
end

function CatchRace:inEvent(player)
  return getPlayerStorageValue(player, self.storages.join) > 0 and true or false
end

function CatchRace:updateStatus()
	local value = self:isOpen() and -1 or 1
	setGlobalStorageValue(self.storages.status, value)
end

function CatchRace:open()
  if self:isOpen() then
      return
  end
  self:updateStatus()
end


--[[
x = 0
for _, i in pairs(lua.points) do
 if i > x then
    table.insert(lua.rank, 1, _)
    x = i
  elseif i == x then
    table.insert(lua.rank, 2, _)
  else
    table.insert(lua.rank, _)
  end
end]]