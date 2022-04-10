RustboroCity_DevonCorp_3F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, RustboroCity_DevonCorp_3F_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

RustboroCity_DevonCorp_3F_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
	map_script_2 VAR_RUSTBORO_CITY_STATE, 1, RustboroCity_DevonCorp_3F_EventScript_JosephStoneIntro
	.2byte 0


RustboroCity_DevonCorp_3F_EventScript_JosephStoneIntro::
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
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 1
	setvar VAR_0x8006, 16
	setvar VAR_0x8007, 3
	special ShakeCamera
	playse SE_EFFECTIVE
	goto RustboroCity_DevonCorp_3F_EventScript_SuddenLargeNoise
	return


RustboroCity_DevonCorp_3F_EventScript_SuddenLargeNoise::
	applymovement 4, Common_Movement_ExclamationMark
	applymovement 5, Common_Movement_ExclamationMark
	applymovement 6, Common_Movement_ExclamationMark
	applymovement 7, Common_Movement_ExclamationMark
	applymovement 1, Common_Movement_ExclamationMark
	waitmovement 0
	delay 60
	msgbox RustboroCity_DevonCorp_3F_EventScript_SuddenLargeNoise_Text_0
	applymovement 7, Common_Movement_WalkInPlaceDown
	waitmovement 0
	applymovement 1, Common_Movement_WalkInPlaceUp
	waitmovement 0
	msgbox RustboroCity_DevonCorp_3F_Text_RareRocksGuard4Dialogue
	applymovement 1, Common_Movement_WalkInPlaceLeft
	waitmovement 0
	msgbox RustboroCity_DevonCorp_3F_Text_JosephStone2
	applymovement 4, Common_Movement_WalkInPlaceRight
	applymovement 5, Common_Movement_WalkInPlaceRight
	waitmovement 0
	msgbox RustboroCity_DevonCorp_3F_EventScript_SuddenLargeNoise_Text_1
	applymovement 4, RustboroCity_DevonCorp_3F_Guard1WalkRightFaceDown
	applymovement 5, RustboroCity_DevonCorp_3F_Guard2WalkRightFaceUp
	applymovement OBJ_EVENT_ID_PLAYER, RustboroCity_DevonCorp_3F_PlayerLookUpAndDown
	msgbox RustboroCity_DevonCorp_3F_EventScript_SuddenLargeNoise_Text_2
	waitmovement 0
	applymovement 4, Common_Movement_WalkLeft3
	applymovement 5, Common_Movement_WalkLeft3
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkLeft3
	waitmovement 0
	warp MAP_RUSTBORO_CITY_DEVON_CORP_2F, 255, 2, 2
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

RustboroCity_DevonCorp_3F_Guard1WalkRightFaceDown:
	walk_right
	face_down
	step_end

RustboroCity_DevonCorp_3F_Guard2WalkRightFaceUp:
	walk_right
	face_up
	step_end

RustboroCity_DevonCorp_3F_PlayerLookUpAndDown:
	face_down
	delay_16
	face_up
	delay_16
	face_down
	step_end

RustboroCity_DevonCorp_3F_EventScript_SuddenLargeNoise_Text_0:
	.string "...what the hell was that?$"

RustboroCity_DevonCorp_3F_EventScript_SuddenLargeNoise_Text_1:
	.string "Yes, sir!$"

RustboroCity_DevonCorp_3F_EventScript_SuddenLargeNoise_Text_2:
	.string "Let's go, newbie!$"

RustboroCity_DevonCorp_3F_Text_JosephStone1::
	.string "TEXT$"

RustboroCity_DevonCorp_3F_Text_RareRocksDisplay::
	.string "It's a collection of rare rocks and\n"
	.string "stones assembled by the President.$"

RustboroCity_DevonCorp_3F_Text_RareRocksGuard4Dialogue::
	.string "Sir! Security downstairs say there's\n"
	.string "been a breach!\p"
	.string "Magma activists have stormed the rear\n"
	.string "entrance to the building!\p"
	.string "We have to take you to the helipad!$"

RustboroCity_DevonCorp_3F_Text_JosephStone2::
	.string "I see...\p"
	.string "Well, aren't we lucky?\p"
	.string "What an excellent opportunity to put\n"
	.string "your skills to use!\p"
	.string "You three, go downstairs and deal with\n"
	.string "these terrorists!\p"
	.string "I have to get out of here as soon as\n"
	.string "possible...$"
