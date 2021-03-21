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


LittlerootSW_EventScript_OldManOnBeach::
	checkplayergender
	compare VAR_RESULT, MALE
	goto_if_eq LittlerootSW_EventScript_OldManOnBeach_1
	msgbox LittlerootSW_OldManOnBeach_Female_Text, MSGBOX_NPC
	return

LittlerootSW_EventScript_OldManOnBeach_1:
	msgbox LittlerootSW_OldManOnBeach_Male_Text, MSGBOX_NPC
	return


LittlerootSW_EventScript_OldWomanOnBeach::
	goto_if_unset FLAG_GAVE_MONEY_TO_OLD_LADY_REFUGEE, LittlerootSW_EventScript_OldWomanOnBeach_1
	msgbox LittlerootSW_EventScript_OldWomanOnBeach_Text_3, MSGBOX_NPC
	return

LittlerootSW_EventScript_OldWomanOnBeach_1:
	lock
	faceplayer
	msgbox LittlerootSW_EventScript_OldWomanOnBeach_Text_0
	checkmoney 100, 0
	compare VAR_RESULT, 0
	goto_if_ne LittlerootSW_EventScript_OldWomanOnBeach_5
LittlerootSW_EventScript_OldWomanOnBeach_4:
	release
	end

LittlerootSW_EventScript_OldWomanOnBeach_5:
	showmoneybox 0, 0, 0
	msgbox LittlerootSW_EventScript_OldWomanOnBeach_Text_1
	multichoicedefault 20, 8, MULTI_YESNO, 0, 1
	compare VAR_RESULT, 0
	goto_if_eq LittlerootSW_EventScript_OldWomanOnBeach_8
	msgbox LittlerootSW_EventScript_OldWomanOnBeach_Text_2, MSGBOX_NPC
LittlerootSW_EventScript_OldWomanOnBeach_7:
	hidemoneybox
	goto LittlerootSW_EventScript_OldWomanOnBeach_4

LittlerootSW_EventScript_OldWomanOnBeach_8:
	removemoney 100, 0
	updatemoneybox 0, 0
	setflag FLAG_GAVE_MONEY_TO_OLD_LADY_REFUGEE
	msgbox LittlerootSW_OldWomanOnBeach_Text, MSGBOX_NPC
	giveitem ITEM_MOON_STONE
	goto LittlerootSW_EventScript_OldWomanOnBeach_7


LittlerootSW_EventScript_BoyMissingFamily_Text_0:
	.string "Não gosto daqui... Tenho saudades da\n"
	.string "minha família.$"

LittlerootSW_EventScript_OldWomanOnBeach_Text_0:
	.string "Oh, hello, young man! Are you a\n"
	.string "volunteer?$"

LittlerootSW_EventScript_OldWomanOnBeach_Text_1:
	.string "Can you spare some money for an old\n"
	.string "lady? Just ¥100 will do!$"

LittlerootSW_EventScript_OldWomanOnBeach_Text_2:
	.string "I see...$"

LittlerootSW_EventScript_OldWomanOnBeach_Text_3:
	.string "Hello again, young man! How are you\n"
	.string "today?$"

LittlerootSW_OldWomanOnBeach_Text::
	.string "Oh, thank you, so generous!\p"
	.string "Please, let me say thank you with this!$"

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

LittlerootSW_OldManOnBeach_Male_Text::
	.string "Buenos días, joven. Where are you from?\p"
	.string "My family used to own sugar plantations\n"
	.string "in Nicaragua.\p"
	.string "When the revolutionaries took over,\n"
	.string "they seized the farmlands.\p"
	.string "I lost everything...$"

LittlerootSW_OldManOnBeach_Female_Text::
	.string "Buenos días, jovencita. Where are you\n"
	.string "from?\p"
	.string "My family used to own sugar plantations\n"
	.string "in Nicaragua.\p"
	.string "When the revolutionaries took over,\n"
	.string "they seized the farmlands.\p"
	.string "I lost everything...$"
