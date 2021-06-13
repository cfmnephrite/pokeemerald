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
	.string "What? I have ordered a double\n"
	.string "cheeseburger, but there's no cheese in\l"
	.string "there! Uh? Do you want to battle us?$"

Route101_JuliaLoses::
	.string "Oh wow, takeout service is terrible and\n"
	.string "so are our monsters...$"

Route101_JuliaGeneral::
	.string "We are here in vacation. The beach is\n"
	.string "lovely, but the services around here\l"
	.string "leave a lot to be desired...$"

Route101_JuliaNotEnoughMons::
	.string "Huh? You have just one monster. We\n"
	.string "can't bother to battle you like that.$"

Route101_PhilIntro::
	.string "Oh hello there! Are you too in vacation?\n"
	.string "Ah, you want to battle us? Alright!$"

Route101_PhilLoses::
	.string "Oh oh. What strong monsters you have!$"

Route101_PhilGeneral::
	.string "We are here in vacation. It's a lovely\n"
	.string "place, shame about that refugees\l"
	.string "situation...$"

Route101_PhilNotEnoughMons::
	.string "Hoho. I see you want to battle us, but\n"
	.string "you need more monsters in your team...$"
