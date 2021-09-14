PetalburgWoods_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PetalburgWoods_MapScripts_MAP_SCRIPT_ON_TRANSITION
	.byte 0

PetalburgWoods_MapScripts_MAP_SCRIPT_ON_TRANSITION:
	compare VAR_PETALBURG_WOODS_STATE, 0
	goto_if_eq PetalburgWoods_MapScripts_MAP_SCRIPT_ON_TRANSITION_1
	return

PetalburgWoods_MapScripts_MAP_SCRIPT_ON_TRANSITION_1:
	setobjectxyperm 11, 16, 26
	setobjectmovementtype 11, MOVEMENT_TYPE_LOOK_AROUND
	setobjectxyperm 16, 7, 8
	setobjectmovementtype 11, MOVEMENT_TYPE_FACE_DOWN
	addobject 13
	addobject 14
	addobject 1
	addobject 15
	addobject 2
	addobject 12
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
	playse SE_PIN
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
	applymovement 13, Common_Movement_WalkInPlaceRight
	msgbox PetalburgWoods_EventScript_FirstEncounter_Text_5
	goto PetalburgWoods_EventScript_FirstSpecialDoubleBattle
	return

PetalburgWoods_EventScript_FirstEncounter_3:
	applymovement 17, PetalburgWoods_Movement_BrendanMovesIntoPosition1
	goto PetalburgWoods_EventScript_FirstEncounter_1

PetalburgWoods_EventScript_FirstEncounter_4:
	applymovement 17, PetalburgWoods_Movement_BrendanMovesIntoPosition2
	goto PetalburgWoods_EventScript_FirstEncounter_1


PetalburgWoods_EventScript_FirstSpecialDoubleBattle::
	setvar VAR_PETALBURG_WOODS_STATE, 1
	goto PetalburgWoods_EventScript_FirstSpecialDoubleBattleOver
	return


PetalburgWoods_EventScript_FirstSpecialDoubleBattleOver::
	applymovement 13, PetalburgWoods_Movement_Grunts12DefeatedLockRightWalkLeft
	applymovement 14, PetalburgWoods_Movement_Grunts12DefeatedLockRightWalkLeft
	waitmovement 0
	applymovement 13, Common_Movement_FaceUp
	applymovement 14, Common_Movement_FaceDown
	waitmovement 0
	delay 90
	applymovement 13, Common_Movement_FaceRight
	applymovement 14, Common_Movement_FaceRight
	waitmovement 0
	delay 90
	applymovement 13, PetalburgWoods_Movement_Grunt1Flees
	applymovement 14, PetalburgWoods_Movement_Grunt2Flees
	waitmovement 0
	hideobjectat 13, MAP_PETALBURG_WOODS
	hideobjectat 14, MAP_PETALBURG_WOODS
	applymovement 17, Common_Movement_WalkInPlaceLeft
	msgbox PetalburgWoods_EventScript_FirstSpecialDoubleBattleOver_Text_0
	switch VAR_TEMP_0
	case 1, PetalburgWoods_EventScript_FirstSpecialDoubleBattleOver_3
	case 2, PetalburgWoods_EventScript_FirstSpecialDoubleBattleOver_4
PetalburgWoods_EventScript_FirstSpecialDoubleBattleOver_1:
	waitmovement 0
	msgbox PetalburgWoods_Text_BrendanIntro, MSGBOX_YESNO
	compare VAR_RESULT, 0
	goto_if_eq PetalburgWoods_EventScript_FirstSpecialDoubleBattleOver_6
PetalburgWoods_EventScript_FirstSpecialDoubleBattleOver_5:
	msgbox PetalburgWoods_Text_BrendanIntro2, MSGBOX_AUTOCLOSE
	end

PetalburgWoods_EventScript_FirstSpecialDoubleBattleOver_3:
	applymovement 17, Common_Movement_FaceDown
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	goto PetalburgWoods_EventScript_FirstSpecialDoubleBattleOver_1

PetalburgWoods_EventScript_FirstSpecialDoubleBattleOver_4:
	applymovement 17, Common_Movement_FaceUp
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceDown
	goto PetalburgWoods_EventScript_FirstSpecialDoubleBattleOver_1

PetalburgWoods_EventScript_FirstSpecialDoubleBattleOver_6:
	msgbox PetalburgWoods_EventScript_FirstSpecialDoubleBattleOver_Text_1
	goto PetalburgWoods_EventScript_FirstSpecialDoubleBattleOver_5


PetalburgWoods_EventScript_RocketEncounterContinues::
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, PetalburgWoods_Movement_CameraPansDownForBattle2
	applymovement OBJ_EVENT_ID_PLAYER, PetalburgWoods_Movement_PlayerMovesIntoBattle2Position
	waitmovement 0
	applymovement 1, Common_Movement_WalkInPlaceRight
	msgbox PetalburgWoods_EventScript_RocketEncounterContinues_Text_0
	applymovement 15, Common_Movement_WalkInPlaceDown
	msgbox PetalburgWoods_EventScript_RocketEncounterContinues_Text_1
	applymovement 2, Common_Movement_WalkInPlaceUp
	msgbox PetalburgWoods_EventScript_RocketEncounterContinues_Text_2
	playse SE_PIN
	applymovement 1, Common_Movement_ExclamationMarkLookUp
	applymovement 15, Common_Movement_ExclamationMarkLookUp
	waitmovement 0
	delay 60
	applymovement 15, Common_Movement_WalkInPlaceDown
	msgbox PetalburgWoods_EventScript_RocketEncounterContinues_Text_3
	applymovement 15, Common_Movement_WalkInPlaceUp
	msgbox PetalburgWoods_EventScript_RocketEncounterContinues_Text_4
	applymovement 1, PetalburgWoods_Movement_Grunt3MovesIntoBattle2Position
	applymovement 15, PetalburgWoods_Movement_Grunt4MovesIntoBattle2Position
	msgbox PetalburgWoods_EventScript_RocketEncounterContinues_Text_5
	goto PetalburgWoods_EventScript_SecondSpecialDoubleBattle
	return


PetalburgWoods_EventScript_SecondSpecialDoubleBattle::
	setvar VAR_PETALBURG_WOODS_STATE, 2
	goto PetalburgWoods_EventScript_Battle2GruntsRetreat
	return


PetalburgWoods_EventScript_Battle2GruntsRetreat::
	applymovement 1, PetalburgWoods_Movement_Grunt3Recoils
	applymovement 15, PetalburgWoods_Movement_Grunt4WalksBack
	waitmovement 0
	applymovement 15, Common_Movement_WalkInPlaceUp
	msgbox PetalburgWoods_EventScript_Battle2GruntsRetreat_Text_0
	playse SE_PIN
	applymovement 1, PetalburgWoods_Movement_Grunt3Flees
	applymovement 15, Common_Movement_ExclamationMarkLookDown
	delay 60
	removeobject 1
	applymovement 15, Common_Movement_WalkInPlaceUp
	msgbox PetalburgWoods_EventScript_Battle2GruntsRetreat_Text_1
	applymovement 15, PetalburgWoods_Movement_Grunt4WalksBack
	waitmovement 0
	msgbox PetalburgWoods_EventScript_Battle2GruntsRetreat_Text_1, MSGBOX_AUTOCLOSE
	applymovement 15, PetalburgWoods_Movement_Grunt4Flees
	waitmovement 0
	removeobject 15
	setflag FLAG_PETALBURG_WOODS_HIDE_SPRITES
	goto PetalburgWoods_EventScript_SecondSpecialDoubleBattleOver
	return


PetalburgWoods_EventScript_SecondSpecialDoubleBattleOver::
	applymovement OBJ_EVENT_ID_CAMERA, PetalburgWoods_Movement_CameraReverts
	waitmovement 0
	special RemoveCameraObject
	end


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

PetalburgWoods_Movement_Grunts12DefeatedLockRightWalkLeft:
	lock_facing_direction
	walk_left
	unlock_facing_direction
	step_end

PetalburgWoods_Movement_Grunt1Flees:
	walk_fastest_left
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_right
	walk_fastest_down
	walk_fastest_right
	step_end

PetalburgWoods_Movement_Grunt2Flees:
	walk_fastest_left
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_right
	walk_fastest_down
	walk_fastest_right
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

PetalburgWoods_Movement_CameraPansDownForBattle2:
	walk_slow_diag_southeast
	walk_slow_diag_southeast
	step_end

PetalburgWoods_Movement_Grunt3MovesIntoBattle2Position:
	walk_left
	walk_up
	walk_up
	step_end

PetalburgWoods_Movement_Grunt4MovesIntoBattle2Position:
	walk_left
	walk_up
	step_end

PetalburgWoods_Movement_PlayerMovesIntoBattle2Position:
	walk_right
	walk_right
	face_down
	step_end

PetalburgWoods_Movement_Grunt3Recoils:
	lock_facing_direction
	walk_fast_down
	walk_fast_down
	unlock_facing_direction
	step_end

PetalburgWoods_Movement_Grunt4WalksBack:
	lock_facing_direction
	walk_down
	unlock_facing_direction
	step_end

PetalburgWoods_Movement_Grunt3Flees:
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	step_end

PetalburgWoods_Movement_Grunt4Flees:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

PetalburgWoods_Movement_CameraReverts:
	walk_slow_up
	walk_slow_up
	step_end

PetalburgWoods_EventScript_BrendanSaysYouCantLeave::
	msgbox PetalburgWoods_Text_BrendanSaysCantLeave, MSGBOX_SIGN
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkUp
	end


PetalburgWoods_EventScript_Sign::
	setvar VAR_PETALBURG_WOODS_STATE, 0
	msgbox PetalburgWoods_Text_Sign, MSGBOX_SIGN
	return


PetalburgWoods_EventScript_Girl::
	switch VAR_PETALBURG_WOODS_STATE
	case 0, PetalburgWoods_EventScript_Girl_3
	case 1, PetalburgWoods_EventScript_Girl_3
	msgbox PetalburgWoods_TextGirl, MSGBOX_NPC
PetalburgWoods_EventScript_Girl_1:
	end

PetalburgWoods_EventScript_Girl_3:
	msgbox PetalburgWoods_Text_GirlVar0Var1, MSGBOX_NPC
	goto PetalburgWoods_EventScript_Girl_1


PetalburgWoods_EventScript_Boy3::
	lock
	switch VAR_PETALBURG_WOODS_STATE
	case 0, PetalburgWoods_EventScript_Boy3_3
	case 1, PetalburgWoods_EventScript_Boy3_3
	goto_if_unset FLAG_BERRY_PETALBURG_WOODS_RECEIVED_SITRUS, PetalburgWoods_EventScript_Boy3_9
PetalburgWoods_EventScript_Boy3_8:
	msgbox PetalburgWoods_Text_Boy, MSGBOX_NPC
PetalburgWoods_EventScript_Boy3_1:
	release
	end

PetalburgWoods_EventScript_Boy3_3:
	goto_if_unset FLAG_BERRY_PETALBURG_WOODS_RECEIVED_SITRUS, PetalburgWoods_EventScript_Boy3_6
PetalburgWoods_EventScript_Boy3_5:
	msgbox PetalburgWoods_EventScript_Boy3_Text_1, MSGBOX_NPC
	goto PetalburgWoods_EventScript_Boy3_1

PetalburgWoods_EventScript_Boy3_6:
	msgbox PetalburgWoods_EventScript_Boy3_Text_0
	giveitem ITEM_SITRUS_BERRY
	setflag FLAG_BERRY_PETALBURG_WOODS_RECEIVED_SITRUS
	goto PetalburgWoods_EventScript_Boy3_5

PetalburgWoods_EventScript_Boy3_9:
	msgbox PetalburgWoods_EventScript_Boy3_Text_2
	giveitem ITEM_SITRUS_BERRY
	setflag FLAG_BERRY_PETALBURG_WOODS_RECEIVED_SITRUS
	goto PetalburgWoods_EventScript_Boy3_8


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
	.string "???: Wait a second, scumbags!$"

PetalburgWoods_EventScript_FirstEncounter_Text_5:
	.string "Oh, good! More fresh meat!\n"
	.string "All right, let's put you kids to bed.$"

PetalburgWoods_EventScript_FirstSpecialDoubleBattleOver_Text_0:
	.string "Pah!\nWhat a bunch of cowards!$"

PetalburgWoods_EventScript_FirstSpecialDoubleBattleOver_Text_1:
	.string "No? You you mean you have no fear?$"

PetalburgWoods_EventScript_RocketEncounterContinues_Text_0:
	.string "We need the goods you've got in that\n"
	.string "truck, chief.\p"
	.string "You going to give us the code to the\n"
	.string "safe?\p"
	.string "Or do you want me to bring out my\n"
	.string "Seviper?$"

PetalburgWoods_EventScript_RocketEncounterContinues_Text_1:
	.string "And if you still don't want to let us in\p"
	.string "after he delights you with his purple\n"
	.string "snake,\p"
	.string "I'll smash your head in.$"

PetalburgWoods_EventScript_RocketEncounterContinues_Text_2:
	.string "Look, fellas!\p"
	.string "I'm just a courier! They don't give me\n"
	.string "the code.\p"
	.string "I don't even know what I'm carryi-$"

PetalburgWoods_EventScript_RocketEncounterContinues_Text_3:
	.string "Boss: You wait here.$"

PetalburgWoods_EventScript_RocketEncounterContinues_Text_4:
	.string "You must be the ones who scared away\n"
	.string "our colleagues.$"

PetalburgWoods_EventScript_RocketEncounterContinues_Text_5:
	.string "And I see you're just a couple of stupid\n"
	.string "kids!\p"
	.string "Makes no difference to me.\n"
	.string "You're both dead.$"

PetalburgWoods_EventScript_Battle2GruntsRetreat_Text_0:
	.string "How?! How did you beat us?!$"

PetalburgWoods_EventScript_Battle2GruntsRetreat_Text_1:
	.string "dialogue$"

PetalburgWoods_EventScript_Boy3_Text_0:
	.string "Thank you, thank you, thank you! Here,\n"
	.string "take this!$"

PetalburgWoods_EventScript_Boy3_Text_1:
	.string "I was just walking and they grabbed me...$"

PetalburgWoods_EventScript_Boy3_Text_2:
	.string "Hey! Thank you for saving me from the\n"
	.string "Rockets!\p"
	.string "I have a present for you!$"

PetalburgWoods_Text_Grunt1Defeat::
	.string "Useless bat! First it gives me some\n"
	.string "weird cough, now this!$"

PetalburgWoods_Text_Grunt2Defeat::
	.string "Hmm, maybe actual training is better\n"
	.string "than Rare Candies...$"

PetalburgWoods_Text_Grunt3Defeat::
	.string "Oh, the boss isn't going to like this...$"

PetalburgWoods_Text_Grunt4Defeat::
	.string "What? What the hell?!$"

PetalburgWoods_Text_BrendanIntro::
	.string "My name's Brendan\n"
	.string "My dad's a gym leader in Petalburg.\p"
	.string "And you are? {PLAYER}?\p"
	.string "Listen, {PLAYER}ey, there are two\n"
	.string "things you should know about me.\p"
	.string "The first is that my hair isn't white -\n"
	.string "it's a hat, see?\p"
	.string "The second is that I'll never turn down\n"
	.string "a chance to slap some bottom.\p"
	.string "So how about we go and take down the\n"
	.string "rest of these Rocket thugs, eh?$"

PetalburgWoods_Text_BrendanIntro2::
	.string "That's the spirit!\n"
	.string "Now let's go do this!$"

PetalburgWoods_Text_BrendanSaysCantLeave::
	.string "Where are you going?\n"
	.string "Come on, let's take 'em down!$"

PetalburgWoods_Text_Sign::
	.string "Petalburg Woods\n"
	.string "{DOWN_ARROW}Petalburg$"

PetalburgWoods_Text_GirlVar0Var1::
	.string "What's going on?\p"
	.string "There's a crashed truck blocking the\n"
	.string "road and I hear angry men shouting...$"

PetalburgWoods_TextGirl::
	.string "There used to be Shroomish around here!\p"
	.string "But I haven't seen any in a long time...$"

PetalburgWoods_Text_Boy::
	.string "Those Rocket guys are scary...\n"
	.string "My dad says they're not from Hoenn.\p"
	.string "He says we should stop all the\n"
	.string "foreigners coming in...\p"
	.string "...because they could be Rockets or\n"
	.string "drug dealers or French.$"

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
