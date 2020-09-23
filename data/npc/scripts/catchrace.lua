local keywordHandler = KeywordHandler:new()
local npcHandler = NpcHandler:new(keywordHandler)
NpcSystem.parseParameters(npcHandler)
 
function onCreatureAppear(cid)         npcHandler:onCreatureAppear(cid)         end
function onCreatureDisappear(cid)      npcHandler:onCreatureDisappear(cid)         end
function onCreatureSay(cid, type, msg)   npcHandler:onCreatureSay(cid, type, msg:lower())   end
function onThink()                  npcHandler:onThink()                  end
local talkState = {}

function onCreatureSay(cid, type, msg)
    player = Player(cid)
    npcHandler:setMessage(MESSAGE_GREET, "Ola " ..player:getName().. " você quer uma missão?")
    npcHandler:setMessage(MESSAGE_WALKAWAY, "Semprem fogem")
    npcHandler:setMessage(MESSAGE_FAREWELL, "Até... "..getCreatureName(cid)..".")
	npcHandler:onCreatureSay(cid, type, msg)		
end
 
function creatureSayCallback(cid, type, msg)
    if (not npcHandler:isFocused(cid)) then
        return false
    end
local talkUser = NPCHANDLER_CONVbehavior == CONVERSATION_DEFAULT and 0 or cid
    -- INICIO DE CONVERSA --
    player = Player(cid)
    local storage = 4000

    if isInArray({"yes", "sim"}, msg) then
        npcHandler:say("Puxe a alavanca e volte até mim e fale puxei", cid)
        player:setStorageValue(storage, 1)
    end

    -- MISSAO PUXAR ALAVANCA 
    if player:getStorageValue(storage) >= 1 then
        if isInArray({"puxei"}, msg) then
            if player:getStorageValue(storage) == 2 then
                npcHandler:say("parabens", cid)
                player:setStorageValue(storage, 3)
            else
                npcHandler:say("voce nao fez a missao ainda", cid)
            end
        end
    end
    -- FIM MISSAO

    
return true
end


npcHandler:setCallback(CALLBACK_MESSAGE_DEFAULT, creatureSayCallback)
npcHandler:addModule(FocusModule:new())