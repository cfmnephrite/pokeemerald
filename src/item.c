#include "global.h"
#include "item.h"
#include "berry.h"
#include "pokeball.h"
#include "string_util.h"
#include "text.h"
#include "event_data.h"
#include "malloc.h"
#include "secret_base.h"
#include "item_menu.h"
#include "party_menu.h"
#include "strings.h"
#include "load_save.h"
#include "item_use.h"
#include "battle_pyramid.h"
#include "battle_pyramid_bag.h"
#include "graphics.h"
#include "constants/battle.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/item_effects.h"
#include "constants/hold_effects.h"

static bool8 CheckPyramidBagHasItem(u16 itemId, u16 count);
static bool8 CheckPyramidBagHasSpace(u16 itemId, u16 count);
static const u8 *GetItemPluralName(u16);
static bool32 DoesItemHavePluralName(u16);

EWRAM_DATA struct BagPocket gBagPockets[POCKETS_COUNT] = {0};

#include "data/pokemon/item_effects.h"
#include "data/items.h"

static inline u32 GetPocketBaseCapacity(enum Pocket pocketId)
{
    switch (pocketId)
    {
        case POCKET_ITEMS:
            return BAG_ITEMS_BASE_COUNT;
        case POCKET_KEY_ITEMS:
            return BAG_KEYITEMS_BASE_COUNT;
        case POCKET_POKE_BALLS:
            return BAG_POKEBALLS_BASE_COUNT;
        case POCKET_TM_HM:
            return BAG_TMHM_BASE_COUNT;
        case POCKET_BERRIES:
            return BAG_BERRIES_BASE_COUNT;
        case POCKET_PC_DUMMY:
            return PC_ITEMS_COUNT;
        default:
            return 0;
    }
}

#define GET_OR_SET_EXTRA_ITEM_ID_OR_QUANTITY(_itemSlots, _pocketPos)                                        \
    if (isSetting)                                                                                          \
    {                                                                                                       \
        _itemSlots[_pocketPos].extraItemId = (itemId && quantity > 0) ? (itemId >> 5) : ITEM_NONE;          \
        _itemSlots[(_pocketPos) + 1].extraItemId = (itemId && quantity > 0) ? itemId : ITEM_NONE;           \
        _itemSlots[_pocketPos].extraItemQuantity = (quantity >> 5);                                         \
        _itemSlots[(_pocketPos) + 1].extraItemQuantity = quantity;                                          \
        return 0;                                                                                           \
    }                                                                                                       \
    return itemId ?                                                                                         \
        ((_itemSlots[_pocketPos].extraItemId << 5) | _itemSlots[(_pocketPos) + 1].extraItemId) :            \
        ((_itemSlots[_pocketPos].extraItemQuantity << 5) | _itemSlots[(_pocketPos) + 1].extraItemQuantity);

/*
 * Works in the following way:
 * - isSetting is TRUE: sets both itemId (if > 0), quantity; setting quantity = 0 clears itemId
 * - isSetting is FALSE: if itemID is TRUE, return that, otherwise quantity
*/
static u16 GetSetPocketSlot_Generic(struct BagPocket *pocket, u32 pocketPos, u16 itemId, u16 quantity, bool32 isSetting)
{
    u16 baseCapacity = GetPocketBaseCapacity(pocket->id);
    if (pocketPos < baseCapacity)
    {
        if (isSetting)
        {
            pocket->itemSlots[pocketPos].itemId = (itemId && quantity > 0) ? itemId : ITEM_NONE;
            pocket->itemSlots[pocketPos].quantity = quantity ^ gSaveBlock2Ptr->encryptionKey;
            return 0;
        }

        return itemId ?
            pocket->itemSlots[pocketPos].itemId :
            ((pocket->itemSlots[pocketPos].quantity ^ gSaveBlock2Ptr->encryptionKey) & 0x3FF);
    }

    GET_OR_SET_EXTRA_ITEM_ID_OR_QUANTITY(pocket->itemSlots, (pocketPos - baseCapacity) * 2)
}

/*
 * Works in the following way:
 * - isSetting is TRUE: sets both itemId (if > 0), quantity; setting quantity = 0 clears itemId
 * - isSetting is FALSE: if itemID is TRUE, return that, otherwise quantity
*/
static u16 GetSetPocketSlot_Items(struct BagPocket *pocket, u32 pocketPos, u16 itemId, u16 quantity, bool32 isSetting)
{
    if (pocketPos >= BAG_ITEMS_BASE_COUNT * 3 / 2)
    {
        // Adjust pocketPos to use additional slots in PC storage
        GET_OR_SET_EXTRA_ITEM_ID_OR_QUANTITY(gSaveBlock1Ptr->pcItems, (pocketPos - (BAG_ITEMS_BASE_COUNT * 3 / 2)) * 2)
    }

    return GetSetPocketSlot_Generic(pocket, pocketPos, itemId, quantity, isSetting);
}

#define GET_OR_SET_EXTRA_KEY_ITEM_SLOT(_pocketPos, _keyItemSlot)                                                \
    if (isSetting)                                                                                              \
    {                                                                                                           \
        if (!pocket->itemSlots[_pocketPos].expansionBit)                                                        \
            pocket->itemSlots[_pocketPos].keyItemSlot2 = pocket->itemSlots[_pocketPos].keyItemSlot3 = 0;        \
        pocket->itemSlots[_pocketPos].expansionBit |= !!itemId;                                                 \
        pocket->itemSlots[_pocketPos]._keyItemSlot = itemId;                                                    \
        return 0;                                                                                               \
    }                                                                                                           \
    return pocket->itemSlots[_pocketPos].expansionBit ?                                                         \
        (itemId ? pocket->itemSlots[_pocketPos]._keyItemSlot : !!pocket->itemSlots[_pocketPos]._keyItemSlot) :  \
        0;

/*
 * Works in the following way:
 * - isSetting is TRUE: sets itemId, does not set a quantity; setting quantity = 0 clears itemId
 * - isSetting is FALSE: if itemID is TRUE, return that, otherwise quantity
*/
static u16 GetSetPocketSlot_KeyItems(struct BagPocket *pocket, u32 pocketPos, u16 itemId, u16 quantity, bool32 isSetting)
{
    // Nothing to be done here...
    if (!itemId && quantity > 0)
        return 0;

    if (pocketPos < BAG_KEYITEMS_BASE_COUNT)
    {
        if (isSetting)
        {
            pocket->itemSlots[pocketPos].itemId = itemId;
            return 0;
        }

        return itemId ? pocket->itemSlots[pocketPos].itemId : !!pocket->itemSlots[pocketPos].itemId;
    }
    else {
        // Adjust pocketPos to get the right value from either keyItemSlot2 or keyItemSlot3
        if (pocketPos >= (2 * BAG_KEYITEMS_BASE_COUNT - KEY_ITEM_SLOTS_SIPHONED_FOR_TMS_HMS))
        {
            GET_OR_SET_EXTRA_KEY_ITEM_SLOT(pocketPos - (2 * BAG_KEYITEMS_BASE_COUNT - KEY_ITEM_SLOTS_SIPHONED_FOR_TMS_HMS), keyItemSlot3)
        }
        GET_OR_SET_EXTRA_KEY_ITEM_SLOT(pocketPos - BAG_KEYITEMS_BASE_COUNT, keyItemSlot2)
    }
}

/*
 * Works in the following way:
 * - isSetting is TRUE: sets both itemId (if > 0), quantity; setting quantity = 0 clears itemId
 * - isSetting is FALSE: if itemID is TRUE, return that, otherwise quantity
*/
static u16 GetSetPocketSlot_TMsHMs(struct BagPocket *pocket, u32 pocketPos, u16 itemId, u16 quantity, bool32 isSetting)
{
    if (pocketPos >= BAG_TMHM_BASE_COUNT * 3 / 2)
    {
        // Adjust pocketPos to use additional slots in Key Items pocket
        pocketPos = (pocketPos - (BAG_TMHM_BASE_COUNT * 3 / 2)) * 2 + BAG_KEYITEMS_BASE_COUNT - KEY_ITEM_SLOTS_SIPHONED_FOR_TMS_HMS;
        pocket = &gBagPockets[POCKET_KEY_ITEMS];

        if (isSetting)
        {
            pocket->itemSlots[pocketPos].expansionBit |= !!(itemId && quantity > 0);
            pocket->itemSlots[pocketPos].keyItemSlot2 = (itemId && quantity > 0) ? itemId : ITEM_NONE;
            pocket->itemSlots[pocketPos].keyItemSlot3 = quantity;
            return 0;
        }

        return pocket->itemSlots[pocketPos].expansionBit ?
            (itemId ? pocket->itemSlots[pocketPos].keyItemSlot2 : pocket->itemSlots[pocketPos].keyItemSlot3) :
            0;
    }

    return GetSetPocketSlot_Generic(pocket, pocketPos, itemId, quantity, isSetting);
}

static u16 (*const sGetSetPocketSlotFuncs[])(struct BagPocket *pocket, u32 pocketPos, u16 itemId, u16 quantity, bool32 isSetting) =
{
    [POCKET_ITEMS] = GetSetPocketSlot_Items,
    [POCKET_KEY_ITEMS] = GetSetPocketSlot_KeyItems,
    [POCKET_POKE_BALLS] = GetSetPocketSlot_Generic,
    [POCKET_TM_HM] = GetSetPocketSlot_TMsHMs,
    [POCKET_BERRIES] = GetSetPocketSlot_Generic,
    [POCKET_PC_DUMMY] = GetSetPocketSlot_Generic,
};

static inline u16 GetBagItemIdPocket(struct BagPocket *pocket, u32 pocketPos)
{
    return sGetSetPocketSlotFuncs[pocket->id](pocket, pocketPos, TRUE, FALSE, FALSE);
}

// Returns zero if the slot contains no item
static inline u16 GetBagItemQuantityPocket(struct BagPocket *pocket, u32 pocketPos)
{
    return sGetSetPocketSlotFuncs[pocket->id](pocket, pocketPos, FALSE, TRUE, FALSE);
}

static inline void SetBagItemIdPocket(struct BagPocket *pocket, u32 pocketPos, u16 itemId)
{
    sGetSetPocketSlotFuncs[pocket->id](pocket, pocketPos, itemId, 1, TRUE); // quantity required, default is 1
}

// If the new quantity is zero, make sure to clear the ID
static inline void SetBagItemQuantityPocket(struct BagPocket *pocket, u32 pocketPos, u16 newValue)
{
    sGetSetPocketSlotFuncs[pocket->id](pocket, pocketPos, 0, newValue, TRUE);
}

u16 GetBagItemId(enum Pocket pocketId, u32 pocketPos)
{
    return GetBagItemIdPocket(&gBagPockets[pocketId], pocketPos);
}

u16 GetBagItemQuantity(enum Pocket pocketId, u32 pocketPos)
{
    return GetBagItemQuantityPocket(&gBagPockets[pocketId], pocketPos);
}

static void SetBagItemId(enum Pocket pocketId, u32 pocketPos, u16 itemId)
{
    SetBagItemIdPocket(&gBagPockets[pocketId], pocketPos, itemId);
}

static void SetBagItemQuantity(enum Pocket pocketId, u32 pocketPos, u16 newValue)
{
    SetBagItemQuantityPocket(&gBagPockets[pocketId], pocketPos, newValue);
}

void ApplyNewEncryptionKeyToBagItems(u32 newKey)
{
    enum Pocket pocketId;
    u32 item;
    for (pocketId = 0; pocketId < POCKETS_COUNT; pocketId++)
    {
        // Don't bother with Key Items
        if (pocketId == POCKET_KEY_ITEMS)
            continue;

        for (item = 0; item < GetPocketBaseCapacity(pocketId); item++)
        {
            gBagPockets[pocketId].itemSlots[item].quantity ^= gSaveBlock2Ptr->encryptionKey;
            gBagPockets[pocketId].itemSlots[item].quantity ^= newKey;
        }
    }
}

void SetBagItemsPointers(void)
{
    gBagPockets[POCKET_ITEMS].itemSlots = gSaveBlock1Ptr->bag.items;
    gBagPockets[POCKET_ITEMS].capacity = BAG_ITEMS_COUNT * 3 / 2;
    gBagPockets[POCKET_ITEMS].id = POCKET_ITEMS;

    gBagPockets[POCKET_KEY_ITEMS].itemSlots = gSaveBlock1Ptr->bag.keyItems;
    gBagPockets[POCKET_KEY_ITEMS].capacity = BAG_KEYITEMS_COUNT * 3 / 2;
    gBagPockets[POCKET_KEY_ITEMS].id = POCKET_KEY_ITEMS;

    gBagPockets[POCKET_POKE_BALLS].itemSlots = gSaveBlock1Ptr->bag.pokeBalls;
    gBagPockets[POCKET_POKE_BALLS].capacity = BAG_POKEBALLS_COUNT * 3 / 2;
    gBagPockets[POCKET_POKE_BALLS].id = POCKET_POKE_BALLS;

    gBagPockets[POCKET_TM_HM].itemSlots = gSaveBlock1Ptr->bag.TMsHMs;
    gBagPockets[POCKET_TM_HM].capacity = BAG_TMHM_COUNT * 3 / 2;
    gBagPockets[POCKET_TM_HM].id = POCKET_TM_HM;

    gBagPockets[POCKET_BERRIES].itemSlots = gSaveBlock1Ptr->bag.berries;
    gBagPockets[POCKET_BERRIES].capacity = BAG_BERRIES_COUNT * 3 / 2;
    gBagPockets[POCKET_BERRIES].id = POCKET_BERRIES;
}

u8 *CopyItemName(u16 itemId, u8 *dst)
{
    return StringCopy(dst, GetItemName(itemId));
}

const u8 sText_s[] =_("s");

u8 *CopyItemNameHandlePlural(u16 itemId, u8 *dst, u32 quantity)
{
    if (quantity == 1)
    {
        return StringCopy(dst, GetItemName(itemId));
    }
    else if (DoesItemHavePluralName(itemId))
    {
        return StringCopy(dst, GetItemPluralName(itemId));
    }
    else
    {
        u8 *end = StringCopy(dst, GetItemName(itemId));
        return StringCopy(end, sText_s);
    }
}

bool8 IsBagPocketNonEmpty(enum Pocket pocketId)
{
    u8 i;

    for (i = 0; i < gBagPockets[pocketId].capacity; i++)
    {
        if (GetBagItemId(pocketId, i) != 0)
            return TRUE;
    }
    return FALSE;
}

bool8 CheckBagHasItem(u16 itemId, u16 count)
{
    u8 i;
    enum Pocket pocketId;

    if (GetItemPocket(itemId) >= POCKETS_COUNT)
        return FALSE;
    if (InBattlePyramid() || FlagGet(FLAG_STORING_ITEMS_IN_PYRAMID_BAG) == TRUE)
        return CheckPyramidBagHasItem(itemId, count);
    pocketId = GetItemPocket(itemId);
    // Check for item slots that contain the item
    for (i = 0; i < gBagPockets[pocketId].capacity; i++)
    {
        if (GetBagItemId(pocketId, i) == itemId)
        {
            u16 quantity;
            // Does this item slot contain enough of the item?
            quantity = GetBagItemQuantity(pocketId, i);
            if (quantity >= count)
                return TRUE;
            count -= quantity;
            // Does this item slot and all previous slots contain enough of the item?
            if (count == 0)
                return TRUE;
        }
    }
    return FALSE;
}

bool8 HasAtLeastOneBerry(void)
{
    u16 i;

    for (i = FIRST_BERRY_INDEX; i <= LAST_BERRY_INDEX; i++)
    {
        if (CheckBagHasItem(i, 1) == TRUE)
        {
            gSpecialVar_Result = TRUE;
            return TRUE;
        }
    }
    gSpecialVar_Result = FALSE;
    return FALSE;
}

bool8 HasAtLeastOnePokeBall(void)
{
    u16 ballId;

    for (ballId = BALL_STRANGE; ballId < POKEBALL_COUNT; ballId++)
    {
        if (CheckBagHasItem(ballId, 1) == TRUE)
            return TRUE;
    }
    return FALSE;
}

bool8 CheckBagHasSpace(u16 itemId, u16 count)
{
    if (GetItemPocket(itemId) >= POCKETS_COUNT)
        return FALSE;

    if (InBattlePyramid() || FlagGet(FLAG_STORING_ITEMS_IN_PYRAMID_BAG) == TRUE)
        return CheckPyramidBagHasSpace(itemId, count);

    return GetFreeSpaceForItemInBag(itemId) >= count;
}

u32 GetFreeSpaceForItemInBag(u16 itemId)
{
    u8 i;
    enum Pocket pocketId = GetItemPocket(itemId);
    u16 ownedCount;
    u32 spaceForItem = 0;

    if (GetItemPocket(itemId) >= POCKETS_COUNT)
        return 0;

    // Check space in any existing item slots that already contain this item
    for (i = 0; i < gBagPockets[pocketId].capacity; i++)
    {

        if (GetBagItemId(pocketId, i) == itemId)
        {
            ownedCount = GetBagItemQuantity(pocketId, i);
            spaceForItem += max(0, MAX_BAG_ITEM_CAPACITY - ownedCount);
        }
        else if (GetBagItemId(pocketId, i) == ITEM_NONE)
        {
            spaceForItem += MAX_BAG_ITEM_CAPACITY;
        }
    }
    return spaceForItem;
}

static inline bool32 CheckSlotAndUpdateCount(struct BagPocket *pocket, u16 itemId, u32 pocketPos, u32 *nextPocketPos, u16 *count, u16 *tempPocketSlotQuantities)
{
    u16 tempItemId, tempQuantity;
    tempItemId = GetBagItemIdPocket(pocket, pocketPos);
    if (tempItemId == ITEM_NONE || tempItemId == itemId)
    {
        // The quantity already at the slot
        tempQuantity = (tempItemId == itemId) * GetBagItemQuantityPocket(pocket, pocketPos);

        // Record slot quantity in tempPocketSlotQuantities, adjust count
        tempPocketSlotQuantities[pocketPos] = min(MAX_BAG_ITEM_CAPACITY, *count + tempQuantity);
        *count -= min(*count, MAX_BAG_ITEM_CAPACITY - tempQuantity);

        // Set the starting index for the next loop to set items (shifted by one)
        if (!(*nextPocketPos))
            *nextPocketPos = pocketPos + 1;

        return TRUE;
    }

    return FALSE;
}

static bool32 AddItemToPocket(struct BagPocket *pocket, u16 itemId, u16 count)
{
    u32 i, j = 0;

    // First, check that there is a free slot for this item
    u16 *tempPocketSlotQuantities = AllocZeroed(sizeof(u16) * pocket->capacity);

    switch (pocket->id)
    {
        case POCKET_BERRIES:
        case POCKET_KEY_ITEMS:
            for (i = 0; i < pocket->capacity && count > 0; i++)
            {
                // Check if we found a slot to store the item but weren't able to reduce count to 0
                // This means that we have more than one stack's worth, which isn't allowed in these pockets
                if (CheckSlotAndUpdateCount(pocket, itemId, i, &j, &count, tempPocketSlotQuantities) && count > 0)
                {
                    Free(tempPocketSlotQuantities);
                    return FALSE;
                }
            }
            break;
        default:
            for (i = 0; i < pocket->capacity && count > 0; i++)
                CheckSlotAndUpdateCount(pocket, itemId, i, &j, &count, tempPocketSlotQuantities);
    }

    // If the count is still greater than zero, clearly we have not found enough slots for this...
    // Otherwise, we have found slots - update the actual pockets with the updated quantities
    if (count == 0)
    {
        for (j = j - 1; j <= i; j++)
        {
            if (tempPocketSlotQuantities[i] > 0)
                sGetSetPocketSlotFuncs[pocket->id](pocket, j, itemId, tempPocketSlotQuantities[i], TRUE);
        }
    }

    Free(tempPocketSlotQuantities);
    return !(count > 0);
}

bool32 AddBagItem(u16 itemId, u16 count)
{
    if (GetItemPocket(itemId) >= POCKETS_COUNT)
        return FALSE;

    // check Battle Pyramid Bag
    if (InBattlePyramid() || FlagGet(FLAG_STORING_ITEMS_IN_PYRAMID_BAG) == TRUE)
    {
        return AddPyramidBagItem(itemId, count);
    }

    return AddItemToPocket(&gBagPockets[gItemsInfo[itemId].pocket], itemId, count);
}

static bool32 RemoveItemFromPocket(struct BagPocket *pocket, u16 itemId, u16 count)
{
    u32 i, j = 0, totalQuantity = 0;
    u16 tempQuantity;
    u16 *tempPocketSlotQuantities = AllocZeroed(sizeof(u16) * pocket->capacity);

    for (i = 0; i < pocket->capacity && totalQuantity < count; i++)
    {
        if (GetBagItemIdPocket(pocket, i) == itemId)
        {
            // Index for the next loop
            if (j == 0)
                j = i + 1;

            tempQuantity = GetBagItemQuantityPocket(pocket, i);
            totalQuantity += tempQuantity;

            tempPocketSlotQuantities[i] = (tempQuantity <= count ? 0 : tempQuantity - count) + 1;
        }
    }

    if (totalQuantity < count)
        return FALSE;   // We don't have enough of the item

    if (CurMapIsSecretBase() == TRUE)
    {
        VarSet(VAR_SECRET_BASE_LOW_TV_FLAGS, VarGet(VAR_SECRET_BASE_LOW_TV_FLAGS) | SECRET_BASE_USED_BAG);
        VarSet(VAR_SECRET_BASE_LAST_ITEM_USED, itemId);
    }

    // Update the quantities correctly with the items removed
    for (j = j - 1; j <= i; j++)
    {
        if (tempPocketSlotQuantities[j])
            SetBagItemQuantityPocket(pocket, j, tempPocketSlotQuantities[j] - 1);
    }
    return TRUE;
}

bool32 RemoveBagItem(u16 itemId, u16 count)
{
    if (GetItemPocket(itemId) >= POCKETS_COUNT || itemId == ITEM_NONE)
    return FALSE;
    
    // check Battle Pyramid Bag
    if (InBattlePyramid() || FlagGet(FLAG_STORING_ITEMS_IN_PYRAMID_BAG) == TRUE)
    {
        return RemovePyramidBagItem(itemId, count);
    }

    return RemoveItemFromPocket(&gBagPockets[GetItemPocket(itemId)], itemId, count);
}

static s32 FindFreePCItemSlot(void)
{
    s8 i;

    for (i = 0; i < PC_ITEMS_COUNT; i++)
    {
        if (gSaveBlock1Ptr->pcItems[i].itemId == ITEM_NONE)
            return i;
    }
    return -1;
}

u8 CountUsedPCItemSlots(void)
{
    u8 usedSlots = 0;
    u8 i;

    for (i = 0; i < PC_ITEMS_COUNT; i++)
    {
        if (gSaveBlock1Ptr->pcItems[i].itemId != ITEM_NONE)
            usedSlots++;
    }
    return usedSlots;
}

bool8 CheckPCHasItem(u16 itemId, u16 count)
{
    u8 i;

    for (i = 0; i < PC_ITEMS_COUNT; i++)
    {
        if (gSaveBlock1Ptr->pcItems[i].itemId == itemId && gSaveBlock1Ptr->pcItems[i].quantity >= count)
            return TRUE;
    }
    return FALSE;
}

bool8 AddPCItem(u16 itemId, u16 count)
{
    struct BagPocket tempPocket = {
        .capacity = PC_ITEMS_COUNT,
        .id = POCKET_PC_DUMMY,
        .itemSlots = &gSaveBlock1Ptr->pcItems,
    };

    return AddItemToPocket(&tempPocket, itemId, count);
}

void RemovePCItem(u8 index, u16 count)
{
    gSaveBlock1Ptr->pcItems[index].quantity -= count;
    if (gSaveBlock1Ptr->pcItems[index].quantity == 0)
    {
        gSaveBlock1Ptr->pcItems[index].itemId = ITEM_NONE;
        CompactPCItems();
    }
}

void CompactPCItems(void)
{
    u16 i;
    u16 j;

    for (i = 0; i < PC_ITEMS_COUNT - 1; i++)
    {
        for (j = i + 1; j < PC_ITEMS_COUNT; j++)
        {
            if (gSaveBlock1Ptr->pcItems[i].itemId == 0)
            {
                struct ItemSlot temp = gSaveBlock1Ptr->pcItems[i];
                gSaveBlock1Ptr->pcItems[i] = gSaveBlock1Ptr->pcItems[j];
                gSaveBlock1Ptr->pcItems[j] = temp;
            }
        }
    }
}

void SwapRegisteredBike(void)
{
    switch (gSaveBlock1Ptr->registeredItem)
    {
    case ITEM_MACH_BIKE:
        gSaveBlock1Ptr->registeredItem = ITEM_ACRO_BIKE;
        break;
    case ITEM_ACRO_BIKE:
        gSaveBlock1Ptr->registeredItem = ITEM_MACH_BIKE;
        break;
    }
}

static void SwapItemSlots(enum Pocket pocketId, u32 pocketPosA, u16 pocketPosB)
{
    struct BagPocket *pocket = &gBagPockets[pocketId];
    u16 itemIdA = GetBagItemIdPocket(pocket, pocketPosA),
        quantityA = GetBagItemQuantityPocket(pocket, pocketPosA);

    // Swap quantity and item id
    SetBagItemIdPocket(pocket, pocketPosA, GetBagItemIdPocket(pocket, pocketPosB));
    SetBagItemQuantityPocket(pocket, pocketPosA, GetBagItemQuantityPocket(pocket, pocketPosB));
    SetBagItemIdPocket(pocket, pocketPosB, itemIdA);
    SetBagItemQuantityPocket(pocket, pocketPosB, quantityA);
}

void CompactItemsInBagPocket(enum Pocket pocketId)
{
    u16 i, j;

    for (i = 0; i < gBagPockets[pocketId].capacity - 1; i++)
    {
        for (j = i + 1; j < gBagPockets[pocketId].capacity; j++)
        {
            if (GetBagItemId(pocketId, i) == ITEM_NONE)
                SwapItemSlots(pocketId, i, j);
        }
    }
}

void SortBerriesOrTMHMs(enum Pocket pocketId)
{
    u16 i, j;

    for (i = 0; i < gBagPockets[pocketId].capacity - 1; i++)
    {
        for (j = i + 1; j < gBagPockets[pocketId].capacity; j++)
        {
            if (GetBagItemId(pocketId, i) != ITEM_NONE)
            {
                if (GetBagItemQuantity(pocketId, j) == 0)
                    continue;
                if (GetBagItemId(pocketId, i) <= GetBagItemId(pocketId, j))
                    continue;
            }
            SwapItemSlots(pocketId, i, j);
        }
    }
}

void MoveItemSlotInPocket(enum Pocket pocketId, u32 from, u32 to)
{
    if (from != to)
    {
        u32 i;
        s8 shift = -1;
        struct BagPocket *pocket = &gBagPockets[pocketId];

        // Record the values at "from"
        u16 fromItemId = GetBagItemIdPocket(pocket, from),
            fromQuantity = GetBagItemQuantityPocket(pocket, from);

        // Shuffle items between "to" and "from"
        if (to > from)
        {
            to--;
            shift = 1;
        }

        for (i = from; i == to - shift; i += shift)
        {
            SetBagItemIdPocket(pocket, i, GetBagItemIdPocket(pocket, i + shift));
            SetBagItemQuantityPocket(pocket, i, GetBagItemQuantityPocket(pocket, i + shift));
        }

        // Move the saved "from" to "to"
        SetBagItemIdPocket(pocket, to, fromItemId);
        SetBagItemQuantityPocket(pocket, to, fromQuantity);
    }
}

void MoveItemSlotInPC(struct ItemSlot *itemSlots, u32 from, u32 to)
{
    if (from != to)
    {
        s16 i, count;
        struct ItemSlot firstSlot = itemSlots[from];

        if (to > from)
        {
            to--;
            for (i = from, count = to; i < count; i++)
                itemSlots[i] = itemSlots[i + 1];
        }
        else
        {
            for (i = from, count = to; i > count; i--)
                itemSlots[i] = itemSlots[i - 1];
        }
        itemSlots[to] = firstSlot;
    }
}

void ClearBag(void)
{
    CpuFastFill(0, &gSaveBlock1Ptr->bag, sizeof(struct Bag));
}

u16 CountTotalItemQuantityInBag(u16 itemId)
{
    u16 i;
    u16 ownedCount = 0;
    enum Pocket pocketId = GetItemPocket(itemId);

    for (i = 0; i < gBagPockets[pocketId].capacity; i++)
    {
        if (GetBagItemId(pocketId, i) == itemId)
            ownedCount += GetBagItemQuantity(pocketId, i);
    }

    return ownedCount;
}

static bool8 CheckPyramidBagHasItem(u16 itemId, u16 count)
{
    u8 i;
    u16 *items = gSaveBlock2Ptr->frontier.pyramidBag.itemId[gSaveBlock2Ptr->frontier.lvlMode];
#if MAX_PYRAMID_BAG_ITEM_CAPACITY > 255
    u16 *quantities = gSaveBlock2Ptr->frontier.pyramidBag.quantity[gSaveBlock2Ptr->frontier.lvlMode];
#else
    u8 *quantities = gSaveBlock2Ptr->frontier.pyramidBag.quantity[gSaveBlock2Ptr->frontier.lvlMode];
#endif

    for (i = 0; i < PYRAMID_BAG_ITEMS_COUNT; i++)
    {
        if (items[i] == itemId)
        {
            if (quantities[i] >= count)
                return TRUE;

            count -= quantities[i];
            if (count == 0)
                return TRUE;
        }
    }

    return FALSE;
}

static bool8 CheckPyramidBagHasSpace(u16 itemId, u16 count)
{
    u8 i;
    u16 *items = gSaveBlock2Ptr->frontier.pyramidBag.itemId[gSaveBlock2Ptr->frontier.lvlMode];
#if MAX_PYRAMID_BAG_ITEM_CAPACITY > 255
    u16 *quantities = gSaveBlock2Ptr->frontier.pyramidBag.quantity[gSaveBlock2Ptr->frontier.lvlMode];
#else
    u8 *quantities = gSaveBlock2Ptr->frontier.pyramidBag.quantity[gSaveBlock2Ptr->frontier.lvlMode];
#endif

    for (i = 0; i < PYRAMID_BAG_ITEMS_COUNT; i++)
    {
        if (items[i] == itemId || items[i] == ITEM_NONE)
        {
            if (quantities[i] + count <= MAX_PYRAMID_BAG_ITEM_CAPACITY)
                return TRUE;

            count = (quantities[i] + count) - MAX_PYRAMID_BAG_ITEM_CAPACITY;
            if (count == 0)
                return TRUE;
        }
    }

    return FALSE;
}

bool8 AddPyramidBagItem(u16 itemId, u16 count)
{
    u16 i;

    u16 *items = gSaveBlock2Ptr->frontier.pyramidBag.itemId[gSaveBlock2Ptr->frontier.lvlMode];
    u16 *newItems = Alloc(PYRAMID_BAG_ITEMS_COUNT * sizeof(*newItems));

#if MAX_PYRAMID_BAG_ITEM_CAPACITY > 255
    u16 *quantities = gSaveBlock2Ptr->frontier.pyramidBag.quantity[gSaveBlock2Ptr->frontier.lvlMode];
    u16 *newQuantities = Alloc(PYRAMID_BAG_ITEMS_COUNT * sizeof(*newQuantities));
#else
    u8 *quantities = gSaveBlock2Ptr->frontier.pyramidBag.quantity[gSaveBlock2Ptr->frontier.lvlMode];
    u8 *newQuantities = Alloc(PYRAMID_BAG_ITEMS_COUNT * sizeof(*newQuantities));
#endif

    memcpy(newItems, items, PYRAMID_BAG_ITEMS_COUNT * sizeof(*newItems));
    memcpy(newQuantities, quantities, PYRAMID_BAG_ITEMS_COUNT * sizeof(*newQuantities));

    for (i = 0; i < PYRAMID_BAG_ITEMS_COUNT; i++)
    {
        if (newItems[i] == itemId && newQuantities[i] < MAX_PYRAMID_BAG_ITEM_CAPACITY)
        {
            newQuantities[i] += count;
            if (newQuantities[i] > MAX_PYRAMID_BAG_ITEM_CAPACITY)
            {
                count = newQuantities[i] - MAX_PYRAMID_BAG_ITEM_CAPACITY;
                newQuantities[i] = MAX_PYRAMID_BAG_ITEM_CAPACITY;
            }
            else
            {
                count = 0;
            }

            if (count == 0)
                break;
        }
    }

    if (count > 0)
    {
        for (i = 0; i < PYRAMID_BAG_ITEMS_COUNT; i++)
        {
            if (newItems[i] == ITEM_NONE)
            {
                newItems[i] = itemId;
                newQuantities[i] = count;
                if (newQuantities[i] > MAX_PYRAMID_BAG_ITEM_CAPACITY)
                {
                    count = newQuantities[i] - MAX_PYRAMID_BAG_ITEM_CAPACITY;
                    newQuantities[i] = MAX_PYRAMID_BAG_ITEM_CAPACITY;
                }
                else
                {
                    count = 0;
                }

                if (count == 0)
                    break;
            }
        }
    }

    if (count == 0)
    {
        memcpy(items, newItems, PYRAMID_BAG_ITEMS_COUNT * sizeof(*items));
        memcpy(quantities, newQuantities, PYRAMID_BAG_ITEMS_COUNT * sizeof(*quantities));
        Free(newItems);
        Free(newQuantities);
        return TRUE;
    }
    else
    {
        Free(newItems);
        Free(newQuantities);
        return FALSE;
    }
}

bool8 RemovePyramidBagItem(u16 itemId, u16 count)
{
    u16 i;

    u16 *items = gSaveBlock2Ptr->frontier.pyramidBag.itemId[gSaveBlock2Ptr->frontier.lvlMode];
#if MAX_PYRAMID_BAG_ITEM_CAPACITY > 255
    u16 *quantities = gSaveBlock2Ptr->frontier.pyramidBag.quantity[gSaveBlock2Ptr->frontier.lvlMode];
#else
    u8 *quantities = gSaveBlock2Ptr->frontier.pyramidBag.quantity[gSaveBlock2Ptr->frontier.lvlMode];
#endif

    i = gPyramidBagMenuState.cursorPosition + gPyramidBagMenuState.scrollPosition;
    if (items[i] == itemId && quantities[i] >= count)
    {
        quantities[i] -= count;
        if (quantities[i] == 0)
            items[i] = ITEM_NONE;
        return TRUE;
    }
    else
    {
        u16 *newItems = Alloc(PYRAMID_BAG_ITEMS_COUNT * sizeof(*newItems));
    #if MAX_PYRAMID_BAG_ITEM_CAPACITY > 255
        u16 *newQuantities = Alloc(PYRAMID_BAG_ITEMS_COUNT * sizeof(*newQuantities));
    #else
        u8 *newQuantities = Alloc(PYRAMID_BAG_ITEMS_COUNT * sizeof(*newQuantities));
    #endif

        memcpy(newItems, items, PYRAMID_BAG_ITEMS_COUNT * sizeof(*newItems));
        memcpy(newQuantities, quantities, PYRAMID_BAG_ITEMS_COUNT * sizeof(*newQuantities));

        for (i = 0; i < PYRAMID_BAG_ITEMS_COUNT; i++)
        {
            if (newItems[i] == itemId)
            {
                if (newQuantities[i] >= count)
                {
                    newQuantities[i] -= count;
                    count = 0;
                    if (newQuantities[i] == 0)
                        newItems[i] = ITEM_NONE;
                }
                else
                {
                    count -= newQuantities[i];
                    newQuantities[i] = 0;
                    newItems[i] = ITEM_NONE;
                }

                if (count == 0)
                    break;
            }
        }

        if (count == 0)
        {
            memcpy(items, newItems, PYRAMID_BAG_ITEMS_COUNT * sizeof(*items));
            memcpy(quantities, newQuantities, PYRAMID_BAG_ITEMS_COUNT * sizeof(*quantities));
            Free(newItems);
            Free(newQuantities);
            return TRUE;
        }
        else
        {
            Free(newItems);
            Free(newQuantities);
            return FALSE;
        }
    }
}

static u16 SanitizeItemId(u16 itemId)
{
    if (itemId >= ITEMS_COUNT)
        return ITEM_NONE;
    else
        return itemId;
}

const u8 *GetItemName(u16 itemId)
{
    return gItemsInfo[SanitizeItemId(itemId)].name;
}

u32 GetItemPrice(u16 itemId)
{
    return gItemsInfo[SanitizeItemId(itemId)].price;
}

static bool32 DoesItemHavePluralName(u16 itemId)
{
    return (gItemsInfo[SanitizeItemId(itemId)].pluralName[0] != '\0');
}

static const u8 *GetItemPluralName(u16 itemId)
{
    return gItemsInfo[SanitizeItemId(itemId)].pluralName;
}

const u8 *GetItemEffect(u32 itemId)
{
    if (itemId == ITEM_ENIGMA_BERRY_E_READER)
    #if FREE_ENIGMA_BERRY == FALSE
        return gSaveBlock1Ptr->enigmaBerry.itemEffect;
    #else
        return 0;
    #endif //FREE_ENIGMA_BERRY
    else
        return gItemsInfo[SanitizeItemId(itemId)].effect;
}

u32 GetItemHoldEffect(u32 itemId)
{
    return gItemsInfo[SanitizeItemId(itemId)].holdEffect;
}

u32 GetItemHoldEffectParam(u32 itemId)
{
    return gItemsInfo[SanitizeItemId(itemId)].holdEffectParam;
}

const u8 *GetItemDescription(u16 itemId)
{
    return gItemsInfo[SanitizeItemId(itemId)].description;
}

u8 GetItemImportance(u16 itemId)
{
    return gItemsInfo[SanitizeItemId(itemId)].importance;
}

u8 GetItemConsumability(u16 itemId)
{
    return !gItemsInfo[SanitizeItemId(itemId)].notConsumed;
}

enum Pocket GetItemPocket(u16 itemId)
{
    return gItemsInfo[SanitizeItemId(itemId)].pocket;
}

u8 GetItemType(u16 itemId)
{
    return gItemsInfo[SanitizeItemId(itemId)].type;
}

ItemUseFunc GetItemFieldFunc(u16 itemId)
{
    return gItemsInfo[SanitizeItemId(itemId)].fieldUseFunc;
}

// Returns an item's battle effect script ID.
u8 GetItemBattleUsage(u16 itemId)
{
    u16 item = SanitizeItemId(itemId);
    // Handle E-Reader berries.
    if (item == ITEM_ENIGMA_BERRY_E_READER)
    {
        switch (GetItemEffectType(gSpecialVar_ItemId))
        {
            case ITEM_EFFECT_X_ITEM:
                return EFFECT_ITEM_INCREASE_STAT;
            case ITEM_EFFECT_HEAL_HP:
                return EFFECT_ITEM_RESTORE_HP;
            case ITEM_EFFECT_CURE_POISON:
            case ITEM_EFFECT_CURE_SLEEP:
            case ITEM_EFFECT_CURE_BURN:
            case ITEM_EFFECT_CURE_FREEZE_FROSTBITE:
            case ITEM_EFFECT_CURE_PARALYSIS:
            case ITEM_EFFECT_CURE_ALL_STATUS:
            case ITEM_EFFECT_CURE_CONFUSION:
            case ITEM_EFFECT_CURE_INFATUATION:
                return EFFECT_ITEM_CURE_STATUS;
            case ITEM_EFFECT_HEAL_PP:
                return EFFECT_ITEM_RESTORE_PP;
            default:
                return 0;
        }
    }
    else
        return gItemsInfo[item].battleUsage;
}

u32 GetItemSecondaryId(u32 itemId)
{
    return gItemsInfo[SanitizeItemId(itemId)].secondaryId;
}

u32 GetItemFlingPower(u32 itemId)
{
    return gItemsInfo[SanitizeItemId(itemId)].flingPower;
}


u32 GetItemStatus1Mask(u16 itemId)
{
    const u8 *effect = GetItemEffect(itemId);
    switch (effect[3])
    {
        case ITEM3_PARALYSIS:
            return STATUS1_PARALYSIS;
        case ITEM3_FREEZE:
            return STATUS1_FREEZE | STATUS1_FROSTBITE;
        case ITEM3_BURN:
            return STATUS1_BURN;
        case ITEM3_POISON:
            return STATUS1_PSN_ANY | STATUS1_TOXIC_COUNTER;
        case ITEM3_SLEEP:
            return STATUS1_SLEEP;
        case ITEM3_STATUS_ALL:
            return STATUS1_ANY | STATUS1_TOXIC_COUNTER;
    }
    return 0;
}

u32 GetItemStatus2Mask(u16 itemId)
{
    const u8 *effect = GetItemEffect(itemId);
    if (effect[3] & ITEM3_STATUS_ALL)
        return STATUS2_INFATUATION | STATUS2_CONFUSION;
    else if (effect[0] & ITEM0_INFATUATION)
        return STATUS2_INFATUATION;
    else if (effect[3] & ITEM3_CONFUSION)
        return STATUS2_CONFUSION;
    else
        return 0;
}
