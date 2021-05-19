Route101_MapScripts::
	.byte 0


make::
	trainerbattle_single TRAINER_CALVIN_1, Route101_Text_AveryIntro, Route101_Text_AveryLoses
	msgbox Route101_Text_AveryGeneral, MSGBOX_AUTOCLOSE
	end


Route101_Text_AveryIntro::
	.string "Ah, I'm having the time of my life...\n"
	.string "The beach here is beautiful!\p"
	.string "Oh? A battle?$"

Route101_Text_AveryLoses::
	.string "Well, thanks for ruining my vacation...$"

Route101_Text_AveryGeneral::
	.string "Razor Wind is such a cool move!\p"
	.string "It's a special Flying-type attack that\n"
	.string "targets physical defense!$"
