Route101_MapScripts::
	.byte 0


make::
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
	.string "Give it all in this battle!$"

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
	.string "Oh, hello there, young man! This beach is\n"
	.string "popular among tourists, but is also a\l"
	.string "great place for fishing! Say, would you\l"
	.string "like to learn to fish? First however, we\l"
	.string "battle!$"

Route101_ErnestLoses::
	.string "Excellent!$"

Route101_HaveOneOfMyRods::
	.string "That was a great battle! Now, take one\n"
	.string "of my Rods!$"

Route101_FishingAdvice::
	.string "So, fishing is very simple. All you have\n"
	.string "to do is facing the water and use your\l"
	.string "Rod. If you get a bite, pull the Rod.$"

Route101_NotInterested::
	.string "Oh, you're not interested? Too bad.\n"
	.string "Anyway, if you change your mind, you\l"
	.string "can find me here.$"

Route101_HavingFunFishing::
	.string "So, are you having fun fishing?$"
