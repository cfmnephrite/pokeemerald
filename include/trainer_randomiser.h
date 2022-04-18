#ifndef GUARD_TRAINER_RANDOMISER_H
#define GUARD_TRAINER_RANDOMISER_H

#include "global.h"
#include "data.h"
#include "constants/trainers.h"

enum {
    RANDOM_MON_CHIMECHO_1,
    RANDOM_MON_CHIMECHO_2,
};

enum {
    ABILITY_SLOT_0,
    ABILITY_SLOT_1,
    ABILITY_SLOT_HIDDEN
};

struct RandomMonSet
{
    // Possible natures and abilities (two each)
    u8 natures[2];
    u8 abilityNums[2];

    // Two possible items per set
    u16 items[2];

    // Two possible moves for each slot
    u16 moves[4][2];

    // EVs
    u8 evs[NUM_STATS];

    // IVs
    u8 ivs[NUM_STATS];
};

#define RANDOM_MON_MAX_SETS     4

struct RandomMon
{
    u16 species;
    u8 flags; // idk right now
    u8 maxLevel;
    u16 maxLevelReplace; // if above the "maxLevel", replace with this mon
    u8 happiness;
    u8 setCount;
    const struct RandomMonSet *sets[RANDOM_MON_MAX_SETS];
};

extern const struct RandomMon gRandomMons[];
struct TrainerMonCustomMovesItemEVsIVs CreateRandomisedMonForTrainer(struct Trainer *trainer);
u16 GetRandomMonForTrainer(u16 trainerNum, u8 randomNum);
u8 CreateRandomNumberForTrainer(u16 trainerNum);

#endif //GUARD_TRAINER_RANDOMISER_H