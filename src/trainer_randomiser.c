#include "global.h"
#include "trainer_randomiser.h"
#include "data.h"

static const u16 sRandomMonsHiker[] =
{
    RANDOM_MON_CHIMECHO_1
};

// static const u16 sRandomMonsByTrainerClass[][] =
// {
//     // TRAINER_CLASS_PKMN_TRAINER_1
//     {},
//     // TRAINER_CLASS_PKMN_TRAINER_2,
//     {},
//     // TRAINER_CLASS_HIKER,
//     {
//         RANDOM_MON_CHIMECHO_1
//     }
// };

// struct TrainerMonCustomMovesItemEVsIVs CreateRandomisedMonForTrainer(struct Trainer *trainer)
// {
//     u8 heldItem, abilityNum, randomNum = CreateRandomNumberForTrainer(trainer);
//     struct RandomMon randomMon = gRandomMons[GetRandomMonForTrainer(trainer, randomNum)];
//     struct RandomMonSet randomMonSet = randomMon.sets[randomNum % randomMon.setCount];

//     // Create the struct
//     struct TrainerMonCustomMovesItemEVsIvs result = {
//         .species = randomMon.species,
//         .heldItem = randomMonSet.items[randomNum & 0x80],
//         .evs = randomMonSet.evs,
//         .moves = {
//             randomMonSet.moves[0][randomNum & 0x40],
//             randomMonSet.moves[0][randomNum & 0x20],
//             randomMonSet.moves[0][randomNum & 0x10],
//             randomMonSet.moves[0][randomNum & 0x8]
//         },
//         .nature = randomMonSet.natures[randomNum & 0x4],
//         .abilityNum = randomMonSet.abilityNums[randomNum & 0x2],
//         .ivs = randomMonSet.ivs,
//     };

//     return result;
// }

u16 GetRandomMonForTrainer(u16 trainerNum, u8 randomNum)
{
    u16 randomMonId;
    bool8 passed = FALSE;

    // Return an id from the class definition
    switch (gTrainers[trainerNum].trainerClass)
    {
        case TRAINER_CLASS_HIKER:
            randomMonId = sRandomMonsHiker[randomNum % ARRAY_COUNT(sRandomMonsHiker)];
            break;
    }

    // Make sure that we're below the max level for the selected set
    while (!passed)
    {
        if (gSaveBlock1Ptr->globalLevel > gRandomMons[randomMonId].maxLevel)
            randomMonId = gRandomMons[randomMonId].maxLevelReplace;
        else
            passed = TRUE;
    }

    return randomMonId;
}

u8 CreateRandomNumberForTrainer(u16 trainerNum)
{
    u32 largeNum = 0;
    u8 i;

    // Prepare a large number from the trainer's name (requires trainers to have unique names, but oh, well)
    for (i = 0; i < TRAINER_NAME_LENGTH; i++)
    {
        largeNum += gTrainers[trainerNum].trainerName[i] * (i + 1);
    }

    // Multiply by class and xor with player id
    largeNum *= (gTrainers[trainerNum].trainerClass + 1);
    largeNum ^= T1_READ_32(gSaveBlock2Ptr->playerTrainerId);

    // Break down into a u8 - (1st byte | 4th byte) & (2nd byte | 3rd byte)
    return (T1_READ_8((u8*)largeNum) | T1_READ_8((u8*)largeNum + 3)) & (T1_READ_8((u8*)largeNum + 1) | T1_READ_8((u8*)largeNum + 2));
}

