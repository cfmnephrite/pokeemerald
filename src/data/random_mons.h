#include "trainer_randomiser.h"
#include "random_mon_sets.h"
const struct RandomMon gRandomMons[] =
{
    [RANDOM_MON_CHIMECHO_1] = {
        .species = SPECIES_CHIMECHO,
        .flags = 0,
        .maxLevel = 30,
        .maxLevelReplace = RANDOM_MON_CHIMECHO_2,
        .happiness = MAX_FRIENDSHIP,
        .setCount = 2,
        .sets = {&sChimecho_1_1, &sChimecho_1_2}
    },
    [RANDOM_MON_CHIMECHO_2] = {
        .species = SPECIES_CHIMECHO,
        .flags = 0,
        .maxLevel = MAX_LEVEL,
        .maxLevelReplace = 0,
        .happiness = MAX_FRIENDSHIP,
        .setCount = 2,
        .sets = {&sChimecho_1_1, &sChimecho_1_2}
    }
};