#ifndef GUARD_BATTLE_INTERFACE_H
#define GUARD_BATTLE_INTERFACE_H

#include "battle_controllers.h"

enum
{
    HP_CURRENT,
    HP_MAX
};

enum
{
    HEALTH_BAR,
    EXP_BAR
};

enum
{
    HP_BAR_EMPTY,
    HP_BAR_RED,
    HP_BAR_YELLOW,
    HP_BAR_GREEN,
    HP_BAR_FULL,
};

#define TAG_HEALTHBOX_PLAYER1_TILE      0xD6FF
#define TAG_HEALTHBOX_PLAYER2_TILE      0xD700
#define TAG_HEALTHBOX_OPPONENT1_TILE    0xD701
#define TAG_HEALTHBOX_OPPONENT2_TILE    0xD702

#define TAG_HEALTHBAR_PLAYER1_TILE      0xD704
#define TAG_HEALTHBAR_OPPONENT1_TILE    0xD705
#define TAG_HEALTHBAR_PLAYER2_TILE      0xD706
#define TAG_HEALTHBAR_OPPONENT2_TILE    0xD707

#define TAG_HEALTHBOX_SAFARI_TILE       0xD70B

#define TAG_STATUS_SUMMARY_BAR_TILE     0xD70C
#define TAG_STATUS_SUMMARY_BALLS_TILE   0xD714

#define TAG_MEGA_TRIGGER_TILE			0xD777
#define TAG_MEGA_INDICATOR_TILE         0xD778

#define TAG_HEALTHBOX_PAL               0xD6FF
#define TAG_HEALTHBAR_PAL               0xD704
#define TAG_STATUS_SUMMARY_BAR_PAL      0xD710
#define TAG_STATUS_SUMMARY_BALLS_PAL    0xD712

#define TAG_MEGA_TRIGGER_PAL			0xD777
#define TAG_MEGA_INDICATOR_PAL			0xD778

#define TAG_MOVE_BOX_MYSTERY_TILE     0xD800
#define TAG_MOVE_BOX_BUG_TILE     0xD801
#define TAG_MOVE_BOX_DARK_TILE     0xD802
#define TAG_MOVE_BOX_DRAGON_TILE     0xD803
#define TAG_MOVE_BOX_ELECTRIC_TILE     0xD804
#define TAG_MOVE_BOX_FAIRY_TILE     0xD805
#define TAG_MOVE_BOX_FIGHTING_TILE     0xD806
#define TAG_MOVE_BOX_FIRE_TILE     0xD807
#define TAG_MOVE_BOX_FLYING_TILE     0xD808
#define TAG_MOVE_BOX_GHOST_TILE     0xD809
#define TAG_MOVE_BOX_GRASS_TILE     0xD80A
#define TAG_MOVE_BOX_GROUND_TILE     0xD80B
#define TAG_MOVE_BOX_ICE_TILE     0xD80C
#define TAG_MOVE_BOX_NORMAL_TILE     0xD80D
#define TAG_MOVE_BOX_POISON_TILE     0xD80E
#define TAG_MOVE_BOX_PSYCHIC_TILE     0xD80F
#define TAG_MOVE_BOX_ROCK_TILE     0xD810
#define TAG_MOVE_BOX_STEEL_TILE     0xD811
#define TAG_MOVE_BOX_WATER_TILE     0xD812
#define TAG_MOVE_BOX_MYSTERY_TILE2     0xD813
#define TAG_MOVE_BOX_BUG_TILE2     0xD814
#define TAG_MOVE_BOX_DARK_TILE2     0xD815
#define TAG_MOVE_BOX_DRAGON_TILE2     0xD816
#define TAG_MOVE_BOX_ELECTRIC_TILE2     0xD817
#define TAG_MOVE_BOX_FAIRY_TILE2     0xD818
#define TAG_MOVE_BOX_FIGHTING_TILE2     0xD819
#define TAG_MOVE_BOX_FIRE_TILE2     0xD81A
#define TAG_MOVE_BOX_FLYING_TILE2     0xD81B
#define TAG_MOVE_BOX_GHOST_TILE2     0xD81C
#define TAG_MOVE_BOX_GRASS_TILE2     0xD81D
#define TAG_MOVE_BOX_GROUND_TILE2     0xD81E
#define TAG_MOVE_BOX_ICE_TILE2     0xD81F
#define TAG_MOVE_BOX_NORMAL_TILE2     0xD820
#define TAG_MOVE_BOX_POISON_TILE2     0xD821
#define TAG_MOVE_BOX_PSYCHIC_TILE2     0xD822
#define TAG_MOVE_BOX_ROCK_TILE2     0xD823
#define TAG_MOVE_BOX_STEEL_TILE2     0xD824
#define TAG_MOVE_BOX_WATER_TILE2     0xD825
#define TAG_MOVE_BOX_MYSTERY_TILE3     0xD826
#define TAG_MOVE_BOX_BUG_TILE3     0xD827
#define TAG_MOVE_BOX_DARK_TILE3     0xD828
#define TAG_MOVE_BOX_DRAGON_TILE3     0xD829
#define TAG_MOVE_BOX_ELECTRIC_TILE3     0xD82A
#define TAG_MOVE_BOX_FAIRY_TILE3     0xD82B
#define TAG_MOVE_BOX_FIGHTING_TILE3     0xD82C
#define TAG_MOVE_BOX_FIRE_TILE3     0xD82D
#define TAG_MOVE_BOX_FLYING_TILE3     0xD82E
#define TAG_MOVE_BOX_GHOST_TILE3     0xD82F
#define TAG_MOVE_BOX_GRASS_TILE3     0xD830
#define TAG_MOVE_BOX_GROUND_TILE3     0xD831
#define TAG_MOVE_BOX_ICE_TILE3     0xD832
#define TAG_MOVE_BOX_NORMAL_TILE3     0xD833
#define TAG_MOVE_BOX_POISON_TILE3     0xD834
#define TAG_MOVE_BOX_PSYCHIC_TILE3     0xD835
#define TAG_MOVE_BOX_ROCK_TILE3     0xD836
#define TAG_MOVE_BOX_STEEL_TILE3     0xD837
#define TAG_MOVE_BOX_WATER_TILE3     0xD838
#define TAG_MOVE_BOX_MYSTERY_TILE4     0xD839
#define TAG_MOVE_BOX_BUG_TILE4     0xD83A
#define TAG_MOVE_BOX_DARK_TILE4     0xD83B
#define TAG_MOVE_BOX_DRAGON_TILE4     0xD83C
#define TAG_MOVE_BOX_ELECTRIC_TILE4     0xD83D
#define TAG_MOVE_BOX_FAIRY_TILE4     0xD83E
#define TAG_MOVE_BOX_FIGHTING_TILE4     0xD83F
#define TAG_MOVE_BOX_FIRE_TILE4     0xD840
#define TAG_MOVE_BOX_FLYING_TILE4     0xD841
#define TAG_MOVE_BOX_GHOST_TILE4     0xD842
#define TAG_MOVE_BOX_GRASS_TILE4     0xD843
#define TAG_MOVE_BOX_GROUND_TILE4     0xD844
#define TAG_MOVE_BOX_ICE_TILE4     0xD845
#define TAG_MOVE_BOX_NORMAL_TILE4     0xD846
#define TAG_MOVE_BOX_POISON_TILE4     0xD847
#define TAG_MOVE_BOX_PSYCHIC_TILE4     0xD848
#define TAG_MOVE_BOX_ROCK_TILE4     0xD849
#define TAG_MOVE_BOX_STEEL_TILE4     0xD84A
#define TAG_MOVE_BOX_WATER_TILE4     0xD84B
#define TAG_MOVE_BOX_RIGHTHALF_TILE     0xD84C
#define TAG_MOVE_BOX_MYSTERY_PAL     0xD84D
#define TAG_MOVE_BOX_BUG_PAL     0xD84E
#define TAG_MOVE_BOX_DARK_PAL     0xD84F
#define TAG_MOVE_BOX_DRAGON_PAL     0xD850
#define TAG_MOVE_BOX_ELECTRIC_PAL     0xD851
#define TAG_MOVE_BOX_FAIRY_PAL     0xD852
#define TAG_MOVE_BOX_FIGHTING_PAL     0xD853
#define TAG_MOVE_BOX_FIRE_PAL     0xD854
#define TAG_MOVE_BOX_FLYING_PAL     0xD855
#define TAG_MOVE_BOX_GHOST_PAL     0xD856
#define TAG_MOVE_BOX_GRASS_PAL     0xD857
#define TAG_MOVE_BOX_GROUND_PAL     0xD858
#define TAG_MOVE_BOX_ICE_PAL     0xD859
#define TAG_MOVE_BOX_NORMAL_PAL     0xD85A
#define TAG_MOVE_BOX_POISON_PAL     0xD85B
#define TAG_MOVE_BOX_PSYCHIC_PAL     0xD85C
#define TAG_MOVE_BOX_ROCK_PAL     0xD85D
#define TAG_MOVE_BOX_STEEL_PAL     0xD85E
#define TAG_MOVE_BOX_WATER_PAL     0xD85F
#define TAG_MOVE_BOX_CURSOR     0xD860

enum
{
    HEALTHBOX_ALL,
    HEALTHBOX_CURRENT_HP,
    HEALTHBOX_MAX_HP,
    HEALTHBOX_LEVEL,
    HEALTHBOX_NICK,
    HEALTHBOX_HEALTH_BAR,
    HEALTHBOX_EXP_BAR,
    HEALTHBOX_UNUSED_7,
    HEALTHBOX_UNUSED_8,
    HEALTHBOX_STATUS_ICON,
    HEALTHBOX_SAFARI_ALL_TEXT,
    HEALTHBOX_SAFARI_BALLS_TEXT
};

u8 GetMegaIndicatorSpriteId(u32 healthboxSpriteId);
void CreateAllMoveBoxes(void);
void CreateMoveBox(u8 type, u8 position);
void CreateMoveBoxCursor(void);
void ConfirmMoveBoxCursor(void);
void ResetMoveBoxes(void);
void DestroyMoveBoxes(void);
void DestroyMoveBoxCursor(void);
void CreateMoveScreen(void);
void DestroyMoveScreen(void);
void SetMoveScreenSplitIcons(void);
void SetMoveScreenCursor(void);
void UpdateTypeBg(void);
void UpdateScrollBar(u8 totalMoveNo);
void UpdateMoveBoxList(void);
void ChangeMoveBox(u8 type, u8 position, u8 upOrDown);
void MoveBox_PrintMoveName(u8 position);
void MoveBox_PrintMovePP(u8 position);

u8 CreateBattlerHealthboxSprites(u8 battler);
u8 CreateSafariPlayerHealthboxSprites(void);
void SetBattleBarStruct(u8 battler, u8 healthboxSpriteId, s32 maxVal, s32 currVal, s32 receivedValue);
void SetHealthboxSpriteInvisible(u8 healthboxSpriteId);
void SetHealthboxSpriteVisible(u8 healthboxSpriteId);
void DestoryHealthboxSprite(u8 healthboxSpriteId);
void DummyBattleInterfaceFunc(u8 healthboxSpriteId, bool8 isDoubleBattleBankOnly);
void UpdateOamPriorityInAllHealthboxes(u8 priority);
void InitBattlerHealthboxCoords(u8 battler);
void UpdateHpTextInHealthbox(u8 healthboxSpriteId, s16 value, u8 maxOrCurrent);
void SwapHpBarsWithHpText(void);
void ChangeMegaTriggerSprite(u8 spriteId, u8 animId);
void ChangeZMoveTriggerSprite(u8 battlerId, u8 palId);
void CreateMegaTriggerSprite(u8 battlerId, u8 palId);
void CreateZMoveTriggerSprite(u8 battlerId, u8 palId);
bool32 IsMegaTriggerSpriteActive(void);
bool32 IsZMoveTriggerSpriteActive(void);
void HideMegaTriggerSprite(void);
void DestroyMegaTriggerSprite(void);
void HideZMoveTriggerSprite(void);
void DestroyZMoveTriggerSprite(void);
u32 CreateMegaIndicatorSprite(u32 battlerId, u32 which);
void DestroyMegaIndicatorSprite(u32 healthboxSpriteId);
u8 CreatePartyStatusSummarySprites(u8 battler, struct HpAndStatus *partyInfo, u8 arg2, bool8 isBattleStart);
void Task_HidePartyStatusSummary(u8 taskId);
void UpdateHealthboxAttribute(u8 healthboxSpriteId, struct Pokemon *mon, u8 elementId);
s32 MoveBattleBar(u8 battler, u8 healthboxSpriteId, u8 whichBar, u8 arg3);
u8 GetScaledHPFraction(s16 hp, s16 maxhp, u8 scale);
u8 GetHPBarLevel(s16 hp, s16 maxhp);
void CreateAbilityPopUp(u8 battlerId, u32 ability, bool32 isDoubleBattle);

#endif // GUARD_BATTLE_INTERFACE_H
