PetalburgWoods_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PetalburgWoods_MapScripts_MAP_SCRIPT_ON_TRANSITION
	.byte 0

PetalburgWoods_MapScripts_MAP_SCRIPT_ON_TRANSITION:
	switch VAR_PETALBURG_WOODS_STATE
	case 0, PetalburgWoods_MapScripts_MAP_SCRIPT_ON_TRANSITION_2
	case 1, PetalburgWoods_MapScripts_MAP_SCRIPT_ON_TRANSITION_3
	return

PetalburgWoods_MapScripts_MAP_SCRIPT_ON_TRANSITION_2:
	call PetalburgWoods_EventScript_MoveGirlToVar0Var1Position
	return

PetalburgWoods_MapScripts_MAP_SCRIPT_ON_TRANSITION_3:
	call PetalburgWoods_EventScript_MoveGirlToVar0Var1Position
	call PetalburgWoods_EventScript_MoveGruntsToVar1Positions
	return


PetalburgWoods_EventScript_FirstEncounter_Position1::
	setvar VAR_TEMP_0, 1
	goto PetalburgWoods_EventScript_FirstEncounter
	return


PetalburgWoods_EventScript_FirstEncounter_Position2::
	setvar VAR_TEMP_0, 2
	goto PetalburgWoods_EventScript_FirstEncounter
	return


PetalburgWoods_EventScript_FirstEncounter::
	applymovement 16, Common_Movement_WalkInPlaceDown
	msgbox PetalburgWoods_EventScript_FirstEncounter_Text_0
	applymovement 13, Common_Movement_WalkInPlaceUp
	msgbox PetalburgWoods_EventScript_FirstEncounter_Text_1
	applymovement 16, Common_Movement_ExclamationMarkLookRight
	msgbox PetalburgWoods_EventScript_FirstEncounter_Text_2
	applymovement 13, Common_Movement_ExclamationMarkLookRight
	applymovement 14, Common_Movement_ExclamationMarkLookRight
	waitmovement 0
	msgbox PetalburgWoods_EventScript_FirstEncounter_Text_3
	applymovement 13, PetalburgWoods_Movement_Grunt1MovesIntoBattlePosition
	applymovement 14, PetalburgWoods_Movement_Grunt2MovesIntoBattlePosition
	waitmovement 0
	msgbox PetalburgWoods_EventScript_FirstEncounter_Text_4
	addobject 17
	switch VAR_TEMP_0
	case 1, PetalburgWoods_EventScript_FirstEncounter_3
	case 2, PetalburgWoods_EventScript_FirstEncounter_4
PetalburgWoods_EventScript_FirstEncounter_1:
	waitmovement 0
	releaseall
	end

PetalburgWoods_EventScript_FirstEncounter_3:
	applymovement 17, PetalburgWoods_Movement_BrendanMovesIntoPosition1
	goto PetalburgWoods_EventScript_FirstEncounter_1

PetalburgWoods_EventScript_FirstEncounter_4:
	applymovement 17, PetalburgWoods_Movement_BrendanMovesIntoPosition2
	goto PetalburgWoods_EventScript_FirstEncounter_1


PetalburgWoods_Movement_Grunt1MovesIntoBattlePosition:
	walk_down
	walk_right
	walk_right
	step_end

PetalburgWoods_Movement_Grunt2MovesIntoBattlePosition:
	walk_right
	walk_down
	face_right
	step_end

PetalburgWoods_Movement_BrendanMovesIntoPosition1:
	walk_fast_up
	walk_fast_up
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_left
	walk_fast_up
	walk_fast_left
	step_end

PetalburgWoods_Movement_BrendanMovesIntoPosition2:
	walk_fast_up
	walk_fast_up
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_left
	walk_fast_left
	step_end

PetalburgWoods_EventScript_MoveGirlToVar0Var1Position::
	setobjectxyperm 11, 16, 26
	setobjectmovementtype 11, MOVEMENT_TYPE_LOOK_AROUND
	return


PetalburgWoods_EventScript_MoveGruntsToVar1Positions::
	setobjectxyperm 13, 11, 30
	setobjectxyperm 14, 12, 29
	setobjectmovementtype 13, MOVEMENT_TYPE_FACE_DOWN
	setobjectmovementtype 14, MOVEMENT_TYPE_FACE_DOWN
	return


PetalburgWoods_EventScript_Sign::
	msgbox PetalburgWoods_Text_Sign, MSGBOX_SIGN
	return


PetalburgWoods_EventScript_Lyle::
	trainerbattle_single TRAINER_LYLE, PetalburgWoods_Text_GoBugPokemonTeam, PetalburgWoods_Text_ICouldntWin
	msgbox PetalburgWoods_Text_ImOutOfPokeBalls, MSGBOX_AUTOCLOSE
	end


PetalburgWoods_EventScript_James::
	trainerbattle_single TRAINER_JAMES_1, PetalburgWoods_Text_InstantlyPopularWithBugPokemon, PetalburgWoods_Text_CantBePopularIfILose, PetalburgWoods_EventScript_TryRegisterJames
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, 0
	goto_if_ne PetalburgWoods_EventScript_James_2
PetalburgWoods_EventScript_James_1:
	setvar VAR_0x8004, TRAINER_JAMES_1
	specialvar VAR_RESULT, IsTrainerRegistered
	compare VAR_RESULT, 0
	goto_if_eq PetalburgWoods_EventScript_James_5
PetalburgWoods_EventScript_James_4:
	msgbox PetalburgWoods_Text_PeopleRespectYou, MSGBOX_DEFAULT
	release
	end

PetalburgWoods_EventScript_James_2:
	goto PetalburgWoods_EventScript_JamesRematch
	goto PetalburgWoods_EventScript_James_1

PetalburgWoods_EventScript_James_5:
	goto PetalburgWoods_EventScript_TryRegisterJames2
	goto PetalburgWoods_EventScript_James_4


PetalburgWoods_EventScript_TryRegisterJames::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	goto_if_set FLAG_HAS_MATCH_CALL, PetalburgWoods_EventScript_TryRegisterJames_2
PetalburgWoods_EventScript_TryRegisterJames_1:
	release
	end

PetalburgWoods_EventScript_TryRegisterJames_2:
	goto PetalburgWoods_EventScript_RegisterJames
	goto PetalburgWoods_EventScript_TryRegisterJames_1


PetalburgWoods_EventScript_JamesRematch::
	trainerbattle_rematch TRAINER_JAMES_1, PetalburgWoods_Text_MyPokemonHaveGrown, PetalburgWoods_Text_CantBePopularIfILose
	msgbox PetalburgWoods_Text_IveBeenTrainingHard, MSGBOX_AUTOCLOSE
	end


PetalburgWoods_EventScript_TryRegisterJames2::
	goto_if_set FLAG_HAS_MATCH_CALL, PetalburgWoods_EventScript_TryRegisterJames2_2
PetalburgWoods_EventScript_TryRegisterJames2_1:
	msgbox PetalburgWoods_Text_PeopleRespectYou, MSGBOX_DEFAULT
	release
	end

PetalburgWoods_EventScript_TryRegisterJames2_2:
	goto PetalburgWoods_EventScript_RegisterJames
	goto PetalburgWoods_EventScript_TryRegisterJames2_1


PetalburgWoods_EventScript_RegisterJames::
	msgbox PetalburgWoods_Text_IWantRematch, MSGBOX_DEFAULT
	register_matchcall TRAINER_JAMES_1
	release
	end


PetalburgWoods_EventScript_Boy1::
	msgbox PetalburgWoods_Text_StayOutOfTallGrass, MSGBOX_NPC
	end


PetalburgWoods_EventScript_Boy2::
	msgbox PetalburgWoods_Text_HiddenItemsExplanation, MSGBOX_NPC
	end


PetalburgWoods_EventScript_FirstEncounter_Text_0:
	.string "Boy: Please let me go!\n"
	.string "I won't tell anyone, I swear!$"

PetalburgWoods_EventScript_FirstEncounter_Text_1:
	.string "Sorry, kid, you know how it is.\n"
	.string "Can't have any loose en-$"

PetalburgWoods_EventScript_FirstEncounter_Text_2:
	.string "Boy: Oh, you!\n"
	.string "Please help meeee!$"

PetalburgWoods_EventScript_FirstEncounter_Text_3:
	.string "Well, look what we have here...$"

PetalburgWoods_EventScript_FirstEncounter_Text_4:
	.string "You trying to be a hero, kid?\p"
	.string "???: Wait a second, gay boys!$"

PetalburgWoods_Text_Sign::
	.string "Petalburg Woods\n"
	.string "{DOWN_ARROW}Petalburg$"

PetalburgWoods_Text_GoBugPokemonTeam::
	.string "I caught a whole bunch of monsters!\p"
	.string "Go, go, go!\n"
	.string "My Bug team!$"

PetalburgWoods_Text_ICouldntWin::
	.string "I have all these monsters,\n"
	.string "but I couldn't win…$"

PetalburgWoods_Text_ImOutOfPokeBalls::
	.string "I caught a bunch of monsters.\n"
	.string "Now I'm out of Monster Balls...$"

PetalburgWoods_Text_InstantlyPopularWithBugPokemon::
	.string "If you take Bug monsters to school,\n"
	.string "you get to be instantly popular!$"

PetalburgWoods_Text_CantBePopularIfILose::
	.string "I can't be popular if I lose.$"

PetalburgWoods_Text_PeopleRespectYou::
	.string "If you have a big Bug monster,\n"
	.string "people respect you for it.$"

PetalburgWoods_Text_IWantRematch::
	.string "I want a rematch when my Bug\n"
	.string "monsters grow up!\p"
	.string "I'm registering you in my PokéNav!$"

PetalburgWoods_Text_MyPokemonHaveGrown::
	.string "My Bug monsters have grown.\n"
	.string "I'll be popular again!$"

PetalburgWoods_Text_IveBeenTrainingHard::
	.string "You get to be popular if you have\n"
	.string "strong monsters, right?\l"
	.string "So, I've been training hard.$"

PetalburgWoods_Text_StayOutOfTallGrass::
	.string "Yo, there!\n"
	.string "Your monsters doing okay?\p"
	.string "If your monsters are weak and you want\n"
	.string "to avoid battles, you should stay out\l"
	.string "of tall grass.$"

PetalburgWoods_Text_HiddenItemsExplanation::
	.string "Sometimes, there are things on the\n"
	.string "ground even if you can't see them.\p"
	.string "That's why I always check where I'm\n"
	.string "walking.$"
