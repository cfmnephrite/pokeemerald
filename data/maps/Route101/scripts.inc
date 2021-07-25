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
	msgbox Route101_Text_HavingFunFishing, MSGBOX_DEFAULT
	release
	end

Route101_EventScript_Ernest_1:
	msgbox Route101_Text_WantToLearnToFish, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq Route101_EventScript_Ernest_4
	msgbox Route101_Text_NotInterested, MSGBOX_DEFAULT
	release
	end

Route101_EventScript_Ernest_4:
	msgbox Route101_EventScript_Ernest_Text_0
	trainerbattle_no_intro TRAINER_IVAN, Route101_Text_ErnestLoses
	msgbox Route101_Text_HaveOneOfMyRods, MSGBOX_DEFAULT
	giveitem ITEM_OLD_ROD
	setflag FLAG_RECEIVED_OLD_ROD
	msgbox Route101_Text_FishingAdvice, MSGBOX_DEFAULT
	release
	end


Route101_EventScript_YoungsterWildMons::
	msgbox Route101_Text_YoungsterWildMons, MSGBOX_NPC
	end


Route101_EventScript_Lily::
	trainerbattle_single TRAINER_CALVIN_1, Route101_Text_LilyIntro, Route101_Text_LilyLoses
	msgbox Route101_Text_LilyGeneral, MSGBOX_AUTOCLOSE
	end


Route101_EventScript_Lilys_Mum::
	msgbox Route101_Text_LilysMum, MSGBOX_NPC
	return


Route101_EventScript_RouteSign::
	msgbox Route101_Text_RouteSign, MSGBOX_SIGN
	return


Route101_EventScript_Ernest_Text_0:
	.string "Give it your all in this battle!$"

Route101_Text_AveryIntro::
	.string "Ah, I'm having the time of my life...\n The beach here is beautiful!\p"
	.string "Oh? A battle?$"

Route101_Text_AveryLoses::
	.string "Well, thanks for ruining my vacation...$"

Route101_Text_AveryGeneral::
	.string "Razor Wind is such a cool move!\p"
	.string "It's a special Flying-type attack that\n"
	.string "targets physical defense!$"

Route101_Text_WantToLearnToFish::
	.string "Oh, hello there, young man!\p"
	.string "This beach is popular for tourists,\nbut it's also a great fishing spot!\p"
	.string "Say, would you like a little fishing lesson?\p"
	.string "First, however, we battle!$"

Route101_Text_ErnestLoses::
	.string "Excellent!$"

Route101_Text_HaveOneOfMyRods::
	.string "That was a great battle!\nNow, take my rod!$"

Route101_Text_FishingAdvice::
	.string "So, fishing is very simple.\p"
	.string "All you have to do is face the water and use your Rod.\p"
	.string "If you get a nibble on your rod,\npull it hard!$"

Route101_Text_NotInterested::
	.string "Oh, you're not interested?\nToo bad. Anyway, if you change your mind, you can find me here.$"

Route101_Text_HavingFunFishing::
	.string "So, are you having fun fishing?$"

Route101_Text_YoungsterWildMons::
	.string "Wow, there're so many different\n"
	.string "monsters around here now!$"

Route101_Text_LilyIntro::
	.string "Mommy got me a monster!\nBattle me! Battle me!$"

Route101_Text_LilyLoses::
	.string "Hey, no fair!\nYou big meanie!$"

Route101_Text_LilyGeneral::
	.string "Have you heard of Cherbui?\nIt's so cute!\p"
	.string "I want one! I want one!$"

Route101_Text_LilysMum::
	.string "Isn't she precious?\n"
	.string "I take her here every year!\p"
	.string "I wish those ghastly immigrants\n"
	.string "wouldn't come and ruin it though...$"

Route101_Text_RouteSign::
	.string "Route 101\n"
	.string "{UP_ARROW}Oldale\l{LEFT_ARROW}Petalburg$"
