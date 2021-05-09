LittlerootSE_MapScripts::
	.byte 0


LittlerootSE_MagmaRallyTrigger::
	lockall
	goto LittlerootSE_MagmaRally
	end


LittlerootSE_MagmaRally::
	msgbox LittlerootSE_WeAreTeamMagma, MSGBOX_DEFAULT
	addobject 13
	addobject 14
	addobject 15
	addobject 16
	msgbox LittlerootSE_MagmaRally_Text_0
	waitmessage
	playse SE_PIN
	applymovement 3, Common_Movement_QuestionMark
	applymovement 4, Common_Movement_QuestionMark
	applymovement 5, Common_Movement_QuestionMark
	applymovement 7, Common_Movement_FaceDown
	applymovement 9, Common_Movement_FaceDown
	applymovement 10, Common_Movement_FaceDown
	applymovement 11, Common_Movement_FaceDown
	applymovement 12, Common_Movement_FaceDown
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceDown
	applymovement 13, LittlerootSE_Movement_Grunt1GoungUp
	applymovement 14, LittlerootSE_Movement_OtherGruntsGoungUp
	applymovement 15, LittlerootSE_Movement_OtherGruntsGoungUp
	applymovement 16, LittlerootSE_Movement_OtherGruntsGoungUp
	msgbox LittlerootSE_WeAreTeamAqua, MSGBOX_DEFAULT
	applymovement 3, Common_Movement_WalkInPlaceFastestDown
	msgbox LittlerootSE_YouCowards, MSGBOX_DEFAULT
	applymovement 7, LittlerootSE_Movement_CrowdDispersing1
	applymovement 9, LittlerootSE_Movement_CrowdDispersing2
	applymovement 10, LittlerootSE_Movement_CrowdDispersing3
	applymovement 11, LittlerootSE_Movement_CrowdDispersing4
	applymovement 12, LittlerootSE_Movement_CrowdDispersing5
	removeobject 7
	removeobject 9
	removeobject 10
	removeobject 11
	removeobject 12
	msgbox LittlerootSE_AreYouWithUsOrWithThem, MSGBOX_DEFAULT
	end


LittlerootSE_Movement_Grunt1GoungUp:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

LittlerootSE_Movement_OtherGruntsGoungUp:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

LittlerootSE_Movement_CrowdDispersing1:
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	step_end

LittlerootSE_Movement_CrowdDispersing2:
	walk_fastest_left
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	walk_fastest_down
	step_end

LittlerootSE_Movement_CrowdDispersing3:
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	step_end

LittlerootSE_Movement_CrowdDispersing4:
	walk_fastest_left
	walk_fastest_left
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	step_end

LittlerootSE_Movement_CrowdDispersing5:
	walk_fastest_right
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	step_end

LittlerootSE_MagmaRally_Text_0:
	.string "???: Hold it right there!$"

LittlerootSE_WeAreTeamMagma::
	.string "Magma Grunt 1: Comrades! We live in\n"
	.string "desperate times!\p"
	.string "Some of you have escaped from horrific\n"
	.string "violence.\p"
	.string "Some of you have fled from the rising\n"
	.string "waters.\p"
	.string "And some have been forced here by\n"
	.string "drought and famine.\p"
	.string "We can't change the past, but the\n"
	.string "future is ours!\p"
	.string "We must work together to build a\n"
	.string "better, fairer society!\p"
	.string "We shall overthrow our corrupt, failing\n"
	.string "governments!\p"
	.string "We can share resources, build shelters,\n"
	.string "schools, and hospitals so that\l"
	.string "everyone has a chance for a\l"
	.string "comfortable life.\p"
	.string "We can no longer let the elite exploit\n"
	.string "us while they ravage our planet.\p"
	.string "In time, science will help us to undo the\n"
	.string "damage.$"

LittlerootSE_WeAreTeamAqua::
	.string "Aqua Grunt 1: What a load of nonsense.\n"
	.string "Surely you people aren't buying this?\p"
	.string "You're all here because you are\n"
	.string "stronger than the rest.\p"
	.string "Because you had the courage and\n"
	.string "determination to fight your way here.\p"
	.string "Our planet has been ruined by the\n"
	.string "greedy, the weak and the faithless.\p"
	.string "Don't give up your fight to join them\n"
	.string "and follow a bunch of spineless\l"
	.string "hypocrites.\p"
	.string "No matter what these criminals might\n"
	.string "tell you, the end is near.\p"
	.string "The heavens shall open and a great\n"
	.string "flood shall sweep the Earth.\p"
	.string "The only path of salvation is through\n"
	.string "us - through Aqua!$"

LittlerootSE_YouCowards::
	.string "Magma Grunt 2: The words of these\n"
	.string "deranged bigots are meaningless!\p"
	.string "You, Aqua, don't want to save anyone\n"
	.string "but your supporters.\p"
	.string "You call us criminals, while you pigs\n"
	.string "stuff your pockets with dirty money!\p"
	.string "Aqua Grunt 2: We're not here to argue\n"
	.string "with you violent thugs.\p"
	.string "You should leave, you pathetic bleeding\n"
	.string "hearts!$"

LittlerootSE_AreYouWithUsOrWithThem::
	.string "Magma Grunt 1: Who are you? Are you with\n"
	.string "us or are you with them?$"
