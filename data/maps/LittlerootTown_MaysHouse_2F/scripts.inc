LittlerootTown_MaysHouse_2F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LittlerootTown_MaysHouse_2F_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

LittlerootTown_MaysHouse_2F_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 1, LittlerootTown_MaysHouse_2F_TheRescueStart
	.2byte 0


LittlerootTown_MaysHouse_2F_TheRescueStart::
	setvar VAR_LITTLEROOT_INTRO_STATE, 2
	lock
	applymovement 1, Common_Movement_WalkInPlaceRight
	msgbox LittlerootTown_MaysHouse_2F_TheRescueStart_Text_0
	waitmessage
	playse SE_PIN
	applymovement 1, Common_Movement_ExclamationMark
	applymovement 1, Common_Movement_FaceUp
	applymovement 2, Common_Movement_ExclamationMark
	applymovement 2, Common_Movement_FaceUp
	waitmovement 0
	msgbox LittlerootTown_MaysHouse_2F_TheRescueStart_Text_1
	waitmessage
	applymovement 1, Common_Movement_WalkInPlaceDown
	msgbox LittlerootTown_MaysHouse_2F_TheRescueStart_Text_2
	waitmessage
	applymovement 2, Common_Movement_WalkInPlaceUp
	msgbox LittlerootTown_MaysHouse_2F_TheRescueStart_Text_3
	waitmessage
	applymovement 1, Common_Movement_WalkInPlaceRight
	applymovement 2, Common_Movement_WalkUp2
	waitmovement 0
	trainerbattle_single TRAINER_INTRO_GRUNT_1, LittlerootTown_MaysHouse_2F_Intro_Grunt_1_Intro, LittlerootTown_MaysHouse_2F_Intro_Grunt_1_Defeat
	release
	end


LittlerootTown_MaysHouse_2F_EventScript_CheckRivalsPC::
	msgbox gText_PokemonTrainerSchoolEmail
	releaseall
	end


LittlerootTown_MaysHouse_2F_TheRescueStart_Text_0:
	.string "Intruder 1: Tell us now or...$"

LittlerootTown_MaysHouse_2F_TheRescueStart_Text_1:
	.string "Intruder 1: Who the hell is this?$"

LittlerootTown_MaysHouse_2F_TheRescueStart_Text_2:
	.string "Go deal with it! No witnesses!$"

LittlerootTown_MaysHouse_2F_TheRescueStart_Text_3:
	.string "Intruder 2: You got it, boss!$"

LittlerootTown_MaysHouse_2F_Intro_Grunt_1_Intro::
	.string "Sorry, kid...$"

LittlerootTown_MaysHouse_2F_Intro_Grunt_1_Defeat::
	.string "Wait, what?$"
