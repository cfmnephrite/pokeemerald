#ifndef GUARD_TRAINER_GENERATOR_H
#define GUARD_TRAINER_GENERATOR_H

#define MAX_SPECIES_PER_TRAINER_CLASS   30
#define MIN_LEVEL_FOR_FULL_MOVESET      30
#define LOWER_LEVEL_MON_MOVE_BP_LIMIT   70 // totally arbitrary
#define MIN_LEVEL_FOR_MAX_EVS           50
#define MAX_ALTERNATIVES                2

// "Moveslot placeholders"
#define MOVE_PLACEHOLDER_PRIORITY       1
#define MOVE_PLACEHOLDER_PIVOT          2
#define MOVE_PLACEHOLDER_RECOVERY       3
#define MOVE_PLACEHOLDER_SETUP          4
#define MOVE_PLACEHOLDER_NUKE           5
#define MOVE_PLACEHOLDER_UTILITY        6
#define MOVE_PLACEHOLDER_PHAZER_HAZER   7
#define MOVE_PLACEHOLDER_STATUS         8

#define MOVE_PLACEHOLDERS_COUNT         8
#define SPECIES_SUITABLE_ROLES_COUNT    4
#define IS_Z_MOVE(move)     (move >= MOVE_BREAKNECK_BLITZ && move <= MOVE_SOUL_STEALING_7_STAR_STRIKE)

enum MonRole
{
    MON_ROLE_UNASSIGNED,
    MON_ROLE_PHYSICAL_ALL_OUT_ATTACKER,
    MON_ROLE_SPECIAL_ALL_OUT_ATTACKER,
    MON_ROLE_PHYSICAL_SETUP_SWEEPER,
    MON_ROLE_SPECIAL_SETUP_SWEEPER,
    MON_ROLE_PHYSICAL_TANK,
    MON_ROLE_SPECIAL_TANK,
    MON_ROLE_PHYSICALLY_ATTACKING_PHYSICAL_WALL,
    MON_ROLE_SPECIALLY_ATTACKING_PHYSICAL_WALL,
    MON_ROLE_PHYSICALLY_ATTACKING_SPECIAL_WALL,
    MON_ROLE_SPECIALLY_ATTACKING_SPECIAL_WALL,
};

// Pokemon types as bits
enum BitType
{
    BIT_TYPE_NORMAL = (1 << TYPE_NORMAL),
    BIT_TYPE_FIGHTING = (1 << TYPE_FIGHTING),
    BIT_TYPE_FLYING = (1 << TYPE_FLYING),
    BIT_TYPE_POISON = (1 << TYPE_POISON),
    BIT_TYPE_GROUND = (1 << TYPE_GROUND),
    BIT_TYPE_ROCK = (1 << TYPE_ROCK),
    BIT_TYPE_BUG = (1 << TYPE_BUG),
    BIT_TYPE_GHOST = (1 << TYPE_GHOST),
    BIT_TYPE_STEEL = (1 << TYPE_STEEL),
    BIT_TYPE_MYSTERY = (1 << TYPE_MYSTERY),
    BIT_TYPE_FIRE = (1 << TYPE_FIRE),
    BIT_TYPE_WATER = (1 << TYPE_WATER),
    BIT_TYPE_GRASS = (1 << TYPE_GRASS),
    BIT_TYPE_ELECTRIC = (1 << TYPE_ELECTRIC),
    BIT_TYPE_PSYCHIC = (1 << TYPE_PSYCHIC),
    BIT_TYPE_ICE = (1 << TYPE_ICE),
    BIT_TYPE_DRAGON = (1 << TYPE_DRAGON),
    BIT_TYPE_DARK = (1 << TYPE_DARK),
    BIT_TYPE_FAIRY = (1 << TYPE_FAIRY),
    BIT_TYPE_NONE = 0xFFFFFFFF,
};

struct AttackOptions {
    const u16 *baseAttacks;
    const u16 *priorityAttacks;
    const u16 *complexAttacks;
};

struct Coverage {
    // u16 moves[MAX_MON_MOVES];
    // u16 moveTypes[MAX_MON_MOVES];
    u32 resisted;
    u32 combinedResisted; // i.e. types that might resist all moves in certain combinations
    u32 immune;
    u32 superEffective;
};

u32 GenerateTrainerMon(struct Pokemon *pokemon, u32 trainerClass, u32 lvl, u32 iv);
extern const u16 gPriorityAttacks[];
extern const u16 gSpecialPriorityAttacks[];
extern const u16 gPivotOrSwitchMoves[];
extern const u16 gPhysicalSetupMoves[];
extern const u16 gSpecialSetupMoves[];
extern const u16 gPhysicalNukes[];
extern const u16 gSpecialNukes[];
extern const u16 gUtilityMoves[];
extern const u16 gPhysicalHPDrainMoves[];
extern const u16 gSpecialHPDrainMoves[];
extern const u16 gRecoveryMoves[];
extern const u16 gStatusAfflictingMoves[];
extern const u16 gPhazerHazerMoves[];
extern const struct AttackOptions gMoveOptionsPerTypeByLevel[][2];

#define MON_ROLE_IS_ALL_OUT_ATTACKER        (sRole / 2 == 0)
#define MON_ROLE_IS_SETUP_SWEEPER           (sRole / 2 == 1)
#define MON_ROLE_IS_TANK                    (sRole / 2 == 2)
#define MON_ROLE_IS_OFFENSIVE               (sRole <= MON_ROLE_SPECIAL_TANK)
#define MON_ROLE_IS_DEFENSIVE               (sRole > MON_ROLE_SPECIAL_TANK)

#endif // GUARD_TRAINER_GENERATOR_H