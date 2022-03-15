RustboroCity_Gym_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, RustboroCity_Gym_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

RustboroCity_Gym_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
	map_script_2 VAR_RUSTBORO_CITY_STATE, 0, RustboroCity_Gym_EventScript_TriggerGoSeeRoxanne
	.2byte 0


RustboroCity_Gym_EventScript_GymGuide::
	lock
	faceplayer
	switch VAR_RUSTBORO_CITY_STATE
	case 0, RustboroCity_Gym_EventScript_GymGuide_3
	goto_if_set FLAG_DEFEATED_RUSTBORO_GYM, RustboroCity_Gym_EventScript_GymGuide_5
	msgbox RustboroCity_Gym_Text_GymGuideAdvice
RustboroCity_Gym_EventScript_GymGuide_1:
	release
	end

RustboroCity_Gym_EventScript_GymGuide_3:
	msgbox RustboroCity_Gym_Text_GymGuide_GoSeeRoxanne
	goto RustboroCity_Gym_EventScript_GymGuide_1

RustboroCity_Gym_EventScript_GymGuide_5:
	msgbox RustboroCity_Gym_Text_GymGuidePostVictory
	goto RustboroCity_Gym_EventScript_GymGuide_1


RustboroCity_Gym_EventScript_TriggerGoSeeRoxanne::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkUp
	waitmovement 0
	applymovement 4, Common_Movement_ExclamationMarkLookRight
	playse SE_PIN
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceLeft
	waitmovement 0
	msgbox RustboroCity_Gym_Text_GymGuide_GoSeeRoxanne, MSGBOX_AUTOCLOSE
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkDown
	waitmovement 0
	warp MAP_RUSTBOROUGH_SOUTH, 19, 22, 42
	waitstate
	end


RustboroCity_Gym_Text_GymGuide_GoSeeRoxanne::
	.string "Yo! Are you here to see Roxanne?\n"
	.string "She's not here right now...\p"
	.string "But she is giving a lecture at the\n"
	.string "university!\p"
	.string "Big building just north of the gym, you\n"
	.string "can't miss it!$"

RustboroCity_Gym_Text_GymGuideAdvice::
	.string "Yo, how's it going?\p"
	.string "Listen, my friend!\n"
	.string "Would you like to become the CHAMPION?\p"
	.string "I'm no TRAINER, not me, but I can\n"
	.string "sure give you winning advice.\p"
	.string "That's settled, then! We'll aim for the\n"
	.string "POKéMON CHAMPIONSHIP together!\p"
	.string "It's your job as a TRAINER to collect\n"
	.string "GYM BADGES, am I right?\p"
	.string "But GYM LEADERS aren't pushovers!\p"
	.string "And that's where I come in!\n"
	.string "I'm here to provide expert advice!\p"
	.string "ROXANNE, the GYM LEADER, is a user\n"
	.string "of ROCK-type POKéMON.\p"
	.string "The ROCK type is very durable, but\n"
	.string "it can't stand WATER-type and\l"
	.string "GRASS-type moves.\p"
	.string "Come see me afterwards, if you beat\n"
	.string "the GYM LEADER.\p"
	.string "Well, go for it!$"

RustboroCity_Gym_Text_GymGuidePostVictory::
	.string "Whoa! What a breathtaking victory!\n"
	.string "My cheering must've worked!\p"
	.string "Great!\n"
	.string "Check your TRAINER CARD.\p"
	.string "The STONE BADGE you got should be\n"
	.string "properly recorded on it.\p"
	.string "In other words…\p"
	.string "You've climbed the first step on\n"
	.string "the stairs to the CHAMPIONSHIP!\p"
	.string "That's got to feel awesome!$"
