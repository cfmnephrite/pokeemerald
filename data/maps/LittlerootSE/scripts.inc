LittlerootSE_MapScripts::
	.byte 0


LittlerootSE_MagmaRallyTrigger::
	lockall
	goto LittlerootSE_MagmaRally
	end


LittlerootSE_MagmaRally::
	msgbox LittlerootSE_WeAreTeamMagma, MSGBOX_DEFAULT
	clearflag FLAG_HIDE_AQUA_GRUNTS
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

LittlerootSE_MagmaRally_Text_0:
	.string "???: Hold it right there!$"

LittlerootSE_WeAreTeamMagma::
	.string "Magma Grunt 1: Welcome, refugees...\p"
	.string "Allow us to express our sympathy for all\n"
	.string "of your hardships, from the bottom of\l"
	.string "our hearts.\p"
	.string "We, Team Magma, are an organization\n"
	.string "dedicated to fight against climate\l"
	.string "change to prevent tragedies, such as\l"
	.string "the one that struck your homeland,\l"
	.string "from happening ever again.\p"
	.string "Even though everyone turns a blind eye\n"
	.string "over it, climate change is becoming a\l"
	.string "bigger and bigger problem here in Hoenn\l"
	.string "too.\p"
	.string "Corrupt corporations are not willing to\n"
	.string "make the change, just for the sake of\l"
	.string "their own gains, not caring of what will\l"
	.string "be of our beautiful land!\p"
	.string "As you can see, we are all in the same\n"
	.string "boat. We need the cooperation of all\l"
	.string "people in our crusade against the\l"
	.string "status quo!\p"
	.string "So, people of the world, uni-$"

LittlerootSE_WeAreTeamAqua::
	.string "Aqua Grunt 1: Look at you, refugees.\p"
	.string "You escaped your countries only to\n"
	.string "arrive in a wretched land, imploring\l"
	.string "charity, listening to the blabbering of\l"
	.string "some buffoons.\p"
	.string "No matter what others may tell you, the\n"
	.string "end of the world is coming. The climate\l"
	.string "crisis that is sweeping nations one by\l"
	.string "one is a divine punishment by the hands\l"
	.string "of God.\p"
	.string "Greedy, godless and filthy human beings\n"
	.string "have ruined the planet. Exploiting\l"
	.string "other humans and Earth's resources\l"
	.string "has brought the wrath of the Heavens\l"
	.string "upon all us.\p"
	.string "There is but one way of salvation from\n"
	.string "the impending doom -- joining Team\l"
	.string "Aqua, our noble organization!\p"
	.string "If you're worthy of living among the\n"
	.string "chosen by God, that is...$"

LittlerootSE_YouCowards::
	.string "Magma Grunt 1: Aqua, you bastards!\p"
	.string "Comrades, do not listen to a single word\n"
	.string "from the mouth of those bigots!\p"
	.string "They don't care about the safety of\n"
	.string "anyone...$"
