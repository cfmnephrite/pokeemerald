LittlerootTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LittlerootTown_MapScripts_MAP_SCRIPT_ON_TRANSITION
	.byte 0

LittlerootTown_MapScripts_MAP_SCRIPT_ON_TRANSITION:
	compare VAR_LITTLEROOT_INTRO_STATE, 1
	goto_if_eq LittlerootTown_MapScripts_MAP_SCRIPT_ON_TRANSITION_1
	return

LittlerootTown_MapScripts_MAP_SCRIPT_ON_TRANSITION_1:
	setweather WEATHER_SHADE
	return


LittlerootTown_EventScript_CheckNextDoorForceMovement::
	compare VAR_LITTLEROOT_INTRO_STATE, 1
	goto_if_eq LittlerootTown_EventScript_CheckNextDoorForceMovement_2
	setvar VAR_LITTLEROOT_INTRO_STATE, 2
LittlerootTown_EventScript_CheckNextDoorForceMovement_1:
	releaseall
	end

LittlerootTown_EventScript_CheckNextDoorForceMovement_2:
	msgbox gText_BetterCheckNextDoor
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_Movement_CheckNextDoorPushUp
	waitmovement 0
	goto LittlerootTown_EventScript_CheckNextDoorForceMovement_1


LittlerootTown_Movement_CheckNextDoorPushUp:
	walk_up
	step_end

LittlerootTown_EventScript_FatMan::
	msgbox LittlerootTown_EventScript_FatMan_Text_0
	end


LittlerootTown_EventScript_Boy::
	msgbox LittlerootTown_Text_BirchSpendsDaysInLab
	end


LittlerootTown_EventScript_Twin::
	msgbox LittlerootTown_EventScript_Twin_Text_0
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

LittlerootTown_EventScript_BirchsLabSign_Text_0:
	.string "BIRCH LABORATORY\n"
	.string "Monster Research$"

gText_BetterCheckNextDoor::
	.string "Better check what's happening next\n"
	.string "door...$"

LittlerootTown_Text_BirchSpendsDaysInLab::
	.string "Prof. Birch spends days in his Lab\n"
	.string "studying, then he'll suddenly go out in\l"
	.string "the wild to do more research…\p"
	.string "When does he spend time at home?$"
