local combat50_Brush = createCombatObject()
setCombatParam(combat50_Brush, COMBAT_PARAM_EFFECT, CONST_ME_MORTAREA)
setCombatParam(combat50_Brush, COMBAT_PARAM_TYPE, COMBAT_DEATHDAMAGE)
setAttackFormula(combat, COMBAT_FORMULA_LEVELMAGIC, 5, 5, 1.4, 2.8, 40, 70)
setCombatArea(combat50_Brush,createCombatArea({
{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0},
{0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
{1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1},
{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
{0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
{0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
}))

local function RunPart(c,cid,var)
	if (isCreature(cid)) then
		doCombat(cid, c, var)
		doCreatureSay(cid, "Gaz'haragoth calls down: DEATH AND DOOM!", TALKTYPE_ORANGE_2)
	end
end

function onCastSpell(cid, var)
	doCreatureSay(cid, "Gaz'haragoth begins to channel DEATH AND DOOM into the area! RUN!", TALKTYPE_ORANGE_2)
	addEvent(RunPart,5000,combat50_Brush,cid,var)
	return true
end