PetalburgCity_WallysHouse_MapScripts::
	.byte 0


PetalburgCity_WallysHouse_EventScript_WallysMom::
	lock
	faceplayer
	msgbox PetalburgCity_Text_WallysMom, MSGBOX_NPC
	release
	end


PetalburgCity_Text_WallysMom::
	.string "Oh! Are you one of those so-called...\n"
	.string "Trainers?\p"
	.string "Those people who catch monsters and\n"
	.string "battle with them?\p"
	.string "You would probably get along with my\n"
	.string "son. He's really passionate about\l"
	.string "monsters too.\p"
	.string "But sometimes I wish that he focused\n"
	.string "more on his studies!$"
