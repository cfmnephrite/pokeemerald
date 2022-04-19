PetalburgCity_Gym_MapScripts::
	.byte 0


PetalburgCity_Gym_EventScript_GymGuide::
	lock
	faceplayer
	msgbox PetalburgCity_Gym_EventScript_GymGuide_Text_0
	multichoice 0, 0, MULTI_PETALBURG_GYM_GUIDE, FALSE
	switch VAR_RESULT
	case 0, PetalburgCity_Gym_EventScript_GymGuide_3
	case 1, PetalburgCity_Gym_EventScript_GymGuide_4
	case 2, PetalburgCity_Gym_EventScript_GymGuide_5
PetalburgCity_Gym_EventScript_GymGuide_1:
	release
	end

PetalburgCity_Gym_EventScript_GymGuide_3:
	msgbox PetalburgCity_Gym_TheGymSystem, MSGBOX_DEFAULT
	waitmessage
	goto PetalburgCity_Gym_EventScript_GymGuideLoop
	goto PetalburgCity_Gym_EventScript_GymGuide_1

PetalburgCity_Gym_EventScript_GymGuide_4:
	msgbox PetalburgCity_Gym_TheNormalType, MSGBOX_DEFAULT
	waitmessage
	goto PetalburgCity_Gym_EventScript_GymGuideLoop
	goto PetalburgCity_Gym_EventScript_GymGuide_1

PetalburgCity_Gym_EventScript_GymGuide_5:
	msgbox PetalburgCity_Gym_EventScript_GymGuide_Text_1
	goto PetalburgCity_Gym_EventScript_GymGuide_1


PetalburgCity_Gym_EventScript_GymGuideLoop::
	msgbox PetalburgCity_Gym_EventScript_GymGuideLoop_Text_0
	multichoice 0, 0, MULTI_PETALBURG_GYM_GUIDE, FALSE
	switch VAR_RESULT
	case 0, PetalburgCity_Gym_EventScript_GymGuideLoop_3
	case 1, PetalburgCity_Gym_EventScript_GymGuideLoop_4
	case 2, PetalburgCity_Gym_EventScript_GymGuideLoop_5
PetalburgCity_Gym_EventScript_GymGuideLoop_1:
	release
	end

PetalburgCity_Gym_EventScript_GymGuideLoop_3:
	msgbox PetalburgCity_Gym_TheGymSystem, MSGBOX_DEFAULT
	waitmessage
	goto PetalburgCity_Gym_EventScript_GymGuideLoop
	goto PetalburgCity_Gym_EventScript_GymGuideLoop_1

PetalburgCity_Gym_EventScript_GymGuideLoop_4:
	msgbox PetalburgCity_Gym_TheNormalType, MSGBOX_DEFAULT
	waitmessage
	goto PetalburgCity_Gym_EventScript_GymGuideLoop
	goto PetalburgCity_Gym_EventScript_GymGuideLoop_1

PetalburgCity_Gym_EventScript_GymGuideLoop_5:
	msgbox PetalburgCity_Gym_EventScript_GymGuide_Text_1
	goto PetalburgCity_Gym_EventScript_GymGuideLoop_1


PetalburgCity_Gym_EventScript_LeftGymStatue::
	lock
	goto_if_unset FLAG_BADGE05_GET, PetalburgCity_Gym_EventScript_LeftGymStatue_1
	msgbox PetalburgCity_Gym_GymStatueCertified, MSGBOX_DEFAULT
	release
	end

PetalburgCity_Gym_EventScript_LeftGymStatue_1:
	msgbox PetalburgCity_Gym_GymStatue, MSGBOX_DEFAULT
	release
	end


PetalburgCity_Gym_EventScript_RightGymStatue::
	lock
	goto_if_unset FLAG_BADGE05_GET, PetalburgCity_Gym_EventScript_RightGymStatue_1
	msgbox PetalburgCity_Gym_GymStatueCertified, MSGBOX_DEFAULT
	release
	end

PetalburgCity_Gym_EventScript_RightGymStatue_1:
	msgbox PetalburgCity_Gym_GymStatue, MSGBOX_DEFAULT
	release
	end


PetalburgCity_Gym_EventScript_GymGuide_Text_0:
	.string "Welcome to Petalburg Gym!\n"
	.string "Do you have any questions?$"

PetalburgCity_Gym_EventScript_GymGuide_Text_1:
	.string "Feel free to ask if you have any\n"
	.string "questions!$"

PetalburgCity_Gym_EventScript_GymGuideLoop_Text_0:
	.string "Is there something else you would like\n"
	.string "to ask?$"

PetalburgCity_Gym_TheGymSystem::
	.string "There are eight Gyms in the Hoenn\n"
	.string "region.\p"
	.string "In those Gyms, Trainers' skills are put\n"
	.string "to the test against Gym Leaders.\p"
	.string "You may challenge Gym Leaders and\n"
	.string "obtain their Badges in any order.\p"
	.string "Earning all eight Badges awards you\n"
	.string "with the right of challenging\l"
	.string "the prestigious Hoenn League!$"

PetalburgCity_Gym_TheNormalType::
	.string "The Normal type is basically an\n"
	.string "all-rounder type, with no notable\l"
	.string "strength or weakness.\p"
	.string "Unlike other Gym Leaders in Hoenn,\n"
	.string "our Norman is a traditionalist.\p"
	.string "He doesn't carry any wild card to cover\n"
	.string "his type's weaknesses, preferring to\l"
	.string "stick with his speciality type.\p"
	.string "Don't think even for a moment that he\n"
	.string "will go down easily, though!$"

PetalburgCity_Gym_GymStatue::
	.string "Petalburg City Gym$"

PetalburgCity_Gym_GymStatueCertified::
	.string "Petalburg City Gym\p"
	.string "Norman's Certified Trainers:\n"
	.string "{PLAYER}$"
