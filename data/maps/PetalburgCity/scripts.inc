PetalburgCity_MapScripts::
	.byte 0


PetalburgCity_EventScript_Gentleman::
	msgbox PetalburgCity_Text_Gentleman, MSGBOX_NPC
	end


PetalburgCity_Movement_NormanLeaving:
	face_up
	walk_in_place_fastest_up
	step_end

PetalburgCity_Movement_NormanEntersGym:
	walk_up
	step_end

PetalburgCity_Text_NormanIntro::
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

PetalburgCity_Text_Gentleman::
	.string "Bah! I don't won't to hear about those\n"
	.string "immigrants anymore!\p"
	.string "Actually, I don't even want to see them!\p"
	.string "I don't trust them...$"
