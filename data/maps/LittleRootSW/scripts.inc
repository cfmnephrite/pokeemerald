LittleRootSW_MapScripts::
	.byte 0


LittlerootSW_EventScript_First_NPC::
	msgbox LittlerootSW_FirstNPC_Text, MSGBOX_NPC
	return


LittlerootSW_EventScript_BoyMissingFamily::
	msgbox LittlerootSW_EventScript_BoyMissingFamily_Text_0, MSGBOX_NPC
	return


LittlerootSW_EventScript_GuyaneseMan::
	msgbox LittlerootSW_GuyaneseMan_Text, MSGBOX_NPC
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	end


LittlerootSW_EventScript_GuyaneseGirl::
	msgbox LittlerootSW_GuyaneseGirl_Text, MSGBOX_NPC
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	end


LittlerootSW_EventScript_BoyMissingFamily_Text_0:
	.string "Não gosto daqui... Tenho saudades da\n"
	.string "minha família.$"

LittlerootSW_FirstNPC_Text::
	.string "¡Tú! ¡No somos criminales!\p"
	.string "¡Solo queremos vivir y trabajar con\n"
	.string "seguridad!\p"
	.string "¿Por qué su gobierno nos trata como\n"
	.string "animales?$"

LittlerootSW_GuyaneseMan_Text::
	.string "My daughter and I are from Guyana.\p"
	.string "When I was a kid, we lived on the\n"
	.string "Essequibo in a little town called\l"
	.string "Bartica.\p"
	.string "When the town sank, my family moved\n"
	.string "into the forest to find a new home.\p"
	.string "But the Brazilian soldiers came and\n"
	.string "took the forest. They forced us back\l"
	.string "towards the coast.\p"
	.string "I had to build a raft out of driftwood,\n"
	.string "and took my daughter with me onto the\l"
	.string "open sea.\p"
	.string "It's a miracle that we arrived here...$"

LittlerootSW_GuyaneseGirl_Text::
	.string "When we left home, we had to leave\n"
	.string "everyone else behind...\p"
	.string "We wait here every day, hoping to see\n"
	.string "our friends again.$"
