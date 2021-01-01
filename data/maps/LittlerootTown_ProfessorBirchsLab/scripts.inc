.set LOCALID_AIDE, 1
.set LOCALID_BIRCH, 2
.set LOCALID_MOM, 3
.set LOCALID_RIVAL, 4

LittlerootTown_ProfessorBirchsLab_MapScripts:: @ 81F9C91
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LittlerootTown_ProfessorBirchsLab_OnFrame
	.byte 0

LittlerootTown_ProfessorBirchsLab_OnFrame: @ 81F9DB9
	map_script_2 VAR_BIRCH_LAB_STATE, 2, LittlerootTown_ProfessorBirchsLab_EventScript_GivePichuEvent
	.2byte 0

LittlerootTown_ProfessorBirchsLab_EventScript_GivePichuEvent:: @ 81F9E67
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_ProfessorBirchsLab_Movement_PlayerEnter
	waitmovement 0
	goto LittlerootTown_ProfessorBirchsLab_EventScript_GivePichu
	end

LittlerootTown_ProfessorBirchsLab_EventScript_GivePichu::
	lockall
	msgbox LittlerootTown_ProfessorBirchsLab_Text_ThankYouSoMuch, MSGBOX_DEFAULT
	waitmessage
	playfanfare MUS_FANFA4
	waitfanfare
	msgbox LittlerootTown_ProfessorBirchsLab_Text_GiveNicknameToPichu, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_NicknamePichu
	compare VAR_RESULT, NO
	goto_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_ButFirst
	end

LittlerootTown_ProfessorBirchsLab_EventScript_NicknamePichu::
	setvar VAR_0x8004, 0
	call Common_EventScript_NameReceivedPartyMon
	goto LittlerootTown_ProfessorBirchsLab_EventScript_ButFirst
	end

LittlerootTown_ProfessorBirchsLab_EventScript_ButFirst::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_IHaveAJobForYouButFirst, MSGBOX_DEFAULT
	addobject 4
	playbgm MUS_GIRL_SUP, 1
	msgbox LittlerootTown_ProfessorBirchsLab_Text_RivalYelling
	closemessage
	delay 65
	applymovement 4, LittlerootTown_ProfessorBirchsLab_Movement_RivalEnter
	waitmovement 0
	msgbox LittlerootTown_ProfessorBirchsLab_Text_GetRivalToTestYou, MSGBOX_DEFAULT
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_ProfessorBirchsLab_Movement_FacingRival
	msgbox LittlerootTown_ProfessorBirchsLab_Text_LetsBattle, MSGBOX_DEFAULT
	goto LittlerootTown_ProfessorBirchsLab_EventScript_BattleMay
	end
	
LittlerootTown_ProfessorBirchsLab_EventScript_BattleMay::
	setvar VAR_CONTINUE_AFTER_LOSING_BATTLE, 1
	trainerbattle_no_intro TRAINER_MAY_ROUTE_103_TORCHIC, LittlerootTown_ProfessorBirchsLab_Text_MayDefeat
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_WON
	call_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_WonMayBattle
	compare VAR_RESULT, B_OUTCOME_LOST
	call_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_LostMayBattle
	special HealPlayerParty
	end

LittlerootTown_ProfessorBirchsLab_EventScript_WonMayBattle::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_NotTooBad, MSGBOX_DEFAULT
	applymovement 2, LittlerootTown_ProfessorBirchsLab_Movement_BirchFetchPokedex
	waitmovement 0
	call LittlerootTown_ProfessorBirchsLab_EventScript_ReceivePokedex
	msgbox LittlerootTown_ProfessorBirchsLab_Text_ExplainPokedex1, MSGBOX_DEFAULT
	goto LittlerootTown_ProfessorBirchsLab_EventScript_MayGivePokeBalls1
	end
	
LittlerootTown_ProfessorBirchsLab_EventScript_ReceivePokedex:: @ 81FA3AC
	playfanfare MUS_FANFA4
	waitfanfare
	message LittlerootTown_ProfessorBirchsLab_Text_ReceivedPokedex
	waitfanfare
	setflag FLAG_SYS_POKEDEX_GET
	special SetUnlockedPokedexFlags
	setflag FLAG_RECEIVED_POKEDEX_FROM_BIRCH
	return	
	
LittlerootTown_ProfessorBirchsLab_EventScript_MayGivePokeBalls1::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_ALittleGiftFromMe, MSGBOX_DEFAULT
	giveitem ITEM_POKE_BALL, 5
	msgbox LittlerootTown_ProfessorBirchsLab_Text_CatchPokemonWithPokeBalls, MSGBOX_DEFAULT
	setvar VAR_RESULT, 0
	releaseall
	end
	
LittlerootTown_ProfessorBirchsLab_EventScript_LostMayBattle::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_Disappointing, MSGBOX_DEFAULT
	applymovement 2, LittlerootTown_ProfessorBirchsLab_Movement_BirchFetchPokedex
	waitmovement 0
	call LittlerootTown_ProfessorBirchsLab_EventScript_ReceivePokedex
	msgbox LittlerootTown_ProfessorBirchsLab_Text_ExplainPokedex2, MSGBOX_DEFAULT
	goto LittlerootTown_ProfessorBirchsLab_EventScript_MayGivePokeBalls2
	end
	
LittlerootTown_ProfessorBirchsLab_EventScript_MayGivePokeBalls2::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_Hehehehe, MSGBOX_DEFAULT
	giveitem ITEM_POKE_BALL, 5
	msgbox LittlerootTown_ProfessorBirchsLab_Text_CatchPokemonWithPokeBalls, MSGBOX_DEFAULT
	setvar VAR_RESULT, 0
	releaseall
	end
	
LittlerootTown_ProfessorBirchsLab_EventScript_Birch:: @ 81FA25A
	lock
	faceplayer
	goto ProfBirch_EventScript_AskRatePokedex
	end
	
LittlerootTown_ProfessorBirchsLab_EventScript_Machine:: @ 81FA3E3
	msgbox LittlerootTown_ProfessorBirchsLab_Text_SeriousLookingMachine, MSGBOX_SIGN
	end

LittlerootTown_ProfessorBirchsLab_EventScript_Book::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BookTooHardToRead, MSGBOX_SIGN
	end

LittlerootTown_ProfessorBirchsLab_EventScript_Bookshelf::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_CrammedWithBooksOnPokemon, MSGBOX_SIGN
	end

LittlerootTown_ProfessorBirchsLab_EventScript_PC::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_PCUsedForResearch, MSGBOX_SIGN
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

LittlerootTown_ProfessorBirchsLab_Movement_RivalEnter:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end
	
LittlerootTown_ProfessorBirchsLab_Movement_FacingRival:
	face_down
	step_end
	
LittlerootTown_ProfessorBirchsLab_Movement_BirchFetchPokedex:
	walk_up
	walk_up
	walk_down
	walk_down
	step_end

LittlerootTown_ProfessorBirchsLab_Text_ThankYouSoMuch:
	.string "Prof. Birch: {PLAYER}, thank you so much\n"
	.string "for last night.\p"
	.string "There are no words with which I can\n"
	.string "express my gratitude.\p"
	.string "Mom: That was so incredibly brave,\n"
	.string "{PLAYER}. I'm very proud of you!\p"
	.string "Prof. Birch: So before I've had a little\n"
	.string "talk with your mother.\p"
	.string "With her consent, I've decided to let\n"
	.string "you keep this special Pichu.\p"
	.string "I have a feeling you'll get along with it\n"
	.string "really well!$"
	
LittlerootTown_ProfessorBirchsLab_Text_GiveNicknameToPichu:
	.string "Do you want to give a nickname\n"
	.string "to Pichu?$"
	
LittlerootTown_ProfessorBirchsLab_Text_IHaveAJobForYouButFirst:
	.string "Mom: Up until now, I didn't let you keep\n"
	.string "Pokémon.\p"
	.string "That was because I wanted you to focus\n"
	.string "on finishing school.\p"
	.string "But now you're old enough to be able to\n"
	.string "look after yourself.\p"
	.string "Prof. Birch: Oh yes, another thing we\n"
	.string "were talking about...\p"
	.string "You see, there's a job I would like to\n"
	.string "offer you.\p"
	.string "I need someone to help me researching\n"
	.string "the wildlife in the region.\p"
	.string "You would be traveling across Hoenn\n"
	.string "catching Pokémon in the Pokédex!\p"
	.string "But first...$"
	
LittlerootTown_ProfessorBirchsLab_Text_RivalYelling:
	.string "Daaaad!$"
	
LittlerootTown_ProfessorBirchsLab_Text_GetRivalToTestYou:
	.string "Prof. Birch: Oh, May! Great timing...\p"
	.string "{PLAYER}, I would like to see you battle\n"
	.string "against my daughter.\p"
	.string "Your feat of last night was impressive\n"
	.string "for a first timer, but I want to make\l"
	.string "sure it wasn't just a fluke.\p"
	.string "It's just a formality to see if you're\n"
	.string "up for the task!$"
	
LittlerootTown_ProfessorBirchsLab_Text_LetsBattle:
	.string "May: That's right!\p"
	.string "I've been itching to have a battle\n"
	.string "since I saw what you did last night!\p"
	.string "After beating those thugs, you\n"
	.string "shouldn't be afraid battle me...\p"
	.string "Right?$"
	
LittlerootTown_ProfessorBirchsLab_Text_MayDefeat:
	.string "What? You...\n"
	.string "{PLAYER}, you're pretty good!"
	
LittlerootTown_ProfessorBirchsLab_Text_NotTooBad:
	.string "That was a great battle,{PLAYER}!\p"
	.string "I didn't expect any less after\n"
	.string "last night.\p"
	.string "Now, as I promised, I'll give you\n"
	.string "a Pokédex!$"
	
LittlerootTown_ProfessorBirchsLab_Text_Disappointing:
	.string "Oh... That was disappointing.\p"
	.string "I suppose last night's performance\n"
	.string "was just dumb luck?\p"
	.string "Still, I really need some help,\n"
	.string "so I'll give you the job anyways.\p"
	
LittlerootTown_ProfessorBirchsLab_Text_ExplainPokedex1:
	.string "This Pokédex I just gave you is a\n"
	.string "high-tech device to register data\l"
	.string "of any Pokémon you catch.\p"
	.string "It is pretty straightforward, you\n"
	.string "should find it easy to use.$"
	
LittlerootTown_ProfessorBirchsLab_Text_ALittleGiftFromMe:
	.string "Kudos for winning, {PLAYER}!\n"
	.string "You totally caught me off-guard.\p"
    .string "As a reward, here's a little gift\n"
    .string "from me!$"	
	
LittlerootTown_ProfessorBirchsLab_Text_ExplainPokedex2:
	.string "This Pokédex I just gave you is a\n"
	.string "high-tech device to register data\l"
	.string "of any Pokémon you catch.\p"
	.string "It is very easy to use, even a\n"
	.string "baby should have no trouble\l"
	.string "understanding how it works.$"
	
LittlerootTown_ProfessorBirchsLab_Text_Hehehehe:
	.string "Hehe... Don't feel bad, {PLAYER}!\n"
	.string "It's just that I'm too good!\p"
	.string "Anyway, here's a little gift\n"
	.string "because I feel sorry for you!$"
	
LittlerootTown_ProfessorBirchsLab_Text_CatchPokemonWithPokeBalls:
	.string "These are Poké Balls! They are\n"
	.string "used for catching wild Pokémon!\p"
	.string "You need to weaken a little bit\n"
	.string "to make 'em easier to catch.$"
	
LittlerootTown_ProfessorBirchsLab_Text_ReceivedPokedex:
	.string "{PLAYER} received the Pokédex!$"
	
LittlerootTown_ProfessorBirchsLab_Text_SeriousLookingMachine: @ 81FB0A2
	.string "It's a serious-looking machine.\n"
	.string "The Prof must use this for research.$"

LittlerootTown_ProfessorBirchsLab_Text_PCUsedForResearch: @ 81FB0E7
	.string "It's a PC used for research.\n"
	.string "Better not mess around with it.$"

LittlerootTown_ProfessorBirchsLab_Text_CrammedWithBooksOnPokemon: @ 81FB124
	.string "It's crammed with books on Pokémon.$"

LittlerootTown_ProfessorBirchsLab_Text_BookTooHardToRead: @ 81FB148
	.string "It's a book that's too hard to read.$"
