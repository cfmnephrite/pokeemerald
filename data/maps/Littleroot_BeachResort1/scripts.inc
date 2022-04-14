Littleroot_BeachResort1_MapScripts::
	.byte 0


Route101_EventScript_Julia::
	trainerbattle_double TRAINER_DEZ_AND_LUKE, Route101_JuliaIntro, Route101_JuliaLoses, Route101_JuliaNotEnoughMons
	msgbox Route101_JuliaGeneral, MSGBOX_AUTOCLOSE
	end


Route101_EventScript_Phil::
	trainerbattle_double TRAINER_DEZ_AND_LUKE, Route101_PhilIntro, Route101_PhilLoses, Route101_PhilNotEnoughMons
	msgbox Route101_PhilGeneral, MSGBOX_AUTOCLOSE
	end


Route101_JuliaIntro::
	.string "What?\p"
	.string "I ordered a double cheeseburger and\n"
	.string "there's no cheese in it!\p"
	.string "Huh? Do you want to battle us?$"

Route101_JuliaLoses::
	.string "Oh, wow! The takeout service is terrible\n"
	.string "and so are our monsters...$"

Route101_JuliaGeneral::
	.string "The beach here is fantastic!\p"
	.string "Amazing to think that it used to be\n"
	.string "miles inland...\p"
	.string "The services leave a lot to be desired\n"
	.string "though!$"

Route101_JuliaNotEnoughMons::
	.string "Huh? You only have one monster.\p"
	.string "Come back when we can have a proper\n"
	.string "double battle!$"

Route101_PhilIntro::
	.string "Oh hello there!\n"
	.string "Are you on vacation too?\p"
	.string "You want to battle us? All right!$"

Route101_PhilLoses::
	.string "Oof. What strong monsters you have!$"

Route101_PhilGeneral::
	.string "We're here on vacation.\p"
	.string "It's a lovely place, but I wish that\n"
	.string "refugee camp weren't so close by.$"

Route101_PhilNotEnoughMons::
	.string "Hoho, I see you want to battle us!\p"
	.string "But you need more monsters in your\n"
	.string "team...$"
