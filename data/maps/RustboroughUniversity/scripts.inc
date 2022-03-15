RustboroughUniversity_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, RustboroughUniversity_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

RustboroughUniversity_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
	map_script_2 VAR_RUSTBORO_CITY_STATE, 0, RustboroughUniversity_EventScript_FirstEntry
	.2byte 0


RustboroughUniversity_EventScript_FirstEntry::
	setvar VAR_RUSTBORO_CITY_STATE, 1
	lock
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, RustboroughUniversity_Movement_MoveCameraUp14
	applymovement OBJ_EVENT_ID_PLAYER, RustboroughUniversity_Movement_MovePlayerUp12
	msgbox RustboroughUniversity_Text_RoxanneIntro1
	waitmovement 0
	playse SE_PIN
	applymovement 7, Common_Movement_ExclamationMarkLookDown
	waitmovement 0
	delay 60
	applymovement 7, Common_Movement_WalkDown2
	applymovement OBJ_EVENT_ID_CAMERA, Common_Movement_WalkDown2
	waitmovement 0
	special RemoveCameraObject
	msgbox RustboroughUniversity_Text_RoxanneIntro2
	applymovement 7, RustboroughUniversity_Movement_MoveRoxanneIntoBattlePosition
	waitmovement 0
	msgbox RustboroughUniversity_EventScript_FirstEntry_Text_0
	applymovement OBJ_EVENT_ID_PLAYER, RustboroughUniversity_Movement_MovePlayerIntoBattlePosition
	msgbox RustboroughUniversity_EventScript_FirstEntry_Text_1, MSGBOX_AUTOCLOSE
	waitmovement 0
	applymovement 7, Common_Movement_FaceDown
	msgbox RustboroughUniversity_Text_RoxanneIntro3, MSGBOX_AUTOCLOSE
	applymovement 7, Common_Movement_FaceRight
	waitmovement 0
	delay 30
	msgbox RustboroughUniversity_EventScript_FirstEntry_Text_2, MSGBOX_YESNO
	compare VAR_RESULT, 0
	goto_if_eq RustboroughUniversity_EventScript_FirstEntry_2
RustboroughUniversity_EventScript_FirstEntry_1:
	msgbox RustboroughUniversity_EventScript_FirstEntry_Text_4, MSGBOX_AUTOCLOSE
	release
	end

RustboroughUniversity_EventScript_FirstEntry_2:
	msgbox RustboroughUniversity_EventScript_FirstEntry_Text_3
	goto RustboroughUniversity_EventScript_FirstEntry_1


RustboroughUniversity_EventScript_NPCGolemFact::
	lock
	faceplayer
	msgbox RustboroughUniversity_EventScript_NPCGolemFact_Text_0, MSGBOX_NPC
	release
	end


RustboroughUniversity_EventScript_NPCLevitationFact::
	lock
	faceplayer
	msgbox RustboroughUniversity_EventScript_NPCLevitationFact_Text_0, MSGBOX_NPC
	release
	end


RustboroughUniversity_Movement_MovePlayerUp12:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

RustboroughUniversity_Movement_MoveCameraUp14:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

RustboroughUniversity_Movement_MoveRoxanneIntoBattlePosition:
	walk_left
	walk_left
	walk_in_place_right
	step_end

RustboroughUniversity_Movement_MovePlayerIntoBattlePosition:
	walk_up
	walk_up
	walk_fast_right
	walk_fast_right
	walk_in_place_fast_left
	step_end

RustboroughUniversity_EventScript_FirstEntry_Text_0:
	.string "Move to the other side of the training\n"
	.string "area, please.$"

RustboroughUniversity_EventScript_FirstEntry_Text_1:
	.string "Come on, chop-chop!$"

RustboroughUniversity_EventScript_FirstEntry_Text_2:
	.string "Are you ready?$"

RustboroughUniversity_EventScript_FirstEntry_Text_3:
	.string "Too late now!$"

RustboroughUniversity_EventScript_FirstEntry_Text_4:
	.string "I'm looking forward to studying your\n"
	.string "technique...$"

RustboroughUniversity_EventScript_NPCGolemFact_Text_0:
	.string "Between Red, Blue, and Yellow Versions\n"
	.string "in Generation I\p"
	.string ", Golem is the only monster that cannot\n"
	.string "ever be seen without trading\p"
	.string "However, its existence is implied by a\n"
	.string "non-player character\p"
	.string "who had just received his friend's\n"
	.string "Graveler.$"

RustboroughUniversity_EventScript_NPCLevitationFact_Text_0:
	.string "Did you know that a lot of monsters are\n"
	.string "airborne?\p"
	.string "That makes them completely immune to\n"
	.string "moves like Earthquake & Bulldoze!\p"
	.string "However, attacks like Drill Run and Mud\n"
	.string "Bomb still hit them...$"

RustboroughUniversity_Text_RoxanneIntro1::
	.string "Roxanne: So, in summary, humans and\n"
	.string "monsters have a symbiotic\l"
	.string "relationship.\p"
	.string "Humans use monsters as companions, or\n"
	.string "for work or battling.\p"
	.string "And monsters rely on humans for food,\n"
	.string "shelter and, yes, training.\p"
	.string "While it might take a monster decades\n"
	.string "to reach its full potential in the wild...\p"
	.string "...with a good trainer that process can\n"
	.string "take as little as months.\p"
	.string "Of course, that greatly increases their\n"
	.string "chances of sexual reproduction...$"

RustboroughUniversity_Text_RoxanneIntro2::
	.string "You know, I don't appreciate you\n"
	.string "walking in halfway through my class.\p"
	.string "I mean, really, it's disprespectful, lazy\n"
	.string "and...\p"
	.string "Oh? Norman sent you to find out about\n"
	.string "gyms and the League?\p"
	.string "That doesn't explain why you barged in\n"
	.string "while I was teaching a class...\p"
	.string "Although...\p"
	.string "Maybe you can make it up to me...\p"
	.string "You're clearly no stranger to battling,\n"
	.string "so...\p"
	.string "Class, I think this is an opportunity\n"
	.string "for a demonstration!$"

RustboroughUniversity_Text_RoxanneIntro3::
	.string "As penance for the interruption, this\n"
	.string "one has kindly volunteered!\p"
	.string "We'll be showing you a monster battle in\n"
	.string "League format!\p"
	.string "For those of you who don't know...\p"
	.string "In League battles, all monsters are set\n"
	.string "to Lv 50 by the computer.\p"
	.string "Their stats are recalculated\n"
	.string "accordingly.\p"
	.string "What's more, Trainers are not allowed to\n"
	.string "use items.\p"
	.string "Are you ready to see what some\n"
	.string "well-trained monsters can do?$"
