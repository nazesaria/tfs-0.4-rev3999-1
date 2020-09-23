if not CatchRacer then
    CatchRacer = {
        members = {},
        points = {},
        rank = {}
    }
end

CatchRacer.storages = {status = 1007701}

function CatchRacer:isOpen()
    return getGlobalStorageValue(self.storages.status) > 0 and true or false
end

function CatchRacer:updateStatus()
	local value = self:isOpen() and -1 or 1
	setGlobalStorageValue(self.storages.status, value)
end

function CatchRacer:open()
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