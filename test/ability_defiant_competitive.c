#include "global.h"
#include "test_battle.h"

SINGLE_BATTLE_TEST("Status moves activate Defiant/Competitive")
{
    PARAMETRIZE {}
    GIVEN {
        ASSUME(gBattleMoves[MOVE_CHARM].effect == EFFECT_ATTACK_DOWN_2);
        ASSUME(gBattleMoves[MOVE_SCARY_FACE].effect == EFFECT_SPEED_DOWN_2);
        PLAYER(SPECIES_WIGGLYTUFF) { Ability(ABILITY_COMPETITIVE); };
        OPPONENT(SPECIES_PRIMEAPE) { Ability(ABILITY_DEFIANT); };
    } WHEN {
        TURN { MOVE(opponent, MOVE_SCARY_FACE); }
        TURN { MOVE(player, MOVE_CHARM); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_COMPETITIVE);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, player);
        MESSAGE("Wigglytuff's Competitive sharply raised its Sp. Atk!");
        ABILITY_POPUP(opponent, ABILITY_DEFIANT);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponent);
        MESSAGE("Foe Primeape's Defiant sharply raised its Attack!");
    } FINALLY {
        EXPECT_EQ(player->statStages[STAT_SPATK], DEFAULT_STAT_STAGE + 2);
        EXPECT_EQ(opponent->statStages[STAT_ATK], DEFAULT_STAT_STAGE);
    }
}

SINGLE_BATTLE_TEST("Multiple stat drop status moves activate Defiant/Competitive multiple times")
{
    PARAMETRIZE {}
    GIVEN {
        ASSUME(gBattleMoves[MOVE_NOBLE_ROAR].effect == EFFECT_NOBLE_ROAR);
        ASSUME(gBattleMoves[MOVE_TICKLE].effect == EFFECT_TICKLE);
        PLAYER(SPECIES_WIGGLYTUFF) { Ability(ABILITY_COMPETITIVE); };
        OPPONENT(SPECIES_PRIMEAPE) { Ability(ABILITY_DEFIANT); };
    } WHEN {
        TURN { MOVE(opponent, MOVE_NOBLE_ROAR); }
        TURN { MOVE(player, MOVE_TICKLE); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_COMPETITIVE);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, player);
        MESSAGE("Wigglytuff's Competitive sharply raised its Sp. Atk!");
        ABILITY_POPUP(player, ABILITY_COMPETITIVE);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, player);
        MESSAGE("Wigglytuff's Competitive sharply raised its Sp. Atk!");
        ABILITY_POPUP(opponent, ABILITY_DEFIANT);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponent);
        MESSAGE("Foe Primeape's Defiant sharply raised its Attack!");
        ABILITY_POPUP(opponent, ABILITY_DEFIANT);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponent);
        MESSAGE("Foe Primeape's Defiant sharply raised its Attack!");
    } FINALLY {
        EXPECT_EQ(player->statStages[STAT_SPATK], DEFAULT_STAT_STAGE + 3);
        EXPECT_EQ(opponent->statStages[STAT_ATK], player->statStages[STAT_SPATK]);
    }
}

SINGLE_BATTLE_TEST("Attacking moves activate Defiant/Competitive")
{
    PARAMETRIZE {}
    GIVEN {
        ASSUME(gBattleMoves[MOVE_ICY_WIND].effect == EFFECT_SPEED_DOWN_HIT);
        ASSUME(gBattleMoves[MOVE_ACID_SPRAY].effect == EFFECT_SPECIAL_DEFENSE_DOWN_HIT_2);
        PLAYER(SPECIES_WIGGLYTUFF) { Ability(ABILITY_COMPETITIVE); };
        OPPONENT(SPECIES_PRIMEAPE) { Ability(ABILITY_DEFIANT); };
    } WHEN {
        TURN { MOVE(opponent, MOVE_ICY_WIND); }
        TURN { MOVE(player, MOVE_ACID_SPRAY); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_COMPETITIVE);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, player);
        MESSAGE("Wigglytuff's Competitive sharply raised its Sp. Atk!");
        ABILITY_POPUP(opponent, ABILITY_DEFIANT);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponent);
        MESSAGE("Foe Primeape's Defiant sharply raised its Attack!");
    } FINALLY {
        EXPECT_EQ(player->statStages[STAT_SPATK], DEFAULT_STAT_STAGE + 2);
        EXPECT_EQ(opponent->statStages[STAT_ATK], DEFAULT_STAT_STAGE + 2);
    }
}

SINGLE_BATTLE_TEST("Self-stat-dropping moves don't trigger Defiant/Competitive")
{
    GIVEN {
        ASSUME(gBattleMoves[MOVE_HAMMER_ARM].effect == EFFECT_HAMMER_ARM);
        ASSUME(gBattleMoves[MOVE_OVERHEAT].effect == EFFECT_OVERHEAT);
        PLAYER(SPECIES_WIGGLYTUFF) { Ability(ABILITY_COMPETITIVE); };
        OPPONENT(SPECIES_PRIMEAPE) { Ability(ABILITY_DEFIANT); };
    } WHEN {
        TURN { MOVE(opponent, MOVE_HAMMER_ARM); }
        TURN { MOVE(player, MOVE_OVERHEAT); }
    } SCENE {
        NONE_OF {
            ABILITY_POPUP(opponent, ABILITY_DEFIANT);
            MESSAGE("Foe Primeape's Defiant sharply raised its Attack!");
            ABILITY_POPUP(player, ABILITY_COMPETITIVE);
            MESSAGE("Wigglytuff's Competitive sharply raised its Sp. Atk!");
        }
    }
}
