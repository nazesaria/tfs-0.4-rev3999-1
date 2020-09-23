local item = {uid = 000, itemid = 7887, aid = 87184}

function onUse(player, item, fromPosition, itemEx, toPosition)

    print(fromPosition.x)
    setPlayerStorageValue(player, 4000, 2)
    return true
end