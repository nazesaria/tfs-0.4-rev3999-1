local function BSComparator(a, b)
	if a > b then return -1
	elseif a < b then return 1
	else return 0
	end
end

local function BSComparatorSortType(a, b, sortType)
    assert(type(sortType) == 'string', "invalid sortType, string expected got ".. type(sortType) ..".")
    local comparatorA, comparatorB
	if sortType == 'distance' then
		comparatorA, comparatorB = a.distance, type(b) == "table" and b.distance or b
	elseif sortType == 'health' then
		comparatorA, comparatorB = a.healthPercent, type(b) == "table" and b.healthPercent or b
	elseif sortType == 'age' then
		comparatorA, comparatorB = a.age, type(b) == "table" and b.age or b
    elseif sortType == 'name' then
        comparatorA, comparatorB = (a.name):lower(), type(b) == "table" and (b.name):lower() or b
	end
	if comparatorA > comparatorB then return -1
	elseif comparatorA < comparatorB then return 1
	else return 0
	end
end

local function binarySearch(tbl, value, comparator, ...)
	if not comparator then
		comparator = BSComparator
	end
	
	local mini = 1
	local maxi = #tbl
	
	while mini <= maxi do
		local mid = math.floor((maxi+mini)/2)
		local tmp_value = comparator(tbl[mid], value, ...)
		
		if tmp_value == 0 then 
			return mid
		elseif tmp_value > 0 then
			mini = mid + 1
		else
			maxi = mid - 1
		end
	end
	return nil	
end

local function binaryInsert(tbl, value, comparator, ...)
	if not comparator then
		comparator = BSComparator
	end
	
	local mini = 1
	local maxi = #tbl
    local state = 0
    local mid = 1
	
	while mini <= maxi do
		mid = math.floor((maxi+mini)/2)
		
		if comparator(tbl[mid], value, ...) < 0 then 
			maxi, state = mid - 1, 0
		else
			mini, state = mid + 1, 1
		end
	end
    table.insert(tbl, mid + state, value)
	return (mid + state)
end
        

local creatureList = {
    {name ="ades1", distance = 51},
    {name ="ades6", distance = 3},
    {name ="ades3", distance = 3},
    {name ="ades4", distance = 10},
    {name ="ades5", distance = 15},
}

--print(binaryInsert(creatureList, {name ="ades6", distance = 1}, BSComparatorSortType, "distance"))

local newSortType = "distance"

table.sort(creatureList, 
			function(a, b)
			return BSComparatorSortType(a, b, newSortType) >= 1
		end)

print("Printing table:")
for i, v in ipairs (creatureList) do print(i, v.name, v.distance) end

print(---------- Running Search --------)
)

print(binarySearch(creatureList, 15, BSComparatorSortType, newSortType))


print(------------)
)
