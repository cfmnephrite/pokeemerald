Littleroot_BeachCafe_MapScripts::
	.byte 0


Littleroot_BeachCafe_EventScript_SailorExposition::
	lock
	faceplayer
	msgbox Littleroot_BeachCafe_EventScript_SailorExposition_Text_0, MSGBOX_AUTOCLOSE
	release
	end


Littleroot_BeachCafe_EventScript_LittleGirl::
	lock
	faceplayer
	msgbox Littleroot_BeachCafe_EventScript_LittleGirl_Text_0, MSGBOX_AUTOCLOSE
	release
	end


Littleroot_BeachCafe_EventScript_SailorExposition_Text_0:
	.string "Slateport used to be my favorite place\n"
	.string "to work.\p"
	.string "It's a real shame what happened to it.$"

Littleroot_BeachCafe_EventScript_LittleGirl_Text_0:
	.string "I'm here on vacation with Mama and\n"
	.string "Papa!\p"
	.string "My papa works at Devon!\n"
	.string "What about yours?$"
