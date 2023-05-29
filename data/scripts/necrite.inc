SpecialBattle_EventScript_VsRayquazaDeoxys::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_RAYQUAZA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_RAYQUAZA, 1, ITEM_NONE, SPECIES_DEOXYS, 1, ITEM_NONE
	special StartVsRayquazaDeoxysBattle
	waitstate
	release
	end
