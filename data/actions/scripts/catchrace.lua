function onUse(cid, item, fromPosition, itemEx, toPosition)
    print(CatchRace:inEvent(cid))
    if CatchRace:inEvent(cid) then
        -- local corpse = getTopCorpse(topos).uid
        -- CatchRace:catchPokemon(cid, itemEx.uid)
        -- doRemoveItem(itemEx.uid, 1)
        doSendMagicEffect(fromPosition, 10)
    end
end