#include "constants/battle.h"
#include "constants/moves.h"

const u16 gPriorityAttacks[] =
{
    MOVE_EXTREME_SPEED, MOVE_SUCKER_PUNCH, MOVE_JET_PUNCH, MOVE_MACH_PUNCH, MOVE_ACCELEROCK, MOVE_ICE_SHARD, MOVE_AQUA_JET, MOVE_SHADOW_SNEAK, MOVE_BULLET_PUNCH, MOVE_FEINT, MOVE_QUICK_ATTACK, MOVE_UNAVAILABLE
};

const u16 gPivotOrSwitchMoves[] =
{
    MOVE_SHED_TAIL, MOVE_PARTING_SHOT, MOVE_U_TURN, MOVE_FLIP_TURN, MOVE_VOLT_SWITCH, MOVE_TELEPORT, MOVE_BATON_PASS, MOVE_CHILLY_RECEPTION, MOVE_UNAVAILABLE
};

const u16 gPhysicalSetupMoves[] =
{
    MOVE_SHELL_SMASH, MOVE_SHIFT_GEAR, MOVE_VICTORY_DANCE, MOVE_DRAGON_DANCE, MOVE_SWORDS_DANCE, MOVE_COIL, MOVE_BULK_UP, MOVE_HONE_CLAWS, MOVE_GROWTH, MOVE_WORK_UP, MOVE_POWER_UP_PUNCH, MOVE_UNAVAILABLE
};

const u16 gSpecialSetupMoves[] =
{
    MOVE_SHELL_SMASH, MOVE_QUIVER_DANCE, MOVE_TAIL_GLOW, MOVE_NASTY_PLOT, MOVE_CALM_MIND, MOVE_HONE_CLAWS, MOVE_GROWTH, MOVE_WORK_UP, MOVE_UNAVAILABLE
};

const u16 gPhysicalNukes[] =
{
    MOVE_HEAD_SMASH, MOVE_EXPLOSION, MOVE_SELF_DESTRUCT, MOVE_ROCK_WRECKER, MOVE_METEOR_ASSAULT, MOVE_GIGA_IMPACT, MOVE_UNAVAILABLE
};

const u16 gSpecialNukes[] =
{
    MOVE_LIGHT_OF_RUIN, MOVE_FLEUR_CANNON, MOVE_ETERNABEAM, MOVE_DRACO_METEOR, MOVE_ROAR_OF_TIME, MOVE_BLAST_BURN, MOVE_OVERHEAT, MOVE_MIND_BLOWN, MOVE_STEEL_BEAM, MOVE_FRENZY_PLANT, MOVE_LEAF_STORM, MOVE_HYDRO_CANNON, MOVE_HYPER_BEAM, MOVE_PRISMATIC_LASER, MOVE_UNAVAILABLE
};

const u16 gUtilityMoves[] =
{
    MOVE_KNOCK_OFF, MOVE_STEALTH_ROCK, MOVE_SPIKES, MOVE_RAPID_SPIN, MOVE_DEFOG, MOVE_CLEAR_SMOG, MOVE_UNAVAILABLE
};

const u16 gPhysicalHPDrainMoves[] =
{
    MOVE_BITTER_BLADE, MOVE_DRAIN_PUNCH, MOVE_LEECH_LIFE, MOVE_HORN_LEECH, MOVE_UNAVAILABLE
};

const u16 gSpecialHPDrainMoves[] =
{
    MOVE_OBLIVION_WING, MOVE_GIGA_DRAIN, MOVE_DRAINING_KISS, MOVE_PARABOLIC_CHARGE, MOVE_UNAVAILABLE
};

const u16 gRecoveryMoves[] =
{
    MOVE_STRENGTH_SAP, MOVE_SHORE_UP, MOVE_ROOST, MOVE_RECOVER, MOVE_MILK_DRINK, MOVE_SOFT_BOILED, MOVE_SLACK_OFF, MOVE_LUNAR_BLESSING, MOVE_JUNGLE_HEALING, MOVE_MORNING_SUN, MOVE_MOONLIGHT, MOVE_SYNTHESIS, MOVE_LIFE_DEW, MOVE_REST, MOVE_UNAVAILABLE
};

const u16 gStatusAfflictingMoves[] =
{
    MOVE_SPORE, MOVE_SLEEP_POWDER, MOVE_TOXIC, MOVE_HYPNOSIS, MOVE_WILL_O_WISP, MOVE_GLARE, MOVE_THUNDER_WAVE, MOVE_CONFUSE_RAY, MOVE_UNAVAILABLE
};

const u16 gPhazerHazerMoves[] =
{
    MOVE_DRAGON_TAIL, MOVE_CIRCLE_THROW, MOVE_HAZE, MOVE_CLEAR_SMOG, MOVE_WHIRLWIND, MOVE_ROAR, MOVE_UNAVAILABLE
};

static const u16 sPhysicalBugAttacks[] = 
{
    MOVE_MEGAHORN, MOVE_ATTACK_ORDER, MOVE_LEECH_LIFE, MOVE_LUNGE, MOVE_X_SCISSOR, MOVE_SKITTER_SMACK, MOVE_STEAMROLLER, MOVE_BUG_BITE, MOVE_PIN_MISSILE, MOVE_TWINEEDLE, MOVE_FELL_STINGER, MOVE_POUNCE, MOVE_UNAVAILABLE
};

static const u16 sPhysicalBugPriorityAttacks[] =
{
    MOVE_FIRST_IMPRESSION, MOVE_UNAVAILABLE
};

static const u16 sPhysicalBugComplexAttacks[] =
{
    MOVE_FIRST_IMPRESSION, MOVE_FURY_CUTTER, MOVE_UNAVAILABLE
};

static const u16 sSpecialBugAttacks[] =
{
    MOVE_POLLEN_PUFF, MOVE_BUG_BUZZ, MOVE_SIGNAL_BEAM, MOVE_SILVER_WIND, MOVE_STRUGGLE_BUG, MOVE_INFESTATION, MOVE_UNAVAILABLE
};

static const u16 sPhysicalDarkAttacks[] =
{
    MOVE_HYPERSPACE_FURY, MOVE_WICKED_BLOW, MOVE_KNOCK_OFF, MOVE_KOWTOW_CLEAVE, MOVE_DARKEST_LARIAT, MOVE_CRUNCH, MOVE_THROAT_CHOP, MOVE_LASH_OUT, MOVE_NIGHT_SLASH, MOVE_BRUTAL_SWING, MOVE_BITE, MOVE_FEINT_ATTACK, MOVE_ASSURANCE, MOVE_PAYBACK, MOVE_THIEF, MOVE_UNAVAILABLE
};

static const u16 sPhysicalDarkPriorityAttacks[] =
{
    MOVE_SUCKER_PUNCH, MOVE_UNAVAILABLE
};

static const u16 sPhysicalDarkComplexAttacks[] =
{
    MOVE_AURA_WHEEL, MOVE_FOUL_PLAY, MOVE_PURSUIT, MOVE_POWER_TRIP, MOVE_FLING, MOVE_BEAT_UP, MOVE_UNAVAILABLE
};

static const u16 sSpecialDarkAttacks[] =
{
    MOVE_SNARL, MOVE_FIERY_WRATH, MOVE_NIGHT_DAZE, MOVE_DARK_PULSE, MOVE_UNAVAILABLE
};

static const u16 sPhysicalDragonAttacks[] =
{
    MOVE_DRAGON_DARTS, MOVE_GLAIVE_RUSH, MOVE_OUTRAGE, MOVE_DRAGON_HAMMER, MOVE_ORDER_UP, MOVE_DRAGON_CLAW, MOVE_DUAL_CHOP, MOVE_DRAGON_RUSH, MOVE_BREAKING_SWIPE, MOVE_DRAGON_TAIL, MOVE_SCALE_SHOT, MOVE_UNAVAILABLE
};

static const u16 sPhysicalDragonComplexAttacks[] =
{
    MOVE_SCALE_SHOT, MOVE_UNAVAILABLE
};

static const u16 sSpecialDragonAttacks[] =
{
    MOVE_CLANGING_SCALES, MOVE_SPACIAL_REND, MOVE_DYNAMAX_CANNON, MOVE_CORE_ENFORCER, MOVE_DRAGON_PULSE, MOVE_DRAGON_BREATH, MOVE_TWISTER, MOVE_UNAVAILABLE
};

static const u16 sSpecialDragonComplexAttacks[] =
{
    MOVE_DRAGON_ENERGY, MOVE_DRACO_METEOR, MOVE_UNAVAILABLE
};

static const u16 sPhysicalElectricAttacks[] =
{
    MOVE_BOLT_STRIKE, MOVE_VOLT_TACKLE, MOVE_WILDBOLT_STORM, MOVE_PLASMA_FISTS, MOVE_FUSION_BOLT, MOVE_WILD_CHARGE, MOVE_BOLT_BEAK, MOVE_ZING_ZAP, MOVE_THUNDER_PUNCH, MOVE_SPARK, MOVE_THUNDER_FANG, MOVE_NUZZLE, MOVE_UNAVAILABLE
};

static const u16 sPhysicalElectricComplexAttacks[] =
{
    MOVE_AURA_WHEEL, MOVE_UNAVAILABLE
};

static const u16 sSpecialElectricAttacks[] =
{
    MOVE_THUNDERBOLT, MOVE_ELECTRO_DRIFT, MOVE_THUNDER_CAGE, MOVE_OVERDRIVE, MOVE_DISCHARGE, MOVE_RISING_VOLTAGE, MOVE_PARABOLIC_CHARGE, MOVE_SHOCK_WAVE, MOVE_CHARGE_BEAM, MOVE_ELECTROWEB, MOVE_THUNDER_SHOCK, MOVE_UNAVAILABLE
};

static const u16 sSpecialElectricComplexAttacks[] =
{
    MOVE_THUNDER, MOVE_RISING_VOLTAGE, MOVE_ZAP_CANNON, MOVE_CHARGE_BEAM, MOVE_UNAVAILABLE
};

static const u16 sPhysicalFairyAttacks[] =
{
    MOVE_PLAY_ROUGH, MOVE_SPIRIT_BREAK, MOVE_UNAVAILABLE
};

static const u16 sSpecialFairyAttacks[] =
{
    MOVE_SPRINGTIDE_STORM, MOVE_MOONBLAST, MOVE_STRANGE_STEAM, MOVE_DAZZLING_GLEAM, MOVE_DRAINING_KISS, MOVE_DISARMING_VOICE, MOVE_FAIRY_WIND, MOVE_UNAVAILABLE
};

static const u16 sSpecialFairyComplexAttacks[] =
{
    MOVE_LIGHT_OF_RUIN, MOVE_FLEUR_CANNON, MOVE_UNAVAILABLE
};

static const u16 sPhysicalFightingAttacks[] =
{
    MOVE_CLOSE_COMBAT, MOVE_HIGH_JUMP_KICK, MOVE_AXE_KICK, MOVE_COLLISION_COURSE, MOVE_TRIPLE_ARROWS, MOVE_THUNDEROUS_KICK, MOVE_DRAIN_PUNCH, MOVE_SACRED_SWORD, MOVE_JUMP_KICK, MOVE_CROSS_CHOP, MOVE_SKY_UPPERCUT, MOVE_SUPERPOWER, MOVE_HAMMER_ARM, MOVE_STORM_THROW, MOVE_BRICK_BREAK, MOVE_WAKE_UP_SLAP, MOVE_FORCE_PALM, MOVE_LOW_SWEEP, MOVE_VITAL_THROW, MOVE_DOUBLE_KICK, MOVE_KARATE_CHOP, MOVE_ROLLING_KICK, MOVE_POWER_UP_PUNCH, MOVE_REVENGE, MOVE_ROCK_SMASH, MOVE_ARM_THRUST, MOVE_TRIPLE_KICK, MOVE_SEISMIC_TOSS, MOVE_UNAVAILABLE
};

static const u16 sPhysicalFightingPriorityAttacks[] =
{
    MOVE_MACH_PUNCH, MOVE_UNAVAILABLE
};

static const u16 sPhysicalFightingComplexAttacks[] =
{
    MOVE_SUPERPOWER, MOVE_DYNAMIC_PUNCH, MOVE_LOW_KICK, MOVE_REVERSAL, MOVE_COUNTER, MOVE_UNAVAILABLE
};

static const u16 sSpecialFightingAttacks[] =
{
    MOVE_SECRET_SWORD, MOVE_AURA_SPHERE, MOVE_FOCUS_BLAST, MOVE_VACUUM_WAVE, MOVE_UNAVAILABLE
};

static const u16 sSpecialFightingPriorityAttacks[] =
{
    MOVE_VACUUM_WAVE, MOVE_UNAVAILABLE
};

static const u16 sPhysicalFireAttacks[] =
{
    MOVE_V_CREATE, MOVE_PYRO_BALL, MOVE_RAGING_FURY, MOVE_BITTER_BLADE, MOVE_FIRE_LASH, MOVE_FLARE_BLITZ, MOVE_SACRED_FIRE, MOVE_BLAZE_KICK, MOVE_FIRE_PUNCH, MOVE_FIRE_FANG, MOVE_FLAME_CHARGE, MOVE_FLAME_WHEEL, MOVE_UNAVAILABLE
};

static const u16 sSpecialFireAttacks[] =
{
    MOVE_BLUE_FLARE, MOVE_ARMOR_CANNON, MOVE_MAGMA_STORM, MOVE_FIRE_BLAST, MOVE_FIERY_DANCE, MOVE_TORCH_SONG, MOVE_SEARING_SHOT, MOVE_FUSION_FLARE, MOVE_FLAMETHROWER, MOVE_HEAT_WAVE, MOVE_LAVA_PLUME, MOVE_FLAME_BURST, MOVE_MYSTICAL_FIRE, MOVE_INCINERATE, MOVE_EMBER, MOVE_FIRE_SPIN, MOVE_UNAVAILABLE
};

static const u16 sSpecialFireComplexAttacks[] =
{
    MOVE_ERUPTION, MOVE_OVERHEAT, MOVE_UNAVAILABLE
};

static const u16 sPhysicalFlyingAttacks[] =
{
    MOVE_DRAGON_ASCENT, MOVE_BRAVE_BIRD, MOVE_DRILL_PECK, MOVE_DUAL_WINGBEAT, MOVE_BOUNCE, MOVE_FLY, MOVE_PLUCK, MOVE_AERIAL_ACE, MOVE_WING_ATTACK, MOVE_PECK, MOVE_UNAVAILABLE
};

static const u16 sPhysicalFlyingComplexAttacks[] =
{
    MOVE_ACROBATICS, MOVE_BEAK_BLAST, MOVE_UNAVAILABLE
};

static const u16 sSpecialFlyingAttacks[] =
{
    MOVE_OBLIVION_WING, MOVE_HURRICANE, MOVE_AEROBLAST, MOVE_AIR_SLASH, MOVE_BLEAKWIND_STORM, MOVE_CHATTER, MOVE_AIR_CUTTER, MOVE_GUST, MOVE_UNAVAILABLE
};

static const u16 sPhysicalGhostAttacks[] =
{
    MOVE_SPECTRAL_THIEF, MOVE_SHADOW_FORCE, MOVE_POLTERGEIST, MOVE_SHADOW_BONE, MOVE_SPIRIT_SHACKLE, MOVE_PHANTOM_FORCE, MOVE_SHADOW_CLAW, MOVE_SHADOW_PUNCH, MOVE_SHADOW_SNEAK, MOVE_ASTONISH, MOVE_UNAVAILABLE
};

static const u16 sPhysicalGhostPriorityAttacks[] =
{
    MOVE_SHADOW_SNEAK, MOVE_UNAVAILABLE
};

static const u16 sPhysicalGhostComplexAttacks[] =
{
    MOVE_LAST_RESPECTS, MOVE_RAGE_FIST, MOVE_UNAVAILABLE
};

static const u16 sSpecialGhostAttacks[] =
{
    MOVE_ASTRAL_BARRAGE, MOVE_MOONGEIST_BEAM, MOVE_SHADOW_BALL, MOVE_BITTER_MALICE, MOVE_HEX, MOVE_INFERNAL_PARADE, MOVE_OMINOUS_WIND, MOVE_UNAVAILABLE
};

static const u16 sSpecialGhostComplexAttacks[] =
{
    MOVE_HEX, MOVE_INFERNAL_PARADE, MOVE_UNAVAILABLE
};

static const u16 sPhysicalGrassAttacks[] =
{
    MOVE_WOOD_HAMMER, MOVE_POWER_WHIP, MOVE_FLOWER_TRICK, MOVE_LEAF_BLADE, MOVE_HORN_LEECH, MOVE_PETAL_BLIZZARD, MOVE_GRAV_APPLE, MOVE_TROP_KICK, MOVE_DRUM_BEATING, MOVE_SEED_BOMB, MOVE_NEEDLE_ARM, MOVE_GRASSY_GLIDE, MOVE_RAZOR_LEAF, MOVE_TRAILBLAZE, MOVE_VINE_WHIP, MOVE_SNAP_TRAP, MOVE_BRANCH_POKE, MOVE_LEAFAGE, MOVE_BULLET_SEED, MOVE_UNAVAILABLE
};

static const u16 sPhysicalGrassComplexAttacks[] =
{
    MOVE_SOLAR_BLADE, MOVE_UNAVAILABLE
};

static const u16 sSpecialGrassAttacks[] =
{
    MOVE_SEED_FLARE, MOVE_GIGA_DRAIN, MOVE_PETAL_DANCE, MOVE_APPLE_ACID, MOVE_ENERGY_BALL, MOVE_GRASS_KNOT, MOVE_LEAF_TORNADO, MOVE_MAGICAL_LEAF, MOVE_MEGA_DRAIN, MOVE_UNAVAILABLE
};

static const u16 sSpecialGrassComplexAttacks[] =
{
    MOVE_SOLAR_BEAM, MOVE_LEAF_STORM, MOVE_CHLOROBLAST, MOVE_UNAVAILABLE
};

static const u16 sPhysicalGroundAttacks[] =
{
    MOVE_THOUSAND_ARROWS, MOVE_PRECIPICE_BLADES, MOVE_HEADLONG_RUSH, MOVE_HIGH_HORSEPOWER, MOVE_BONEMERANG, MOVE_EARTHQUAKE, MOVE_THOUSAND_WAVES, MOVE_LANDS_WRATH, MOVE_DRILL_RUN, MOVE_STOMPING_TANTRUM, MOVE_BONE_CLUB, MOVE_BULLDOZE, MOVE_MAGNITUDE, MOVE_DIG, MOVE_BONE_RUSH, MOVE_SAND_TOMB, MOVE_UNAVAILABLE
};

static const u16 sSpecialGroundAttacks[] =
{
    MOVE_EARTH_POWER, MOVE_SCORCHING_SANDS, MOVE_SANDSEAR_STORM, MOVE_MUD_BOMB, MOVE_MUD_SHOT, MOVE_MUD_SLAP, MOVE_UNAVAILABLE
};

static const u16 sPhysicalIceAttacks[] =
{
    MOVE_GLACIAL_LANCE, MOVE_TRIPLE_AXEL, MOVE_MOUNTAIN_GALE, MOVE_ICICLE_CRASH, MOVE_ICE_HAMMER, MOVE_ICE_PUNCH, MOVE_ICE_SPINNER, MOVE_ICE_FANG, MOVE_AVALANCHE, MOVE_ICICLE_SPEAR, MOVE_ICE_SHARD, MOVE_UNAVAILABLE
};

static const u16 sPhysicalIcePriorityAttacks[] =
{
    MOVE_ICE_SHARD, MOVE_UNAVAILABLE
};

static const u16 sSpecialIceAttacks[] =
{
    MOVE_FREEZE_DRY, MOVE_ICE_BEAM, MOVE_GLACIATE, MOVE_AURORA_BEAM, MOVE_ICY_WIND, MOVE_POWDER_SNOW, MOVE_UNAVAILABLE
};

static const u16 sSpecialIceComplexAttacks[] =
{
    MOVE_BLIZZARD, MOVE_UNAVAILABLE
};

static const u16 sPhysicalNormalAttacks[] =
{
    MOVE_MULTI_ATTACK, MOVE_DOUBLE_EDGE, MOVE_HEAD_CHARGE, MOVE_HYPER_DRILL, MOVE_RETURN, MOVE_FRUSTRATION, MOVE_BODY_SLAM, MOVE_EXTREME_SPEED, MOVE_STRENGTH, MOVE_HYPER_FANG, MOVE_HEADBUTT, MOVE_RETALIATE, MOVE_TAIL_SLAP, MOVE_SECRET_POWER, MOVE_SLASH, MOVE_CHIP_AWAY, MOVE_DOUBLE_HIT, MOVE_STOMP, MOVE_HORN_ATTACK, MOVE_RAPID_SPIN, MOVE_QUICK_ATTACK, MOVE_TACKLE, MOVE_SCRATCH, MOVE_POUND, MOVE_UNAVAILABLE
};

static const u16 sPhysicalNormalPriorityAttacks[] =
{
    MOVE_EXTREME_SPEED, MOVE_FEINT, MOVE_QUICK_ATTACK, MOVE_UNAVAILABLE
};

static const u16 sPhysicalNormalComplexAttacks[] =
{
    MOVE_FACADE, MOVE_UNAVAILABLE
};

static const u16 sSpecialNormalAttacks[] =
{
    MOVE_BOOMBURST, MOVE_TECHNO_BLAST, MOVE_JUDGMENT, MOVE_RELIC_SONG, MOVE_HYPER_VOICE, MOVE_TRI_ATTACK, MOVE_SWIFT, MOVE_ROUND, MOVE_ECHOED_VOICE, MOVE_UNAVAILABLE
};

static const u16 sPhysicalPoisonAttacks[] =
{
    MOVE_GUNK_SHOT, MOVE_DIRE_CLAW, MOVE_POISON_JAB, MOVE_BARB_BARRAGE, MOVE_CROSS_POISON, MOVE_POISON_FANG, MOVE_POISON_TAIL, MOVE_MORTAL_SPIN, MOVE_POISON_STING, MOVE_UNAVAILABLE
};

static const u16 sPhysicalPoisonComplexAttacks[] =
{
    MOVE_BARB_BARRAGE, MOVE_SHELL_SIDE_ARM, MOVE_UNAVAILABLE
};

static const u16 sSpecialPoisonAttacks[] =
{
    MOVE_SLUDGE_WAVE, MOVE_SLUDGE_BOMB, MOVE_VENOSHOCK, MOVE_ACID_SPRAY, MOVE_SLUDGE, MOVE_CLEAR_SMOG, MOVE_ACID, MOVE_SMOG, MOVE_UNAVAILABLE
};

static const u16 sSpecialPoisonComplexAttacks[] =
{
    MOVE_SHELL_SIDE_ARM, MOVE_VENOSHOCK, MOVE_BELCH, MOVE_UNAVAILABLE
};

static const u16 sPhysicalPsychicAttacks[] =
{
    MOVE_PSYCHIC_FANGS, MOVE_PSYSHIELD_BASH, MOVE_ZEN_HEADBUTT, MOVE_PSYBLADE, MOVE_PSYCHO_CUT, MOVE_HEART_STAMP, MOVE_UNAVAILABLE
};

static const u16 sSpecialPsychicAttacks[] =
{
    MOVE_PSYSTRIKE, MOVE_PHOTON_GEYSER, MOVE_LUMINA_CRASH, MOVE_FREEZING_GLARE, MOVE_PSYCHIC, MOVE_PSYSHOCK, MOVE_HYPERSPACE_HOLE, MOVE_TWIN_BEAM, MOVE_EERIE_SPELL, MOVE_ESPER_WING, MOVE_EXTRASENSORY, MOVE_MYSTICAL_POWER, MOVE_EXPANDING_FORCE, MOVE_PSYBEAM, MOVE_CONFUSION, MOVE_UNAVAILABLE
};

static const u16 sSpecialPsychicComplexAttacks[] =
{
    MOVE_STORED_POWER, MOVE_FUTURE_SIGHT, MOVE_MIRROR_COAT, MOVE_UNAVAILABLE
};

static const u16 sPhysicalRockAttacks[] =
{
    MOVE_DIAMOND_STORM, MOVE_STONE_EDGE, MOVE_ROCK_SLIDE, MOVE_SALT_CURE, MOVE_STONE_AXE, MOVE_ROCK_TOMB, MOVE_SMACK_DOWN, MOVE_ROCK_BLAST, MOVE_ACCELEROCK, MOVE_ROCK_THROW, MOVE_UNAVAILABLE
};

static const u16 sPhysicalRockPriorityAttacks[] =
{
    MOVE_ACCELEROCK, MOVE_UNAVAILABLE
};

static const u16 sPhysicalRockComplexAttacks[] =
{
    MOVE_HEAD_SMASH, MOVE_UNAVAILABLE
};

static const u16 sSpecialRockAttacks[] =
{
    MOVE_POWER_GEM, MOVE_ANCIENT_POWER, MOVE_UNAVAILABLE
};

static const u16 sSpecialRockComplexAttacks[] =
{
    MOVE_METEOR_BEAM, MOVE_UNAVAILABLE
};

static const u16 sPhysicalSteelAttacks[] =
{
    MOVE_GIGATON_HAMMER, MOVE_SUNSTEEL_STRIKE, MOVE_DOUBLE_IRON_BASH, MOVE_GEAR_GRIND, MOVE_BEHEMOTH_BASH, MOVE_BEHEMOTH_BLADE, MOVE_METEOR_MASH, MOVE_IRON_HEAD, MOVE_ANCHOR_SHOT, MOVE_SPIN_OUT, MOVE_SMART_STRIKE, MOVE_STEEL_WING, MOVE_IRON_TAIL, MOVE_MAGNET_BOMB, MOVE_METAL_CLAW, MOVE_BULLET_PUNCH, MOVE_UNAVAILABLE
};

static const u16 sPhysicalSteelPriorityAttacks[] =
{
    MOVE_BULLET_PUNCH, MOVE_UNAVAILABLE
};

static const u16 sPhysicalSteelComplexAttacks[] =
{
    MOVE_METAL_BURST, MOVE_UNAVAILABLE
};

static const u16 sSpecialSteelAttacks[] =
{
    MOVE_MAKE_IT_RAIN, MOVE_FLASH_CANNON, MOVE_MIRROR_SHOT, MOVE_UNAVAILABLE
};

static const u16 sSpecialSteelComplexAttacks[] =
{
    MOVE_DOOM_DESIRE, MOVE_STEEL_BEAM, MOVE_UNAVAILABLE
};

static const u16 sPhysicalWaterAttacks[] =
{
    MOVE_WAVE_CRASH, MOVE_FISHIOUS_REND, MOVE_SURGING_STRIKES, MOVE_CRABHAMMER, MOVE_AQUA_STEP, MOVE_LIQUIDATION, MOVE_TRIPLE_DIVE, MOVE_RAZOR_SHELL, MOVE_WATERFALL, MOVE_AQUA_TAIL, MOVE_AQUA_CUTTER, MOVE_JET_PUNCH, MOVE_DIVE, MOVE_AQUA_JET, MOVE_CLAMP, MOVE_UNAVAILABLE
};

static const u16 sPhysicalWaterPriorityAttacks[] =
{
    MOVE_JET_PUNCH, MOVE_AQUA_JET, MOVE_UNAVAILABLE
};

static const u16 sSpecialWaterAttacks[] =
{
    MOVE_STEAM_ERUPTION, MOVE_ORIGIN_PULSE, MOVE_HYDRO_PUMP, MOVE_HYDRO_STEAM, MOVE_SNIPE_SHOT, MOVE_SCALD, MOVE_MUDDY_WATER, MOVE_SURF, MOVE_SPARKLING_ARIA, MOVE_WATER_PULSE, MOVE_BRINE, MOVE_BUBBLE_BEAM, MOVE_CHILLING_WATER, MOVE_WATER_GUN, MOVE_WHIRLPOOL, MOVE_BUBBLE, MOVE_UNAVAILABLE
};

static const u16 sSpecialWaterPriorityAttacks[] =
{
    MOVE_WATER_SHURIKEN, MOVE_UNAVAILABLE
};

static const u16 sSpecialWaterComplexAttacks[] =
{
    MOVE_WATER_SPOUT, MOVE_UNAVAILABLE
};

// 6 levels:
// Mons up to Lv 15 can only have random level-up moves (assume there's no point since they learn very few moves at that point anyway)
// Tier 1 physical (intermediate level moves for mons lv 16-30; may have Egg moves (not in a way that cheats level-up moves))
// Tier 1 special
// Tier 2 physical (full powered moves for mons Lv31+; full access to all moves)
// Tier 2 special
// Physical priority (special case)
// Special priority
// Physical "unique" (Pursuit or Stored Power etc. *maybe viable* moves that have to be considered on a case by case basis)
// Special "unique"
// When a move requests a move of a certain type, it takes an appropriate list and calculates the power of each move based on ability etc.
// and picks the strongest. "Unique" moves are also considered options when the mon uses a tier 2 list.
// Ordered from best to worst (in my opinion)
const struct AttackOptions gMoveOptionsPerTypeByLevel[][2] =
{
    [TYPE_BUG] = {
        {
            .baseAttacks = sPhysicalBugAttacks,
            .priorityAttacks = sPhysicalBugPriorityAttacks,
            .complexAttacks = sPhysicalBugComplexAttacks
        },
        {
            .baseAttacks = sSpecialBugAttacks
        }
    },
    [TYPE_DARK] = {
        {
            .baseAttacks = sPhysicalDarkAttacks,
            .priorityAttacks = sPhysicalDarkPriorityAttacks,
            .complexAttacks = sPhysicalDarkComplexAttacks
        },
        {
            .baseAttacks = sSpecialDarkAttacks
        }
    },
    [TYPE_DRAGON] = {
        {
            .baseAttacks = sPhysicalDragonAttacks,
            .complexAttacks = sPhysicalDragonComplexAttacks
        },
        {
            .baseAttacks = sSpecialDragonAttacks,
            .complexAttacks = sSpecialDragonComplexAttacks
        }
    },
    [TYPE_ELECTRIC] = {
        {
            .baseAttacks = sPhysicalElectricAttacks,
            .complexAttacks = sPhysicalElectricComplexAttacks
        },
        {
            .baseAttacks = sSpecialElectricAttacks,
            .complexAttacks = sSpecialElectricComplexAttacks
        }
    },
    [TYPE_FAIRY] = {
        {
            .baseAttacks = sPhysicalFairyAttacks
        },
        {
            .baseAttacks = sSpecialFairyAttacks,
            .complexAttacks = sSpecialFairyComplexAttacks
        }
    },
    [TYPE_FIGHTING] = {
        {
            .baseAttacks = sPhysicalFightingAttacks,
            .priorityAttacks = sPhysicalFightingPriorityAttacks,
            .complexAttacks = sPhysicalFightingComplexAttacks
        },
        {
            .baseAttacks = sSpecialFightingAttacks,
            .priorityAttacks = sSpecialFightingPriorityAttacks
        }
    },
    [TYPE_FIRE] = {
        {
            .baseAttacks = sPhysicalFireAttacks
        },
        {
            .baseAttacks = sSpecialFireAttacks,
            .complexAttacks = sSpecialFireComplexAttacks
        }
    },
    [TYPE_FLYING] = {
        {
            .baseAttacks = sPhysicalFlyingAttacks,
            .complexAttacks = sPhysicalFlyingComplexAttacks
        },
        {
            .baseAttacks = sSpecialFlyingAttacks
        }
    },
    [TYPE_GHOST] = {
        {
            .baseAttacks = sPhysicalGhostAttacks,
            .priorityAttacks = sPhysicalGhostPriorityAttacks,
            .complexAttacks = sPhysicalGhostComplexAttacks
        },
        {
            .baseAttacks = sSpecialGhostAttacks,
            .complexAttacks = sSpecialGhostComplexAttacks
        }
    },
    [TYPE_GRASS] = {
        {
            .baseAttacks = sPhysicalGrassAttacks,
            .complexAttacks = sPhysicalGrassComplexAttacks
        },
        {
            .baseAttacks = sSpecialGrassAttacks,
            .complexAttacks = sSpecialGrassComplexAttacks
        }
    },
    [TYPE_GROUND] = {
        {
            .baseAttacks = sPhysicalGroundAttacks
        },
        {
            .baseAttacks = sSpecialGroundAttacks
        }
    },
    [TYPE_ICE] = {
        {
            .baseAttacks = sPhysicalIceAttacks,
            .priorityAttacks = sPhysicalIcePriorityAttacks
        },
        {
            .baseAttacks = sSpecialIceAttacks,
            .complexAttacks = sSpecialIceComplexAttacks
        }
    },
    [TYPE_NORMAL] = {
        {
            .baseAttacks = sPhysicalNormalAttacks,
            .priorityAttacks = sPhysicalNormalPriorityAttacks,
            .complexAttacks = sPhysicalNormalComplexAttacks
        },
        {
            .baseAttacks = sSpecialNormalAttacks
        }
    },
    [TYPE_POISON] = {
        {
            .baseAttacks = sPhysicalPoisonAttacks,
            .complexAttacks = sPhysicalPoisonComplexAttacks
        },
        {
            .baseAttacks = sSpecialPoisonAttacks,
            .complexAttacks = sSpecialPoisonComplexAttacks
        }
    },
    [TYPE_PSYCHIC] = {
        {
            .baseAttacks = sPhysicalPsychicAttacks
        },
        {
            .baseAttacks = sSpecialPsychicAttacks,
            .complexAttacks = sSpecialPsychicComplexAttacks
        }
    },
    [TYPE_ROCK] = {
        {
            .baseAttacks = sPhysicalRockAttacks,
            .priorityAttacks = sPhysicalRockPriorityAttacks,
            .complexAttacks = sPhysicalRockComplexAttacks
        },
        {
            .baseAttacks = sSpecialRockAttacks,
            .complexAttacks = sSpecialRockComplexAttacks
        }
    },
    [TYPE_STEEL] = {
        {
            .baseAttacks = sPhysicalSteelAttacks,
            .priorityAttacks = sPhysicalSteelPriorityAttacks,
            .complexAttacks = sPhysicalSteelComplexAttacks
        },
        {
            .baseAttacks = sSpecialSteelAttacks,
            .complexAttacks = sSpecialSteelComplexAttacks
        }
    },
    [TYPE_WATER] = {
        {
            .baseAttacks = sPhysicalWaterAttacks,
            .priorityAttacks = sPhysicalWaterPriorityAttacks
        },
        {
            .baseAttacks = sSpecialWaterAttacks,
            .priorityAttacks = sSpecialWaterPriorityAttacks,
            .complexAttacks = sSpecialWaterComplexAttacks
        }
    }
};