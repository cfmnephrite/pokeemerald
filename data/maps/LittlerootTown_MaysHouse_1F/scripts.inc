LittlerootTown_MaysHouse_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LittlerootTown_MaysHouse_1F_MapScripts_MAP_SCRIPT_ON_TRANSITION
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LittlerootTown_MaysHouse_1F_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

LittlerootTown_MaysHouse_1F_MapScripts_MAP_SCRIPT_ON_TRANSITION:
	compare VAR_LITTLEROOT_INTRO_STATE, 1
	goto_if_eq LittlerootTown_MaysHouse_1F_MapScripts_MAP_SCRIPT_ON_TRANSITION_1
	return

LittlerootTown_MaysHouse_1F_MapScripts_MAP_SCRIPT_ON_TRANSITION_1:
	setweather WEATHER_SHADE
	return

LittlerootTown_MaysHouse_1F_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
	map_script_2 VAR_TEMP_0, 0, LittlerootTown_MaysHouse_1F_Beginning
	.2byte 0


LittlerootTown_MaysHouse_1F_TriggerBag::
	lock
	playse SE_PIN
	applymovement 1, Common_Movement_ExclamationMark
	waitmovement 0
	playmoncry SPECIES_PICHU, 0
	waitmoncry
	applymovement OBJ_EVENT_ID_PLAYER, LittleroowTown_MaysHouse_1F_PlayerLookLeft
	waitmovement 0
	goto LittlerootTown_MaysHouse_1F_BirchsBag
	end


LittleroowTown_MaysHouse_1F_PlayerLookLeft:
	face_left
	step_end

LittlerootTown_MaysHouse_1F_BirchsBag::
	lock
	goto_if_unset FLAG_SYS_POKEMON_GET, LittlerootTown_MaysHouse_1F_BirchsBag_2
	msgbox LittlerootTown_MaysHouse_1F_BirchsBag_Text_2, MSGBOX_SIGN
LittlerootTown_MaysHouse_1F_BirchsBag_1:
	release
	end

LittlerootTown_MaysHouse_1F_BirchsBag_2:
	setflag FLAG_SYS_POKEMON_GET
	msgbox LittlerootTown_MaysHouse_1F_BirchsBag_Text_0, MSGBOX_SIGN
	fadescreen FADE_TO_BLACK
	special ChooseStarter
	waitstate
	msgbox LittlerootTown_MaysHouse_1F_BirchsBag_Text_1, MSGBOX_SIGN
	goto LittlerootTown_MaysHouse_1F_BirchsBag_1


LittlerootTown_MaysHouse_1F_Beginning::
	goto_if_unset FLAG_ENTERED_MAYS_HOUSE, LittlerootTown_MaysHouse_1F_Beginning_2
LittlerootTown_MaysHouse_1F_Beginning_1:
	setvar VAR_TEMP_0, 1
	end

LittlerootTown_MaysHouse_1F_Beginning_2:
	lock
	msgbox LittlerootTown_MaysHouse_1F_RocketThreat, MSGBOX_SIGN
	release
	setflag FLAG_ENTERED_MAYS_HOUSE
	goto LittlerootTown_MaysHouse_1F_Beginning_1


LittlerootTown_MaysHouse_1F_BirchsBag_Text_0:
	.string "There's something in here...$"

LittlerootTown_MaysHouse_1F_BirchsBag_Text_1:
	.string "You obtained the Pichu! Its ear looks a\n"
	.string "little crooked though...$"

LittlerootTown_MaysHouse_1F_BirchsBag_Text_2:
	.string "There's nothing else in here.$"

LittlerootTown_MaysHouse_1F_RocketThreat::
	.string "Voice 1: Look, Birch, we know you know we\n"
	.string "know you know where we can find the\l"
	.string "rare monsters.\p"
	.string "Birch: ...What?\p"
	.string "Voice 2: Tell us where they are now! I\n"
	.string "want a Gardev-, uh, a Gallade!\p"
	.string "Birch: Look, I won't tell you...\p"
	.string "Voice 1: If you don't tell us soon, your\n"
	.string "family will pay the price...$"
