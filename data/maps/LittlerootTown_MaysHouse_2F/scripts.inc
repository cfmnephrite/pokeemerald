LittlerootTown_MaysHouse_2F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LittlerootTown_MaysHouse_2F_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

LittlerootTown_MaysHouse_2F_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 1, LittlerootTown_MaysHouse_2F_TheRescueStart
	.2byte 0


LittlerootTown_MaysHouse_2F_TheRescueStart::
	hideobjectat 7, MAP_LITTLEROOT_TOWN_MAYS_HOUSE_2F
	setvar VAR_LITTLEROOT_INTRO_STATE, 2
	lock
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, LittlerootTown_MaysHouse_2F_Movement_Intro_PanCameraDownRight
	waitmovement 0
	applymovement 1, Common_Movement_WalkInPlaceRight
	msgbox LittlerootTown_MaysHouse_2F_TheRescueStart_Text_0
	waitmessage
	playse SE_PIN
	applymovement 1, Common_Movement_ExclamationMarkLookUp
	applymovement 2, Common_Movement_ExclamationMarkLookUp
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
	trainerbattle_single TRAINER_INTRO_GRUNT_2, LittlerootTown_MaysHouse_2F_Intro_Grunt_2_Intro, LittlerootTown_MaysHouse_2F_Intro_Grunt_2_Defeat, LittlerootTown_MaysHouse_2F_TheRescueDefeatedGrunt2
	release
	end


LittlerootTown_MaysHouse_2F_TheRescueDefeatedGrunt2::
	showobjectat 7, MAP_LITTLEROOT_TOWN_MAYS_HOUSE_2F
	setobjectxy 2, 1, 4
	playse SE_M_THUNDER_WAVE
	applymovement 7, LittlerootTown_MaysHouse_2F_Movement_PichuAdvancesOnGrunt2
	applymovement 2, LittlerootTown_MaysHouse_2F_Movement_Grunt2FliesBackwards
	waitmovement 0
	playse SE_EFFECTIVE
	waitse
	playse SE_PIN
	applymovement 1, Common_Movement_ExclamationMarkLookLeft
	waitmovement 0
	msgbox LittlerootTown_MaysHouse_2F_TheRescueDefeatedGrunt2_Text_0
	applymovement 3, Common_Movement_FaceLeft
	playmoncry SPECIES_POOCHYENA, 0
	waitmoncry
	applymovement 3, LittlerootTown_MaysHouse_2F_Movement_PoochyenaMovesToEngage
	waitmovement 0
	applymovement 1, LittlerootTown_MaysHouse_2F_Movement_Grunt1MovesToEngage
	waitmovement 0
	applymovement 7, Common_Movement_FaceRight
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight
	waitmovement 0
	trainerbattle_single TRAINER_INTRO_GRUNT_1, LittlerootTown_MaysHouse_2F_Intro_Grunt_1_Intro, LittlerootTown_MaysHouse_2F_Intro_Grunt_1_Defeat, LittlerootTown_MaysHouse_2F_TheRescueDefeatedGrunt1
	release
	end


LittlerootTown_MaysHouse_2F_TheRescueDefeatedGrunt1::
	playse SE_M_THUNDER_WAVE
	applymovement 7, LittlerootTown_MaysHouse_2F_Movement_PichuAdvancesOnGrunt1
	applymovement 1, LittlerootTown_MaysHouse_2F_Movement_Grunt1_Poochyena_FlyBackwards
	applymovement 3, LittlerootTown_MaysHouse_2F_Movement_Grunt1_Poochyena_FlyBackwards
	waitmovement 0
	playse SE_EFFECTIVE
	waitse
	return


LittlerootTown_MaysHouse_2F_Movement_Intro_PanCameraDownRight:
	walk_slow_diag_southeast
	walk_slow_diag_southeast
	step_end

LittlerootTown_MaysHouse_2F_Movement_PichuAdvancesOnGrunt2:
	lock_facing_direction
	walk_fast_down
	walk_fast_up
	unlock_facing_direction
	step_end

LittlerootTown_MaysHouse_2F_Movement_Grunt2FliesBackwards:
	lock_facing_direction
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	step_end

LittlerootTown_MaysHouse_2F_Movement_PoochyenaMovesToEngage:
	walk_fastest_up
	walk_fastest_left
	walk_fastest_left
	step_end

LittlerootTown_MaysHouse_2F_Movement_Grunt1MovesToEngage:
	lock_facing_direction
	walk_right
	unlock_facing_direction
	walk_up
	face_left
	step_end

LittlerootTown_MaysHouse_2F_Movement_PichuAdvancesOnGrunt1:
	lock_facing_direction
	walk_fast_right
	walk_fast_left
	unlock_facing_direction
	step_end

LittlerootTown_MaysHouse_2F_Movement_Grunt1_Poochyena_FlyBackwards:
	lock_facing_direction
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	unlock_facing_direction
	step_end

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

LittlerootTown_MaysHouse_2F_TheRescueDefeatedGrunt2_Text_0:
	.string "Intruder 2: Why, you little!...\pPooch, get 'em!$"

LittlerootTown_MaysHouse_2F_Intro_Grunt_2_Intro::
	.string "Sorry, kid...$"

LittlerootTown_MaysHouse_2F_Intro_Grunt_2_Defeat::
	.string "Wait, what?$"

LittlerootTown_MaysHouse_2F_Intro_Grunt_1_Intro::
	.string "You shouldn't have messed with us!$"

LittlerootTown_MaysHouse_2F_Intro_Grunt_1_Defeat::
	.string "Oh, I'm in trouble...$"
