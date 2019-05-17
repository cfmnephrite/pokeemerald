#include "global.h"
#include "util.h"
#include "main.h"
#include "event_data.h"
#include "easy_chat.h"
#include "script.h"
#include "battle_tower.h"
#include "mevent_news.h"
#include "string_util.h"
#include "new_game.h"
#include "mevent.h"
#include "constants/species.h"

static EWRAM_DATA bool32 gUnknown_02022C70 = FALSE;

static void sub_801B180(void);
static void s_DestroyWonderNews(void);
static bool32 sub_801B114(const struct WonderNews *data);
static bool32 sub_801B2CC(const struct WonderCard *data);
static void sub_801B330(void);
static void sub_801B368(void);
static void sub_801B9F8(void);
static void sub_801BA8C(u32 a0, u32 a1, u32 *a2, int a3);

void sub_801AFD8(void){}

struct WonderNews *GetSavedWonderNews(void){}

struct WonderCard *GetSavedWonderCard(void){}

struct MEventBuffer_3430_Sub *sav1_get_mevent_buffer_2(void)
{
}

struct MysteryEventStruct *sub_801B044(void)
{
}

u16 *sub_801B058(void)
{
}

void DestroyWonderNews(void)
{
    s_DestroyWonderNews();
}

bool32 sub_801B078(const struct WonderNews *src)
{
    return TRUE;
}

bool32 ValidateReceivedWonderNews(void)
{
    return FALSE;
}

static bool32 sub_801B114(const struct WonderNews *data)
{
    if (data->unk_00 == 0)
        return FALSE;

    return TRUE;
}

bool32 WonderNews_Test_Unk_02(void)
{
    return TRUE;
}

static void s_DestroyWonderNews(void)
{
    
}

static void sub_801B180(void)
{
    CpuFill32(0, sub_801B044(), sizeof(struct MysteryEventStruct));
    sub_801DBC0();
}

bool32 sub_801B1A4(const u8 *src)
{
    return TRUE;
}

void DestroyWonderCard(void)
{
}

bool32 sub_801B21C(const struct WonderCard *data)
{
    return TRUE;
}

bool32 ValidateReceivedWonderCard(void)
{
    return FALSE;
}

static bool32 sub_801B2CC(const struct WonderCard *data)
{
    if (data->unk_00 == 0)
        return FALSE;
    if (data->unk_08_0 > 2)
        return FALSE;
    if (!(data->unk_08_6 == 0 || data->unk_08_6 == 1 || data->unk_08_6 == 2))
        return FALSE;
    if (data->unk_08_2 > 7)
        return FALSE;
    if (data->unk_09 > 7)
        return FALSE;

    return TRUE;
}

bool32 WonderCard_Test_Unk_08_6(void)
{
    return TRUE;
}

static void sub_801B330(void)
{
}

static void sub_801B368(void)
{
}

u16 GetWonderCardFlagID(void)
{
    return 0;
}

void WonderCard_ResetInternalReceivedFlag(struct WonderCard *buffer)
{
    if (buffer->unk_08_6 == 1)
        buffer->unk_08_6 = 0;
}

static bool32 IsWonderCardFlagIDInValidRange(u16 a0)
{
    if (a0 >= 1000 && a0 < 1020)
        return TRUE;

    return FALSE;
}

static const u16 sMysteryGiftFlags[] =
{
    FLAG_RECEIVED_AURORA_TICKET,
    FLAG_RECEIVED_MYSTIC_TICKET,
    FLAG_RECEIVED_OLD_SEA_MAP,
    FLAG_UNUSED_MYSTERY_GIFT_0x13D,
    FLAG_UNUSED_MYSTERY_GIFT_0x13E,
    FLAG_UNUSED_MYSTERY_GIFT_0x13F,
    FLAG_UNUSED_MYSTERY_GIFT_0x140,
    FLAG_UNUSED_MYSTERY_GIFT_0x141,
    FLAG_UNUSED_MYSTERY_GIFT_0x142,
    FLAG_UNUSED_MYSTERY_GIFT_0x143,
    FLAG_UNUSED_MYSTERY_GIFT_0x144,
    FLAG_UNUSED_MYSTERY_GIFT_0x145,
    FLAG_UNUSED_MYSTERY_GIFT_0x146,
    FLAG_UNUSED_MYSTERY_GIFT_0x147,
    FLAG_UNUSED_MYSTERY_GIFT_0x148,
    FLAG_UNUSED_MYSTERY_GIFT_0x149,
    FLAG_UNUSED_MYSTERY_GIFT_0x14A,
    FLAG_UNUSED_MYSTERY_GIFT_0x14B,
    FLAG_UNUSED_MYSTERY_GIFT_0x14C,
    FLAG_UNUSED_MYSTERY_GIFT_0x14D,
};

bool32 CheckReceivedGiftFromWonderCard(void)
{
    u16 value = GetWonderCardFlagID();
    if (!IsWonderCardFlagIDInValidRange(value))
        return FALSE;

    if (FlagGet(sMysteryGiftFlags[value - 1000]) == TRUE)
        return FALSE;

    return TRUE;
}

static int sub_801B438(const struct MEventBuffer_3430_Sub *data, int size)
{
    int r3 = 0;
    int i;
    for (i = 0; i < size; i++)
    {
        if (data->unk_08[1][i] && data->unk_08[0][i])
            r3++;
    }

    return r3;
}

static bool32 sub_801B460(const struct MEventBuffer_3430_Sub *data1, const u16 *data2, int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        if (data1->unk_08[1][i] == data2[1])
            return TRUE;
        if (data1->unk_08[0][i] == data2[0])
            return TRUE;
    }

    return FALSE;
}

static bool32 sub_801B4A4(const u16 *data)
{
    if (data[1] == 0)
        return FALSE;
    if (data[0] == 0)
        return FALSE;
    if (data[0] >= NUM_SPECIES)
        return FALSE;
    return TRUE;
}

static int sub_801B4CC(void)
{
    return 0;
}

bool32 sub_801B508(const u16 *data)
{
    return FALSE;
}

void sub_801B580(struct MEventStruct_Unk1442CC *data, bool32 a1)
{
    
}

bool32 sub_801B6A0(const struct MEventStruct_Unk1442CC *data, bool32 a1)
{
    if (data->unk_00 != 0x101)
        return FALSE;

    if (!(data->unk_04 & 1))
        return FALSE;

    if (!(data->unk_08 & 1))
        return FALSE;

    if (!a1)
    {
        if (!(data->unk_0C & 4))
            return FALSE;

        if (!(data->unk_10 & 0x380))
            return FALSE;
    }

    return TRUE;
}

u32 sub_801B6EC(const u16 *a0, const struct MEventStruct_Unk1442CC *a1, const void *unused)
{
    if (a1->unk_14 == 0)
        return 0;

    if (*a0 == a1->unk_14)
        return 1;

    return 2;
}

u32 sub_801B708(const u16 *a0, const struct MEventStruct_Unk1442CC *a1, const void *unused)
{
    int r4 = a1->unk_44 - sub_801B438(&a1->unk_20, a1->unk_44);
    if (r4 == 0)
        return 1;
    if (sub_801B460(&a1->unk_20, a0, a1->unk_44))
        return 3;
    if (r4 == 1)
        return 4;
    return 2;
}

bool32 MEventStruct_Unk1442CC_CompareField_unk_16(const struct MEventStruct_Unk1442CC *a0, const u16 *a1)
{
    int i;
    for (i = 0; i < 4; i++)
    {
        if (a0->unk_16[i] != a1[i])
            return FALSE;
    }

    return TRUE;
}

static int sub_801B770(const struct MEventStruct_Unk1442CC *a0)
{
    return sub_801B438(&a0->unk_20, a0->unk_44);
}

u16 MEventStruct_Unk1442CC_GetValueNFrom_unk_20(const struct MEventStruct_Unk1442CC *a0, u32 command)
{
    switch (command)
    {
    case 0:
        return a0->unk_20.unk_00;
    case 1:
        return a0->unk_20.unk_02;
    case 2:
        return a0->unk_20.unk_04;
    case 3:
        return sub_801B770(a0);
    case 4:
        return a0->unk_44;
    default:
        AGB_ASSERT(0);
        return 0;
    }
}

static void sub_801B7D8(u32 command)
{
    
}

u16 mevent_081445C0(u32 command)
{
    return 0;
}

void sub_801B940(void)
{
    gUnknown_02022C70 = FALSE;
}

bool32 sub_801B94C(u16 a0)
{
    return TRUE;
}

void sub_801B990(u32 a0, u32 a1)
{
    
}

static void sub_801B9F8(void)
{
}

static bool32 sub_801BA24(u32 a0, u32 *a1, int size)
{
    int i;
    int j;

    for (i = 0; i < size; i++)
    {
        if (a1[i] == a0)
            break;
    }

    if (i == size)
    {
        for (j = size - 1; j > 0; j--)
            a1[j] = a1[j - 1];

        a1[0] = a0;
        return TRUE;
    }
    else
    {
        for (j = i; j > 0; j--)
            a1[j] = a1[j - 1];

        a1[0] = a0;
        return FALSE;
    }
}

static void sub_801BA8C(u32 a0, u32 a1, u32 *a2, int a3)
{
    if (sub_801BA24(a1, a2, a3))
        sub_801B7D8(a0);
}
