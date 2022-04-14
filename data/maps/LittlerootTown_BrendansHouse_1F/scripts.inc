LittlerootTown_BrendansHouse_1F_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, LittlerootTown_BrendansHouse_1F_EventScript_ShowRunningShoesManual
	.byte 0


LittlerootTown_BrendansHouse_1F_EventScript_ShowRunningShoesManual::
	setmetatile 3, 7, METATILE_BrendansMaysHouse_BookOnTable, 1
	return


EventScript_RunningShoesManual::
	msgbox PlayersHouse_1F_Text_RunningShoesManual, MSGBOX_SIGN
	end


PlayersHouse_1F_Text_RunningShoesManual::
	.string "It's the instruction booklet for the\n"
	.string "RUNNING SHOES.\p"
	.string "“Press the B Button to run while\n"
	.string "wearing your RUNNING SHOES.\p"
	.string "“Lace up your RUNNING SHOES and hit\n"
	.string "the road running!”$"

PlayersHouse_1F_Text_TheresAMusicVideoOnTV::
	.string "There is a music video on TV.\p"
	.string "...\p"
	.string "Never gonna give you up\n"
	.string "Never gonna let you down\p"
	.string "Naver gonna run around and\n"
	.string "desert you\p"
	.string "Never gonna make you cry\n"
	.string "Never gonna say goodbye\p"
	.string "Never gonna tell a lie\n"
	.string "and hurt you...$"
