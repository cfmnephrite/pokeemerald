LittlerootTown_ProfessorBirchsLab_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LittlerootTown_ProfessorBirchsLab_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, LittlerootTown_ProfessorBirchsLab_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE
	.byte 0

LittlerootTown_ProfessorBirchsLab_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 2, LittlerootTown_ProfessorBirchsLab_Script_Intro
	.2byte 0

LittlerootTown_ProfessorBirchsLab_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE:
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 2, LittlerootTown_ProfessorBirchsLab_FacePlayerNorth
	.2byte 0


LittlerootTown_ProfessorBirchsLab_FacePlayerNorth::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end


LittlerootTown_ProfessorBirchsLab_Script_Intro::
	lockall
	setvar VAR_LITTLEROOT_INTRO_STATE, 3
	msgbox LittlerootTown_ProfessorBirchsLab_ThankYouSoMuch, MSGBOX_DEFAULT
	waitmessage
	playfanfare MUS_OBTAIN_ITEM
	waitfanfare
	msgbox LittlerootTown_ProfessorBirchsLab_Script_Intro_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq LittlerootTown_ProfessorBirchsLab_Script_Intro_2
LittlerootTown_ProfessorBirchsLab_Script_Intro_1:
	goto LittlerootTown_ProfessorBirchsLab_ButFirst
	end

LittlerootTown_ProfessorBirchsLab_Script_Intro_2:
	setvar VAR_0x8004, 0
	call Common_EventScript_NameReceivedPartyMon
	goto LittlerootTown_ProfessorBirchsLab_Script_Intro_1


LittlerootTown_ProfessorBirchsLab_ButFirst::
	msgbox LittlerootTown_ProfessorBirchsLab_IHaveAJobForYou, MSGBOX_DEFAULT
	addobject 3
	msgbox LittlerootTown_ProfessorBirchsLab_ButFirst_Text_0
	applymovement 3, LittlerootTown_ProfessorBirchsLab_Movement_MayEnter
	waitmovement 0
	msgbox LittlerootTown_ProfessorBirchsLab_GetRivalToTestYou, MSGBOX_DEFAULT
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_ProfessorBirchsLab_Movement_FacingMay
	applymovement 3, LittlerootTown_ProfessorBirchsLab_Movement_MayFacingPlayer
	setvar VAR_CONTINUE_AFTER_LOSING_BATTLE, 1
	trainerbattle_no_intro TRAINER_MAY_ROUTE_103_TORCHIC, LittlerootTown_ProfessorBirchsLab_MayDefeat
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq LittlerootTown_ProfessorBirchsLab_ButFirst_2
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_ProfessorBirchsLab_Movement_FacingBirch
	msgbox LittlerootTown_ProfessorBirchsLab_Disappointing, MSGBOX_DEFAULT
	setflag FLAG_LOST_MAY_BATTLE
LittlerootTown_ProfessorBirchsLab_ButFirst_1:
	goto LittlerootTown_ProfessorBirchsLab_PostMayBattle
	end

LittlerootTown_ProfessorBirchsLab_ButFirst_2:
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_ProfessorBirchsLab_Movement_FacingBirch
	msgbox LittlerootTown_ProfessorBirchsLab_NotBad, MSGBOX_DEFAULT
	goto LittlerootTown_ProfessorBirchsLab_ButFirst_1


LittlerootTown_ProfessorBirchsLab_PostMayBattle::
	applymovement 2, LittlerootTown_ProfessorBirchsLab_Movement_BirchFetchPokedex
	waitmovement 0
	playfanfare MUS_OBTAIN_ITEM
	msgbox LittlerootTown_ProfessorBirchsLab_PostMayBattle_Text_0
	waitfanfare
	setflag FLAG_RECEIVED_POKEDEX_FROM_BIRCH
	goto_if_unset FLAG_LOST_MAY_BATTLE, LittlerootTown_ProfessorBirchsLab_PostMayBattle_2
	msgbox LittlerootTown_ProfessorBirchsLab_ExplainPokedex2, MSGBOX_DEFAULT
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_ProfessorBirchsLab_Movement_FacingMay2
	msgbox LittlerootTown_ProfessorBirchsLab_Hehehehe, MSGBOX_DEFAULT
LittlerootTown_ProfessorBirchsLab_PostMayBattle_1:
	giveitem ITEM_POKE_BALL, 5
	msgbox LittlerootTown_ProfessorBirchsLab_TheseArePokeBalls, MSGBOX_DEFAULT
	releaseall
	end

LittlerootTown_ProfessorBirchsLab_PostMayBattle_2:
	msgbox LittlerootTown_ProfessorBirchsLab_ExplainPokedex1, MSGBOX_DEFAULT
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_ProfessorBirchsLab_Movement_FacingMay2
	msgbox LittlerootTown_ProfessorBirchsLab_Congrats, MSGBOX_DEFAULT
	goto LittlerootTown_ProfessorBirchsLab_PostMayBattle_1


LittlerootTown_ProfessorBirchsLab_RatePokedex::
	lock
	faceplayer
	goto ProfBirch_EventScript_AskRatePokedex
	release
	end


LittlerootTown_ProfessorBirchsLab_Rival::
	lock
	faceplayer
	msgbox LittlerootTown_ProfessorBirchsLab_TrainingMonstersIsDifficult, MSGBOX_DEFAULT
	release
	end


LittlerootTown_ProfessorBirchsLab_EventScript_Machine::
	msgbox LittlerootTown_ProfessorBirchsLab_SeriousLookingMachine, MSGBOX_SIGN
	end


LittlerootTown_ProfessorBirchsLab_EventScript_Book::
	msgbox LittlerootTown_ProfessorBirchsLab_EventScript_Book_Text_0, MSGBOX_SIGN
	end


LittlerootTown_ProfessorBirchsLab_EventScript_Bookshelf::
	msgbox LittlerootTown_ProfessorBirchsLab_EventScript_Bookshelf_Text_0, MSGBOX_SIGN
	end


LittlerootTown_ProfessorBirchsLab_EventScript_PC::
	msgbox LittlerootTown_ProfessorBirchsLab_EventScript_PCUsedForResearch, MSGBOX_SIGN
	end


LittlerootTown_ProfessorBirchsLab_Movement_MayEnter:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_ProfessorBirchsLab_Movement_FacingMay:
	face_right
	step_end

LittlerootTown_ProfessorBirchsLab_Movement_MayFacingPlayer:
	face_left
	step_end

LittlerootTown_ProfessorBirchsLab_Movement_FacingBirch:
	face_up
	step_end

LittlerootTown_ProfessorBirchsLab_Movement_FacingMay2:
	face_right
	step_end

LittlerootTown_ProfessorBirchsLab_Movement_BirchFetchPokedex:
	walk_up
	walk_up
	walk_down
	walk_down
	step_end

LittlerootTown_ProfessorBirchsLab_Script_Intro_Text_0:
	.string "Would you like to give a nickname to\n"
	.string "Pichu?$"

LittlerootTown_ProfessorBirchsLab_ButFirst_Text_0:
	.string "Daaaad!$"

LittlerootTown_ProfessorBirchsLab_PostMayBattle_Text_0:
	.string "{PLAYER} received the Pokédex!$"

LittlerootTown_ProfessorBirchsLab_EventScript_Book_Text_0:
	.string "It's a book too hard to read.$"

LittlerootTown_ProfessorBirchsLab_EventScript_Bookshelf_Text_0:
	.string "It's crammed with books on monsters.$"

LittlerootTown_ProfessorBirchsLab_ThankYouSoMuch::
	.string "Birch: {PLAYER}, thank you so much for\n"
	.string "what you did last night.\p"
	.string "There are no words with which I can\n"
	.string "express my gratitude.\p"
	.string "I decided to let you keep that special\n"
	.string "Pichu. I have a feeling you'll get along\l"
	.string "with it really well!$"

LittlerootTown_ProfessorBirchsLab_IHaveAJobForYou::
	.string "Birch: Ah yes, the other thing I wanted\n"
	.string "to mention...\p"
	.string "There is a job I would like to offer you.\p"
	.string "I need someone to help me gather\n"
	.string "information on all monsters in the\l"
	.string "region.\p"
	.string "You would take this Pokedex and travel\n"
	.string "around Hoenn catching them, analysing\l"
	.string "them, registering their information\l"
	.string "here!\p"
	.string "But first, howewer...$"

LittlerootTown_ProfessorBirchsLab_GetRivalToTestYou::
	.string "Birch: Oh, May! Great timing...\p"
	.string "{PLAYER}, I would like you to have a\n"
	.string "battle with my daughter.\p"
	.string "Last night was indeed impressive, but I\n"
	.string "want to make sure it wasn't all just a\l"
	.string "fluke.\p"
	.string "Consider it a test to see if you're up to\n"
	.string "the task!$"

LittlerootTown_ProfessorBirchsLab_May_Intro::
	.string "May: That's right!\p"
	.string "I've been itching to have a battle with\n"
	.string "you since I saw what you did last\l"
	.string "night!\p"
	.string "C'mon, after beating down those thugs,\n"
	.string "you shouldn't be afraid to battle me...\p"
	.string "Right?$"

LittlerootTown_ProfessorBirchsLab_MayDefeat::
	.string "WHAT? You... {PLAYER}, you're really\n"
	.string "good!$"

LittlerootTown_ProfessorBirchsLab_NotBad::
	.string "Birch: That was a great battle,\n"
	.string "{PLAYER}! I didn't expect any less.\p"
	.string "Now, as I promised, I shall give you a\n"
	.string "Pokédex!$"

LittlerootTown_ProfessorBirchsLab_ExplainPokedex1::
	.string "Birch: This Pokedex is a high-tech\n"
	.string "device that registers data of any\l"
	.string "monster you catch.\p"
	.string "It is actually pretty straightforward,\n"
	.string "you should find it easy to use.$"

LittlerootTown_ProfessorBirchsLab_Congrats::
	.string "May: Kudos for winning, {PLAYER}!\p"
	.string "I gotta admit, I have underestimated\n"
	.string "you...\p"
	.string "As a reward, here's a little gift!$"

LittlerootTown_ProfessorBirchsLab_Disappointing::
	.string "Birch: Oh... that was disappointing,\n"
	.string "{PLAYER}.\p"
	.string "So the feat of last night was only dumb\n"
	.string "luck?\p"
	.string "Still, I really need help for my\n"
	.string "research, so I can't be too picky.\p"
	.string "I'll give you the Pokédex anyways.$"

LittlerootTown_ProfessorBirchsLab_ExplainPokedex2::
	.string "Birch: This Pokedex is a high-tech\n"
	.string "device that registers data of any\l"
	.string "monster you catch.\p"
	.string "It is very easy to use, even a baby\n"
	.string "should understand how it works.\p"
	.string "$"

LittlerootTown_ProfessorBirchsLab_Hehehehe::
	.string "May: Hehehehe, don't feel too bad,\n"
	.string "{PLAYER}!\p"
	.string "It's just that I'm too strong for you!\p"
	.string "Here's a little gift, because I feel\n"
	.string "sorry for you!$"

LittlerootTown_ProfessorBirchsLab_TheseArePokeBalls::
	.string "May: These are Poké Balls!\p"
	.string "They are used for catching wild\n"
	.string "Pokémon!\p"
	.string "You need to weaken your target a little\n"
	.string "bit first to make 'em easier to catch.$"

LittlerootTown_ProfessorBirchsLab_TrainingMonstersIsDifficult::
	.string "May: Training monsters is difficult,\n"
	.string "you know.\p"
	.string "This is not a game where you can go back\n"
	.string "and make different choices, after all!$"

LittlerootTown_ProfessorBirchsLab_SeriousLookingMachine::
	.string "Wow, Core 2 Duo?\n"
	.string "4 gigs of RAM?\p"
	.string "It's a serious looking machine. Birch\n"
	.string "must use it for research.$"

LittlerootTown_ProfessorBirchsLab_EventScript_PCUsedForResearch::
	.string "It's a PC used for research. Better not\n"
	.string "mess with it.$"
