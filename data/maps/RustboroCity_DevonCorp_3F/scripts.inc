RustboroCity_DevonCorp_3F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, RustboroCity_DevonCorp_3F_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

RustboroCity_DevonCorp_3F_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
	map_script_2 VAR_RUSTBORO_CITY_STATE, 1, RustboroCity_DevonCorp_3F_EventScript_JosephStone
	.2byte 0


RustboroCity_DevonCorp_3F_EventScript_JosephStone::
	setvar VAR_RUSTBORO_CITY_STATE, 2
	lock
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, RustboroCity_DevonCorp_3F_Movement_CameraEntrance
	applymovement 4, RustboroCity_DevonCorp_3F_Movement_Guard1Entrance
	applymovement 5, RustboroCity_DevonCorp_3F_Movement_Guard2Entrance
	applymovement OBJ_EVENT_ID_PLAYER, RustboroCity_DevonCorp_3F_Movement_PlayerEntrance
	waitmovement 0
	delay 60
	msgbox RustboroCity_DevonCorp_3F_Text_JosephStone1, MSGBOX_AUTOCLOSE
	end


RustboroCity_DevonCorp_3F_EventScript_RareRocksDisplay::
	msgbox RustboroCity_DevonCorp_3F_Text_RareRocksDisplay, MSGBOX_SIGN
	return


RustboroCity_DevonCorp_3F_Movement_Guard1Entrance:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	step_end

RustboroCity_DevonCorp_3F_Movement_Guard2Entrance:
	walk_up
	walk_up
	walk_up
	walk_in_place_right
	step_end

RustboroCity_DevonCorp_3F_Movement_PlayerEntrance:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	step_end

RustboroCity_DevonCorp_3F_Movement_CameraEntrance:
	walk_diag_northeast
	walk_diag_northeast
	walk_diag_northeast
	walk_diag_northeast
	walk_slow_right
	walk_slow_right
	walk_slow_right
	step_end

RustboroCity_DevonCorp_3F_Text_JosephStone1::
	.string "I'm very busy so I won't keep you for\n"
	.string "long.\p"
	.string "My name is Stone and I'm the President\n"
	.string "of the Board of the Devon Corporation.\p"
	.string "I simply wanted to thank you for saving\n"
	.string "our truck in Petalburg.\p"
	.string "Truly, you put most of security forces\n"
	.string "to shame!\p"
	.string "I am prepared to pay 5,000 for service\n"
	.string "rendered and more for future work.\p"
	.string "Which brings me to my next point...\p"
	.string "I need reliable Trainers to escort some\n"
	.string "goods from Rustborough to Slateport.\p"
	.string "Be at the harbour when it arrives and\n"
	.string "the men will sort you out.\p"
	.string "I am offering you 10,000 for the job\n"
	.string "and-$"

RustboroCity_DevonCorp_3F_Text_RareRocksDisplay::
	.string "It's a collection of rare rocks and\n"
	.string "stones assembled by the President.$"
