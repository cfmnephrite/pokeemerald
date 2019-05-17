#include "global.h"
#include "event_data.h"
#include "pokemon.h"
#include "random.h"
#include "roamer.h"
#include "constants/maps.h"
#include "constants/species.h"
#include "pokemon_storage_system.h"

enum
{
    MAP_GRP = 0, // map group
    MAP_NUM = 1, // map number
};

EWRAM_DATA static u8 sLocationHistory[3][2] = {0};
EWRAM_DATA static u8 sRoamerLocation[2] = {0};

static const u8 sRoamerLocations[][6] =
{
    { MAP_NUM(ROUTE110), MAP_NUM(ROUTE111), MAP_NUM(ROUTE117), MAP_NUM(ROUTE118), MAP_NUM(ROUTE134), 0xFF },
    { MAP_NUM(ROUTE111), MAP_NUM(ROUTE110), MAP_NUM(ROUTE117), MAP_NUM(ROUTE118), 0xFF, 0xFF },
    { MAP_NUM(ROUTE117), MAP_NUM(ROUTE111), MAP_NUM(ROUTE110), MAP_NUM(ROUTE118), 0xFF, 0xFF },
    { MAP_NUM(ROUTE118), MAP_NUM(ROUTE117), MAP_NUM(ROUTE110), MAP_NUM(ROUTE111), MAP_NUM(ROUTE119), MAP_NUM(ROUTE123) },
    { MAP_NUM(ROUTE119), MAP_NUM(ROUTE118), MAP_NUM(ROUTE120), 0xFF, 0xFF, 0xFF },
    { MAP_NUM(ROUTE120), MAP_NUM(ROUTE119), MAP_NUM(ROUTE121), 0xFF, 0xFF, 0xFF },
    { MAP_NUM(ROUTE121), MAP_NUM(ROUTE120), MAP_NUM(ROUTE122), MAP_NUM(ROUTE123), 0xFF, 0xFF },
    { MAP_NUM(ROUTE122), MAP_NUM(ROUTE121), MAP_NUM(ROUTE123), 0xFF, 0xFF, 0xFF },
    { MAP_NUM(ROUTE123), MAP_NUM(ROUTE122), MAP_NUM(ROUTE118), 0xFF, 0xFF, 0xFF },
    { MAP_NUM(ROUTE124), MAP_NUM(ROUTE121), MAP_NUM(ROUTE125), MAP_NUM(ROUTE126), 0xFF, 0xFF },
    { MAP_NUM(ROUTE125), MAP_NUM(ROUTE124), MAP_NUM(ROUTE127), 0xFF, 0xFF, 0xFF },
    { MAP_NUM(ROUTE126), MAP_NUM(ROUTE124), MAP_NUM(ROUTE127), 0xFF, 0xFF, 0xFF },
    { MAP_NUM(ROUTE127), MAP_NUM(ROUTE125), MAP_NUM(ROUTE126), MAP_NUM(ROUTE128), 0xFF, 0xFF },
    { MAP_NUM(ROUTE128), MAP_NUM(ROUTE127), MAP_NUM(ROUTE129), 0xFF, 0xFF, 0xFF },
    { MAP_NUM(ROUTE129), MAP_NUM(ROUTE128), MAP_NUM(ROUTE130), 0xFF, 0xFF, 0xFF },
    { MAP_NUM(ROUTE130), MAP_NUM(ROUTE129), MAP_NUM(ROUTE131), 0xFF, 0xFF, 0xFF },
    { MAP_NUM(ROUTE131), MAP_NUM(ROUTE130), MAP_NUM(ROUTE132), 0xFF, 0xFF, 0xFF },
    { MAP_NUM(ROUTE132), MAP_NUM(ROUTE131), MAP_NUM(ROUTE133), 0xFF, 0xFF, 0xFF },
    { MAP_NUM(ROUTE133), MAP_NUM(ROUTE132), MAP_NUM(ROUTE134), 0xFF, 0xFF, 0xFF },
    { MAP_NUM(ROUTE134), MAP_NUM(ROUTE133), MAP_NUM(ROUTE110), 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF },
};

void ClearRoamerData(void)
{
    memset(&gPokemonStoragePtr->roamer, 0, sizeof(struct Roamer));
    (&gPokemonStoragePtr->roamer)->species = SPECIES_LATIAS;
}

void ClearRoamerLocationData(void)
{
    u8 i;

    for (i = 0; i < 3; i++)
    {
        sLocationHistory[i][MAP_GRP] = 0;
        sLocationHistory[i][MAP_NUM] = 0;
    }

    sRoamerLocation[MAP_GRP] = 0;
    sRoamerLocation[MAP_NUM] = 0;
}

static void CreateInitialRoamerMon(bool16 createLatios)
{
    if (!createLatios)
        (&gPokemonStoragePtr->roamer)->species = SPECIES_LATIAS;
    else
        (&gPokemonStoragePtr->roamer)->species = SPECIES_LATIOS;

    CreateMon(&gEnemyParty[0], (&gPokemonStoragePtr->roamer)->species, 40, 0x20, 0, 0, 0, 0);
    (&gPokemonStoragePtr->roamer)->level = 40;
    (&gPokemonStoragePtr->roamer)->status = 0;
    (&gPokemonStoragePtr->roamer)->active = TRUE;
    (&gPokemonStoragePtr->roamer)->ivs = GetMonData(&gEnemyParty[0], MON_DATA_IVS);
    (&gPokemonStoragePtr->roamer)->personality = GetMonData(&gEnemyParty[0], MON_DATA_PERSONALITY);
    (&gPokemonStoragePtr->roamer)->hp = GetMonData(&gEnemyParty[0], MON_DATA_MAX_HP);
    (&gPokemonStoragePtr->roamer)->cool = GetMonData(&gEnemyParty[0], MON_DATA_COOL);
    (&gPokemonStoragePtr->roamer)->beauty = GetMonData(&gEnemyParty[0], MON_DATA_BEAUTY);
    (&gPokemonStoragePtr->roamer)->cute = GetMonData(&gEnemyParty[0], MON_DATA_CUTE);
    (&gPokemonStoragePtr->roamer)->smart = GetMonData(&gEnemyParty[0], MON_DATA_SMART);
    (&gPokemonStoragePtr->roamer)->tough = GetMonData(&gEnemyParty[0], MON_DATA_TOUGH);
    sRoamerLocation[MAP_GRP] = 0;
    sRoamerLocation[MAP_NUM] = sRoamerLocations[Random() % (ARRAY_COUNT(sRoamerLocations) - 1)][0];
}

void InitRoamer(void)
{
    ClearRoamerData();
    ClearRoamerLocationData();
    CreateInitialRoamerMon(gSpecialVar_0x8004);
}

void UpdateLocationHistoryForRoamer(void)
{
    sLocationHistory[2][MAP_GRP] = sLocationHistory[1][MAP_GRP];
    sLocationHistory[2][MAP_NUM] = sLocationHistory[1][MAP_NUM];

    sLocationHistory[1][MAP_GRP] = sLocationHistory[0][MAP_GRP];
    sLocationHistory[1][MAP_NUM] = sLocationHistory[0][MAP_NUM];

    sLocationHistory[0][MAP_GRP] = gSaveBlockPtr->location.mapGroup;
    sLocationHistory[0][MAP_NUM] = gSaveBlockPtr->location.mapNum;
}

void RoamerMoveToOtherLocationSet(void)
{
    u8 mapNum = 0;
    struct Roamer *roamer = &gPokemonStoragePtr->roamer;

    if (!roamer->active)
        return;

    sRoamerLocation[MAP_GRP] = 0;

    while (1)
    {
        mapNum = sRoamerLocations[Random() % (ARRAY_COUNT(sRoamerLocations) - 1)][0];
        if (sRoamerLocation[MAP_NUM] != mapNum)
        {
            sRoamerLocation[MAP_NUM] = mapNum;
            return;
        }
    }
}

void RoamerMove(void)
{
    u8 locSet = 0;

    if ((Random() % 16) == 0)
    {
        RoamerMoveToOtherLocationSet();
    }
    else
    {
        struct Roamer *roamer = &gPokemonStoragePtr->roamer;

        if (!roamer->active)
            return;

        while (locSet < (ARRAY_COUNT(sRoamerLocations) - 1))
        {
            if (sRoamerLocation[MAP_NUM] == sRoamerLocations[locSet][0])
            {
                u8 mapNum;
                while (1)
                {
                    mapNum = sRoamerLocations[locSet][(Random() % 5) + 1];
                    if (!(sLocationHistory[2][MAP_GRP] == 0 && sLocationHistory[2][MAP_NUM] == mapNum) && mapNum != 0xFF)
                        break;
                }
                sRoamerLocation[MAP_NUM] = mapNum;
                return;
            }
            locSet++;
        }
    }
}

bool8 IsRoamerAt(u8 mapGroup, u8 mapNum)
{
    struct Roamer *roamer = &gPokemonStoragePtr->roamer;

    if (roamer->active && mapGroup == sRoamerLocation[MAP_GRP] && mapNum == sRoamerLocation[MAP_NUM])
        return TRUE;
    else
        return FALSE;
}

void CreateRoamerMonInstance(void)
{
    struct Pokemon *mon;
    struct Roamer *roamer;

    mon = &gEnemyParty[0];
    ZeroEnemyPartyMons();
    roamer = &gPokemonStoragePtr->roamer;
    CreateMonWithIVsPersonality(mon, roamer->species, roamer->level, roamer->ivs, roamer->personality);
    SetMonData(mon, MON_DATA_STATUS, &gPokemonStoragePtr->roamer.status);
    SetMonData(mon, MON_DATA_HP, &gPokemonStoragePtr->roamer.hp);
    SetMonData(mon, MON_DATA_COOL, &gPokemonStoragePtr->roamer.cool);
    SetMonData(mon, MON_DATA_BEAUTY, &gPokemonStoragePtr->roamer.beauty);
    SetMonData(mon, MON_DATA_CUTE, &gPokemonStoragePtr->roamer.cute);
    SetMonData(mon, MON_DATA_SMART, &gPokemonStoragePtr->roamer.smart);
    SetMonData(mon, MON_DATA_TOUGH, &gPokemonStoragePtr->roamer.tough);
}

bool8 TryStartRoamerEncounter(void)
{
    if (IsRoamerAt(gSaveBlockPtr->location.mapGroup, gSaveBlockPtr->location.mapNum) == TRUE && (Random() % 4) == 0)
    {
        CreateRoamerMonInstance();
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

void UpdateRoamerHPStatus(struct Pokemon *mon)
{
    (&gPokemonStoragePtr->roamer)->hp = GetMonData(mon, MON_DATA_HP);
    (&gPokemonStoragePtr->roamer)->status = GetMonData(mon, MON_DATA_STATUS);

    RoamerMoveToOtherLocationSet();
}

void SetRoamerInactive(void)
{
    struct Roamer *roamer = &gPokemonStoragePtr->roamer;
    roamer->active = FALSE;
}

void GetRoamerLocation(u8 *mapGroup, u8 *mapNum)
{
    *mapGroup = sRoamerLocation[MAP_GRP];
    *mapNum = sRoamerLocation[MAP_NUM];
}
