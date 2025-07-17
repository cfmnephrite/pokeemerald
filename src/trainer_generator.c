#include "global.h"
#include "battle.h"
#include "battle_util.h"
#include "pokemon.h"
#include "constants/abilities.h"
#include "constants/battle_move_effects.h"
#include "constants/hold_effects.h"
#include "constants/species.h"
#include "constants/trainers.h"
#include "trainer_generator.h"
#include "data/battle_moves_by_viability.h"
#include "data/trainer_generator_class_species.h"
#include "random.h"

// Super-effective bits (as an attacking type)
static const u32 sSuperEffectiveCoverageByType[] =
{
    [TYPE_NORMAL]   = 0,
    [TYPE_FIGHTING] = (BIT_TYPE_ICE | BIT_TYPE_STEEL | BIT_TYPE_DARK | BIT_TYPE_NORMAL | BIT_TYPE_ROCK),
    [TYPE_FLYING]   = (BIT_TYPE_GRASS | BIT_TYPE_FIGHTING | BIT_TYPE_BUG),
    [TYPE_POISON]   = (BIT_TYPE_GRASS | BIT_TYPE_FAIRY),
    [TYPE_GROUND]   = (BIT_TYPE_ELECTRIC | BIT_TYPE_ROCK | BIT_TYPE_STEEL | BIT_TYPE_FIRE),
    [TYPE_ROCK]     = (BIT_TYPE_BUG | BIT_TYPE_FIRE | BIT_TYPE_FLYING | BIT_TYPE_ICE),
    [TYPE_BUG]      = (BIT_TYPE_GRASS | BIT_TYPE_DARK | BIT_TYPE_PSYCHIC),
    [TYPE_GHOST]    = (BIT_TYPE_GHOST | BIT_TYPE_PSYCHIC),
    [TYPE_STEEL]    = (BIT_TYPE_ICE | BIT_TYPE_ROCK | BIT_TYPE_FAIRY),
    [TYPE_FIRE]     = (BIT_TYPE_ICE | BIT_TYPE_STEEL | BIT_TYPE_GRASS),
    [TYPE_WATER]    = (BIT_TYPE_GROUND | BIT_TYPE_ROCK | BIT_TYPE_FIRE),
    [TYPE_GRASS]    = (BIT_TYPE_GROUND | BIT_TYPE_WATER | BIT_TYPE_ROCK),
    [TYPE_ELECTRIC] = (BIT_TYPE_FLYING | BIT_TYPE_WATER),
    [TYPE_PSYCHIC]  = (BIT_TYPE_FIGHTING | BIT_TYPE_POISON),
    [TYPE_ICE]      = (BIT_TYPE_DRAGON | BIT_TYPE_FLYING | BIT_TYPE_GRASS | BIT_TYPE_GROUND),
    [TYPE_DRAGON]   = (BIT_TYPE_DRAGON),
    [TYPE_DARK]     = (BIT_TYPE_PSYCHIC | BIT_TYPE_GHOST),
    [TYPE_FAIRY]    = (BIT_TYPE_FIGHTING | BIT_TYPE_DRAGON | BIT_TYPE_DARK)
};

// Resisted bits (as an attacking type)
static const u32 sNotVeryEffectiveCoverageByType[] =
{
    [TYPE_NORMAL]   = (BIT_TYPE_ROCK | BIT_TYPE_STEEL),
    [TYPE_FIGHTING] = (BIT_TYPE_BUG | BIT_TYPE_FAIRY | BIT_TYPE_FLYING | BIT_TYPE_POISON),
    [TYPE_FLYING]   = (BIT_TYPE_ELECTRIC | BIT_TYPE_ROCK | BIT_TYPE_STEEL),
    [TYPE_POISON]   = (BIT_TYPE_ROCK | BIT_TYPE_GROUND | BIT_TYPE_POISON),
    [TYPE_GROUND]   = (BIT_TYPE_GRASS | BIT_TYPE_BUG),
    [TYPE_ROCK]     = (BIT_TYPE_FIGHTING | BIT_TYPE_GROUND | BIT_TYPE_STEEL),
    [TYPE_BUG]      = (BIT_TYPE_FIRE | BIT_TYPE_FLYING | BIT_TYPE_FAIRY | BIT_TYPE_STEEL | BIT_TYPE_GHOST | BIT_TYPE_POISON),
    [TYPE_GHOST]    = (BIT_TYPE_DARK),
    [TYPE_STEEL]    = (BIT_TYPE_FIRE | BIT_TYPE_WATER | BIT_TYPE_ELECTRIC | BIT_TYPE_STEEL),
    [TYPE_FIRE]     = (BIT_TYPE_FIRE | BIT_TYPE_WATER | BIT_TYPE_ROCK | BIT_TYPE_DRAGON),
    [TYPE_WATER]    = (BIT_TYPE_WATER | BIT_TYPE_GRASS | BIT_TYPE_DRAGON),
    [TYPE_GRASS]    = (BIT_TYPE_GRASS | BIT_TYPE_FIRE | BIT_TYPE_BUG | BIT_TYPE_FLYING | BIT_TYPE_POISON | BIT_TYPE_STEEL | BIT_TYPE_DRAGON),
    [TYPE_ELECTRIC] = (BIT_TYPE_ELECTRIC | BIT_TYPE_DRAGON),
    [TYPE_PSYCHIC]  = (BIT_TYPE_PSYCHIC | BIT_TYPE_STEEL),
    [TYPE_ICE]      = (BIT_TYPE_ICE | BIT_TYPE_WATER | BIT_TYPE_FIRE | BIT_TYPE_STEEL),
    [TYPE_DRAGON]   = (BIT_TYPE_STEEL),
    [TYPE_DARK]     = (BIT_TYPE_FIGHTING | BIT_TYPE_DARK | BIT_TYPE_FAIRY),
    [TYPE_FAIRY]    = (BIT_TYPE_FIRE | BIT_TYPE_STEEL | BIT_TYPE_POISON)
};

// Immune bits (as an attacking type)
static const u32 sDoesntAffectCoverageByType[] =
{
    [TYPE_NORMAL]   = (BIT_TYPE_GHOST),
    [TYPE_FIGHTING] = (BIT_TYPE_GHOST),
    [TYPE_FLYING]   = 0,
    [TYPE_POISON]   = (BIT_TYPE_STEEL),
    [TYPE_GROUND]   = (BIT_TYPE_FLYING),
    [TYPE_ROCK]     = 0,
    [TYPE_BUG]      = 0,
    [TYPE_GHOST]    = (BIT_TYPE_NORMAL),
    [TYPE_STEEL]    = 0,
    [TYPE_FIRE]     = 0,
    [TYPE_WATER]    = 0,
    [TYPE_GRASS]    = 0,
    [TYPE_ELECTRIC] = (BIT_TYPE_GROUND),
    [TYPE_PSYCHIC]  = (BIT_TYPE_DARK),
    [TYPE_ICE]      = 0,
    [TYPE_DRAGON]   = (BIT_TYPE_FAIRY),
    [TYPE_DARK]     = 0,
    [TYPE_FAIRY]    = 0
};

// Super-effective bits (as a defending type)
static const u32 sWeaknessesByType[] =
{
    [TYPE_NORMAL]   = (BIT_TYPE_FIGHTING),
    [TYPE_FIGHTING] = (BIT_TYPE_PSYCHIC | BIT_TYPE_FLYING | BIT_TYPE_FAIRY),
    [TYPE_FLYING]   = (BIT_TYPE_ELECTRIC | BIT_TYPE_ROCK | BIT_TYPE_ICE),
    [TYPE_POISON]   = (BIT_TYPE_PSYCHIC | BIT_TYPE_GROUND),
    [TYPE_GROUND]   = (BIT_TYPE_WATER | BIT_TYPE_GRASS | BIT_TYPE_ICE),
    [TYPE_ROCK]     = (BIT_TYPE_WATER | BIT_TYPE_GRASS | BIT_TYPE_FIGHTING | BIT_TYPE_GROUND | BIT_TYPE_STEEL),
    [TYPE_BUG]      = (BIT_TYPE_FLYING | BIT_TYPE_FIRE | BIT_TYPE_ROCK),
    [TYPE_GHOST]    = (BIT_TYPE_GHOST | BIT_TYPE_DARK),
    [TYPE_STEEL]    = (BIT_TYPE_FIRE | BIT_TYPE_FIGHTING | BIT_TYPE_GROUND),
    [TYPE_FIRE]     = (BIT_TYPE_WATER | BIT_TYPE_ROCK | BIT_TYPE_GROUND),
    [TYPE_WATER]    = (BIT_TYPE_GRASS | BIT_TYPE_ELECTRIC),
    [TYPE_GRASS]    = (BIT_TYPE_FIRE | BIT_TYPE_FLYING | BIT_TYPE_BUG | BIT_TYPE_POISON),
    [TYPE_ELECTRIC] = (BIT_TYPE_GROUND),
    [TYPE_PSYCHIC]  = (BIT_TYPE_BUG | BIT_TYPE_GHOST | BIT_TYPE_DARK),
    [TYPE_ICE]      = (BIT_TYPE_FIRE | BIT_TYPE_ROCK | BIT_TYPE_STEEL | BIT_TYPE_FIGHTING),
    [TYPE_DRAGON]   = (BIT_TYPE_DRAGON | BIT_TYPE_ICE | BIT_TYPE_FAIRY),
    [TYPE_DARK]     = (BIT_TYPE_FIGHTING | BIT_TYPE_BUG | BIT_TYPE_FAIRY),
    [TYPE_FAIRY]    = (BIT_TYPE_POISON | BIT_TYPE_STEEL)
};

// Resisted bits (as a defending type)
static const u32 sResistancesByType[] =
{
    [TYPE_NORMAL]   = 0,
    [TYPE_FIGHTING] = (BIT_TYPE_BUG | BIT_TYPE_DARK | BIT_TYPE_ROCK),
    [TYPE_FLYING]   = (BIT_TYPE_BUG | BIT_TYPE_GRASS | BIT_TYPE_FIGHTING),
    [TYPE_POISON]   = (BIT_TYPE_POISON | BIT_TYPE_BUG | BIT_TYPE_FIGHTING | BIT_TYPE_GRASS | BIT_TYPE_FAIRY),
    [TYPE_GROUND]   = (BIT_TYPE_ROCK | BIT_TYPE_POISON),
    [TYPE_ROCK]     = (BIT_TYPE_NORMAL | BIT_TYPE_POISON | BIT_TYPE_FLYING),
    [TYPE_BUG]      = (BIT_TYPE_FIGHTING | BIT_TYPE_GROUND | BIT_TYPE_GRASS),
    [TYPE_GHOST]    = (BIT_TYPE_BUG | BIT_TYPE_POISON),
    [TYPE_STEEL]    = (BIT_TYPE_NORMAL | BIT_TYPE_FLYING | BIT_TYPE_BUG | BIT_TYPE_GRASS | BIT_TYPE_ROCK | BIT_TYPE_FAIRY | BIT_TYPE_DRAGON | BIT_TYPE_ICE | BIT_TYPE_STEEL | BIT_TYPE_PSYCHIC),
    [TYPE_FIRE]     = (BIT_TYPE_GRASS | BIT_TYPE_FIRE | BIT_TYPE_BUG | BIT_TYPE_STEEL | BIT_TYPE_FAIRY),
    [TYPE_WATER]    = (BIT_TYPE_FIRE | BIT_TYPE_WATER | BIT_TYPE_STEEL),
    [TYPE_GRASS]    = (BIT_TYPE_GROUND | BIT_TYPE_WATER | BIT_TYPE_GRASS | BIT_TYPE_ELECTRIC),
    [TYPE_ELECTRIC] = (BIT_TYPE_ELECTRIC | BIT_TYPE_STEEL | BIT_TYPE_FLYING),
    [TYPE_PSYCHIC]  = (BIT_TYPE_FIGHTING | BIT_TYPE_PSYCHIC),
    [TYPE_ICE]      = (BIT_TYPE_ICE),
    [TYPE_DRAGON]   = (BIT_TYPE_WATER | BIT_TYPE_FIRE | BIT_TYPE_GRASS | BIT_TYPE_ELECTRIC),
    [TYPE_DARK]     = (BIT_TYPE_DARK | BIT_TYPE_GHOST),
    [TYPE_FAIRY]    = (BIT_TYPE_DARK | BIT_TYPE_BUG | BIT_TYPE_FIGHTING)
};

// Immune bits (as a defending type)
static const u32 sImmunitiesByType[] =
{
    [TYPE_NORMAL]   = (BIT_TYPE_GHOST),
    [TYPE_FIGHTING] = 0,
    [TYPE_FLYING]   = (BIT_TYPE_GROUND),
    [TYPE_POISON]   = 0,
    [TYPE_GROUND]   = (BIT_TYPE_ELECTRIC),
    [TYPE_ROCK]     = 0,
    [TYPE_BUG]      = 0,
    [TYPE_GHOST]    = (BIT_TYPE_NORMAL | BIT_TYPE_FIGHTING),
    [TYPE_STEEL]    = (BIT_TYPE_POISON),
    [TYPE_FIRE]     = 0,
    [TYPE_WATER]    = 0,
    [TYPE_GRASS]    = 0,
    [TYPE_ELECTRIC] = 0,
    [TYPE_PSYCHIC]  = 0,
    [TYPE_ICE]      = 0,
    [TYPE_DRAGON]   = 0,
    [TYPE_DARK]     = (BIT_TYPE_PSYCHIC),
    [TYPE_FAIRY]    = (BIT_TYPE_DRAGON)
};

// Static variables
static u16 sAtkAbility;
static u16 sHoldEffectAtk;
static u16 sSpecies;
static u8 sLevel;
static u8 sRole;
static u8 sSlot;
extern struct Evolution gEvolutionTable[][9];

static u8 popcount(u32 i)
{
    i = i - ((i >> 1) & 0x55555555);        // add pairs of bits
    i = (i & 0x33333333) + ((i >> 2) & 0x33333333);  // quads
    i = (i + (i >> 4)) & 0x0F0F0F0F;        // groups of 8
    return (i * 0x01010101) >> 24;          // horizontal sum of bytes
}

static inline u32 MinBPCap(void)
{
    if (sLevel < MIN_LEVEL_FOR_FULL_MOVESET)
        return 30;
    return 60;
}

static bool32 CanLearnMove(u16 species, u16 move, u8 level)
{
    // To do
    // return (CanLearnLevelUpMove(species, move, level) || CanLearnTeachableMove(species, move));
    return TRUE;
}

static u32 GetRandomSpeciesFromTrainerClass(u32 trainerClass, u32 level)
{
    u16 species = SPECIES_NONE;
    switch (trainerClass)
    {
        case TRAINER_CLASS_AROMA_LADY:
            // species = sAromaLadySpecies[Random32() % ARRAY_COUNT(sAromaLadySpecies)];
        break;
        case TRAINER_CLASS_BATTLE_GIRL:
            species = sBattleGirlSpecies[Random32() % ARRAY_COUNT(sBattleGirlSpecies)];
        break;
        case TRAINER_CLASS_BEAUTY:
            species = sBeautySpecies[Random32() % ARRAY_COUNT(sBeautySpecies)];
        break;
        case TRAINER_CLASS_BIRD_KEEPER:
            species = sBirdKeeperSpecies[Random32() % ARRAY_COUNT(sBirdKeeperSpecies)];
        break;
        case TRAINER_CLASS_BLACK_BELT:
            species = sBlackBeltSpecies[Random32() % ARRAY_COUNT(sBlackBeltSpecies)];
        break;
        case TRAINER_CLASS_BUG_CATCHER:
            species = sBugCatcherSpecies[Random32() % ARRAY_COUNT(sBugCatcherSpecies)];
        break;
        case TRAINER_CLASS_CAMPER:
            species = sCamperSpecies[Random32() % ARRAY_COUNT(sCamperSpecies)];
        break;
        case TRAINER_CLASS_COLLECTOR:
            species = sCollectorSpecies[Random32() % ARRAY_COUNT(sCollectorSpecies)];
        break;
        case TRAINER_CLASS_COOLTRAINER:
            species = sCoolTrainerSpecies[Random32() % ARRAY_COUNT(sCoolTrainerSpecies)];
        break;
        case TRAINER_CLASS_DRAGON_TAMER:
            species = sDragonTamerSpecies[Random32() % ARRAY_COUNT(sDragonTamerSpecies)];
        break;
        case TRAINER_CLASS_EXPERT:
            species = sExpertSpecies[Random32() % ARRAY_COUNT(sExpertSpecies)];
        break;
        case TRAINER_CLASS_FISHERMAN:
            species = sFishermanSpecies[Random32() % ARRAY_COUNT(sFishermanSpecies)];
        break;
        case TRAINER_CLASS_GENTLEMAN:
            species = sGentlemanSpecies[Random32() % ARRAY_COUNT(sGentlemanSpecies)];
        break;
        case TRAINER_CLASS_GUITARIST:
            species = sGuitaristSpecies[Random32() % ARRAY_COUNT(sGuitaristSpecies)];
        break;
        case TRAINER_CLASS_HEX_MANIAC:
            species = sHexManiacSpecies[Random32() % ARRAY_COUNT(sHexManiacSpecies)];
        break;
        case TRAINER_CLASS_HIKER:
            species = sHikerSpecies[Random32() % ARRAY_COUNT(sHikerSpecies)];
        break;
        case TRAINER_CLASS_LADY:
            species = sLadySpecies[Random32() % ARRAY_COUNT(sLadySpecies)];
        break;
        case TRAINER_CLASS_LASS:
            species = sLassSpecies[Random32() % ARRAY_COUNT(sLassSpecies)];
        break;
        case TRAINER_CLASS_NINJA_BOY:
            species = sNinjaBoySpecies[Random32() % ARRAY_COUNT(sNinjaBoySpecies)];
        break;
        case TRAINER_CLASS_PARASOL_LADY:
            species = sParasolLadySpecies[Random32() % ARRAY_COUNT(sParasolLadySpecies)];
        break;
        case TRAINER_CLASS_PKMN_BREEDER:
            species = sPkmnBreederSpecies[Random32() % ARRAY_COUNT(sPkmnBreederSpecies)];
        break;
        case TRAINER_CLASS_PKMN_RANGER:
            species = sPkmnRangerSpecies[Random32() % ARRAY_COUNT(sPkmnRangerSpecies)];
        break;
        case TRAINER_CLASS_PSYCHIC:
            species = sPsychicSpecies[Random32() % ARRAY_COUNT(sPsychicSpecies)];
        break;
        case TRAINER_CLASS_RICH_BOY:
            species = sRichBoySpecies[Random32() % ARRAY_COUNT(sRichBoySpecies)];
        break;
        case TRAINER_CLASS_RUIN_MANIAC:
            species = sRuinManiacSpecies[Random32() % ARRAY_COUNT(sRuinManiacSpecies)];
        break;
        case TRAINER_CLASS_SAILOR:
            species = sSailorSpecies[Random32() % ARRAY_COUNT(sSailorSpecies)];
        break;
        case TRAINER_CLASS_SWIMMER_F:
        case TRAINER_CLASS_SWIMMER_M:
            species = sSwimmerSpecies[Random32() % ARRAY_COUNT(sSwimmerSpecies)];
        break;
        case TRAINER_CLASS_TEAM_AQUA:
            species = sTeamAquaSpecies[Random32() % ARRAY_COUNT(sTeamAquaSpecies)];
        break;
        case TRAINER_CLASS_TEAM_MAGMA:
            species = sTeamMagmaSpecies[Random32() % ARRAY_COUNT(sTeamMagmaSpecies)];
        break;
        case TRAINER_CLASS_TRIATHLETE:
            species = sTriathleteSpecies[Random32() % ARRAY_COUNT(sTriathleteSpecies)];
        break;
        default: // for now...
        case TRAINER_CLASS_YOUNGSTER:
            species = sYoungsterSpecies[Random32() % ARRAY_COUNT(sYoungsterSpecies)];
        break;
    }

    return species;
}

static bool32 AlreadyHaveMoveOfType(struct Pokemon *pokemon, u8 type)
{
    u8 i;
    u16 move;
    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        move = GetMonData(pokemon, MON_DATA_MOVE1 + i);
        if (gMovesInfo[move].type == type)
            return TRUE;
    }
    return FALSE;
}

static bool32 AlreadyHaveMove(struct Pokemon *pokemon, u16 moveToFind, u8 index)
{
    u8 i;
    u16 move;
    for (i = 0; i < index; i++)
    {
        move = GetMonData(pokemon, MON_DATA_MOVE1 + i);
        if (move == moveToFind)
            return TRUE;
    }
    return FALSE;
}

static u8 AccuracyAdjustedForMoveAbilityItem(u16 move)
{
    u16 accuracy = gMovesInfo[move].accuracy;
    uq4_12_t modifier = UQ_4_12(1.0);

    switch (sAtkAbility)
    {
        case ABILITY_COMPOUND_EYES:
            if (gMovesInfo[move].effect != EFFECT_OHKO)
                modifier = uq4_12_multiply(modifier, UQ_4_12(1.3));
        break;
        case ABILITY_HUSTLE:
            if (gMovesInfo[move].category == DAMAGE_CATEGORY_PHYSICAL && accuracy > 0)
                modifier = uq4_12_multiply(modifier, UQ_4_12(0.8));
        break;
        case ABILITY_VICTORY_STAR:
            if (gMovesInfo[move].effect != EFFECT_OHKO)
                modifier = uq4_12_multiply(modifier, UQ_4_12(1.1));
        break;
        case ABILITY_NO_GUARD:
            return 100; // all moves hit
    }

    switch (sHoldEffectAtk)
    {
        case HOLD_EFFECT_WIDE_LENS:
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.1));
        break;
        case HOLD_EFFECT_ZOOM_LENS: // assume we won't get this if the mon isn't slow
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.2));
        break;
    }

    // Always-hit moves have base accuracy of 0
    if (move != MOVE_NONE && accuracy == 0)
        accuracy = 100;

    return min(100, uq4_12_multiply_by_int_half_up(modifier, accuracy));
}

static u16 BPAdjustedForMultihitOnly(u16 move, u8 basePower)
{
    if (gMovesInfo[move].strikeCount > 0)
        basePower *= gMovesInfo[move].strikeCount;
    else if (gMovesInfo[move].effect == EFFECT_MULTI_HIT)
        basePower = (basePower * 5 / 2); // arbitrary, I know...

    return basePower;
}

static u32 BPAdjustedForMultihitAndEffects(u32 move, u32 moveType)
{
    u16 basePower = gMovesInfo[move].power;
    uq4_12_t modifier = UQ_4_12(1.0);

    // Duh
    if (gMovesInfo[move].category == DAMAGE_CATEGORY_STATUS)
        return 0;

    // In case we have null moveType, revert to move's type
    if (moveType == TYPE_NONE)
        moveType = gMovesInfo[move].type;

    // To do - update
    // modifier = CalcMoveBasePowerBeforeBattle(move, sAtkAbility, sHoldEffectAtk, basePower, moveType, modifier, 0, FALSE);

    // Modifications based on assessed worth of effect (not necessarily raw power)
    switch (gMovesInfo[move].effect)
    {
        case EFFECT_MAGNITUDE:
            basePower = 60; // Avg power is actually 71
        break;
        case EFFECT_KNOCK_OFF:
           modifier = uq4_12_multiply(modifier, UQ_4_12(1.5)); // assume it's always boosted
        break;
        // case EFFECT_SALT_CURE:
        //    modifier = uq4_12_multiply(modifier, UQ_4_12(2));
        // break;
    }
    return uq4_12_multiply_by_int_half_up(modifier, BPAdjustedForMultihitOnly(move, basePower));
}

static u32 TrySetChosenMoveForSpeciesReturnBP(struct Pokemon *pokemon, u32 type, const u16 *movesArray, u16 *move)
{
    u8 i = 0;
    bool32 lowLevel = sLevel < MIN_LEVEL_FOR_FULL_MOVESET;
    u16 currentMove, currentMovePower = 0;
    s16 modifiedPower = -1; // this is to allow for the selection of moves with BP = 0
    *move = MOVE_NONE;
    while ((currentMove = *(movesArray + i++)) != MOVE_UNAVAILABLE) {
        if (lowLevel) { 
            // Don't allow lower levelled mons to have full BP moves like Fire Blast - would be a little unfair for the player
            // However, we cheat to allow them to run 2-5 hit multihit moves even though their BP can be a little higher
            if (BPAdjustedForMultihitOnly(currentMove, gMovesInfo[currentMove].power) > LOWER_LEVEL_MON_MOVE_BP_LIMIT
                || !CanLearnMove(sSpecies, currentMove, sLevel))
            continue;
        } else if (CanLearnMove(sSpecies, currentMove, 0) // At higher levels, ignore level checks for level-up moves
            && !(type == TYPE_NONE && AlreadyHaveMove(pokemon, currentMove, sSlot)) // only run this check when type is TYPE_NONE
            && (currentMovePower = BPAdjustedForMultihitAndEffects(currentMove, type)) > modifiedPower)
        {
            *move = currentMove;
            modifiedPower = currentMovePower;
        }
    }

    // DebugPrintf("Move & power: %S; %d", gMoveNames[*move], modifiedPower);
    return max(0, modifiedPower);
}

static u32 GetGoodCoverageMove(struct Pokemon *pokemon, bool32 special, struct Coverage *coverage, bool32 haveMoves)
{
    u8 currType, currentMoveAcc, winningMoveAcc = 0, type1 = gSpeciesInfo[sSpecies].types[0], type2 = gSpeciesInfo[sSpecies].types[1];
    u16 currentMoveBP;
    s32 currentTypePoints;
    u16 winningTypePoints = 0, currentMove, winningMove = MOVE_NONE; // just use the regular learnset move
    u8 immunePoints, resistedPoints, combinedResistedPoints, threateningTypesPoints, neutralOrSePoints;
    s8 negativeResistPoints;
    for (currType = TYPE_NORMAL + 1; currType < NUMBER_OF_MON_TYPES; currType++)
    {
        if (AlreadyHaveMoveOfType(pokemon, currType) || currType == TYPE_MYSTERY) // No mon ever wants Dragon coverage...
            continue;

        // Start with points at 0
        immunePoints = resistedPoints = combinedResistedPoints = threateningTypesPoints = neutralOrSePoints = negativeResistPoints = 0;
        currentTypePoints = 0;

        // 10 points for a move that hits something that's immune to All moves
        if (coverage->immune)
            currentTypePoints += (immunePoints = (10 * popcount(coverage->immune & sSuperEffectiveCoverageByType[currType])));

        // 5 points for every resisted type it hits for SE damage
        if (coverage->resisted)
            currentTypePoints += (resistedPoints = (5 * popcount(coverage->resisted & sSuperEffectiveCoverageByType[currType])));

        // 3 points for hitting as many potential types that could resist in combination
        if (coverage->combinedResisted)
            currentTypePoints += (combinedResistedPoints = (3 * popcount(coverage->combinedResisted & sSuperEffectiveCoverageByType[currType])));

        // 2 points for every threatening type hit super-effectively
        currentTypePoints += (threateningTypesPoints = (2 * popcount(
            (sWeaknessesByType[type1] | sWeaknessesByType[type2])
            & ~(sResistancesByType[type1] | sResistancesByType[type2])
            & ~(sImmunitiesByType[type1] | sImmunitiesByType[type2])
            & sSuperEffectiveCoverageByType[currType]
        )));

        // 1 point for every resisted or immune type it hits neutrally or better
        currentTypePoints += (neutralOrSePoints = (popcount((coverage->combinedResisted & ~(sNotVeryEffectiveCoverageByType[currType])))));

        // -1 point for every resistance
        currentTypePoints = max(0, currentTypePoints + haveMoves * (negativeResistPoints = -(popcount(sNotVeryEffectiveCoverageByType[currType]))));

        // If worth considering, try and find the strongest available move of this type
        /* DebugPrintf("Checking coverage for type: %S: I: %d (%d), R: %d (%d), CR: %d (%d), T: %d, N: %d, NR: %d, total: %d",
            gTypeNames[currType], immunePoints, coverage->immune, resistedPoints, coverage->resisted,
            combinedResistedPoints, coverage->combinedResisted, threateningTypesPoints,
            neutralOrSePoints, negativeResistPoints, currentTypePoints);*/
        if (currentTypePoints > 0)
        {
            // Sometimes we want to take a stronger move with worse coverage or vice versa
            // So we take move bp x points x accuracy as the determinant
            // In case of a tie, the higher accuracy move wins
            // If same accuracy, the move first picked wins
            currentTypePoints *= ((currentMoveBP = TrySetChosenMoveForSpeciesReturnBP(pokemon, currType, gMoveOptionsPerTypeByLevel[currType][special].baseAttacks, &currentMove))
                * (currentMoveAcc = AccuracyAdjustedForMoveAbilityItem(currentMove)));
            if (currentMoveBP > MinBPCap() && (currentTypePoints > winningTypePoints || (currentTypePoints == winningTypePoints && winningMoveAcc > currentMoveAcc)))
            {
                winningMove = currentMove;
                winningTypePoints = currentTypePoints;
                winningMoveAcc = currentMoveAcc;
            }
            // DebugPrintf("Checking coverage for type: %S; best move: %S (%d); (BP: %d, Acc: %d), final points: %d", gTypeNames[currType], gMoveNames[currentMove], currentMove, currentMoveBP, currentMoveAcc, currentTypePoints);
        }
    }

    // DebugPrintf("Winning move! %S", gMoveNames[winningMove]);
    return winningMove;
}

static bool32 _SetGoodOtherMove(struct Pokemon *pokemon, bool32 special, u16 *chosenMove, u8 *choosersArray, u8 chooser, u8 chooserCount)
{
    const u16 *movesArray = NULL;

    // All flags filled - time to quit
    if (chooser >= chooserCount)
        return FALSE;

    switch (*(choosersArray + chooser))
    {
        case MOVE_PLACEHOLDER_PRIORITY:
            movesArray = gPriorityAttacks;
            break;
        case MOVE_PLACEHOLDER_PIVOT:
            movesArray = gPivotOrSwitchMoves;
            break;
        case MOVE_PLACEHOLDER_SETUP:
            movesArray = (special ? gSpecialSetupMoves : gPhysicalSetupMoves);
            break;
        case MOVE_PLACEHOLDER_UTILITY:
            movesArray = gUtilityMoves;
            break;
        case MOVE_PLACEHOLDER_NUKE:
            movesArray = (special ? gSpecialNukes : gPhysicalNukes);
            break;
        case MOVE_PLACEHOLDER_STATUS:
            movesArray = gStatusAfflictingMoves;
            break;
        case MOVE_PLACEHOLDER_PHAZER_HAZER:
            movesArray = gPhazerHazerMoves;
            break;
        case MOVE_PLACEHOLDER_RECOVERY:
            // Attackers should prioritise moves that recover HP through damage
            // although tanks have a 50/50 chance of having a real recovery move
            movesArray = gRecoveryMoves;
            break;
    }
    // if can't find move, rerun
    TrySetChosenMoveForSpeciesReturnBP(pokemon, TYPE_NONE, movesArray, chosenMove);
    return (*chosenMove == MOVE_NONE || AlreadyHaveMove(pokemon, *chosenMove, sSlot)) ? _SetGoodOtherMove(pokemon, special, chosenMove, choosersArray, chooser + 1, chooserCount) : TRUE;
}

static void SetGoodOtherMove(struct Pokemon *pokemon, bool32 special, u16 *chosenMove)
{
    // "other good move" depends on the role
    // Tanks may have set up moves but should otherwise use "defensive" moves
    u8 tankRandomNum = Random() % 2, choosersArray[] = {
        (MON_ROLE_IS_TANK & tankRandomNum) || MON_ROLE_IS_DEFENSIVE ? MOVE_PLACEHOLDER_PHAZER_HAZER : MOVE_PLACEHOLDER_SETUP,
        (MON_ROLE_IS_TANK & !tankRandomNum) || MON_ROLE_IS_DEFENSIVE ? MOVE_PLACEHOLDER_STATUS : MOVE_PLACEHOLDER_SETUP,
        MON_ROLE_IS_ALL_OUT_ATTACKER || MON_ROLE_IS_TANK ? MOVE_PLACEHOLDER_PRIORITY : MOVE_PLACEHOLDER_PIVOT,
        MOVE_PLACEHOLDER_PIVOT, // every mon could do with a pivot move...
        MON_ROLE_IS_TANK || MON_ROLE_IS_DEFENSIVE ? MOVE_PLACEHOLDER_RECOVERY : MOVE_PLACEHOLDER_NUKE,
        MON_ROLE_IS_TANK || MON_ROLE_IS_DEFENSIVE ? MOVE_PLACEHOLDER_UTILITY : MOVE_PLACEHOLDER_NUKE,
    };

    // Shuffle is shifted for set up sweepers as they MUST try to find a set up move first
    Shuffle(choosersArray + MON_ROLE_IS_SETUP_SWEEPER, ARRAY_COUNT(choosersArray) - (MON_ROLE_IS_SETUP_SWEEPER ? 1 : 0), 1);
    _SetGoodOtherMove(pokemon, special, chosenMove, choosersArray, 0, ARRAY_COUNT(choosersArray));
}

static void FillAllOutAttackerMoveset(struct Pokemon *pokemon, bool32 special)
{
    u8 i, chosenMoveType;
    u16 chosenMove, chosenMovePower;
    struct Coverage coverage = {0};
    u32 currTypeResisted, currTypeImmune, currTypeSuperEffective;
    for (sSlot = 0; sSlot < MAX_MON_MOVES; sSlot++)
    {
        chosenMove = chosenMoveType = chosenMovePower = i = 0;
        switch (sSlot)
        {
            case 0: // ALWAYS a STAB move
            case 1: // ALWAYS a STAB move if the mon is an attacker with two types - otherwise fall through
                if (!(sSlot == 1 && gSpeciesInfo[sSpecies].types[0] == gSpeciesInfo[sSpecies].types[1])
                    && TrySetChosenMoveForSpeciesReturnBP(
                        pokemon,
                        gSpeciesInfo[sSpecies].types[sSlot],
                        gMoveOptionsPerTypeByLevel[gSpeciesInfo[sSpecies].types[sSlot]][special].baseAttacks,
                        &chosenMove
                        ) > MinBPCap()
                    )
                    break;
                // fall-through
            case 2: // DEPENDS ON ROLE
                if (sRole < MON_ROLE_PHYSICALLY_ATTACKING_PHYSICAL_WALL)
                {
                    // Setup sweepers and all-out attackers definitely prefer a coverage move
                    // Tanks might want an extra recovery move, a utility/phazing move, or a coverage move
                    // Get coverage based on typing and/or typechart
                    if (sSlot == 1 || sRole <= MON_ROLE_SPECIAL_SETUP_SWEEPER || Random() % 2) {
                        chosenMove = GetGoodCoverageMove(pokemon, special, &coverage, sSlot > 0);
                        break;
                    }
                }
            case 3: // priority/pivot/nuke etc
                SetGoodOtherMove(pokemon, special, &chosenMove);
                break;
        }

        // Set mon move
        // DebugPrintf("chosenMove - %d: %S", chosenMove, gMoveNames[chosenMove]);
        if (chosenMove != MOVE_NONE)
        {
            // Defensive mons don't need to bother calcing for a good coverage move
            if (sRole < MON_ROLE_PHYSICALLY_ATTACKING_PHYSICAL_WALL)
            {
                chosenMoveType = gMovesInfo[chosenMove].type;
                coverage.superEffective |= (currTypeSuperEffective = sSuperEffectiveCoverageByType[chosenMoveType]);
                if (sSlot == 0)
                {
                    coverage.resisted   = (currTypeResisted = sNotVeryEffectiveCoverageByType[chosenMoveType]);
                    coverage.immune     = (currTypeImmune = sDoesntAffectCoverageByType[chosenMoveType]);
                }
                else
                {
                    coverage.resisted   &= (currTypeResisted = sNotVeryEffectiveCoverageByType[chosenMoveType]);
                    coverage.immune     &= (currTypeImmune = sDoesntAffectCoverageByType[chosenMoveType]);
                }

                // Combinations of types that, in combination, can resist all moves so far
                coverage.combinedResisted = ((coverage.combinedResisted | currTypeResisted) & ~(coverage.superEffective));
            }
            SetMonData(pokemon, MON_DATA_MOVE1 + sSlot, &chosenMove);
        }
    }
}

static void FillTankMoveset(struct Pokemon *pokemon, bool32 special)
{
    // To do
}

static void FillSetupSweeperMoveset(struct Pokemon *pokemon, bool32 special)
{
    // To do
}

static void FillWallMoveset(struct Pokemon *pokemon, bool32 special)
{
    // To do
}

static void (* const sGenerateTrainerMonMovesetByRole[])(struct Pokemon*, bool32) =
{
    [MON_ROLE_PHYSICAL_ALL_OUT_ATTACKER]            = FillAllOutAttackerMoveset,
    [MON_ROLE_SPECIAL_ALL_OUT_ATTACKER]             = FillAllOutAttackerMoveset,
    [MON_ROLE_PHYSICAL_SETUP_SWEEPER]               = FillSetupSweeperMoveset,
    [MON_ROLE_SPECIAL_SETUP_SWEEPER]                = FillSetupSweeperMoveset,
    [MON_ROLE_PHYSICAL_TANK]                        = FillTankMoveset,
    [MON_ROLE_SPECIAL_TANK]                         = FillTankMoveset,
    [MON_ROLE_PHYSICALLY_ATTACKING_PHYSICAL_WALL]   = FillWallMoveset,
    [MON_ROLE_SPECIALLY_ATTACKING_PHYSICAL_WALL]    = FillWallMoveset,
    [MON_ROLE_PHYSICALLY_ATTACKING_SPECIAL_WALL]    = FillWallMoveset,
    [MON_ROLE_SPECIALLY_ATTACKING_SPECIAL_WALL]     = FillWallMoveset,
};

static const u8 sEVSpreadsByRole[][NUM_STATS] =
{
    [MON_ROLE_PHYSICAL_ALL_OUT_ATTACKER]            = {4, 252, 0, 252, 0, 0},
    [MON_ROLE_SPECIAL_ALL_OUT_ATTACKER]             = {4, 0, 0, 252, 252, 0},
    [MON_ROLE_PHYSICAL_SETUP_SWEEPER]               = {4, 252, 0, 252, 0, 0},
    [MON_ROLE_SPECIAL_SETUP_SWEEPER]                = {4, 0, 0, 252, 252, 0},
    [MON_ROLE_PHYSICAL_TANK]                        = {252, 252, 4, 0, 0, 0},
    [MON_ROLE_SPECIAL_TANK]                         = {252, 0, 0, 0, 252, 4},
    [MON_ROLE_PHYSICALLY_ATTACKING_PHYSICAL_WALL]   = {252, 0, 252, 0, 0, 4},
    [MON_ROLE_SPECIALLY_ATTACKING_PHYSICAL_WALL]    = {252, 0, 252, 0, 0, 4},
    [MON_ROLE_PHYSICALLY_ATTACKING_SPECIAL_WALL]    = {252, 0, 4, 0, 0, 252},
    [MON_ROLE_SPECIALLY_ATTACKING_SPECIAL_WALL]     = {252, 0, 4, 0, 0, 252},
};

static const u32 sNaturesByRole[] =
{
    [MON_ROLE_PHYSICAL_ALL_OUT_ATTACKER]            = NATURE_ADAMANT,
    [MON_ROLE_SPECIAL_ALL_OUT_ATTACKER]             = NATURE_MODEST,
    [MON_ROLE_PHYSICAL_SETUP_SWEEPER]               = NATURE_JOLLY,
    [MON_ROLE_SPECIAL_SETUP_SWEEPER]                = NATURE_TIMID,
    [MON_ROLE_PHYSICAL_TANK]                        = NATURE_ADAMANT,
    [MON_ROLE_SPECIAL_TANK]                         = NATURE_MODEST,
    [MON_ROLE_PHYSICALLY_ATTACKING_PHYSICAL_WALL]   = NATURE_IMPISH,
    [MON_ROLE_SPECIALLY_ATTACKING_PHYSICAL_WALL]    = NATURE_BOLD,
    [MON_ROLE_PHYSICALLY_ATTACKING_SPECIAL_WALL]    = NATURE_CAREFUL,
    [MON_ROLE_SPECIALLY_ATTACKING_SPECIAL_WALL]     = NATURE_CALM,
};

u32 GenerateTrainerMon(struct Pokemon *pokemon, u32 trainerClass, u32 level, u32 iv)
{
    u32 personality = Random32();
    u8 i, ev, rand = Random32() % SPECIES_SUITABLE_ROLES_COUNT;
    sLevel = level;
    sSpecies = GetRandomSpeciesFromTrainerClass(trainerClass, level);
    sRole = 1; //gSpeciesInfo[sSpecies].suitableRoles[rand];
    DebugPrintf("Butterfree roles: %d, %d, %d, %d, %d", gSpeciesInfo[sSpecies].suitableRoles[0], gSpeciesInfo[sSpecies].suitableRoles[1], gSpeciesInfo[sSpecies].suitableRoles[2], gSpeciesInfo[sSpecies].suitableRoles[3], 0);

    // Adjust personality to fit nature - then create mon
    ModifyPersonalityForNature(&personality, sNaturesByRole[sRole] - 1);
    CreateMon(pokemon, sSpecies, level, iv * MAX_PER_STAT_IVS / 255, TRUE, personality, OT_ID_PRESET, 0);

    // If role is unassigned, quit (failsafe)
    if (sRole == MON_ROLE_UNASSIGNED)
        return sRole;

    // Item, ability, tbd
    sAtkAbility = 0;
    sHoldEffectAtk = 0;

    // Assign moves - second arg is whether they should be physical or special
    FillAllOutAttackerMoveset(pokemon, (sRole) % 2);
    // sGenerateTrainerMonMovesetByRole[sRole](pokemon, (sRole) % 2);

    // Assign EVs
    for (i = 0; i < NUM_STATS; i++)
    {
        // If level is under MIN_LEVEL_FOR_MAX_EVS, multiply
        // EVs per stat by lvl / MIN_LEVEL_FOR_MAX_EVS
        ev = sEVSpreadsByRole[sRole][i];
        if (level < MIN_LEVEL_FOR_MAX_EVS)
            ev = (ev * level / MIN_LEVEL_FOR_MAX_EVS);
        // DebugPrintf("%d ev: %d", i, ev);
        SetMonData(pokemon, MON_DATA_HP_EV + i, &ev);
    }

    return sRole;
}
