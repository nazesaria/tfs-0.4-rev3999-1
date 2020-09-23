function isInWarById(guildId, enemyId)
    local resultId = db.storeQuery(string.format('SELECT `id` FROM `guild_wars` WHERE `status` = 1 AND ((`guild1` = %d AND `guild2` = %d) OR (`guild1` = %d AND `guild2` = %d))', guildId, enemyId, enemyId, guildId))
    if resultId then
        result.free(resultId)
        return true
    end

    return false
end

function onSay(player, words, param)
	if player:exhaustCheck(666) then return player:sendTextMessage(MESSAGE_STATUS_DEFAULT, "Aguarde 2 segundos para usar comandos novamente.") end
	player:exhaustSet(666, 2)
	
	local guild = player:getGuild()
	local playerGuild, p = guild:getId(), param:splitTrimmed(",")
	if param == "" then
		player:sendTextMessage(MESSAGE_STATUS_SMALL, "[War Anti-Entrosa] Comando inválido.")
		return true
	end

	if playerGuild <= 0 then
		player:sendTextMessage(MESSAGE_STATUS_DEFAULT, "[War Anti-Entrosa] Você precisa estar em uma Guild para usar eses comando.")
		return true
	end

	if player:getLevel() < 50 then
		player:sendTextMessage(MESSAGE_STATUS_DEFAULT, "[War Anti-Entrosa] Você precisa ser no mínimo level 50 para usar esse comando.")
		return true
	end

	local action = p[1]
	if action == "invite" then		
		if player:getGuildLevel() < 3 then
			player:sendTextMessage(MESSAGE_STATUS_SMALL, "[War Anti-Entrosa] Você precisa ser líder da Guild para poder enviar um pedido de War.")
			return true
		end

		if AntiEntrosa:warInfo(playerGuild) then
			player:sendTextMessage(MESSAGE_STATUS_SMALL, "[War Anti-Entrosa] A sua Guild já está em uma War no Anti-Entrosa, aguarde ela terminar.")
			return true
		end

		local cityName = p[2]
		if not cityName then
			player:sendTextMessage(MESSAGE_STATUS_SMALL, "[War Anti-Entrosa] Defina um nome da cidade para o Anti-Entrosa.")
			return true
		end

		local arenaId = AntiEntrosa:arenaExists(cityName)
		if not arenaId then
			player:sendTextMessage(MESSAGE_STATUS_SMALL, "[War Anti-Entrosa] O nome dessa cidade não existe.")
			return true
		end

		local cityAvaliable = AntiEntrosa:arenaIsFree(arenaId)
		if not cityAvaliable then
			player:sendTextMessage(MESSAGE_STATUS_SMALL, "[War Anti-Entrosa] Essa cidade não está disponível atualmente para War.")
			return true
		end

		-- Tempo em minutos da Wars 
		local timeWar = tonumber(p[3])
		if not timeWar then
			player:sendTextMessage(MESSAGE_STATUS_SMALL, "[War Anti-Entrosa] Defina a tempo em minutos para cado lado.")
			return true
		elseif not isInArray(AntiEntrosa.timeAvaliable, timeWar) then
			local str = ''
			for i = 1, #AntiEntrosa.timeAvaliable do
				local time = AntiEntrosa.timeAvaliable[i]
				str = string.format('%s %d', str, time)
			end

			player:sendTextMessage(MESSAGE_STATUS_CONSOLE_RED, string.format('[War Anti-Entrosa] As opções de tempo são apenas de %s. Por favor escolha um desses Tempos.', str))
			return true
		end

		-- Level mínimo para entrar
		local minLevel = p[4]
		if not minLevel then
			player:sendTextMessage(MESSAGE_STATUS_SMALL, "[War Anti-Entrosa] Por favor defina o level máximo dos players para o Anti-Entrosa.")
			return true
		else
			if (type(minLevel) == "string") then
				if minLevel:lower() == "disabled" then
					minLevel = false
				else
					minLevel = tonumber(minLevel)
				end

				if (type(minLevel) == "number") then
					if minLevel <= 0 then
						player:sendTextMessage(MESSAGE_STATUS_SMALL, '[War Anti-Entrosa] O level não pode ser negativo. Caso não queira limite, coloque "disabled".')
						return true
					end
				end
			else
				return true
			end
		end

		-- UE ativada?
		local ueEnabled = p[5]
		if not ueEnabled then
			player:sendTextMessage(MESSAGE_STATUS_SMALL, "[War Anti-Entrosa] Defina corretamente se UE estará enabled ou disabled.")
			return true
		else
			ueEnabled = ueEnabled:lower()
			if ueEnabled == "enabled" then
				ueEnabled = true
			elseif ueEnabled == "disabled" then
				ueEnabled = false
			else
				player:sendTextMessage(MESSAGE_STATUS_SMALL, "[War Anti-Entrosa] Defina corretamente se UE é ou não permitido.")
				return true
			end
		end

		-- Runas ativadas? 
		local runesEnabled = p[6]
		if not runesEnabled then
			player:sendTextMessage(MESSAGE_STATUS_SMALL, "[War Anti-Entrosa] Defina corretamente se Runas estarão enabled ou disabled.")
			return true
		else
			runesEnabled = runesEnabled:lower()
			if runesEnabled == "enabled" then
				runesEnabled = true
			elseif runesEnabled == "disabled" then
				runesEnabled = false
			else
				player:sendTextMessage(MESSAGE_STATUS_SMALL, "[War Anti-Entrosa] Defina corretamente se Runas são ou não permitidas.")
				return true
			end
		end

		-- SSA ativado?
		local ssaMightRingBlocked = p[7]
		if not ssaMightRingBlocked then
			player:sendTextMessage(MESSAGE_STATUS_SMALL, "[War Anti-Entrosa] Defina corretamente se SSA e Might Ring estarão enabled ou disabled.")
			return true
		else
			ssaMightRingBlocked = ssaMightRingBlocked:lower()
			if ssaMightRingBlocked == "enabled" then
				ssaMightRingBlocked = true
			elseif ssaMightRingBlocked == "disabled" then
				ssaMightRingBlocked = false
			else
				player:sendTextMessage(MESSAGE_STATUS_SMALL, "[War Anti-Entrosa] Defina corretamente se SSA e Might são ou não permitidos.")
				return true
			end
		end

		-- Summons blockiados?
		local summonsBlocked = p[8]
		if not summonsBlocked then
			player:sendTextMessage(MESSAGE_STATUS_SMALL, "[War Anti-Entrosa] Defina corretamente se os Summons estarão enabled ou disabled.")
			return true
		else
			summonsBlocked = summonsBlocked:lower()
			if summonsBlocked == "enabled" then
				summonsBlocked = true
			elseif summonsBlocked == "disabled" then
				summonsBlocked = false
			else
				player:sendTextMessage(MESSAGE_STATUS_SMALL, "[War Anti-Entrosa] Defina corretamente se Summons são ou não permitidos.")
				return true
			end
		end

		-- Definir a quantidade de players
		local maximumPlayers = tonumber(p[9])
		if not maximumPlayers then
			maximumPlayers = 0
		elseif maximumPlayers < AntiEntrosa.minPlayers and maximumPlayers ~= 0 then
			player:sendTextMessage(MESSAGE_STATUS_SMALL, "[War Anti-Entrosa] A quantidade de players mínima é de ".. AntiEntrosa.minPlayers ..".")
			return true
		elseif maximumPlayers > AntiEntrosa.maxPlayers then
			player:sendTextMessage(MESSAGE_STATUS_SMALL, "[War Anti-Entrosa] A quantidade máxima de Players é de ".. AntiEntrosa.maxPlayers .." ou ilimitado.")
			return true
		end

		-- Definir a Guild contra
		local guildEnemy = p[10]
		if not guildEnemy then
			player:sendTextMessage(MESSAGE_STATUS_SMALL, "[War Anti-Entrosa] Defina o nome da guild inimiga.")
			return true
		end

		local enemyGuildId = getGuildId(guildEnemy)
		if not enemyGuildId or enemyGuildId == 0 then
			player:sendTextMessage(MESSAGE_STATUS_SMALL, "[War Anti-Entrosa] Essa Guild não existe.")
			return true
		end

		if enemyGuildId == playerGuild then
			player:sendTextMessage(MESSAGE_STATUS_SMALL, "[War Anti-Entrosa] Você não pode convidar a sua própria Guild para uma War.")
			return true
		end
		
		if AntiEntrosa:warInfo(enemyGuildId) then
			player:sendTextMessage(MESSAGE_STATUS_SMALL, "[War Anti-Entrosa] Essa guild já foi convidada por outra guild.")
			return true
		end

		local enemyGuildName = Guild(enemyGuildId):getName()
		if not isInWarById(playerGuild, enemyGuildId) then
			player:sendTextMessage(MESSAGE_STATUS_CONSOLE_RED, string.format("[War Anti-Entrosa] Sua Guild precisa estar em WarSystem contra a Guild %s para poder enviar um pedido de War no Anti-Entrosa.", enemyGuildName))
			return true
		end

		local hasInvitation = AntiEntrosa:hasInvitation(playerGuild, enemyGuildId)
		if hasInvitation then
			player:sendTextMessage(MESSAGE_STATUS_SMALL, string.format("[War Anti-Entrosa] Já existe um convite de War contra a Guild %s.", enemyGuildName))
			return true
		end
		
		if player:getMoney() >= 350000 then -- gold coin
			if player:removeMoney(350000) then -- gold coin
				AntiEntrosa:sendInvitation(player, arenaId, playerGuild, enemyGuildId, timeWar, minLevel, ueEnabled, runesEnabled, ssaMightRingBlocked, summonsBlocked, maximumPlayers)
			else
				player:sendTextMessage(MESSAGE_STATUS_DEFAULT, "ERROR! Contact the Administrator.")
				return true
			end
		else
			player:sendTextMessage(MESSAGE_STATUS_DEFAULT, "[War Anti-Entrosa] Taxa para enviar um convite no Anti-Entrosa é de 350k.")
			return true
		end

	elseif action == "accept" then
		local guildEnemy = p[2]
		local enemyGuildId = getGuildId(guildEnemy)
		if not enemyGuildId or enemyGuildId == 0 then
			player:sendTextMessage(MESSAGE_STATUS_SMALL, "[War Anti-Entrosa] Essa Guild não existe.")
			return true
		end

		if enemyGuildId == playerGuild then
			player:sendTextMessage(MESSAGE_STATUS_SMALL, "[War Anti-Entrosa] Você não pode executar essa ação.")
			return true
		end
		
		if player:getGuildLevel() < 3 then
			player:sendTextMessage(MESSAGE_STATUS_SMALL, "[War Anti-Entrosa] Você precisa ser líder da Guild para poder enviar um pedido de War.")
			return true
		end

		local enemyGuildName = Guild(enemyGuildId):getName()
		local hasInvitation = AntiEntrosa:hasInvitation(playerGuild, enemyGuildId)
		if not hasInvitation then
			player:sendTextMessage(MESSAGE_STATUS_SMALL, string.format("[War Anti-Entrosa] Não existe nenhum convite de War da Guild %s.", enemyGuildName))
			return true
		end
		
		local arenaId = AntiEntrosa:getWarIdByGuild(playerGuild)
		if arenaId then
			if player:getMoney() >= 150000 then -- gold coin
				if player:removeMoney(150000) then -- gold coin
					AntiEntrosa:confirmInvitation(player, arenaId)
				else
					player:sendTextMessage(MESSAGE_STATUS_DEFAULT, "ERROR! Contact the Administrator.")
					return true
				end
			else
				player:sendTextMessage(MESSAGE_STATUS_DEFAULT, "[War Anti-Entrosa] Taxa para aceitar o Anti-Entrosa é de 150k.")
				return true
			end
		else
			player:sendTextMessage(MESSAGE_STATUS_SMALL, "[War Anti-Entrosa] Não foi possível aceitar o pedido de War no Anti-Entrosa.")
		end
		
	elseif action == "cancel" then
		local guildEnemy = p[2]
		local enemyGuildId = getGuildId(guildEnemy)
		if not enemyGuildId or enemyGuildId == 0 then
			player:sendTextMessage(MESSAGE_STATUS_SMALL, "[War Anti-Entrosa] Essa Guild não existe.")
			return true
		end

		if enemyGuildId == playerGuild then
			player:sendTextMessage(MESSAGE_STATUS_SMALL, "[War Anti-Entrosa] Você não pode executar essa ação.")
			return true
		end
		
		local warInfo = AntiEntrosa:warInfo(playerGuild)
		if not warInfo then
			player:sendTextMessage(MESSAGE_STATUS_SMALL, "[War Anti-Entrosa] A sua Guild não possui uma War Ativa atualmente.")
			return true
		end
		
		local enemyGuildName = Guild(enemyGuildId):getName()
		local canCancel = AntiEntrosa:canCancelInvitation(playerGuild)
		if not canCancel then
			player:sendTextMessage(MESSAGE_STATUS_SMALL, "[War Anti-Entrosa] Você não pode cancelar o pedido dessa War no Anti-Entrosa.")
			return true
		end

		local arenaId = AntiEntrosa:getWarIdByGuild(playerGuild)
		if arenaId then
			AntiEntrosa:cancelInvitation(player, arenaId)
		else
			player:sendTextMessage(MESSAGE_STATUS_SMALL, "[War Anti-Entrosa] Não foi possível aceitar o pedido de War no Anti-Entrosa.")
		end

	elseif action == "go" then
		-- Verifica se a Guild do jogador está no Anti Entrosa
		local arenaId = AntiEntrosa:getWarIdByGuild(playerGuild)
		if not arenaId then
			player:sendTextMessage(MESSAGE_STATUS_SMALL, "[War Anti-Entrosa] Sua Guild não está em War no Anti-Entrosa neste momento.")
			return true
		end

		AntiEntrosa:enterPlayer(player, arenaId)
	elseif action == "exit" then
		if not Tile(player:getPosition()):hasFlag(TILESTATE_PROTECTIONZONE) then
			player:sendTextMessage(MESSAGE_STATUS_SMALL, "[War Anti-Entrosa] Você precisa estar em PZ para sair do Anti-Entrosa.")
			return true
		end
		
		if player:isPzLocked() then
			player:sendTextMessage(MESSAGE_STATUS_SMALL, "[War Anti-Entrosa] Você não pode sair do Anti-Entrosa com PZ Locked.")
			return true
		end
		
		if player:getStorageValue(STORAGE_PLAYER_IN_ARENA) == 1 then
			AntiEntrosa:removePlayersOutside(player, "Você saiu do Anti Entrosa", true)
		else
			player:sendTextMessage(MESSAGE_STATUS_SMALL, "[War Anti-Entrosa] Você não está no Anti Entrosa.")
		end
	else
		player:sendTextMessage(MESSAGE_STATUS_CONSOLE_RED, "[War Anti-Entrosa] Digite o comando corretamente: !citywar invite, cidade, tempo, levelMax, ueMode, runesMode, ssaMode, summonsMode, playersDentro, GuildContra")
	end

	return true
end
