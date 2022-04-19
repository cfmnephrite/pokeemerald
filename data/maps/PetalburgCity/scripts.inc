PetalburgCity_MapScripts::
	.byte 0


PetalburgCity_EventScript_Woman::
	lock
	faceplayer
	msgbox PetalburgCity_Text_Woman, MSGBOX_NPC
	release
	end


PetalburgCity_EventScript_Gentleman::
	lock
	faceplayer
	msgbox PetalburgCity_Text_Gentleman, MSGBOX_NPC
	release
	end


PetalburgCity_EventScript_Boy1::
	lock
	faceplayer
	msgbox PetalburgCity_EventScript_Boy1_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, 0
	goto_if_ne PetalburgCity_EventScript_Boy1_2
	msgbox PetalburgCity_Text_Boy1, MSGBOX_NPC
PetalburgCity_EventScript_Boy1_1:
	release
	end

PetalburgCity_EventScript_Boy1_2:
	msgbox PetalburgCity_EventScript_Boy1_Text_1
	goto PetalburgCity_EventScript_Boy1_1


PetalburgCity_Movement_NormanLeaving:
	face_up
	walk_in_place_fastest_up
	step_end

PetalburgCity_Movement_NormanEntersGym:
	walk_up
	step_end

PetalburgCity_EventScript_Boy1_Text_0:
	.string "Hey! Have you heard?$"

PetalburgCity_EventScript_Boy1_Text_1:
	.string "A big mess, isn't it?$"

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

PetalburgCity_Text_Woman::
	.string "Petalburg is a recently founded harbor\n"
	.string "city.\p"
	.string "Outside of the local Gym, there aren't\n"
	.string "many interesting things here.\p"
	.string "No wonder a lot of young people want to\n"
	.string "leave this town nowadays!$"

PetalburgCity_Text_Gentleman::
	.string "Bah! I don't want to hear about those\n"
	.string "immigrants anymore!\p"
	.string "Actually, I don't even want to see them!\p"
	.string "I don't trust them...$"

PetalburgCity_Text_Boy1::
	.string "There was a big ruckus in Littleroot\n"
	.string "Beach...\p"
	.string "It was caused by those guys, Aqua and\n"
	.string "Magma, I believe they're called...?\p"
	.string "Up there in Rustborough, their fights\n"
	.string "are commonplace.$"
