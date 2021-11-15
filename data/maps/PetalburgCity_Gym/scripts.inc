PetalburgCity_Gym_MapScripts::
	.byte 0


PetalburgCity_Gym_EventScript_Norman::
	lock
	faceplayer
	msgbox PetalburgCity_Gym_Text_NormanIntro, MSGBOX_DEFAULT
	release
	end


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
	msgbox PetalburgCity_Gym_Text_TheGymSystem, MSGBOX_DEFAULT
	goto PetalburgCity_Gym_EventScript_GymGuide_1

PetalburgCity_Gym_EventScript_GymGuide_4:
	msgbox PetalburgCity_Gym_Text_TheNormalType, MSGBOX_DEFAULT
	goto PetalburgCity_Gym_EventScript_GymGuide_1

PetalburgCity_Gym_EventScript_GymGuide_5:
	msgbox PetalburgCity_Gym_EventScript_GymGuide_Text_1
	goto PetalburgCity_Gym_EventScript_GymGuide_1


PetalburgCity_Gym_EventScript_LeftGymStatue::
	lock
	goto_if_unset FLAG_BADGE05_GET, PetalburgCity_Gym_EventScript_LeftGymStatue_1
	msgbox PetalburgCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	release
	end

PetalburgCity_Gym_EventScript_LeftGymStatue_1:
	msgbox PetalburgCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	release
	end


PetalburgCity_Gym_EventScript_RightGymStatue::
	lock
	goto_if_unset FLAG_BADGE05_GET, PetalburgCity_Gym_EventScript_RightGymStatue_1
	msgbox PetalburgCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	release
	end

PetalburgCity_Gym_EventScript_RightGymStatue_1:
	msgbox PetalburgCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	release
	end


PetalburgCity_Gym_EventScript_GymGuide_Text_0:
	.string "Welcome to Petalburg Gym!\n"
	.string "Do you have any questions?$"

PetalburgCity_Gym_EventScript_GymGuide_Text_1:
	.string "Feel free to ask if you have any\n"
	.string "questions!$"

PetalburgCity_Gym_Text_NormanIntro::
	.string "Hello. Are you a rookie Trainer?\p"
	.string "My name is Norman. I'm the Gym Leader in\n"
	.string "this town.\p"
	.string "... ... ...\p"
	.string "Ah! So you're that Trainer my kid was\n"
	.string "talking about!\p"
	.string "{PLAYER}, right?\p"
	.string "Those Rockets... They are all over the\n"
	.string "news nowadays.\p"
	.string "It's a mystery what those guys could be\n"
	.string "up to.\p"
	.string "This world is changing, but young people\n"
	.string "like you and Brendan are the hope for\l"
	.string "this society.\p"
	.string "Anyway! I love good fights, and after\n"
	.string "hearing of your feat, I'd really be glad\l"
	.string "of taking you as a challenger!\p"
	.string "Take your time. If you want to give it a\n"
	.string "go, the guide inside will happily explain\l"
	.string "what you need.\p"
	.string "I hope to see you soon!$"

PetalburgCity_Gym_Text_TheGymSystem::
	.string "There are eight Gyms in the Hoenn region.\p"
	.string "In those Gyms, Trainers' skills are put\n"
	.string "to the test against Gym Leaders.\p"
	.string "You may challenge Gym Leaders and\n"
	.string "obtain their Badges in any order.\p"
	.string "Earning all eight Badges awards you\n"
	.string "with the right of challenging\l"
	.string "the prestigious Hoenn League!$"

PetalburgCity_Gym_Text_TheNormalType::
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

PetalburgCity_Gym_Text_GymStatue::
	.string "Petalburg City Gym$"

PetalburgCity_Gym_Text_GymStatueCertified::
	.string "Petalburg City Gym\p"
	.string "Norman's Certified Trainers:\n"
	.string "{PLAYER}$"
