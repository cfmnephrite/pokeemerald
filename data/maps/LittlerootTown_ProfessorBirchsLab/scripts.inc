LittlerootTown_ProfessorBirchsLab_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LittlerootTown_ProfessorBirchsLab_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

LittlerootTown_ProfessorBirchsLab_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
	map_script_2 VAR_BIRCH_LAB_STATE, 2, LittlerootTown_ProfessorBirchsLab_GivePichu
	.2byte 0


LittlerootTown_ProfessorBirchsLab_GivePichu::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_ProfessorBirchsLab_Movement_PlayerEnter
	waitmovement 0
	msgbox LittlerootTown_ProfessorBirchsLab_ThankYouSoMuch, MSGBOX_DEFAULT
	waitmessage
	playfanfare MUS_FANFA4
	waitfanfare
	msgbox LittlerootTown_ProfessorBirchsLab_GivePichu_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq LittlerootTown_ProfessorBirchsLab_GivePichu_2
	goto LittlerootTown_ProfessorBirchsLab_ButFirst
LittlerootTown_ProfessorBirchsLab_GivePichu_1:
	end

LittlerootTown_ProfessorBirchsLab_GivePichu_2:
	setvar VAR_0x8004, 0
	call Common_EventScript_NameReceivedPartyMon
	goto LittlerootTown_ProfessorBirchsLab_ButFirst
	goto LittlerootTown_ProfessorBirchsLab_GivePichu_1


LittlerootTown_ProfessorBirchsLab_ButFirst::
	msgbox LittlerootTown_ProfessorBirchsLab_IHaveAJobForYou, MSGBOX_DEFAULT
	addobject 4
	msgbox LittlerootTown_ProfessorBirchsLab_ButFirst_Text_0
	applymovement 4, LittlerootTown_ProfessorBirchsLab_Movement_MayEnter
	waitmovement 0
	msgbox LittlerootTown_ProfessorBirchsLab_GetRivalToTestYou, MSGBOX_DEFAULT
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_ProfessorBirchsLab_Movement_FacingMay
	setvar VAR_CONTINUE_AFTER_LOSING_BATTLE, 1
	trainerbattle_no_intro TRAINER_MAY_ROUTE_103_TORCHIC, LittlerootTown_ProfessorBirchsLab_MayDefeat
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq LittlerootTown_ProfessorBirchsLab_ButFirst_2
	call LittlerootTown_ProfessorBirchsLab_LostMayBattle
LittlerootTown_ProfessorBirchsLab_ButFirst_1:
	special HealPlayerParty
	end

LittlerootTown_ProfessorBirchsLab_ButFirst_2:
	call LittlerootTown_ProfessorBirchsLab_WonMayBattle
	goto LittlerootTown_ProfessorBirchsLab_ButFirst_1


LittlerootTown_ProfessorBirchsLab_WonMayBattle::
	msgbox LittlerootTown_ProfessorBirchsLab_NotBad, MSGBOX_DEFAULT
	applymovement 2, LittlerootTown_ProfessorBirchsLab_Movement_BirchFetchPokedex
	waitmovement 0
	playfanfare MUS_FANFA4
	msgbox LittlerootTown_ProfessorBirchsLab_WonMayBattle_Text_0
	waitfanfare
	msgbox LittlerootTown_ProfessorBirchsLab_Congrats, MSGBOX_DEFAULT
	giveitem ITEM_POKE_BALL, 5
	msgbox LittlerootTown_ProfessorBirchsLab_TheseArePokeBalls, MSGBOX_DEFAULT
	setvar VAR_BIRCH_LAB_STATE, 3
	releaseall
	end


LittlerootTown_ProfessorBirchsLab_LostMayBattle::
	msgbox LittlerootTown_ProfessorBirchsLab_Disappointing, MSGBOX_DEFAULT
	applymovement 2, LittlerootTown_ProfessorBirchsLab_Movement_BirchFetchPokedex
	waitmovement 0
	playfanfare MUS_FANFA4
	msgbox LittlerootTown_ProfessorBirchsLab_WonMayBattle_Text_0
	waitfanfare
	msgbox LittlerootTown_ProfessorBirchsLab_Hehehehe, MSGBOX_DEFAULT
	giveitem ITEM_POKE_BALL, 5
	msgbox LittlerootTown_ProfessorBirchsLab_TheseArePokeBalls, MSGBOX_DEFAULT
	setvar VAR_BIRCH_LAB_STATE, 3
	releaseall
	end


LittlerootTown_ProfessorBirchsLab_RatePokedex::
	lock
	faceplayer
	goto ProfBirch_EventScript_AskRatePokedex
	end


LittlerootTown_ProfessorBirchsLab_Machine::
	msgbox LittlerootTown_ProfessorBirchsLab_SeriousLookingMachine, MSGBOX_SIGN
	end


LittlerootTown_ProfessorBirchsLab_Book::
	msgbox LittlerootTown_ProfessorBirchsLab_Book_Text_0, MSGBOX_SIGN
	end


LittlerootTown_ProfessorBirchsLab_Bookshelf::
	msgbox LittlerootTown_ProfessorBirchsLab_Bookshelf_Text_0, MSGBOX_SIGN
	end


LittlerootTown_ProfessorBirchsLab_PC::
	msgbox LittlerootTown_ProfessorBirchsLab_PCUsedForResearch, MSGBOX_SIGN
	end


LittlerootTown_ProfessorBirchsLab_Movement_PlayerEnter:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

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

LittlerootTown_ProfessorBirchsLab_GivePichu_Text_0:
	.string "Would you like to give a nickname to\n"
	.string "Pichu?$"

LittlerootTown_ProfessorBirchsLab_ButFirst_Text_0:
	.string "Daaaad!$"

LittlerootTown_ProfessorBirchsLab_WonMayBattle_Text_0:
	.string "{PLAYER} received the Pokédex!$"

LittlerootTown_ProfessorBirchsLab_Book_Text_0:
	.string "It's a book too hard to read.$"

LittlerootTown_ProfessorBirchsLab_Bookshelf_Text_0:
	.string "It's crammed with books on Pokémon.$"

LittlerootTown_ProfessorBirchsLab_ThankYouSoMuch::
	.string "Birch: {PLAYER}, thank you so much for\n"
	.string "what you did last night. There are no\l"
	.string "words with which I can express my\l"
	.string "gratitude.\p"
	.string "Mom: That was so incredibly brave,\n"
	.string "{PLAYER}. I'm so proud of you!\p"
	.string "Birch: So before your mother and I were\n"
	.string "having a little talk... With her consent\l"
	.string "I decided to let you keep this special\l"
	.string "Pichu. I have a feeling you'll get along\l"
	.string "with it really well!$"

LittlerootTown_ProfessorBirchsLab_IHaveAJobForYou::
	.string "Mom: Up until now I wanted you to focus\n"
	.string "on graduating from school. That is why\l"
	.string "I never let you keep Pokemon until now.\l"
	.string "But now you're old enough to be able to\l"
	.string "look after yourself.\p"
	.string "Birch: Ah yes, another thing we were\n"
	.string "discussing... There is a job I would like\l"
	.string "to offer you. I need someone to help me\l"
	.string "researching Pokémon. You would take\l"
	.string "this Pokedex and travel around Hoenn\l"
	.string "catching Pokémon and registering them\l"
	.string "here! But first, howewer...$"

LittlerootTown_ProfessorBirchsLab_GetRivalToTestYou::
	.string "Birch: Oh, May! Great timing...\n"
	.string "{PLAYER}, I would like you to have a\l"
	.string "Pokémon battle with my daughter. The\l"
	.string "feat of last night was indeed\l"
	.string "impressive, but I want to make sure it\l"
	.string "wasn't all just a fluke. Consider it a\l"
	.string "formality to see if you're up to the\l"
	.string "task!$"

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
	.string "Pokemon you catch. It is actually\l"
	.string "pretty straightforward, you should\l"
	.string "find it easy to use.\p"
	.string "May: Kudos for winning, {PLAYER}! I\n"
	.string "gotta admit I have underestimated\l"
	.string "you... As a reward, here's a little gift!$"

LittlerootTown_ProfessorBirchsLab_Disappointing::
	.string "Birch: Oh... that was disappointing,\n"
	.string "{PLAYER}. Must I suppose that last\l"
	.string "night performance was only dumb luck?\l"
	.string "Still, I really need help for my\l"
	.string "research, so I can't be too picky. I'll\l"
	.string "give you the Pokédex anyways.$"

LittlerootTown_ProfessorBirchsLab_Hehehehe::
	.string "Birch: This Pokedex is a high-tech\n"
	.string "device that registers data of any\l"
	.string "Pokemon you catch. It is extremely\l"
	.string "easy to use, even a baby should\l"
	.string "understand how it works.\p"
	.string "May: Hehehehe, don't feel too bad,\n"
	.string "{PLAYER}! It's just that I'm too\l"
	.string "strong for you! Here's a little gift\l"
	.string "because I feel sorry for you!$"

LittlerootTown_ProfessorBirchsLab_TheseArePokeBalls::
	.string "May: These are Poké Balls! They are used\n"
	.string "for catching wild Pokémon! You need to\l"
	.string "weaken a little bit to make 'em easier\l"
	.string "to catch.$"

LittlerootTown_ProfessorBirchsLab_SeriousLookingMachine::
	.string "It's a serious looking machine. Birch\n"
	.string "must use it for research.$"

LittlerootTown_ProfessorBirchsLab_PCUsedForResearch::
	.string "It's a PC used for research. Better not\n"
	.string "mess with it.$"
