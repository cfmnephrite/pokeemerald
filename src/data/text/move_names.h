const u8 gMoveNames[MOVES_COUNT][MOVE_NAME_LENGTH + 1] =
{
    [MOVE_NONE] = _("-"),
    [MOVE_10_000_000_VOLT_THUNDERBOLT] = _("{V_SKINNY}10,000,000V Thunderbolt"),
    [MOVE_ABSORB] = _("Absorb"),
    [MOVE_ACCELEROCK] = _("Accelerock"),
    [MOVE_ACID] = _("Acid"),
    [MOVE_ACID_ARMOR] = _("Acid Armor"),
    [MOVE_ACID_DOWNPOUR] = _("Acid Downpour"),
    [MOVE_ACID_SPRAY] = _("Acid Spray"),
    [MOVE_ACROBATICS] = _("Acrobatics"),
    [MOVE_ACUPRESSURE] = _("Acupressure"),
    [MOVE_AERIAL_ACE] = _("Aerial Ace"),
    [MOVE_AEROBLAST] = _("Aeroblast"),
    [MOVE_AFTER_YOU] = _("After You"),
    [MOVE_AGILITY] = _("Agility"),
    [MOVE_AIR_CUTTER] = _("Air Cutter"),
    [MOVE_AIR_SLASH] = _("Air Slash"),
    [MOVE_ALL_OUT_PUMMELING] = _("All-Out Pummeling"),
    [MOVE_ALLY_SWITCH] = _("Ally Switch"),
    [MOVE_AMNESIA] = _("Amnesia"),
    [MOVE_ANCHOR_SHOT] = _("Anchor Shot"),
    [MOVE_ANCIENT_POWER] = _("Ancient Power"),
    [MOVE_APPLE_ACID] = _("Apple Acid"),
    [MOVE_AQUA_JET] = _("Aqua Jet"),
    [MOVE_AQUA_RING] = _("Aqua Ring"),
    [MOVE_AQUA_TAIL] = _("Aqua Tail"),
    [MOVE_ARM_THRUST] = _("Arm Thrust"),
    [MOVE_AROMATHERAPY] = _("Aromatherapy"),
    [MOVE_AROMATIC_MIST] = _("Aromatic Mist"),
    [MOVE_ASSIST] = _("Assist"),
    [MOVE_ASSURANCE] = _("Assurance"),
    [MOVE_ASTONISH] = _("Astonish"),
    [MOVE_ATTACK_ORDER] = _("Attack Order"),
    [MOVE_ATTRACT] = _("Attract"),
    [MOVE_AURA_SPHERE] = _("Aura Sphere"),
    [MOVE_AURA_WHEEL] = _("Aura Wheel"),
    [MOVE_AURORA_BEAM] = _("Aurora Beam"),
    [MOVE_AURORA_VEIL] = _("Aurora Veil"),
    [MOVE_AUTOTOMIZE] = _("Autotomize"),
    [MOVE_AVALANCHE] = _("Avalanche"),
    [MOVE_BABY_DOLL_EYES] = _("Baby-Doll Eyes"),
    [MOVE_BANEFUL_BUNKER] = _("Baneful Bunker"),
    [MOVE_BARRAGE] = _("Barrage"),
    [MOVE_BARRIER] = _("Barrier"),
    [MOVE_BATON_PASS] = _("Baton Pass"),
    [MOVE_BEAK_BLAST] = _("Beak Blast"),
    [MOVE_BEAT_UP] = _("Beat Up"),
    [MOVE_BEHEMOTH_BASH] = _("Behemoth Bash"),
    [MOVE_BEHEMOTH_BLADE] = _("Behemoth Blade"),
    [MOVE_BELCH] = _("Belch"),
    [MOVE_BELLY_DRUM] = _("Belly Drum"),
    [MOVE_BESTOW] = _("Bestow"),
    [MOVE_BIDE] = _("Bide"),
    [MOVE_BIND] = _("Bind"),
    [MOVE_BITE] = _("Bite"),
    [MOVE_BLACK_HOLE_ECLIPSE] = _("Black Hole Eclipse"),
    [MOVE_BLAST_BURN] = _("Blast Burn"),
    [MOVE_BLAZE_KICK] = _("Blaze Kick"),
    [MOVE_BLIZZARD] = _("Blizzard"),
    [MOVE_BLOCK] = _("Block"),
    [MOVE_BLOOM_DOOM] = _("Bloom Doom"),
    [MOVE_BLUE_FLARE] = _("Blue Flare"),
    [MOVE_BODY_PRESS] = _("Body Press"),
    [MOVE_BODY_SLAM] = _("Body Slam"),
    [MOVE_BOLT_BEAK] = _("Bolt Beak"),
    [MOVE_BOLT_STRIKE] = _("Bolt Strike"),
    [MOVE_BONE_CLUB] = _("Bone Club"),
    [MOVE_BONE_RUSH] = _("Bone Rush"),
    [MOVE_BONEMERANG] = _("Bonemerang"),
    [MOVE_BOOMBURST] = _("Boomburst"),
    [MOVE_BOUNCE] = _("Bounce"),
    [MOVE_BRANCH_POKE] = _("Branch Poke"),
    [MOVE_BRAVE_BIRD] = _("Brave Bird"),
    [MOVE_BREAKING_SWIPE] = _("Breaking Swipe"),
    [MOVE_BREAKNECK_BLITZ] = _("Breakneck Blitz"),
    [MOVE_BRICK_BREAK] = _("Brick Break"),
    [MOVE_BRINE] = _("Brine"),
    [MOVE_BRUTAL_SWING] = _("Brutal Swing"),
    [MOVE_BUBBLE] = _("Bubble"),
    [MOVE_BUBBLE_BEAM] = _("Bubble Beam"),
    [MOVE_BUG_BITE] = _("Bug Bite"),
    [MOVE_BUG_BUZZ] = _("Bug Buzz"),
    [MOVE_BULK_UP] = _("Bulk Up"),
    [MOVE_BULLDOZE] = _("Bulldoze"),
    [MOVE_BULLET_PUNCH] = _("Bullet Punch"),
    [MOVE_BULLET_SEED] = _("Bullet Seed"),
    [MOVE_BURN_UP] = _("Burn Up"),
    [MOVE_BURNING_JEALOUSY] = _("Burning Jealousy"),
    [MOVE_CALM_MIND] = _("Calm Mind"),
    [MOVE_CAMOUFLAGE] = _("Camouflage"),
    [MOVE_CAPTIVATE] = _("Captivate"),
    [MOVE_CATASTROPIKA] = _("Catastropika"),
    [MOVE_CELEBRATE] = _("Celebrate"),
    [MOVE_CHARGE] = _("Charge"),
    [MOVE_CHARGE_BEAM] = _("Charge Beam"),
    [MOVE_CHARM] = _("Charm"),
    [MOVE_CHATTER] = _("Chatter"),
    [MOVE_CHIP_AWAY] = _("Chip Away"),
    [MOVE_CIRCLE_THROW] = _("Circle Throw"),
    [MOVE_CLAMP] = _("Clamp"),
    [MOVE_CLANGING_SCALES] = _("Clanging Scales"),
    [MOVE_CLANGOROUS_SOUL] = _("Clangorous Soul"),
    [MOVE_CLANGOROUS_SOULBLAZE] = _("{V_SKINNY}Clangorous Soulblaze"),
    [MOVE_CLEAR_SMOG] = _("Clear Smog"),
    [MOVE_CLOSE_COMBAT] = _("Close Combat"),
    [MOVE_COACHING] = _("Coaching"),
    [MOVE_COIL] = _("Coil"),
    [MOVE_COMET_PUNCH] = _("Comet Punch"),
    [MOVE_CONFIDE] = _("Confide"),
    [MOVE_CONFUSE_RAY] = _("Confuse Ray"),
    [MOVE_CONFUSION] = _("Confusion"),
    [MOVE_CONSTRICT] = _("Constrict"),
    [MOVE_CONTINENTAL_CRUSH] = _("Continental Crush"),
    [MOVE_CONVERSION] = _("Conversion"),
    [MOVE_CONVERSION_2] = _("Conversion 2"),
    [MOVE_COPYCAT] = _("Copycat"),
    [MOVE_CORE_ENFORCER] = _("Core Enforcer"),
    [MOVE_CORKSCREW_CRASH] = _("Corkscrew Crash"),
    [MOVE_CORROSIVE_GAS] = _("Corrosive Gas"),
    [MOVE_COSMIC_POWER] = _("Cosmic Power"),
    [MOVE_COTTON_GUARD] = _("Cotton Guard"),
    [MOVE_COTTON_SPORE] = _("Cotton Spore"),
    [MOVE_COUNTER] = _("Counter"),
    [MOVE_COURT_CHANGE] = _("Court Change"),
    [MOVE_COVET] = _("Covet"),
    [MOVE_CRABHAMMER] = _("Crabhammer"),
    [MOVE_CRAFTY_SHIELD] = _("Crafty Shield"),
    [MOVE_CROSS_CHOP] = _("Cross Chop"),
    [MOVE_CROSS_POISON] = _("Cross Poison"),
    [MOVE_CRUNCH] = _("Crunch"),
    [MOVE_CRUSH_CLAW] = _("Crush Claw"),
    [MOVE_CRUSH_GRIP] = _("Crush Grip"),
    [MOVE_CURSE] = _("Curse"),
    [MOVE_CUT] = _("Cut"),
    [MOVE_DARK_PULSE] = _("Dark Pulse"),
    [MOVE_DARK_VOID] = _("Dark Void"),
    [MOVE_DARKEST_LARIAT] = _("Darkest Lariat"),
    [MOVE_DAZZLING_GLEAM] = _("Dazzling Gleam"),
    [MOVE_DECORATE] = _("Decorate"),
    [MOVE_DEFEND_ORDER] = _("Defend Order"),
    [MOVE_DEFENSE_CURL] = _("Defense Curl"),
    [MOVE_DEFOG] = _("Defog"),
    [MOVE_DESTINY_BOND] = _("Destiny Bond"),
    [MOVE_DETECT] = _("Detect"),
    [MOVE_DEVASTATING_DRAKE] = _("Devastating Drake"),
    [MOVE_DIAMOND_STORM] = _("Diamond Storm"),
    [MOVE_DIG] = _("Dig"),
    [MOVE_DISABLE] = _("Disable"),
    [MOVE_DISARMING_VOICE] = _("Disarming Voice"),
    [MOVE_DISCHARGE] = _("Discharge"),
    [MOVE_DIVE] = _("Dive"),
    [MOVE_DIZZY_PUNCH] = _("Dizzy Punch"),
    [MOVE_DOOM_DESIRE] = _("Doom Desire"),
    [MOVE_DOUBLE_EDGE] = _("Double-Edge"),
    [MOVE_DOUBLE_HIT] = _("Double Hit"),
    [MOVE_DOUBLE_IRON_BASH] = _("Double Iron Bash"),
    [MOVE_DOUBLE_KICK] = _("Double Kick"),
    [MOVE_DOUBLE_SLAP] = _("Double Slap"),
    [MOVE_DOUBLE_TEAM] = _("Double Team"),
    [MOVE_DRACO_METEOR] = _("Draco Meteor"),
    [MOVE_DRAGON_ASCENT] = _("Dragon Ascent"),
    [MOVE_DRAGON_BREATH] = _("Dragon Breath"),
    [MOVE_DRAGON_CLAW] = _("Dragon Claw"),
    [MOVE_DRAGON_DANCE] = _("Dragon Dance"),
    [MOVE_DRAGON_DARTS] = _("Dragon Darts"),
    [MOVE_DRAGON_HAMMER] = _("Dragon Hammer"),
    [MOVE_DRAGON_PULSE] = _("Dragon Pulse"),
    [MOVE_DRAGON_RAGE] = _("Dragon Rage"),
    [MOVE_DRAGON_RUSH] = _("Dragon Rush"),
    [MOVE_DRAGON_TAIL] = _("Dragon Tail"),
    [MOVE_DRAIN_PUNCH] = _("Drain Punch"),
    [MOVE_DRAINING_KISS] = _("Draining Kiss"),
    [MOVE_DREAM_EATER] = _("Dream Eater"),
    [MOVE_DRILL_PECK] = _("Drill Peck"),
    [MOVE_DRILL_RUN] = _("Drill Run"),
    [MOVE_DRUM_BEATING] = _("Drum Beating"),
    [MOVE_DUAL_CHOP] = _("Dual Chop"),
    [MOVE_DUAL_WINGBEAT] = _("Dual Wingbeat"),
    [MOVE_DYNAMAX_CANNON] = _("{SKINNY}Dynamax Cannon"),
    [MOVE_DYNAMIC_PUNCH] = _("Dynamic Punch"),
    [MOVE_EARTH_POWER] = _("Earth Power"),
    [MOVE_EARTHQUAKE] = _("Earthquake"),
    [MOVE_ECHOED_VOICE] = _("Echoed Voice"),
    [MOVE_EERIE_IMPULSE] = _("Eerie Impulse"),
    [MOVE_EGG_BOMB] = _("Egg Bomb"),
    [MOVE_ELECTRIC_TERRAIN] = _("Electric Terrain"),
    [MOVE_ELECTRIFY] = _("Electrify"),
    [MOVE_ELECTRO_BALL] = _("Electro Ball"),
    [MOVE_ELECTROWEB] = _("Electroweb"),
    [MOVE_EMBARGO] = _("Embargo"),
    [MOVE_EMBER] = _("Ember"),
    [MOVE_ENCORE] = _("Encore"),
    [MOVE_ENDEAVOR] = _("Endeavor"),
    [MOVE_ENDURE] = _("Endure"),
    [MOVE_ENERGY_BALL] = _("Energy Ball"),
    [MOVE_ENTRAINMENT] = _("Entrainment"),
    [MOVE_ERUPTION] = _("Eruption"),
    [MOVE_ETERNABEAM] = _("Eternabeam"),
    [MOVE_EXPANDING_FORCE] = _("Expanding Force"),
    [MOVE_EXPLOSION] = _("Explosion"),
    [MOVE_EXTRASENSORY] = _("Extrasensory"),
    [MOVE_EXTREME_EVOBOOST] = _("Extreme Evoboost"),
    [MOVE_EXTREME_SPEED] = _("Extreme Speed"),
    [MOVE_FACADE] = _("Façade"),
    [MOVE_FAINT_ATTACK] = _("Feint Attack"),
    [MOVE_FAIRY_LOCK] = _("Fairy Lock"),
    [MOVE_FAIRY_WIND] = _("Fairy Wind"),
    [MOVE_FAKE_OUT] = _("Fake Out"),
    [MOVE_FAKE_TEARS] = _("Fake Tears"),
    [MOVE_FALSE_SURRENDER] = _("False Surrender"),
    [MOVE_FALSE_SWIPE] = _("False Swipe"),
    [MOVE_FEATHER_DANCE] = _("Feather Dance"),
    [MOVE_FEINT] = _("Feint"),
    [MOVE_FELL_STINGER] = _("Fell Stinger"),
    [MOVE_FIERY_DANCE] = _("Fiery Dance"),
    [MOVE_FINAL_GAMBIT] = _("Final Gambit"),
    [MOVE_FIRE_BLAST] = _("Fire Blast"),
    [MOVE_FIRE_FANG] = _("Fire Fang"),
    [MOVE_FIRE_LASH] = _("Fire Lash"),
    [MOVE_FIRE_PLEDGE] = _("Fire Pledge"),
    [MOVE_FIRE_PUNCH] = _("Fire Punch"),
    [MOVE_FIRE_SPIN] = _("Fire Spin"),
    [MOVE_FIRST_IMPRESSION] = _("First Impression"),
    [MOVE_FISHIOUS_REND] = _("Fishious Rend"),
    [MOVE_FISSURE] = _("Fissure"),
    [MOVE_FLAIL] = _("Flail"),
    [MOVE_FLAME_BURST] = _("Flame Burst"),
    [MOVE_FLAME_CHARGE] = _("Flame Charge"),
    [MOVE_FLAME_WHEEL] = _("Flame Wheel"),
    [MOVE_FLAMETHROWER] = _("Flamethrower"),
    [MOVE_FLARE_BLITZ] = _("Flare Blitz"),
    [MOVE_FLASH] = _("Flash"),
    [MOVE_FLASH_CANNON] = _("Flash Cannon"),
    [MOVE_FLATTER] = _("Flatter"),
    [MOVE_FLEUR_CANNON] = _("Fleur Cannon"),
    [MOVE_FLING] = _("Fling"),
    [MOVE_FLIP_TURN] = _("Flip Turn"),
    [MOVE_FLORAL_HEALING] = _("Floral Healing"),
    [MOVE_FLOWER_SHIELD] = _("Flower Shield"),
    [MOVE_FLY] = _("Fly"),
    [MOVE_FLYING_PRESS] = _("Flying Press"),
    [MOVE_FOCUS_BLAST] = _("Focus Blast"),
    [MOVE_FOCUS_ENERGY] = _("Focus Energy"),
    [MOVE_FOCUS_PUNCH] = _("Focus Punch"),
    [MOVE_FOLLOW_ME] = _("Follow Me"),
    [MOVE_FORCE_PALM] = _("Force Palm"),
    [MOVE_FORESIGHT] = _("Foresight"),
    [MOVE_FORESTS_CURSE] = _("Forest's Curse"),
    [MOVE_FOUL_PLAY] = _("Foul Play"),
    [MOVE_FREEZE_DRY] = _("Freeze-Dry"),
    [MOVE_FREEZE_SHOCK] = _("Freeze Shock"),
    [MOVE_FRENZY_PLANT] = _("Frenzy Plant"),
    [MOVE_FROST_BREATH] = _("Frost Breath"),
    [MOVE_FRUSTRATION] = _("Frustration"),
    [MOVE_FURY_ATTACK] = _("Fury Attack"),
    [MOVE_FURY_CUTTER] = _("Fury Cutter"),
    [MOVE_FURY_SWIPES] = _("Fury Swipes"),
    [MOVE_FUSION_BOLT] = _("Fusion Bolt"),
    [MOVE_FUSION_FLARE] = _("Fusion Flare"),
    [MOVE_FUTURE_SIGHT] = _("Future Sight"),
    [MOVE_GASTRO_ACID] = _("Gastro Acid"),
    [MOVE_GEAR_GRIND] = _("Gear Grind"),
    [MOVE_GEAR_UP] = _("Gear Up"),
    [MOVE_GENESIS_SUPERNOVA] = _("Genesis Supernova"),
    [MOVE_GEOMANCY] = _("Geomancy"),
    [MOVE_GIGA_DRAIN] = _("Giga Drain"),
    [MOVE_GIGA_IMPACT] = _("Giga Impact"),
    [MOVE_GIGAVOLT_HAVOC] = _("Gigavolt Havoc"),
    [MOVE_GLACIATE] = _("Glaciate"),
    [MOVE_GLARE] = _("Glare"),
    [MOVE_GRASS_KNOT] = _("Grass Knot"),
    [MOVE_GRASS_PLEDGE] = _("Grass Pledge"),
    [MOVE_GRASS_WHISTLE] = _("Grass Whistle"),
    [MOVE_GRASSY_GLIDE] = _("Grassy Glide"),
    [MOVE_GRASSY_TERRAIN] = _("Grassy Terrain"),
    [MOVE_GRAV_APPLE] = _("Grav Apple"),
    [MOVE_GRAVITY] = _("Gravity"),
    [MOVE_GROWL] = _("Growl"),
    [MOVE_GROWTH] = _("Growth"),
    [MOVE_GRUDGE] = _("Grudge"),
    [MOVE_GUARD_SPLIT] = _("Guard Split"),
    [MOVE_GUARD_SWAP] = _("Guard Swap"),
    [MOVE_GUARDIAN_OF_ALOLA] = _("Guardian of Alola"),
    [MOVE_GUILLOTINE] = _("Guillotine"),
    [MOVE_GUNK_SHOT] = _("Gunk Shot"),
    [MOVE_GUST] = _("Gust"),
    [MOVE_GYRO_BALL] = _("Gyro Ball"),
    [MOVE_HAIL] = _("Hail"),
    [MOVE_HAMMER_ARM] = _("Hammer Arm"),
    [MOVE_HAPPY_HOUR] = _("Happy Hour"),
    [MOVE_HARDEN] = _("Harden"),
    [MOVE_HAZE] = _("Haze"),
    [MOVE_HEAD_CHARGE] = _("Head Charge"),
    [MOVE_HEAD_SMASH] = _("Head Smash"),
    [MOVE_HEADBUTT] = _("Headbutt"),
    [MOVE_HEAL_BELL] = _("Heal Bell"),
    [MOVE_HEAL_BLOCK] = _("Heal Block"),
    [MOVE_HEAL_ORDER] = _("Heal Order"),
    [MOVE_HEAL_PULSE] = _("Heal Pulse"),
    [MOVE_HEALING_WISH] = _("Healing Wish"),
    [MOVE_HEART_STAMP] = _("Heart Stamp"),
    [MOVE_HEART_SWAP] = _("Heart Swap"),
    [MOVE_HEAT_CRASH] = _("Heat Crash"),
    [MOVE_HEAT_WAVE] = _("Heat Wave"),
    [MOVE_HEAVY_SLAM] = _("Heavy Slam"),
    [MOVE_HELPING_HAND] = _("Helping Hand"),
    [MOVE_HEX] = _("Hex"),
    [MOVE_HIDDEN_POWER] = _("Hidden Power"),
    [MOVE_HIDDEN_POWER_BUG] = _("Hidden Power"),
    [MOVE_HIDDEN_POWER_DARK] = _("Hidden Power"),
    [MOVE_HIDDEN_POWER_DRAGON] = _("Hidden Power"),
    [MOVE_HIDDEN_POWER_ELECTRIC] = _("Hidden Power"),
    [MOVE_HIDDEN_POWER_FAIRY] = _("Hidden Power"),
    [MOVE_HIDDEN_POWER_FIGHTING] = _("Hidden Power"),
    [MOVE_HIDDEN_POWER_FIRE] = _("Hidden Power"),
    [MOVE_HIDDEN_POWER_FLYING] = _("Hidden Power"),
    [MOVE_HIDDEN_POWER_GHOST] = _("Hidden Power"),
    [MOVE_HIDDEN_POWER_GRASS] = _("Hidden Power"),
    [MOVE_HIDDEN_POWER_GROUND] = _("Hidden Power"),
    [MOVE_HIDDEN_POWER_ICE] = _("Hidden Power"),
    [MOVE_HIDDEN_POWER_POISON] = _("Hidden Power"),
    [MOVE_HIDDEN_POWER_ROCK] = _("Hidden Power"),
    [MOVE_HIDDEN_POWER_STEEL] = _("Hidden Power"),
    [MOVE_HIDDEN_POWER_WATER] = _("Hidden Power"),
    [MOVE_HIGH_HORSEPOWER] = _("High Horsepower"),
    [MOVE_HIGH_JUMP_KICK] = _("High Jump Kick"),
    [MOVE_HOLD_BACK] = _("Hold Back"),
    [MOVE_HOLD_HANDS] = _("Hold Hands"),
    [MOVE_HONE_CLAWS] = _("Hone Claws"),
    [MOVE_HORN_ATTACK] = _("Horn Attack"),
    [MOVE_HORN_DRILL] = _("Horn Drill"),
    [MOVE_HORN_LEECH] = _("Horn Leech"),
    [MOVE_HOWL] = _("Howl"),
    [MOVE_HURRICANE] = _("Hurricane"),
    [MOVE_HYDRO_CANNON] = _("Hydro Cannon"),
    [MOVE_HYDRO_PUMP] = _("Hydro Pump"),
    [MOVE_HYDRO_VORTEX] = _("Hydro Vortex"),
    [MOVE_HYPER_BEAM] = _("Hyper Beam"),
    [MOVE_HYPER_FANG] = _("Hyper Fang"),
    [MOVE_HYPER_VOICE] = _("Hyper Voice"),
    [MOVE_HYPERSPACE_FURY] = _("Hyperspace Fury"),
    [MOVE_HYPERSPACE_HOLE] = _("Hyperspace Hole"),
    [MOVE_HYPNOSIS] = _("Hypnosis"),
    [MOVE_ICE_BALL] = _("Ice Ball"),
    [MOVE_ICE_BEAM] = _("Ice Beam"),
    [MOVE_ICE_BURN] = _("Ice Burn"),
    [MOVE_ICE_FANG] = _("Ice Fang"),
    [MOVE_ICE_HAMMER] = _("Ice Hammer"),
    [MOVE_ICE_PUNCH] = _("Ice Punch"),
    [MOVE_ICE_SHARD] = _("Ice Shard"),
    [MOVE_ICICLE_CRASH] = _("Icicle Crash"),
    [MOVE_ICICLE_SPEAR] = _("Icicle Spear"),
    [MOVE_ICY_WIND] = _("Icy Wind"),
    [MOVE_IMPRISON] = _("Imprison"),
    [MOVE_INCINERATE] = _("Incinerate"),
    [MOVE_INFERNO] = _("Inferno"),
    [MOVE_INFERNO_OVERDRIVE] = _("Inferno Overdrive"),
    [MOVE_INFESTATION] = _("Infestation"),
    [MOVE_INGRAIN] = _("Ingrain"),
    [MOVE_INSTRUCT] = _("Instruct"),
    [MOVE_ION_DELUGE] = _("Ion Deluge"),
    [MOVE_IRON_DEFENSE] = _("Iron Defense"),
    [MOVE_IRON_HEAD] = _("Iron Head"),
    [MOVE_IRON_TAIL] = _("Iron Tail"),
    [MOVE_JAW_LOCK] = _("Jaw Lock"),
    [MOVE_JUDGMENT] = _("Judgment"),
    [MOVE_JUMP_KICK] = _("Jump Kick"),
    [MOVE_JUNGLE_HEALING] = _("Jungle Healing"),
    [MOVE_KARATE_CHOP] = _("Karate Chop"),
    [MOVE_KINESIS] = _("Kinesis"),
    [MOVE_KINGS_SHIELD] = _("King's Shield"),
    [MOVE_KNOCK_OFF] = _("Knock Off"),
    [MOVE_LANDS_WRATH] = _("Land's Wrath"),
    [MOVE_LASER_FOCUS] = _("Laser Focus"),
    [MOVE_LASH_OUT] = _("Lash Out"),
    [MOVE_LAST_RESORT] = _("Last Resort"),
    [MOVE_LAVA_PLUME] = _("Lava Plume"),
    [MOVE_LEAFAGE] = _("Leafage"),
    [MOVE_LEAF_BLADE] = _("Leaf Blade"),
    [MOVE_LEAF_STORM] = _("Leaf Storm"),
    [MOVE_LEAF_TORNADO] = _("Leaf Tornado"),
    [MOVE_LEECH_LIFE] = _("Leech Life"),
    [MOVE_LEECH_SEED] = _("Leech Seed"),
    [MOVE_LEER] = _("Leer"),
    [MOVE_LETS_SNUGGLE_FOREVER] = _("Let's Snuggle Forever"),
    [MOVE_LICK] = _("Lick"),
    [MOVE_LIFE_DEW] = _("Life Dew"),
    [MOVE_LIGHT_OF_RUIN] = _("Light of Ruin"),
    [MOVE_LIGHT_SCREEN] = _("Light Screen"),
    [MOVE_LIGHT_THAT_BURNS_THE_SKY] = _("Light That Burns the Sky"),
    [MOVE_LIQUIDATION] = _("Liquidation"),
    [MOVE_LOCK_ON] = _("Lock-On"),
    [MOVE_LOVELY_KISS] = _("Lovely Kiss"),
    [MOVE_LOW_KICK] = _("Low Kick"),
    [MOVE_LOW_SWEEP] = _("Low Sweep"),
    [MOVE_LUCKY_CHANT] = _("Lucky Chant"),
    [MOVE_LUNAR_DANCE] = _("Lunar Dance"),
    [MOVE_LUNGE] = _("Lunge"),
    [MOVE_LUSTER_PURGE] = _("Luster Purge"),
    [MOVE_MACH_PUNCH] = _("Mach Punch"),
    [MOVE_MAGICAL_LEAF] = _("Magical Leaf"),
    [MOVE_MAGIC_COAT] = _("Magic Coat"),
    [MOVE_MAGIC_POWDER] = _("Magic Powder"),
    [MOVE_MAGIC_ROOM] = _("Magic Room"),
    [MOVE_MAGMA_STORM] = _("Magma Storm"),
    [MOVE_MAGNET_BOMB] = _("Magnet Bomb"),
    [MOVE_MAGNETIC_FLUX] = _("Magnetic Flux"),
    [MOVE_MAGNET_RISE] = _("Magnet Rise"),
    [MOVE_MAGNITUDE] = _("Magnitude"),
    [MOVE_MALICIOUS_MOONSAULT] = _("Malicious Moonsault"),
    [MOVE_MAT_BLOCK] = _("Mat Block"),
    [MOVE_MAX_AIRSTREAM] = _("Max Airstream"),
    [MOVE_MAX_DARKNESS] = _("Max Darkness"),
    [MOVE_MAX_FLARE] = _("Max Flare"),
    [MOVE_MAX_FLUTTERBY] = _("Max Flutterby"),
    [MOVE_MAX_GEYSER] = _("Max Geyser"),
    [MOVE_MAX_GUARD] = _("Max Guard"),
    [MOVE_MAX_HAILSTORM] = _("Max Hailstorm"),
    [MOVE_MAX_KNUCKLE] = _("Max Knuckle"),
    [MOVE_MAX_LIGHTNING] = _("Max Lightning"),
    [MOVE_MAX_MINDSTORM] = _("Max Mindstorm"),
    [MOVE_MAX_OOZE] = _("Max Ooze"),
    [MOVE_MAX_OVERGROWTH] = _("Max Overgrowth"),
    [MOVE_MAX_PHANTASM] = _("Max Phantasm"),
    [MOVE_MAX_QUAKE] = _("Max Quake"),
    [MOVE_MAX_ROCKFALL] = _("Max Rockfall"),
    [MOVE_MAX_STARFALL] = _("Max Starfall"),
    [MOVE_MAX_STEELSPIKE] = _("Max Steelspike"),
    [MOVE_MAX_STRIKE] = _("Max Strike"),
    [MOVE_MAX_WYRMWIND] = _("Max Wyrmwind"),
    [MOVE_MEAN_LOOK] = _("Mean Look"),
    [MOVE_MEDITATE] = _("Meditate"),
    [MOVE_ME_FIRST] = _("Me First"),
    [MOVE_MEGAHORN] = _("Megahorn"),
    [MOVE_MEGA_DRAIN] = _("Mega Drain"),
    [MOVE_MEGA_KICK] = _("Mega Kick"),
    [MOVE_MEGA_PUNCH] = _("Mega Punch"),
    [MOVE_MEMENTO] = _("Memento"),
    [MOVE_MENACING_MOONRAZE_MAELSTROM] = _("{V_SKINNY}Menacing Moonraze Maelstrom"),
    [MOVE_METAL_BURST] = _("Metal Burst"),
    [MOVE_METAL_CLAW] = _("Metal Claw"),
    [MOVE_METAL_SOUND] = _("Metal Sound"),
    [MOVE_METEOR_ASSAULT] = _("Meteor Assault"),
    [MOVE_METEOR_BEAM] = _("Meteor Beam"),
    [MOVE_METEOR_MASH] = _("Meteor Mash"),
    [MOVE_METRONOME] = _("Metronome"),
    [MOVE_MILK_DRINK] = _("Milk Drink"),
    [MOVE_MIMIC] = _("Mimic"),
    [MOVE_MIND_BLOWN] = _("Mind Blown"),
    [MOVE_MIND_READER] = _("Mind Reader"),
    [MOVE_MINIMIZE] = _("Minimize"),
    [MOVE_MIRACLE_EYE] = _("Miracle Eye"),
    [MOVE_MIRROR_COAT] = _("Mirror Coat"),
    [MOVE_MIRROR_MOVE] = _("Mirror Move"),
    [MOVE_MIRROR_SHOT] = _("Mirror Shot"),
    [MOVE_MIST] = _("Mist"),
    [MOVE_MIST_BALL] = _("Mist Ball"),
    [MOVE_MISTY_EXPLOSION] = _("Misty Explosion"),
    [MOVE_MISTY_TERRAIN] = _("Misty Terrain"),
    [MOVE_MOONBLAST] = _("Moonblast"),
    [MOVE_MOONGEIST_BEAM] = _("Moongeist Beam"),
    [MOVE_MOONLIGHT] = _("Moonlight"),
    [MOVE_MORNING_SUN] = _("Morning Sun"),
    [MOVE_MUD_BOMB] = _("Mud Bomb"),
    [MOVE_MUD_SHOT] = _("Mud Shot"),
    [MOVE_MUD_SLAP] = _("Mud-Slap"),
    [MOVE_MUD_SPORT] = _("Mud Sport"),
    [MOVE_MUDDY_WATER] = _("Muddy Water"),
    [MOVE_MULTI_ATTACK] = _("Multi-Attack"),
    [MOVE_MYSTICAL_FIRE] = _("Mystical Fire"),
    [MOVE_NASTY_PLOT] = _("Nasty Plot"),
    [MOVE_NATURAL_GIFT] = _("Natural Gift"),
    [MOVE_NATURE_POWER] = _("Nature Power"),
    [MOVE_NATURES_MADNESS] = _("{SKINNY}Nature's Madness"),
    [MOVE_NEEDLE_ARM] = _("Needle Arm"),
    [MOVE_NEVER_ENDING_NIGHTMARE] = _("Never-Ending Nightmare"),
    [MOVE_NIGHT_DAZE] = _("Night Daze"),
    [MOVE_NIGHT_SHADE] = _("Night Shade"),
    [MOVE_NIGHT_SLASH] = _("Night Slash"),
    [MOVE_NIGHTMARE] = _("Nightmare"),
    [MOVE_NOBLE_ROAR] = _("Noble Roar"),
    [MOVE_NO_RETREAT] = _("No Retreat"),
    [MOVE_NUZZLE] = _("Nuzzle"),
    [MOVE_OBLIVION_WING] = _("Oblivion Wing"),
    [MOVE_OBSTRUCT] = _("Obstruct"),
    [MOVE_OCEANIC_OPERETTA] = _("Oceanic Operetta"),
    [MOVE_OCTAZOOKA] = _("Octazooka"),
    [MOVE_OCTOLOCK] = _("Octolock"),
    [MOVE_ODOR_SLEUTH] = _("Odor Sleuth"),
    [MOVE_OMINOUS_WIND] = _("Ominous Wind"),
    [MOVE_ORIGIN_PULSE] = _("Origin Pulse"),
    [MOVE_OUTRAGE] = _("Outrage"),
    [MOVE_OVERDRIVE] = _("Overdrive"),
    [MOVE_OVERHEAT] = _("Overheat"),
    [MOVE_PAIN_SPLIT] = _("Pain Split"),
    [MOVE_PARABOLIC_CHARGE] = _("Parabolic Charge"),
    [MOVE_PARTING_SHOT] = _("Parting Shot"),
    [MOVE_PAY_DAY] = _("Pay Day"),
    [MOVE_PAYBACK] = _("Payback"),
    [MOVE_PECK] = _("Peck"),
    [MOVE_PERISH_SONG] = _("Perish Song"),
    [MOVE_PETAL_BLIZZARD] = _("Petal Blizzard"),
    [MOVE_PETAL_DANCE] = _("Petal Dance"),
    [MOVE_PHANTOM_FORCE] = _("Phantom Force"),
    [MOVE_PHOTON_GEYSER] = _("Photon Geyser"),
    [MOVE_PIN_MISSILE] = _("Pin Missile"),
    [MOVE_PLASMA_FISTS] = _("Plasma Fists"),
    [MOVE_PLAY_NICE] = _("Play Nice"),
    [MOVE_PLAY_ROUGH] = _("Play Rough"),
    [MOVE_PLUCK] = _("Pluck"),
    [MOVE_POISON_FANG] = _("Poison Fang"),
    [MOVE_POISON_GAS] = _("Poison Gas"),
    [MOVE_POISON_JAB] = _("Poison Jab"),
    [MOVE_POISON_POWDER] = _("Poison Powder"),
    [MOVE_POISON_STING] = _("Poison Sting"),
    [MOVE_POISON_TAIL] = _("Poison Tail"),
    [MOVE_POLLEN_PUFF] = _("Pollen Puff"),
    [MOVE_POLTERGEIST] = _("Poltergeist"),
    [MOVE_POUND] = _("Pound"),
    [MOVE_POWDER] = _("Powder"),
    [MOVE_POWDER_SNOW] = _("Powder Snow"),
    [MOVE_POWER_GEM] = _("Power Gem"),
    [MOVE_POWER_SPLIT] = _("Power Split"),
    [MOVE_POWER_SWAP] = _("Power Swap"),
    [MOVE_POWER_TRICK] = _("Power Trick"),
    [MOVE_POWER_TRIP] = _("Power Trip"),
    [MOVE_POWER_UP_PUNCH] = _("Power-Up Punch"),
    [MOVE_POWER_WHIP] = _("Power Whip"),
    [MOVE_PRECIPICE_BLADES] = _("Precipice Blades"),
    [MOVE_PRESENT] = _("Present"),
    [MOVE_PRISMATIC_LASER] = _("Prismatic Laser"),
    [MOVE_PROTECT] = _("Protect"),
    [MOVE_PSYBEAM] = _("Psybeam"),
    [MOVE_PSYCH_UP] = _("Psych Up"),
    [MOVE_PSYCHIC] = _("Psychic"),
    [MOVE_PSYCHIC_FANGS] = _("Psychic Fangs"),
    [MOVE_PSYCHIC_TERRAIN] = _("Psychic Terrain"),
    [MOVE_PSYCHO_BOOST] = _("Psycho Boost"),
    [MOVE_PSYCHO_CUT] = _("Psycho Cut"),
    [MOVE_PSYCHO_SHIFT] = _("Psycho Shift"),
    [MOVE_PSYSHOCK] = _("Psyshock"),
    [MOVE_PSYSTRIKE] = _("Psystrike"),
    [MOVE_PSYWAVE] = _("Psywave"),
    [MOVE_PULVERISING_PANCAKE] = _("Pulverizing Pancake"),
    [MOVE_PUNISHMENT] = _("Punishment"),
    [MOVE_PURIFY] = _("Purify"),
    [MOVE_PURSUIT] = _("Pursuit"),
    [MOVE_PYRO_BALL] = _("Pyro Ball"),
    [MOVE_QUASH] = _("Quash"),
    [MOVE_QUICK_ATTACK] = _("Quick Attack"),
    [MOVE_QUICK_GUARD] = _("Quick Guard"),
    [MOVE_QUIVER_DANCE] = _("Quiver Dance"),
    [MOVE_RAGE] = _("Rage"),
    [MOVE_RAGE_POWDER] = _("Rage Powder"),
    [MOVE_RAIN_DANCE] = _("Rain Dance"),
    [MOVE_RAPID_SPIN] = _("Rapid Spin"),
    [MOVE_RAZOR_LEAF] = _("Razor Leaf"),
    [MOVE_RAZOR_SHELL] = _("Razor Shell"),
    [MOVE_RAZOR_WIND] = _("Razor Wind"),
    [MOVE_RECOVER] = _("Recover"),
    [MOVE_RECYCLE] = _("Recycle"),
    [MOVE_REFLECT] = _("Reflect"),
    [MOVE_REFLECT_TYPE] = _("Reflect Type"),
    [MOVE_REFRESH] = _("Refresh"),
    [MOVE_RELIC_SONG] = _("Relic Song"),
    [MOVE_REST] = _("Rest"),
    [MOVE_RETALIATE] = _("Retaliate"),
    [MOVE_RETURN] = _("Return"),
    [MOVE_REVELATION_DANCE] = _("Revelation Dance"),
    [MOVE_REVENGE] = _("Revenge"),
    [MOVE_REVERSAL] = _("Reversal"),
    [MOVE_RISING_VOLTAGE] = _("Rising Voltage"),
    [MOVE_ROAR] = _("Roar"),
    [MOVE_ROAR_OF_TIME] = _("Roar of Time"),
    [MOVE_ROCK_BLAST] = _("Rock Blast"),
    [MOVE_ROCK_CLIMB] = _("Rock Climb"),
    [MOVE_ROCK_POLISH] = _("Rock Polish"),
    [MOVE_ROCK_SLIDE] = _("Rock Slide"),
    [MOVE_ROCK_SMASH] = _("Rock Smash"),
    [MOVE_ROCK_THROW] = _("Rock Throw"),
    [MOVE_ROCK_TOMB] = _("Rock Tomb"),
    [MOVE_ROCK_WRECKER] = _("Rock Wrecker"),
    [MOVE_ROLE_PLAY] = _("Role Play"),
    [MOVE_ROLLING_KICK] = _("Rolling Kick"),
    [MOVE_ROLLOUT] = _("Rollout"),
    [MOVE_ROOST] = _("Roost"),
    [MOVE_ROTOTILLER] = _("Rototiller"),
    [MOVE_ROUND] = _("Round"),
    [MOVE_SACRED_FIRE] = _("Sacred Fire"),
    [MOVE_SACRED_SWORD] = _("Sacred Sword"),
    [MOVE_SAFEGUARD] = _("Safeguard"),
    [MOVE_SAND_ATTACK] = _("Sand Attack"),
    [MOVE_SAND_TOMB] = _("Sand Tomb"),
    [MOVE_SANDSTORM] = _("Sandstorm"),
    [MOVE_SAVAGE_SPIN_OUT] = _("Savage Spin-Out"),
    [MOVE_SCALD] = _("Scald"),
    [MOVE_SCALE_SHOT] = _("Scale Shot"),
    [MOVE_SCARY_FACE] = _("Scary Face"),
    [MOVE_SCORCHING_SANDS] = _("Scorching Sands"),
    [MOVE_SCRATCH] = _("Scratch"),
    [MOVE_SCREECH] = _("Screech"),
    [MOVE_SEARING_SHOT] = _("Searing Shot"),
    [MOVE_SEARING_SUNRAZE_SMASH] = _("Searing Sunraze Smash"),
    [MOVE_SECRET_POWER] = _("Secret Power"),
    [MOVE_SECRET_SWORD] = _("Secret Sword"),
    [MOVE_SEED_BOMB] = _("Seed Bomb"),
    [MOVE_SEED_FLARE] = _("Seed Flare"),
    [MOVE_SEISMIC_TOSS] = _("Seismic Toss"),
    [MOVE_SELF_DESTRUCT] = _("Self-Destruct"),
    [MOVE_SHADOW_BALL] = _("Shadow Ball"),
    [MOVE_SHADOW_BONE] = _("Shadow Bone"),
    [MOVE_SHADOW_CLAW] = _("Shadow Claw"),
    [MOVE_SHADOW_FORCE] = _("Shadow Force"),
    [MOVE_SHADOW_PUNCH] = _("Shadow Punch"),
    [MOVE_SHADOW_SNEAK] = _("Shadow Sneak"),
    [MOVE_SHARPEN] = _("Sharpen"),
    [MOVE_SHATTERED_PSYCHE] = _("Shattered Psyche"),
    [MOVE_SHEER_COLD] = _("Sheer Cold"),
    [MOVE_SHELL_SIDE_ARM] = _("Shell Side Arm"),
    [MOVE_SHELL_SMASH] = _("Shell Smash"),
    [MOVE_SHELL_TRAP] = _("Shell Trap"),
    [MOVE_SHIFT_GEAR] = _("Shift Gear"),
    [MOVE_SHOCK_WAVE] = _("Shock Wave"),
    [MOVE_SHORE_UP] = _("Shore Up"),
    [MOVE_SIGNAL_BEAM] = _("Signal Beam"),
    [MOVE_SILVER_WIND] = _("Silver Wind"),
    [MOVE_SIMPLE_BEAM] = _("Simple Beam"),
    [MOVE_SING] = _("Sing"),
    [MOVE_SINISTER_ARROW_RAID] = _("Sinister Arrow Raid"),
    [MOVE_SKETCH] = _("Sketch"),
    [MOVE_SKILL_SWAP] = _("Skill Swap"),
    [MOVE_SKITTER_SMACK] = _("Skitter Smack"),
    [MOVE_SKULL_BASH] = _("Skull Bash"),
    [MOVE_SKY_ATTACK] = _("Sky Attack"),
    [MOVE_SKY_DROP] = _("Sky Drop"),
    [MOVE_SKY_UPPERCUT] = _("Sky Uppercut"),
    [MOVE_SLACK_OFF] = _("Slack Off"),
    [MOVE_SLAM] = _("Slam"),
    [MOVE_SLASH] = _("Slash"),
    [MOVE_SLEEP_POWDER] = _("Sleep Powder"),
    [MOVE_SLEEP_TALK] = _("Sleep Talk"),
    [MOVE_SLUDGE] = _("Sludge"),
    [MOVE_SLUDGE_BOMB] = _("Sludge Bomb"),
    [MOVE_SLUDGE_WAVE] = _("Sludge Wave"),
    [MOVE_SMACK_DOWN] = _("Smack Down"),
    [MOVE_SMART_STRIKE] = _("Smart Strike"),
    [MOVE_SMELLING_SALT] = _("Smelling Salts"),
    [MOVE_SMOG] = _("Smog"),
    [MOVE_SMOKESCREEN] = _("Smokescreen"),
    [MOVE_SNAP_TRAP] = _("Snap Trap"),
    [MOVE_SNARL] = _("Snarl"),
    [MOVE_SNATCH] = _("Snatch"),
    [MOVE_SNIPE_SHOT] = _("Snipe Shot"),
    [MOVE_SNORE] = _("Snore"),
    [MOVE_SOAK] = _("Soak"),
    [MOVE_SOFT_BOILED] = _("Soft-Boiled"),
    [MOVE_SOLAR_BEAM] = _("Solar Beam"),
    [MOVE_SOLAR_BLADE] = _("Solar Blade"),
    [MOVE_SONIC_BOOM] = _("Sonic Boom"),
    [MOVE_SOUL_STEALING_7_STAR_STRIKE] = _("Soul-Stealing 7-Star Strike"),
    [MOVE_SPACIAL_REND] = _("Spacial Rend"),
    [MOVE_SPARK] = _("Spark"),
    [MOVE_SPARKLING_ARIA] = _("Sparkling Aria"),
    [MOVE_SPECTRAL_THIEF] = _("Spectral Thief"),
    [MOVE_SPEED_SWAP] = _("Speed Swap"),
    [MOVE_SPIDER_WEB] = _("Spider Web"),
    [MOVE_SPIKE_CANNON] = _("Spike Cannon"),
    [MOVE_SPIKES] = _("Spikes"),
    [MOVE_SPIKY_SHIELD] = _("Spiky Shield"),
    [MOVE_SPIRIT_BREAK] = _("Spirit Break"),
    [MOVE_SPIRIT_SHACKLE] = _("Spirit Shackle"),
    [MOVE_SPIT_UP] = _("Spit Up"),
    [MOVE_SPITE] = _("Spite"),
    [MOVE_SPLASH] = _("Splash"),
    [MOVE_SPLINTERED_STORMSHARDS] = _("Splintered Stormshards"),
    [MOVE_SPORE] = _("Spore"),
    [MOVE_SPOTLIGHT] = _("Spotlight"),
    [MOVE_STEALTH_ROCK] = _("Stealth Rock"),
    [MOVE_STEAM_ERUPTION] = _("Steam Eruption"),
    [MOVE_STEAMROLLER] = _("Steamroller"),
    [MOVE_STEEL_BEAM] = _("Steel Beam"),
    [MOVE_STEEL_ROLLER] = _("Steel Roller"),
    [MOVE_STEEL_WING] = _("Steel Wing"),
    [MOVE_STICKY_WEB] = _("Sticky Web"),
    [MOVE_STOCKPILE] = _("Stockpile"),
    [MOVE_STOKED_SPARKSURFER] = _("Stoked Sparksurfer"),
    [MOVE_STOMP] = _("Stomp"),
    [MOVE_STOMPING_TANTRUM] = _("Stomping Tantrum"),
    [MOVE_STONE_EDGE] = _("Stone Edge"),
    [MOVE_STORED_POWER] = _("Stored Power"),
    [MOVE_STORM_THROW] = _("Storm Throw"),
    [MOVE_STRANGE_STEAM] = _("Strange Steam"),
    [MOVE_STRENGTH] = _("Strength"),
    [MOVE_STRENGTH_SAP] = _("Strength Sap"),
    [MOVE_STRING_SHOT] = _("String Shot"),
    [MOVE_STRUGGLE] = _("Struggle"),
    [MOVE_STRUGGLE_BUG] = _("Struggle Bug"),
    [MOVE_STUFF_CHEEKS] = _("Stuff Cheeks"),
    [MOVE_STUN_SPORE] = _("Stun Spore"),
    [MOVE_SUBMISSION] = _("Submission"),
    [MOVE_SUBSTITUTE] = _("Substitute"),
    [MOVE_SUBZERO_SLAMMER] = _("Subzero Slammer"),
    [MOVE_SUCKER_PUNCH] = _("Sucker Punch"),
    [MOVE_SUNNY_DAY] = _("Sunny Day"),
    [MOVE_SUNSTEEL_STRIKE] = _("Sunsteel Strike"),
    [MOVE_SUPER_FANG] = _("Super Fang"),
    [MOVE_SUPERPOWER] = _("Superpower"),
    [MOVE_SUPERSONIC] = _("Supersonic"),
    [MOVE_SUPERSONIC_SKYSTRIKE] = _("Supersonic Skystrike"),
    [MOVE_SURF] = _("Surf"),
    [MOVE_SURGING_STRIKES] = _("Surging Strikes"),
    [MOVE_SWAGGER] = _("Swagger"),
    [MOVE_SWALLOW] = _("Swallow"),
    [MOVE_SWEET_KISS] = _("Sweet Kiss"),
    [MOVE_SWEET_SCENT] = _("Sweet Scent"),
    [MOVE_SWIFT] = _("Swift"),
    [MOVE_SWITCHEROO] = _("Switcheroo"),
    [MOVE_SWORDS_DANCE] = _("Swords Dance"),
    [MOVE_SYNCHRONOISE] = _("Synchronoise"),
    [MOVE_SYNTHESIS] = _("Synthesis"),
    [MOVE_TACKLE] = _("Tackle"),
    [MOVE_TAIL_GLOW] = _("Tail Glow"),
    [MOVE_TAIL_SLAP] = _("Tail Slap"),
    [MOVE_TAIL_WHIP] = _("Tail Whip"),
    [MOVE_TAILWIND] = _("Tailwind"),
    [MOVE_TAKE_DOWN] = _("Take Down"),
    [MOVE_TAR_SHOT] = _("Tar Shot"),
    [MOVE_TAUNT] = _("Taunt"),
    [MOVE_TEARFUL_LOOK] = _("Tearful Look"),
    [MOVE_TEATIME] = _("Teatime"),
    [MOVE_TECHNO_BLAST] = _("Techno Blast"),
    [MOVE_TECTONIC_RAGE] = _("Tectonic Rage"),
    [MOVE_TEETER_DANCE] = _("Teeter Dance"),
    [MOVE_TELEKINESIS] = _("Telekinesis"),
    [MOVE_TELEPORT] = _("Teleport"),
    [MOVE_TERRAIN_PULSE] = _("Terrain Pulse"),
    [MOVE_THIEF] = _("Thief"),
    [MOVE_THOUSAND_ARROWS] = _("Thousand Arrows"),
    [MOVE_THOUSAND_WAVES] = _("Thousand Waves"),
    [MOVE_THRASH] = _("Thrash"),
    [MOVE_THROAT_CHOP] = _("Throat Chop"),
    [MOVE_THUNDER] = _("Thunder"),
    [MOVE_THUNDER_FANG] = _("Thunder Fang"),
    [MOVE_THUNDER_PUNCH] = _("Thunder Punch"),
    [MOVE_THUNDER_SHOCK] = _("Thunder Shock"),
    [MOVE_THUNDER_WAVE] = _("Thunder Wave"),
    [MOVE_THUNDERBOLT] = _("Thunderbolt"),
    [MOVE_TICKLE] = _("Tickle"),
    [MOVE_TOPSY_TURVY] = _("Topsy-Turvy"),
    [MOVE_TORMENT] = _("Torment"),
    [MOVE_TOXIC] = _("Toxic"),
    [MOVE_TOXIC_SPIKES] = _("Toxic Spikes"),
    [MOVE_TOXIC_THREAD] = _("Toxic Thread"),
    [MOVE_TRANSFORM] = _("Transform"),
    [MOVE_TRI_ATTACK] = _("Tri Attack"),
    [MOVE_TRICK] = _("Trick"),
    [MOVE_TRICK_OR_TREAT] = _("Trick-or-Treat"),
    [MOVE_TRICK_ROOM] = _("Trick Room"),
    [MOVE_TRIPLE_AXEL] = _("Triple Axel"),
    [MOVE_TRIPLE_KICK] = _("Triple Kick"),
    [MOVE_TROP_KICK] = _("Trop Kick"),
    [MOVE_TRUMP_CARD] = _("Trump Card"),
    [MOVE_TWINEEDLE] = _("Twineedle"),
    [MOVE_TWINKLE_TACKLE] = _("Twinkle Tackle"),
    [MOVE_TWISTER] = _("Twister"),
    [MOVE_U_TURN] = _("U-turn"),
    [MOVE_UPROAR] = _("Uproar"),
    [MOVE_V_CREATE] = _("V-create"),
    [MOVE_VACUUM_WAVE] = _("Vacuum Wave"),
    [MOVE_VENOM_DRENCH] = _("Venom Drench"),
    [MOVE_VENOSHOCK] = _("Venoshock"),
    [MOVE_VINE_WHIP] = _("Vine Whip"),
    [MOVE_VICE_GRIP] = _("Vise Grip"),
    [MOVE_VITAL_THROW] = _("Vital Throw"),
    [MOVE_VOLT_SWITCH] = _("Volt Switch"),
    [MOVE_VOLT_TACKLE] = _("Volt Tackle"),
    [MOVE_WAKE_UP_SLAP] = _("Wake-Up Slap"),
    [MOVE_WATER_GUN] = _("Water Gun"),
    [MOVE_WATER_PLEDGE] = _("Water Pledge"),
    [MOVE_WATER_PULSE] = _("Water Pulse"),
    [MOVE_WATER_SHURIKEN] = _("Water Shuriken"),
    [MOVE_WATER_SPORT] = _("Water Sport"),
    [MOVE_WATER_SPOUT] = _("Water Spout"),
    [MOVE_WATERFALL] = _("Waterfall"),
    [MOVE_WEATHER_BALL] = _("Weather Ball"),
    [MOVE_WHIRLPOOL] = _("Whirlpool"),
    [MOVE_WHIRLWIND] = _("Whirlwind"),
    [MOVE_WICKED_BLOW] = _("Wicked Blow"),
    [MOVE_WIDE_GUARD] = _("Wide Guard"),
    [MOVE_WILD_CHARGE] = _("Wild Charge"),
    [MOVE_WILL_O_WISP] = _("Will-O-Wisp"),
    [MOVE_WING_ATTACK] = _("Wing Attack"),
    [MOVE_WISH] = _("Wish"),
    [MOVE_WITHDRAW] = _("Withdraw"),
    [MOVE_WONDER_ROOM] = _("Wonder Room"),
    [MOVE_WOOD_HAMMER] = _("Wood Hammer"),
    [MOVE_WORK_UP] = _("Work Up"),
    [MOVE_WORRY_SEED] = _("Worry Seed"),
    [MOVE_WRAP] = _("Wrap"),
    [MOVE_WRING_OUT] = _("Wring Out"),
    [MOVE_X_SCISSOR] = _("X-Scissor"),
    [MOVE_YAWN] = _("Yawn"),
    [MOVE_ZAP_CANNON] = _("Zap Cannon"),
    [MOVE_ZEN_HEADBUTT] = _("Zen Headbutt"),
    [MOVE_ZING_ZAP] = _("Zing Zap"),

    // Dead moves
    [MOVE_Z_NORMAL_2] = _("Not In Yet"),
    [MOVE_Z_PSYCHIC_2] = _("Not In Yet"),
    [MOVE_LGPE_1] = _("Not In Yet"),
    [MOVE_LGPE_2] = _("Not In Yet"),
    [MOVE_LGPE_3] = _("Not In Yet"),
    [MOVE_LGPE_4] = _("Not In Yet"),
    [MOVE_LGPE_5] = _("Not In Yet"),
    [MOVE_LGPE_6] = _("Not In Yet"),
    [MOVE_LGPE_7] = _("Not In Yet"),
    [MOVE_LGPE_8] = _("Not In Yet"),
    [MOVE_LGPE_9] = _("Not In Yet"),
    [MOVE_LGPE_10] = _("Not In Yet"),
    [MOVE_LGPE_11] = _("Not In Yet"),
    [MOVE_LGPE_12] = _("Not In Yet"),
    [MOVE_LGPE_13] = _("Not In Yet"),
};
