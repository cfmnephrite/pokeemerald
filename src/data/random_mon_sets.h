#include "constants/items.h"
#include "constants/moves.h"
#include "constants/abilities.h"
#include "constants/pokemon.h"
static const struct RandomMonSet sChimecho_1_1 =
{
    .natures = {NATURE_MODEST, NATURE_TIMID},
    .abilityNums = {ABILITY_SLOT_HIDDEN, ABILITY_SLOT_HIDDEN}, // MAGIC BOUNCE
    .items = {ITEM_COLBUR_BERRY, ITEM_NONE},
    .moves = {
        {MOVE_PSYBEAM, MOVE_CONFUSION},
        {MOVE_WISH, MOVE_RECOVER},
        {MOVE_CALM_MIND, MOVE_CHARGE_BEAM},
        {MOVE_SHADOW_BALL, MOVE_DAZZLING_GLEAM}
    },
    .evs = {252, 0, 0, 252, 0, 4},
    .ivs = {31, 0, 31, 31, 31, 31}
};

static const struct RandomMonSet sChimecho_1_2 =
{
    .natures = {NATURE_BOLD, NATURE_CALM},
    .abilityNums = {ABILITY_SLOT_1, ABILITY_SLOT_HIDDEN}, // SOUNDPROOF, MAGIC BOUNCE
    .items = {ITEM_LEFTOVERS, ITEM_NONE},
    .moves = {
        {MOVE_PSYBEAM, MOVE_PSYBEAM},
        {MOVE_RECOVER, MOVE_RECOVER},
        {MOVE_COSMIC_POWER, MOVE_CALM_MIND},
        {MOVE_HEAL_BELL, MOVE_STORED_POWER}
    },
    .evs = {252, 0, 128, 0, 128, 0},
    .ivs = {31, 0, 31, 31, 31, 31}
};