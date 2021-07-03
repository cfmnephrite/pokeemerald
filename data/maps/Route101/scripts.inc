Route101_MapScripts::
	.byte 0


Route101_EventScript_Avery::
	trainerbattle_single TRAINER_CALVIN_1, Route101_Text_AveryIntro, Route101_Text_AveryLoses
	msgbox Route101_Text_AveryGeneral, MSGBOX_AUTOCLOSE
	end


Route101_EventScript_Ernest::
	lock
	faceplayer
	goto_if_unset FLAG_RECEIVED_OLD_ROD, Route101_EventScript_Ernest_1
	msgbox Route101_HavingFunFishing, MSGBOX_DEFAULT
	release
	end

Route101_EventScript_Ernest_1:
	msgbox Route101_WantToLearnToFish, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq Route101_EventScript_Ernest_4
	msgbox Route101_NotInterested, MSGBOX_DEFAULT
	release
	end

Route101_EventScript_Ernest_4:
	msgbox Route101_EventScript_Ernest_Text_0
	trainerbattle_no_intro TRAINER_IVAN, Route101_ErnestLoses
	msgbox Route101_HaveOneOfMyRods, MSGBOX_DEFAULT
	giveitem ITEM_OLD_ROD
	setflag FLAG_RECEIVED_OLD_ROD
	msgbox Route101_FishingAdvice, MSGBOX_DEFAULT
	release
	end


Route101_EventScript_Ernest_Text_0:
	.string "Give it your all in this battle!$"

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

Route101_WantToLearnToFish::
	.string "Oh, hello there, young man!\p"
	.string "This beach is popular for tourists,\n"
	.string "but it's also a great fishing spot!\p"
	.string "Say, would you like a little fishing\n"
	.string "lesson?\p"
	.string "First, however, we battle!$"

Route101_ErnestLoses::
	.string "Excellent!$"

Route101_HaveOneOfMyRods::
	.string "That was a great battle!\n"
	.string "Now, take one of my Rods!$"

Route101_FishingAdvice::
	.string "So, fishing is very simple.\p"
	.string "All you have to do is face the water and\n"
	.string "use your Rod.\p"
	.string "If you get a bite, pull the Rod.$"

Route101_NotInterested::
	.string "Oh, you're not interested? Too bad.\n"
	.string "Anyway, if you change your mind, you\l"
	.string "can find me here.$"

Route101_HavingFunFishing::
	.string "So, are you having fun fishing?$"
