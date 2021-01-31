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
	setvar VAR_CONTINUE_AFTER_LOSING_BATTLE, 1
	trainerbattle_no_intro TRAINER_MAY_ROUTE_103_TORCHIC, LittlerootTown_ProfessorBirchsLab_MayDefeat
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq LittlerootTown_ProfessorBirchsLab_ButFirst_2
	msgbox LittlerootTown_ProfessorBirchsLab_Disappointing, MSGBOX_DEFAULT
LittlerootTown_ProfessorBirchsLab_ButFirst_1:
	goto LittlerootTown_ProfessorBirchsLab_PostMayBattle
	end

LittlerootTown_ProfessorBirchsLab_ButFirst_2:
	msgbox LittlerootTown_ProfessorBirchsLab_NotBad, MSGBOX_DEFAULT
	goto LittlerootTown_ProfessorBirchsLab_ButFirst_1


LittlerootTown_ProfessorBirchsLab_PostMayBattle::
	applymovement 2, LittlerootTown_ProfessorBirchsLab_Movement_BirchFetchPokedex
	waitmovement 0
	playfanfare MUS_OBTAIN_ITEM
	msgbox LittlerootTown_ProfessorBirchsLab_PostMayBattle_Text_0
	waitfanfare
	msgbox LittlerootTown_ProfessorBirchsLab_Congrats, MSGBOX_DEFAULT
	giveitem ITEM_POKE_BALL, 5
	msgbox LittlerootTown_ProfessorBirchsLab_TheseArePokeBalls, MSGBOX_DEFAULT
	releaseall
	end


LittlerootTown_ProfessorBirchsLab_RatePokedex::
	lock
	faceplayer
	goto ProfBirch_EventScript_AskRatePokedex
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
	step_end

LittlerootTown_ProfessorBirchsLab_Movement_FacingMay:
	face_down
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
	.string "what you did last night. There are no\l"
	.string "words with which I can express my\l"
	.string "gratitude.\p"
	.string "I decided to let you keep that special\n"
	.string "Pichu. I have a feeling you'll get along\l"
	.string "with it really well!$"

LittlerootTown_ProfessorBirchsLab_IHaveAJobForYou::
	.string "Birch: Ah yes, the other thing I wanted\n"
	.string "to mention... There is a job I would like\l"
	.string "to offer you. I need someone to help me\l"
	.string "gather information on all monsters in\l"
	.string "the region. You would take this\l"
	.string "Pokedex and travel around Hoenn\l"
	.string "catching them, analysing them,\l"
	.string "registering their information here! But\l"
	.string "first, howewer...$"

LittlerootTown_ProfessorBirchsLab_GetRivalToTestYou::
	.string "Birch: Oh, May! Great timing...\n"
	.string "{PLAYER}, I would like you to have a\l"
	.string "battle with my daughter. Last night\l"
	.string "was indeed impressive, but I want to\l"
	.string "make sure it wasn't all just a fluke.\l"
	.string "Consider it a test to see if you're up\l"
	.string "to the task!$"

LittlerootTown_ProfessorBirchsLab_May_Intro::
	.string "May: That's right! I've been itching to\n"
	.string "have a battle with you since I saw what\l"
	.string "you did last night! C'mon, after beating\l"
	.string "down those thugs, you shouldn't be\l"
	.string "afraid to battle me... Right?$"

LittlerootTown_ProfessorBirchsLab_MayDefeat::
	.string "WHAT? You... {PLAYER}, you're really\n"
	.string "good!$"

LittlerootTown_ProfessorBirchsLab_NotBad::
	.string "Birch: That was a great battle,\n"
	.string "{PLAYER}! I didn't expect any less.\l"
	.string "Now, as I promised, I shall give you a\l"
	.string "Pokédex!$"

LittlerootTown_ProfessorBirchsLab_Congrats::
	.string "Birch: This Pokedex is a high-tech\n"
	.string "device that registers data of any\l"
	.string "monster you catch. It is actually\l"
	.string "pretty straightforward, you should\l"
	.string "find it easy to use.\p"
	.string "May: Kudos for winning, {PLAYER}! I\n"
	.string "gotta admit I have underestimated\l"
	.string "you... As a reward, here's a little gift!$"

LittlerootTown_ProfessorBirchsLab_Disappointing::
	.string "Birch: Oh... that was disappointing,\n"
	.string "{PLAYER}. Must I suppose that\l"
	.string "performance last night was only dumb\l"
	.string "luck? Still, I really need help for my\l"
	.string "research, so I can't be too picky. I'll\l"
	.string "give you the Pokédex anyways.$"

LittlerootTown_ProfessorBirchsLab_Hehehehe::
	.string "Birch: This Pokedex is a high-tech\n"
	.string "device that registers data of any\l"
	.string "monster you catch. It is extremely\l"
	.string "easy to use, even a baby should\l"
	.string "understand how it works.\p"
	.string "May: Hehehehe, don't feel too bad,\n"
	.string "{PLAYER}! It's just that I'm too\l"
	.string "strong for you! Here's a little gift\l"
	.string "because I feel sorry for you!$"

LittlerootTown_ProfessorBirchsLab_TheseArePokeBalls::
	.string "May: These are Poké Balls! They are used\n"
	.string "for catching wild Pokémon! You need to\l"
	.string "weaken your target a little bit first\l"
	.string "to make 'em easier to catch.$"

LittlerootTown_ProfessorBirchsLab_SeriousLookingMachine::
	.string "Wow, Core 2 Duo?\n"
	.string "4 gigs of RAM?\p"
	.string "It's a serious looking machine. Birch\n"
	.string "must use it for research.$"

LittlerootTown_ProfessorBirchsLab_EventScript_PCUsedForResearch::
	.string "It's a PC used for research. Better not\n"
	.string "mess with it.$"
