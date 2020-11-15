LittlerootTown_MapScripts::
	.byte 0


LittlerootTown_EventScript_FatMan::
	msgbox LittlerootTown_EventScript_FatMan_Text_0
	end


LittlerootTown_EventScript_Boy::
	msgbox LittlerootTown_Text_BirchSpendsDaysInLab
	end


LittlerootTown_EventScript_Twin::
	msgbox LittlerootTown_EventScript_Twin_Text_0
	end


LittlerootTown_EventScript_TownSign::
	msgbox LittlerootTown_EventScript_TownSign_Text_0
	end


LittlerootTown_EventScript_BirchsLabSign::
	msgbox LittlerootTown_EventScript_BirchsLabSign_Text_0
	return


LittlerootTown_EventScript_FatMan_Text_0:
	.string "If you use a PC at a Pokémon Centre,\n"
	.string "you can store up to 540 monsters!\p"
	.string "The power of science is staggering!$"

LittlerootTown_EventScript_Twin_Text_0:
	.string "Are you going to catch POKéMON?\n"
	.string "Good luck!$"

LittlerootTown_EventScript_TownSign_Text_0:
	.string "Littleroot\n"
	.string "A town that can't be shaded any hue.$"

LittlerootTown_EventScript_BirchsLabSign_Text_0:
	.string "Birch Laboratory for Monster Research$"

LittlerootTown_Text_BirchSpendsDaysInLab::
	.string "Prof. Birch spends days in his Lab\n"
	.string "studying, then he'll suddenly go out in\l"
	.string "the wild to do more research…\p"
	.string "When does he spend time at home?$"
