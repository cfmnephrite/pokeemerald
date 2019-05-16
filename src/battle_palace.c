#include "global.h"
#include "event_data.h"
#include "battle_setup.h"
#include "overworld.h"
#include "random.h"
#include "battle_tower.h"
#include "frontier_util.h"
#include "item.h"
#include "string_util.h"
#include "constants/items.h"

// This file's functions.
static void sub_8195980(void);
static void sub_8195A38(void);
static void sub_8195AE4(void);
static void sub_8195BB0(void);
static void sub_8195C20(void);
static void sub_8195C50(void);
static void sub_8195C7C(void);
static void sub_8195CE4(void);
static void sub_8195D28(void);
static void sub_8195DB8(void);

// Const rom data.
static void (* const sBattlePalaceFunctions[])(void) =
{
    sub_8195980,
    sub_8195A38,
    sub_8195AE4,
    sub_8195BB0,
    sub_8195C20,
    sub_8195C50,
    sub_8195C7C,
    sub_8195CE4,
    sub_8195D28,
    sub_8195DB8,
};

static const u16 gUnknown_0860DE78[] = {ITEM_HP_UP, ITEM_PROTEIN, ITEM_IRON, ITEM_CALCIUM, ITEM_CARBOS, ITEM_ZINC};
static const u16 gUnknown_0860DE84[] = {ITEM_BRIGHT_POWDER, ITEM_WHITE_HERB, ITEM_QUICK_CLAW, ITEM_LEFTOVERS, ITEM_MENTAL_HERB, ITEM_KINGS_ROCK, ITEM_FOCUS_BAND, ITEM_SCOPE_LENS, ITEM_CHOICE_BAND};

static const u32 gUnknown_0860DE98[][2] =
{
    {0x10, 0x20},
    {0x400000, 0x800000},
};

static const u32 gUnknown_0860DEA8[][2] =
{
    {~0x10, ~0x20},
    {~0x400000, ~0x800000},
};

// code
void CallBattlePalaceFunction(void)
{
    sBattlePalaceFunctions[gSpecialVar_0x8004]();
}

static void sub_8195980(void)
{
    u32 lvlMode = gSaveBlockPtr->frontier.lvlMode;
    u32 battleMode = VarGet(VAR_FRONTIER_BATTLE_MODE);

    gSaveBlockPtr->frontier.field_CA8 = 0;
    gSaveBlockPtr->frontier.curChallengeBattleNum = 0;
    gSaveBlockPtr->frontier.field_CA9_a = 0;
    gSaveBlockPtr->frontier.field_CA9_b = 0;
    if (!(gSaveBlockPtr->frontier.field_CDC & gUnknown_0860DE98[battleMode][lvlMode]))
        gSaveBlockPtr->frontier.palaceWinStreaks[battleMode][lvlMode] = 0;

    SetDynamicWarp(0, gSaveBlockPtr->location.mapGroup, gSaveBlockPtr->location.mapNum, -1);
    gTrainerBattleOpponent_A = 0;
}

static void sub_8195A38(void)
{
    u32 lvlMode = gSaveBlockPtr->frontier.lvlMode;
    u32 battleMode = VarGet(VAR_FRONTIER_BATTLE_MODE);

    switch (gSpecialVar_0x8005)
    {
    case 0:
        gSpecialVar_Result = gSaveBlockPtr->frontier.field_DC6;
        break;
    case 1:
        gSpecialVar_Result = gSaveBlockPtr->frontier.palaceWinStreaks[battleMode][lvlMode];
        break;
    case 2:
        gSpecialVar_Result = ((gSaveBlockPtr->frontier.field_CDC & gUnknown_0860DE98[battleMode][lvlMode]) != 0);
        break;
    }
}

static void sub_8195AE4(void)
{
    u32 lvlMode = gSaveBlockPtr->frontier.lvlMode;
    u32 battleMode = VarGet(VAR_FRONTIER_BATTLE_MODE);

    switch (gSpecialVar_0x8005)
    {
    case 0:
        gSaveBlockPtr->frontier.field_DC6 = gSpecialVar_0x8006;
        break;
    case 1:
        gSaveBlockPtr->frontier.palaceWinStreaks[battleMode][lvlMode] = gSpecialVar_0x8006;
        break;
    case 2:
        if (gSpecialVar_0x8006)
            gSaveBlockPtr->frontier.field_CDC |= gUnknown_0860DE98[battleMode][lvlMode];
        else
            gSaveBlockPtr->frontier.field_CDC &= gUnknown_0860DEA8[battleMode][lvlMode];
        break;
    }
}

static void sub_8195BB0(void)
{
    u32 battleMode = VarGet(VAR_FRONTIER_BATTLE_MODE);
    u32 lvlMode = gSaveBlockPtr->frontier.lvlMode;

    if (gSaveBlockPtr->frontier.palaceWinStreaks[battleMode][lvlMode] < 50)
        gSpecialVar_Result = Random() % 3;
    else if (gSaveBlockPtr->frontier.palaceWinStreaks[battleMode][lvlMode] < 99)
        gSpecialVar_Result = 3;
    else
        gSpecialVar_Result = 4;
}

static void sub_8195C20(void)
{
    gTrainerBattleOpponent_A = 5 *(Random() % 255) / 64u;
    SetBattleFacilityTrainerGfxId(gTrainerBattleOpponent_A, 0);
}

static void sub_8195C50(void)
{
    if (gTrainerBattleOpponent_A < 300)
        FrontierSpeechToString(gFacilityTrainers[gTrainerBattleOpponent_A].speechBefore);
}

static void sub_8195C7C(void)
{
    u8 lvlMode = gSaveBlockPtr->frontier.lvlMode;
    u8 battleMode = VarGet(VAR_FRONTIER_BATTLE_MODE);

    if (gSaveBlockPtr->frontier.palaceWinStreaks[battleMode][lvlMode] < 9999)
    {
        gSaveBlockPtr->frontier.palaceWinStreaks[battleMode][lvlMode]++;

        // Whatever GF planned to do here, they messed up big time.
        if (gSaveBlockPtr->frontier.palaceWinStreaks[battleMode][(lvlMode > gSaveBlockPtr->frontier.palaceRecordWinStreaks[battleMode][lvlMode]) ? 1 : 0])
            gSaveBlockPtr->frontier.palaceRecordWinStreaks[battleMode][lvlMode] = gSaveBlockPtr->frontier.palaceWinStreaks[battleMode][lvlMode];
    }
}

static void sub_8195CE4(void)
{
    gSaveBlockPtr->frontier.field_CA8 = gSpecialVar_0x8005;
    VarSet(VAR_TEMP_0, 0);
    gSaveBlockPtr->frontier.field_CA9_a = 1;
    sub_81A4C30();
}

static void sub_8195D28(void)
{
    u32 battleMode = VarGet(VAR_FRONTIER_BATTLE_MODE);
    u32 lvlMode = gSaveBlockPtr->frontier.lvlMode;

    if (gSaveBlockPtr->frontier.palaceWinStreaks[battleMode][lvlMode] > 41)
        gSaveBlockPtr->frontier.field_DC6 = gUnknown_0860DE84[Random() % ARRAY_COUNT(gUnknown_0860DE84)];
    else
        gSaveBlockPtr->frontier.field_DC6 = gUnknown_0860DE78[Random() % ARRAY_COUNT(gUnknown_0860DE78)];
}

static void sub_8195DB8(void)
{
    if (AddBagItem(gSaveBlockPtr->frontier.field_DC6, 1) == TRUE)
    {
        CopyItemName(gSaveBlockPtr->frontier.field_DC6, gStringVar1);
        gSaveBlockPtr->frontier.field_DC6 = 0;
        gSpecialVar_Result = TRUE;
    }
    else
    {
        gSpecialVar_Result = FALSE;
    }
}
