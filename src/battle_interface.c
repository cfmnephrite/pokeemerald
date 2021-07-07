#include "global.h"
#include "malloc.h"
#include "battle.h"
#include "bg.h"
#include "pokemon.h"
#include "battle_controllers.h"
#include "battle_interface.h"
#include "graphics.h"
#include "sprite.h"
#include "window.h"
#include "string_util.h"
#include "text.h"
#include "sound.h"
#include "constants/songs.h"
#include "decompress.h"
#include "task.h"
#include "util.h"
#include "gpu_regs.h"
#include "battle_message.h"
#include "pokedex.h"
#include "palette.h"
#include "international_string_util.h"
#include "safari_zone.h"
#include "battle_anim.h"
#include "constants/battle_anim.h"
#include "constants/rgb.h"
#include "battle_debug.h"
#include "constants/battle_config.h"
#include "data.h"
#include "pokemon_summary_screen.h"

enum
{   // Corresponds to gHealthboxElementsGfxTable (and the tables after it) in graphics.c
    // These are indexes into the tables, which are filled with 8x8 square pixel data.
    HEALTHBOX_GFX_HP_BAR_GREEN, //hp bar [0 pixels]
    HEALTHBOX_GFX_1,  //hp bar [1 pixels]
    HEALTHBOX_GFX_2,  //hp bar [2 pixels]
    HEALTHBOX_GFX_3,  //hp bar [3 pixels]
    HEALTHBOX_GFX_4,  //hp bar [4 pixels]
    HEALTHBOX_GFX_5,  //hp bar [5 pixels]
    HEALTHBOX_GFX_6,  //hp bar [6 pixels]
    HEALTHBOX_GFX_7, //hp bar [7 pixels]
    HEALTHBOX_GFX_8, //hp bar [8 pixels]
    HEALTHBOX_GFX_EXP_BAR, //exp bar [0 pixels]
    HEALTHBOX_GFX_10, //exp bar [1 pixels]
    HEALTHBOX_GFX_11, //exp bar [2 pixels]
    HEALTHBOX_GFX_12, //exp bar [3 pixels]
    HEALTHBOX_GFX_13, //exp bar [4 pixels]
    HEALTHBOX_GFX_14, //exp bar [5 pixels]
    HEALTHBOX_GFX_15, //exp bar [6 pixels]
    HEALTHBOX_GFX_16, //exp bar [7 pixels]
    HEALTHBOX_GFX_17, //exp bar [8 pixels]
    HEALTHBOX_GFX_18, //exp bar [9 pixels]
    HEALTHBOX_GFX_19, //exp bar [10 pixels]
    HEALTHBOX_GFX_STATUS_SLP,
    HEALTHBOX_GFX_21,
    HEALTHBOX_GFX_STATUS_FRZ,
    HEALTHBOX_GFX_23,
    HEALTHBOX_GFX_STATUS_PAR,
    HEALTHBOX_GFX_25,
    HEALTHBOX_GFX_STATUS_BRN,
    HEALTHBOX_GFX_27,
    HEALTHBOX_GFX_STATUS_PSN,
    HEALTHBOX_GFX_29,
    HEALTHBOX_GFX_STATUS_TOX,
    HEALTHBOX_GFX_31,
    HEALTHBOX_GFX_STATUS_NONE,
    HEALTHBOX_GFX_33,
    HEALTHBOX_GFX_STATUS_SLP2,
    HEALTHBOX_GFX_35,
    HEALTHBOX_GFX_STATUS_FRZ2,
    HEALTHBOX_GFX_37,
    HEALTHBOX_GFX_STATUS_PAR2,
    HEALTHBOX_GFX_39,
    HEALTHBOX_GFX_STATUS_BRN2,
    HEALTHBOX_GFX_41,
    HEALTHBOX_GFX_STATUS_PSN2,
    HEALTHBOX_GFX_43,
    HEALTHBOX_GFX_STATUS_TOX2,
    HEALTHBOX_GFX_45,
    HEALTHBOX_GFX_STATUS_NONE2,
    HEALTHBOX_GFX_47,
    HEALTHBOX_GFX_HP_BAR_YELLOW, //hp bar yellow [0 pixels]
    HEALTHBOX_GFX_49, //hp bar yellow [1 pixels]
    HEALTHBOX_GFX_50, //hp bar yellow [2 pixels]
    HEALTHBOX_GFX_51, //hp bar yellow [3 pixels]
    HEALTHBOX_GFX_52, //hp bar yellow [4 pixels]
    HEALTHBOX_GFX_53, //hp bar yellow [5 pixels]
    HEALTHBOX_GFX_54, //hp bar yellow [6 pixels]
    HEALTHBOX_GFX_55, //hp bar yellow [7 pixels]
    HEALTHBOX_GFX_56, //hp bar yellow [8 pixels]
    HEALTHBOX_GFX_HP_BAR_RED,  //hp bar red [0 pixels]
    HEALTHBOX_GFX_58, //hp bar red [1 pixels]
    HEALTHBOX_GFX_59, //hp bar red [2 pixels]
    HEALTHBOX_GFX_60, //hp bar red [3 pixels]
    HEALTHBOX_GFX_61, //hp bar red [4 pixels]
    HEALTHBOX_GFX_62, //hp bar red [5 pixels]
    HEALTHBOX_GFX_63, //hp bar red [6 pixels]
    HEALTHBOX_GFX_64, //hp bar red [7 pixels]
    HEALTHBOX_GFX_65, //hp bar red [8 pixels]
    HEALTHBOX_GFX_CAUGHT_MARKER, //caught marker
};

#define HEALTHBOX_GFX_0 HEALTHBOX_GFX_HP_BAR_GREEN

// strings
extern const u8 gText_Slash[];
extern const u8 gText_HighlightDarkGrey[];
extern const u8 gText_DynColor2[];
extern const u8 gText_RedFemaleSymbol[];
extern const u8 gText_BlueMaleSymbol[];

// this file's functions

static const u8 *GetHealthboxElementGfxPtr(u8 elementId);
static u8* AddTextPrinterAndCreateWindowOnHealthbox(const u8 *str, u32 x, u32 y, u32 bgColor, u32 *windowId);
static u8* AddTextPrinterAndCreateWindowOnMovebox(const u8 *str, u32 x, u32 y, u32 *windowId, u8 fontId, u8 winTemplate);
static void RemoveWindowOnHealthbox(u32 windowId);
static void UpdateHpTextInHealthboxInDoubles(u8 healthboxSpriteId, s16 value, u8 maxOrCurrent);
static void UpdateStatusIconInHealthbox(u8 healthboxSpriteId);

static void TextIntoHealthboxObject(void *dest, u8 *windowTileData, s32 windowWidth);
static void SafariTextIntoHealthboxObject(void *dest, u8 *windowTileData, u32 windowWidth);
static void HpTextIntoHealthboxObject(void *dest, u8 *windowTileData, u32 windowWidth);
static void FillHealthboxObject(void *dest, u32 arg1, u32 arg2);

static void sub_8073E08(u8 taskId);
static void sub_8073F98(u8 taskId);
static void sub_8073E64(u8 taskId);

static void SpriteCB_HealthBoxOther(struct Sprite *sprite);
static void SpriteCB_HealthBar(struct Sprite *sprite);
static void sub_8074158(struct Sprite *sprite);
static void sub_8074090(struct Sprite *sprite);
static void SpriteCB_StatusSummaryBar(struct Sprite *sprite);
static void SpriteCB_StatusSummaryBallsOnBattleStart(struct Sprite *sprite);
static void SpriteCB_StatusSummaryBallsOnSwitchout(struct Sprite *sprite);

static void SpriteCb_MegaTrigger(struct Sprite *sprite);
static void SpriteCb_MegaIndicator(struct Sprite *sprite);

static s32 CalcNewBarValue(s32 maxValue, s32 oldValue, s32 receivedValue, s32 *currValue, u8 scale, u16 toAdd);
static u8 GetScaledExpFraction(s32 currValue, s32 receivedValue, s32 maxValue, u8 scale);
static void MoveBattleBarGraphically(u8 battlerId, u8 whichBar);
static u8 CalcBarFilledPixels(s32 maxValue, s32 oldValue, s32 receivedValue, s32 *currValue, u8 *arg4, u8 scale);
static void CalcExpBarFilledPixels(s32 maxValue, s32 oldValue, s32 receivedValue, s32 *currValue, u8 *arg4, u8 totalPixels);

static void SpriteCb_AbilityPopUp(struct Sprite *sprite);
static void Task_FreeAbilityPopUpGfx(u8 taskId);

// const rom data
static const struct OamData sOamData_HealthBox =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = 0,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(64x32),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(64x32),
    .tileNum = 0,
    .priority = 1,
    .paletteNum = 0,
    .affineParam = 0,
};

static const struct SpriteTemplate sHealthboxSpriteTemplates[MAX_BATTLERS_COUNT] =
{
    {
        .tileTag = TAG_HEALTHBOX_PLAYER1_TILE,
        .paletteTag = TAG_HEALTHBOX_PAL,
        .oam = &sOamData_HealthBox,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_HEALTHBOX_OPPONENT1_TILE,
        .paletteTag = TAG_HEALTHBOX_PAL,
        .oam = &sOamData_HealthBox,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_HEALTHBOX_PLAYER2_TILE,
        .paletteTag = TAG_HEALTHBOX_PAL,
        .oam = &sOamData_HealthBox,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_HEALTHBOX_OPPONENT2_TILE,
        .paletteTag = TAG_HEALTHBOX_PAL,
        .oam = &sOamData_HealthBox,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    }
};

static const struct SpriteTemplate sHealthboxSafariSpriteTemplate =
{
    .tileTag = TAG_HEALTHBOX_SAFARI_TILE,
    .paletteTag = TAG_HEALTHBOX_PAL,
    .oam = &sOamData_HealthBox,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy
};

static const struct Subsprite sHealthBox_Subsprites[] =
{
    {0,     0,  SPRITE_SHAPE(64x32),  SPRITE_SIZE(64x32),  0,      1},
    {64,    0,  SPRITE_SHAPE(64x32),  SPRITE_SIZE(64x32),  32,     1}
};

static const struct SubspriteTable sHealthBox_SubspriteTable[] =
{
    {ARRAY_COUNT(sHealthBox_Subsprites), sHealthBox_Subsprites}
};
static const struct OamData sOamData_Healthbar =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = 0,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(32x8),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(32x8),
    .tileNum = 0,
    .priority = 1,
    .paletteNum = 0,
    .affineParam = 0,
};

static const struct SpriteTemplate sHealthbarSpriteTemplates[MAX_BATTLERS_COUNT] =
{
    {
        .tileTag = TAG_HEALTHBAR_PLAYER1_TILE,
        .paletteTag = TAG_HEALTHBAR_PAL,
        .oam = &sOamData_Healthbar,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCB_HealthBar
    },
    {
        .tileTag = TAG_HEALTHBAR_OPPONENT1_TILE,
        .paletteTag = TAG_HEALTHBAR_PAL,
        .oam = &sOamData_Healthbar,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCB_HealthBar
    },
    {
        .tileTag = TAG_HEALTHBAR_PLAYER2_TILE,
        .paletteTag = TAG_HEALTHBAR_PAL,
        .oam = &sOamData_Healthbar,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCB_HealthBar
    },
    {
        .tileTag = TAG_HEALTHBAR_OPPONENT2_TILE,
        .paletteTag = TAG_HEALTHBAR_PAL,
        .oam = &sOamData_Healthbar,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCB_HealthBar
    }
};

static const struct Subsprite sHealthBar_Subsprites[] =
{
    {240,   0,  1,  1,  0,      1},
    {16,    0,  1,  1,  4,      1}
};

static const struct SubspriteTable sHealthBar_SubspriteTable[] =
{
    {ARRAY_COUNT(sHealthBar_Subsprites), sHealthBar_Subsprites},
};

static const struct Subsprite sStatusSummaryBar_Subsprites_0[] =
{
    {160,   0,  1,  1,  0,      1},
    {192,   0,  1,  1,  4,      1},
    {224,   0,  1,  1,  8,      1},
    {0,     0,  1,  1,  12,     1}
};

static const struct Subsprite sUnknown_0832C2AC[] =
{
    {160,   0,  1,  1,  0,      1},
    {192,   0,  1,  1,  4,      1},
    {224,   0,  1,  1,  8,      1},
    {0,     0,  1,  1,  8,      1},
    {32,    0,  1,  1,  8,      1},
    {64,    0,  1,  1,  12,     1}
};

static const struct SubspriteTable sStatusSummaryBar_SubspriteTable[] =
{
    {ARRAY_COUNT(sStatusSummaryBar_Subsprites_0), sStatusSummaryBar_Subsprites_0}
};

static const struct SubspriteTable sUnknown_0832C2CC[] =
{
    {ARRAY_COUNT(sUnknown_0832C2AC), sUnknown_0832C2AC}
};

static const struct CompressedSpriteSheet sStatusSummaryBarSpriteSheet =
{
    gBattleInterface_BallStatusBarGfx, 0x200, TAG_STATUS_SUMMARY_BAR_TILE
};

static const struct SpritePalette sStatusSummaryBarSpritePal =
{
    gBattleInterface_BallStatusBarPal, TAG_STATUS_SUMMARY_BAR_PAL
};

static const struct SpritePalette sStatusSummaryBallsSpritePal =
{
    gBattleInterface_BallDisplayPal, TAG_STATUS_SUMMARY_BALLS_PAL
};

static const struct SpriteSheet sStatusSummaryBallsSpriteSheet =
{
    gBattleInterface_BallDisplayGfx, 0x80, TAG_STATUS_SUMMARY_BALLS_TILE
};

static const struct OamData sOamData_StatusSummaryBalls =
{
    .y = 0,
    .affineMode = 0,
    .objMode = 0,
    .mosaic = 0,
    .bpp = 0,
    .shape = SPRITE_SHAPE(8x8),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(8x8),
    .tileNum = 0,
    .priority = 1,
    .paletteNum = 0,
    .affineParam = 0,
};

static const struct SpriteTemplate sStatusSummaryBarSpriteTemplates[2] =
{
    {
        .tileTag = TAG_STATUS_SUMMARY_BAR_TILE,
        .paletteTag = TAG_STATUS_SUMMARY_BAR_PAL,
        .oam = &sOamData_HealthBox,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCB_StatusSummaryBar
    },
    {
        .tileTag = TAG_STATUS_SUMMARY_BAR_TILE,
        .paletteTag = TAG_STATUS_SUMMARY_BAR_PAL,
        .oam = &sOamData_HealthBox,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCB_StatusSummaryBar
    }
};

static const struct SpriteTemplate sStatusSummaryBallsSpriteTemplates[2] =
{
    {
        .tileTag = TAG_STATUS_SUMMARY_BALLS_TILE,
        .paletteTag = TAG_STATUS_SUMMARY_BALLS_PAL,
        .oam = &sOamData_StatusSummaryBalls,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCB_StatusSummaryBallsOnBattleStart
    },
    {
        .tileTag = TAG_STATUS_SUMMARY_BALLS_TILE,
        .paletteTag = TAG_STATUS_SUMMARY_BALLS_PAL,
        .oam = &sOamData_StatusSummaryBalls,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCB_StatusSummaryBallsOnBattleStart
    }
};

// Move boxes

static const struct OamData sOamData_BattleMoveBoxes =
{
    .y = 0,
    .affineMode = 0,
    .objMode = 0,
    .mosaic = 0,
    .bpp = 0,
    .shape = SPRITE_SHAPE(64x64),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(64x64),
    .tileNum = 0,
    .priority = 1,
    .paletteNum = 0,
    .affineParam = 0,
};

static const struct SpriteSheet sSpriteSheets_BattleMoveBoxes[] =
{
    {gBattleMoveBoxMystery_Gfx, 0x400, TAG_MOVE_BOX_MYSTERY_TILE},
    {gBattleMoveBoxBug_Gfx, 0x400, TAG_MOVE_BOX_BUG_TILE},
    {gBattleMoveBoxDark_Gfx, 0x400, TAG_MOVE_BOX_DARK_TILE},
    {gBattleMoveBoxDragon_Gfx, 0x400, TAG_MOVE_BOX_DRAGON_TILE},
    {gBattleMoveBoxElectric_Gfx, 0x400, TAG_MOVE_BOX_ELECTRIC_TILE},
    {gBattleMoveBoxFairy_Gfx, 0x400, TAG_MOVE_BOX_FAIRY_TILE},
    {gBattleMoveBoxFighting_Gfx, 0x400, TAG_MOVE_BOX_FIGHTING_TILE},
    {gBattleMoveBoxFire_Gfx, 0x400, TAG_MOVE_BOX_FIRE_TILE},
    {gBattleMoveBoxFlying_Gfx, 0x400, TAG_MOVE_BOX_FLYING_TILE},
    {gBattleMoveBoxGhost_Gfx, 0x400, TAG_MOVE_BOX_GHOST_TILE},
    {gBattleMoveBoxGrass_Gfx, 0x400, TAG_MOVE_BOX_GRASS_TILE},
    {gBattleMoveBoxGround_Gfx, 0x400, TAG_MOVE_BOX_GROUND_TILE},
    {gBattleMoveBoxIce_Gfx, 0x400, TAG_MOVE_BOX_ICE_TILE},
    {gBattleMoveBoxNormal_Gfx, 0x400, TAG_MOVE_BOX_NORMAL_TILE},
    {gBattleMoveBoxPoison_Gfx, 0x400, TAG_MOVE_BOX_POISON_TILE},
    {gBattleMoveBoxPsychic_Gfx, 0x400, TAG_MOVE_BOX_PSYCHIC_TILE},
    {gBattleMoveBoxRock_Gfx, 0x400, TAG_MOVE_BOX_ROCK_TILE},
    {gBattleMoveBoxSteel_Gfx, 0x400, TAG_MOVE_BOX_STEEL_TILE},
    {gBattleMoveBoxWater_Gfx, 0x400, TAG_MOVE_BOX_WATER_TILE},
    {gBattleMoveBoxMystery_Gfx, 0x400, TAG_MOVE_BOX_MYSTERY_TILE2},
    {gBattleMoveBoxBug_Gfx, 0x400, TAG_MOVE_BOX_BUG_TILE2},
    {gBattleMoveBoxDark_Gfx, 0x400, TAG_MOVE_BOX_DARK_TILE2},
    {gBattleMoveBoxDragon_Gfx, 0x400, TAG_MOVE_BOX_DRAGON_TILE2},
    {gBattleMoveBoxElectric_Gfx, 0x400, TAG_MOVE_BOX_ELECTRIC_TILE2},
    {gBattleMoveBoxFairy_Gfx, 0x400, TAG_MOVE_BOX_FAIRY_TILE2},
    {gBattleMoveBoxFighting_Gfx, 0x400, TAG_MOVE_BOX_FIGHTING_TILE2},
    {gBattleMoveBoxFire_Gfx, 0x400, TAG_MOVE_BOX_FIRE_TILE2},
    {gBattleMoveBoxFlying_Gfx, 0x400, TAG_MOVE_BOX_FLYING_TILE2},
    {gBattleMoveBoxGhost_Gfx, 0x400, TAG_MOVE_BOX_GHOST_TILE2},
    {gBattleMoveBoxGrass_Gfx, 0x400, TAG_MOVE_BOX_GRASS_TILE2},
    {gBattleMoveBoxGround_Gfx, 0x400, TAG_MOVE_BOX_GROUND_TILE2},
    {gBattleMoveBoxIce_Gfx, 0x400, TAG_MOVE_BOX_ICE_TILE2},
    {gBattleMoveBoxNormal_Gfx, 0x400, TAG_MOVE_BOX_NORMAL_TILE2},
    {gBattleMoveBoxPoison_Gfx, 0x400, TAG_MOVE_BOX_POISON_TILE2},
    {gBattleMoveBoxPsychic_Gfx, 0x400, TAG_MOVE_BOX_PSYCHIC_TILE2},
    {gBattleMoveBoxRock_Gfx, 0x400, TAG_MOVE_BOX_ROCK_TILE2},
    {gBattleMoveBoxSteel_Gfx, 0x400, TAG_MOVE_BOX_STEEL_TILE2},
    {gBattleMoveBoxWater_Gfx, 0x400, TAG_MOVE_BOX_WATER_TILE2},
    {gBattleMoveBoxMystery_Gfx, 0x400, TAG_MOVE_BOX_MYSTERY_TILE3},
    {gBattleMoveBoxBug_Gfx, 0x400, TAG_MOVE_BOX_BUG_TILE3},
    {gBattleMoveBoxDark_Gfx, 0x400, TAG_MOVE_BOX_DARK_TILE3},
    {gBattleMoveBoxDragon_Gfx, 0x400, TAG_MOVE_BOX_DRAGON_TILE3},
    {gBattleMoveBoxElectric_Gfx, 0x400, TAG_MOVE_BOX_ELECTRIC_TILE3},
    {gBattleMoveBoxFairy_Gfx, 0x400, TAG_MOVE_BOX_FAIRY_TILE3},
    {gBattleMoveBoxFighting_Gfx, 0x400, TAG_MOVE_BOX_FIGHTING_TILE3},
    {gBattleMoveBoxFire_Gfx, 0x400, TAG_MOVE_BOX_FIRE_TILE3},
    {gBattleMoveBoxFlying_Gfx, 0x400, TAG_MOVE_BOX_FLYING_TILE3},
    {gBattleMoveBoxGhost_Gfx, 0x400, TAG_MOVE_BOX_GHOST_TILE3},
    {gBattleMoveBoxGrass_Gfx, 0x400, TAG_MOVE_BOX_GRASS_TILE3},
    {gBattleMoveBoxGround_Gfx, 0x400, TAG_MOVE_BOX_GROUND_TILE3},
    {gBattleMoveBoxIce_Gfx, 0x400, TAG_MOVE_BOX_ICE_TILE3},
    {gBattleMoveBoxNormal_Gfx, 0x400, TAG_MOVE_BOX_NORMAL_TILE3},
    {gBattleMoveBoxPoison_Gfx, 0x400, TAG_MOVE_BOX_POISON_TILE3},
    {gBattleMoveBoxPsychic_Gfx, 0x400, TAG_MOVE_BOX_PSYCHIC_TILE3},
    {gBattleMoveBoxRock_Gfx, 0x400, TAG_MOVE_BOX_ROCK_TILE3},
    {gBattleMoveBoxSteel_Gfx, 0x400, TAG_MOVE_BOX_STEEL_TILE3},
    {gBattleMoveBoxWater_Gfx, 0x400, TAG_MOVE_BOX_WATER_TILE3},
    {gBattleMoveBoxMystery_Gfx, 0x400, TAG_MOVE_BOX_MYSTERY_TILE4},
    {gBattleMoveBoxBug_Gfx, 0x400, TAG_MOVE_BOX_BUG_TILE4},
    {gBattleMoveBoxDark_Gfx, 0x400, TAG_MOVE_BOX_DARK_TILE4},
    {gBattleMoveBoxDragon_Gfx, 0x400, TAG_MOVE_BOX_DRAGON_TILE4},
    {gBattleMoveBoxElectric_Gfx, 0x400, TAG_MOVE_BOX_ELECTRIC_TILE4},
    {gBattleMoveBoxFairy_Gfx, 0x400, TAG_MOVE_BOX_FAIRY_TILE4},
    {gBattleMoveBoxFighting_Gfx, 0x400, TAG_MOVE_BOX_FIGHTING_TILE4},
    {gBattleMoveBoxFire_Gfx, 0x400, TAG_MOVE_BOX_FIRE_TILE4},
    {gBattleMoveBoxFlying_Gfx, 0x400, TAG_MOVE_BOX_FLYING_TILE4},
    {gBattleMoveBoxGhost_Gfx, 0x400, TAG_MOVE_BOX_GHOST_TILE4},
    {gBattleMoveBoxGrass_Gfx, 0x400, TAG_MOVE_BOX_GRASS_TILE4},
    {gBattleMoveBoxGround_Gfx, 0x400, TAG_MOVE_BOX_GROUND_TILE4},
    {gBattleMoveBoxIce_Gfx, 0x400, TAG_MOVE_BOX_ICE_TILE4},
    {gBattleMoveBoxNormal_Gfx, 0x400, TAG_MOVE_BOX_NORMAL_TILE4},
    {gBattleMoveBoxPoison_Gfx, 0x400, TAG_MOVE_BOX_POISON_TILE4},
    {gBattleMoveBoxPsychic_Gfx, 0x400, TAG_MOVE_BOX_PSYCHIC_TILE4},
    {gBattleMoveBoxRock_Gfx, 0x400, TAG_MOVE_BOX_ROCK_TILE4},
    {gBattleMoveBoxSteel_Gfx, 0x400, TAG_MOVE_BOX_STEEL_TILE4},
    {gBattleMoveBoxWater_Gfx, 0x400, TAG_MOVE_BOX_WATER_TILE4},
    {gBattleMoveBoxRightHalf_Gfx, 0x400, TAG_MOVE_BOX_RIGHTHALF_TILE},
    {gBattleMoveBoxCursor, 0x100, TAG_MOVE_BOX_CURSOR}
};

static const struct SpritePalette sSpritePalettes_BattleMoveBoxes[] =
{
    {gBattleMoveBoxNormal_Pal, TAG_MOVE_BOX_MYSTERY_PAL},
    {gBattleMoveBoxBug_Pal, TAG_MOVE_BOX_BUG_PAL},
    {gBattleMoveBoxDark_Pal, TAG_MOVE_BOX_DARK_PAL},
    {gBattleMoveBoxDragon_Pal, TAG_MOVE_BOX_DRAGON_PAL},
    {gBattleMoveBoxElectric_Pal, TAG_MOVE_BOX_ELECTRIC_PAL},
    {gBattleMoveBoxFairy_Pal, TAG_MOVE_BOX_FAIRY_PAL},
    {gBattleMoveBoxFighting_Pal, TAG_MOVE_BOX_FIGHTING_PAL},
    {gBattleMoveBoxFire_Pal, TAG_MOVE_BOX_FIRE_PAL},
    {gBattleMoveBoxFlying_Pal, TAG_MOVE_BOX_FLYING_PAL},
    {gBattleMoveBoxGhost_Pal, TAG_MOVE_BOX_GHOST_PAL},
    {gBattleMoveBoxGrass_Pal, TAG_MOVE_BOX_GRASS_PAL},
    {gBattleMoveBoxGround_Pal, TAG_MOVE_BOX_GROUND_PAL},
    {gBattleMoveBoxIce_Pal, TAG_MOVE_BOX_ICE_PAL},
    {gBattleMoveBoxNormal_Pal, TAG_MOVE_BOX_NORMAL_PAL},
    {gBattleMoveBoxPoison_Pal, TAG_MOVE_BOX_POISON_PAL},
    {gBattleMoveBoxPsychic_Pal, TAG_MOVE_BOX_PSYCHIC_PAL},
    {gBattleMoveBoxRock_Pal, TAG_MOVE_BOX_ROCK_PAL},
    {gBattleMoveBoxSteel_Pal, TAG_MOVE_BOX_STEEL_PAL},
    {gBattleMoveBoxWater_Pal, TAG_MOVE_BOX_WATER_PAL}
};

static const struct SpriteTemplate sBattleMoveBoxSpriteTemplates[] =
{
    {
        .tileTag = TAG_MOVE_BOX_MYSTERY_TILE,
        .paletteTag = TAG_MOVE_BOX_MYSTERY_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_BUG_TILE,
        .paletteTag = TAG_MOVE_BOX_BUG_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_DARK_TILE,
        .paletteTag = TAG_MOVE_BOX_DARK_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_DRAGON_TILE,
        .paletteTag = TAG_MOVE_BOX_DRAGON_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_ELECTRIC_TILE,
        .paletteTag = TAG_MOVE_BOX_ELECTRIC_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_FAIRY_TILE,
        .paletteTag = TAG_MOVE_BOX_FAIRY_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_FIGHTING_TILE,
        .paletteTag = TAG_MOVE_BOX_FIGHTING_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_FIRE_TILE,
        .paletteTag = TAG_MOVE_BOX_FIRE_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_FLYING_TILE,
        .paletteTag = TAG_MOVE_BOX_FLYING_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_GHOST_TILE,
        .paletteTag = TAG_MOVE_BOX_GHOST_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_GRASS_TILE,
        .paletteTag = TAG_MOVE_BOX_GRASS_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_GROUND_TILE,
        .paletteTag = TAG_MOVE_BOX_GROUND_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_ICE_TILE,
        .paletteTag = TAG_MOVE_BOX_ICE_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_NORMAL_TILE,
        .paletteTag = TAG_MOVE_BOX_NORMAL_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_POISON_TILE,
        .paletteTag = TAG_MOVE_BOX_POISON_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_PSYCHIC_TILE,
        .paletteTag = TAG_MOVE_BOX_PSYCHIC_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_ROCK_TILE,
        .paletteTag = TAG_MOVE_BOX_ROCK_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_STEEL_TILE,
        .paletteTag = TAG_MOVE_BOX_STEEL_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_WATER_TILE,
        .paletteTag = TAG_MOVE_BOX_WATER_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_MYSTERY_TILE2,
        .paletteTag = TAG_MOVE_BOX_MYSTERY_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_BUG_TILE2,
        .paletteTag = TAG_MOVE_BOX_BUG_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_DARK_TILE2,
        .paletteTag = TAG_MOVE_BOX_DARK_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_DRAGON_TILE2,
        .paletteTag = TAG_MOVE_BOX_DRAGON_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_ELECTRIC_TILE2,
        .paletteTag = TAG_MOVE_BOX_ELECTRIC_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_FAIRY_TILE2,
        .paletteTag = TAG_MOVE_BOX_FAIRY_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_FIGHTING_TILE2,
        .paletteTag = TAG_MOVE_BOX_FIGHTING_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_FIRE_TILE2,
        .paletteTag = TAG_MOVE_BOX_FIRE_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_FLYING_TILE2,
        .paletteTag = TAG_MOVE_BOX_FLYING_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_GHOST_TILE2,
        .paletteTag = TAG_MOVE_BOX_GHOST_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_GRASS_TILE2,
        .paletteTag = TAG_MOVE_BOX_GRASS_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_GROUND_TILE2,
        .paletteTag = TAG_MOVE_BOX_GROUND_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_ICE_TILE2,
        .paletteTag = TAG_MOVE_BOX_ICE_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_NORMAL_TILE2,
        .paletteTag = TAG_MOVE_BOX_NORMAL_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_POISON_TILE2,
        .paletteTag = TAG_MOVE_BOX_POISON_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_PSYCHIC_TILE2,
        .paletteTag = TAG_MOVE_BOX_PSYCHIC_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_ROCK_TILE2,
        .paletteTag = TAG_MOVE_BOX_ROCK_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_STEEL_TILE2,
        .paletteTag = TAG_MOVE_BOX_STEEL_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_WATER_TILE2,
        .paletteTag = TAG_MOVE_BOX_WATER_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_MYSTERY_TILE3,
        .paletteTag = TAG_MOVE_BOX_MYSTERY_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_BUG_TILE3,
        .paletteTag = TAG_MOVE_BOX_BUG_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_DARK_TILE3,
        .paletteTag = TAG_MOVE_BOX_DARK_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_DRAGON_TILE3,
        .paletteTag = TAG_MOVE_BOX_DRAGON_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_ELECTRIC_TILE3,
        .paletteTag = TAG_MOVE_BOX_ELECTRIC_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_FAIRY_TILE3,
        .paletteTag = TAG_MOVE_BOX_FAIRY_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_FIGHTING_TILE3,
        .paletteTag = TAG_MOVE_BOX_FIGHTING_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_FIRE_TILE3,
        .paletteTag = TAG_MOVE_BOX_FIRE_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_FLYING_TILE3,
        .paletteTag = TAG_MOVE_BOX_FLYING_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_GHOST_TILE3,
        .paletteTag = TAG_MOVE_BOX_GHOST_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_GRASS_TILE3,
        .paletteTag = TAG_MOVE_BOX_GRASS_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_GROUND_TILE3,
        .paletteTag = TAG_MOVE_BOX_GROUND_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_ICE_TILE3,
        .paletteTag = TAG_MOVE_BOX_ICE_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_NORMAL_TILE3,
        .paletteTag = TAG_MOVE_BOX_NORMAL_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_POISON_TILE3,
        .paletteTag = TAG_MOVE_BOX_POISON_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_PSYCHIC_TILE3,
        .paletteTag = TAG_MOVE_BOX_PSYCHIC_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_ROCK_TILE3,
        .paletteTag = TAG_MOVE_BOX_ROCK_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_STEEL_TILE3,
        .paletteTag = TAG_MOVE_BOX_STEEL_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_WATER_TILE3,
        .paletteTag = TAG_MOVE_BOX_WATER_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_MYSTERY_TILE4,
        .paletteTag = TAG_MOVE_BOX_MYSTERY_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_BUG_TILE4,
        .paletteTag = TAG_MOVE_BOX_BUG_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_DARK_TILE4,
        .paletteTag = TAG_MOVE_BOX_DARK_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_DRAGON_TILE4,
        .paletteTag = TAG_MOVE_BOX_DRAGON_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_ELECTRIC_TILE4,
        .paletteTag = TAG_MOVE_BOX_ELECTRIC_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_FAIRY_TILE4,
        .paletteTag = TAG_MOVE_BOX_FAIRY_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_FIGHTING_TILE4,
        .paletteTag = TAG_MOVE_BOX_FIGHTING_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_FIRE_TILE4,
        .paletteTag = TAG_MOVE_BOX_FIRE_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_FLYING_TILE4,
        .paletteTag = TAG_MOVE_BOX_FLYING_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_GHOST_TILE4,
        .paletteTag = TAG_MOVE_BOX_GHOST_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_GRASS_TILE4,
        .paletteTag = TAG_MOVE_BOX_GRASS_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_GROUND_TILE4,
        .paletteTag = TAG_MOVE_BOX_GROUND_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_ICE_TILE4,
        .paletteTag = TAG_MOVE_BOX_ICE_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_NORMAL_TILE4,
        .paletteTag = TAG_MOVE_BOX_NORMAL_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_POISON_TILE4,
        .paletteTag = TAG_MOVE_BOX_POISON_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_PSYCHIC_TILE4,
        .paletteTag = TAG_MOVE_BOX_PSYCHIC_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_ROCK_TILE4,
        .paletteTag = TAG_MOVE_BOX_ROCK_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_STEEL_TILE4,
        .paletteTag = TAG_MOVE_BOX_STEEL_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_MOVE_BOX_WATER_TILE4,
        .paletteTag = TAG_MOVE_BOX_WATER_PAL,
        .oam = &sOamData_BattleMoveBoxes,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    }
};

static const struct Subsprite sBattleMoveBoxSubsprites[] =
{
    {
        .x = 0,
        .y = 0,
        .shape = SPRITE_SHAPE(64x32),
        .size = SPRITE_SIZE(64x32),
        .tileOffset = 0,
        .priority = 1
    },
    {
        .x = 64,
        .y = 0,
        .shape = SPRITE_SHAPE(64x32),
        .size = SPRITE_SIZE(64x32),
        .tileOffset = 32,
        .priority = 1
    }
};

static const struct SubspriteTable sBattleMoveBoxSubspriteTable[] =
{
    {ARRAY_COUNT(sBattleMoveBoxSubsprites), sBattleMoveBoxSubsprites}
};

// Movebox cursor

static const struct OamData sOamData_BattleMoveBoxCursor =
{
    .y = 0,
    .affineMode = 0,
    .objMode = 0,
    .mosaic = 0,
    .bpp = 0,
    .shape = SPRITE_SHAPE(16x16),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(16x16),
    .tileNum = 0,
    .priority = 1,
    .paletteNum = 0,
    .affineParam = 0,
};

static const union AnimCmd sBattleMoveBoxCursorAnim[] =
{
    ANIMCMD_FRAME(0, 20),
    ANIMCMD_FRAME(4, 20),
    ANIMCMD_JUMP(0)
};

static const union AnimCmd sBattleMoveBoxCursorPause[] =
{
    ANIMCMD_FRAME(0, 0),
    ANIMCMD_END
};

static const union AnimCmd *const sBattleMoveBoxCursorAnimTable[] =
{
    sBattleMoveBoxCursorAnim,
    sBattleMoveBoxCursorPause
};

static void SpriteCallback_MoveBoxCursor(struct Sprite *sprite)
{
    if ((sprite->pos1.y - 113) > 23 * sprite->oam.affineParam)
    {
        sprite->pos1.y -= 2;
        if (sprite->pos1.y - 113 != 23 * sprite->oam.affineParam)
            sprite->pos1.y--;

    }
    else if ((sprite->pos1.y - 113) < 23 * sprite->oam.affineParam)
    {
        sprite->pos1.y += 2;
        if (sprite->pos1.y - 113 != 23 * sprite->oam.affineParam)
            sprite->pos1.y++;
    }
}

static const struct SpriteTemplate sBattleMoveBoxCursor =
{
    .tileTag = TAG_MOVE_BOX_CURSOR,
    .paletteTag = TAG_HEALTHBOX_PAL,
    .oam = &sOamData_BattleMoveBoxCursor,
    .anims = sBattleMoveBoxCursorAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallback_MoveBoxCursor
};

static const struct Subsprite sBattleMoveBoxCursorSubsprites[] =
{
    {0,     0,  0,  0,  0,      0},
    {120,   0,  0,  0,  1,      0},
    {0,    14,  0,  0,  2,      0},
    {120,  14,  0,  0,  3,      0}
};

static const struct Subsprite sBattleMoveBoxCursorPausedSubsprites[] =
{
    {0,     0,  0,  0,  0,      1},
    {120,   0,  0,  0,  1,      1},
    {0,    14,  0,  0,  2,      1},
    {120,  14,  0,  0,  3,      1}
};

static const struct SubspriteTable sBattleMoveBoxCursorSubspriteTable[] =
{
    {ARRAY_COUNT(sBattleMoveBoxCursorSubsprites), sBattleMoveBoxCursorSubsprites},
};

static const struct SubspriteTable sBattleMoveBoxCursorPausedSubspriteTable[] =
{
    {ARRAY_COUNT(sBattleMoveBoxCursorPausedSubsprites), sBattleMoveBoxCursorPausedSubsprites}
};


// possibly text
static const u8 sUnknown_0832C3C4[] =
{
    0xfc, 0x01, 0x01, 0xfc, 0x02, 0x02, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
};

// possibly text
static const u8 sUnknown_0832C3D8[] =
{
    0xfc, 0x01, 0x01, 0xfc, 0x02, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
};

enum
{
    PAL_STATUS_PSN,
    PAL_STATUS_PAR,
    PAL_STATUS_SLP,
    PAL_STATUS_FRZ,
    PAL_STATUS_BRN
};

static const u16 sStatusIconColors[] =
{
    [PAL_STATUS_PSN] = RGB(24, 12, 24),
    [PAL_STATUS_PAR] = RGB(23, 23, 3),
    [PAL_STATUS_SLP] = RGB(20, 20, 17),
    [PAL_STATUS_FRZ] = RGB(17, 22, 28),
    [PAL_STATUS_BRN] = RGB(28, 14, 10),
};

static const struct WindowTemplate sHealthboxWindowTemplate = {0, 0, 0, 8, 2, 0, 0}; // width = 8, height = 2

static const u8 sMegaTriggerGfx[] = INCBIN_U8("graphics/battle_interface/mega_trigger.4bpp");
static const u16 sMegaTriggerPal[] = INCBIN_U16("graphics/battle_interface/mega_trigger.gbapal");

static const struct SpriteSheet sSpriteSheet_MegaTrigger =
{
    sMegaTriggerGfx, sizeof(sMegaTriggerGfx), TAG_MEGA_TRIGGER_TILE
};
static const struct SpritePalette sSpritePalette_MegaTrigger =
{
    sMegaTriggerPal, TAG_MEGA_TRIGGER_PAL
};

static const struct OamData sOamData_MegaTrigger =
{
    .y = 0,
    .affineMode = 0,
    .objMode = 0,
    .mosaic = 0,
    .bpp = 0,
    .shape = ST_OAM_SQUARE,
    .x = 0,
    .matrixNum = 0,
    .size = 2,
    .tileNum = 0,
    .priority = 1,
    .paletteNum = 0,
    .affineParam = 0,
};

static const union AnimCmd sSpriteAnim_MegaTriggerOff[] =
{
    ANIMCMD_FRAME(0, 0),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_MegaTriggerOn[] =
{
    ANIMCMD_FRAME(16, 0),
    ANIMCMD_END
};

static const union AnimCmd *const sSpriteAnimTable_MegaTrigger[] =
{
    sSpriteAnim_MegaTriggerOff,
    sSpriteAnim_MegaTriggerOn,
};

static const struct SpriteTemplate sSpriteTemplate_MegaTrigger =
{
    .tileTag = TAG_MEGA_TRIGGER_TILE,
    .paletteTag = TAG_MEGA_TRIGGER_PAL,
    .oam = &sOamData_MegaTrigger,
    .anims = sSpriteAnimTable_MegaTrigger,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCb_MegaTrigger
};

static const u8 sMegaIndicatorGfx[] = INCBIN_U8("graphics/battle_interface/mega_indicator.4bpp");
static const u16 sMegaIndicatorPal[] = INCBIN_U16("graphics/battle_interface/mega_indicator.gbapal");

static const struct SpriteSheet sSpriteSheet_MegaIndicator =
{
    sMegaIndicatorGfx, sizeof(sMegaIndicatorGfx), TAG_MEGA_INDICATOR_TILE
};
static const struct SpritePalette sSpritePalette_MegaIndicator =
{
    sMegaIndicatorPal, TAG_MEGA_INDICATOR_PAL
};

static const struct OamData sOamData_MegaIndicator =
{
    .y = 0,
    .affineMode = 0,
    .objMode = 0,
    .mosaic = 0,
    .bpp = 0,
    .shape = SPRITE_SHAPE(16x16),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(16x16),
    .tileNum = 0,
    .priority = 1,
    .paletteNum = 0,
    .affineParam = 0,
};

static const struct SpriteTemplate sSpriteTemplate_MegaIndicator =
{
    .tileTag = TAG_MEGA_INDICATOR_TILE,
    .paletteTag = TAG_MEGA_INDICATOR_PAL,
    .oam = &sOamData_MegaIndicator,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCb_MegaIndicator,
};


// code

// Because the healthbox is too large to fit into one sprite, it is divided into two sprites.
// healthboxLeft  or healthboxMain  is the left part that is used as the 'main' sprite.
// healthboxRight or healthboxOther is the right part of the healthbox.
// There's also the third sprite under name of healthbarSprite that refers to the healthbar visible on the healtbox.

// data fields for healthboxMain
// oam.affineParam holds healthboxRight spriteId
#define hMain_HealthBarSpriteId     data[5]
#define hMain_Battler               data[6]
#define hOther_IndicatorSpriteId    data[7] // For Mega Evo

// data fields for healthboxRight
#define hOther_HealthBoxSpriteId    data[5]
#define hOther_Data6                data[6] // WAS For Mega Evo

// data fields for healthbar
#define hBar_HealthBoxSpriteId      data[5]
#define hBar_Data6                  data[6]

u8 GetMegaIndicatorSpriteId(u32 healthboxSpriteId)
{
    if (healthboxSpriteId >= MAX_SPRITES)
        return 0xFF;
    return gSprites[healthboxSpriteId].hOther_IndicatorSpriteId;
}

u8 CreateBattlerHealthboxSprites(u8 battlerId)
{
    s16 data6 = 0;
    u8 healthboxSpriteId, healthbarSpriteId, megaIndicatorSpriteId;

    healthboxSpriteId = CreateSprite(&sHealthboxSpriteTemplates[battlerId], 240, 160, 1);
    SetSubspriteTables(&gSprites[healthboxSpriteId], sHealthBox_SubspriteTable);

    healthbarSpriteId = CreateSpriteAtEnd(&sHealthbarSpriteTemplates[gBattlerPositions[battlerId]], 240, 160, 0);
    SetSubspriteTables(&gSprites[healthbarSpriteId], sHealthBar_SubspriteTable);

    gSprites[healthbarSpriteId].subspriteMode = 2;
    gSprites[healthbarSpriteId].oam.priority = 1;

    gSprites[healthboxSpriteId].hMain_HealthBarSpriteId = healthbarSpriteId;
    gSprites[healthboxSpriteId].hMain_Battler = battlerId;
    gSprites[healthboxSpriteId].hOther_IndicatorSpriteId = 0xFF;
    gSprites[healthboxSpriteId].invisible = TRUE;

    gSprites[healthbarSpriteId].hBar_HealthBoxSpriteId = healthboxSpriteId;
    gSprites[healthbarSpriteId].hBar_Data6 = GetBattlerSide(battlerId);
    gSprites[healthbarSpriteId].invisible = TRUE;

    // Create mega indicator sprite if is a mega evolved mon.
    if (gBattleStruct->mega.evolvedPartyIds[GetBattlerSide(battlerId)] & gBitTable[gBattlerPartyIndexes[battlerId]])
    {
        megaIndicatorSpriteId = CreateMegaIndicatorSprite(battlerId, 0);
        gSprites[megaIndicatorSpriteId].invisible = TRUE;
    }

    return healthboxSpriteId;
}

u8 CreateSafariPlayerHealthboxSprites(void)
{
    u8 healthboxLeftSpriteId, healthboxRightSpriteId;

    healthboxLeftSpriteId = CreateSprite(&sHealthboxSafariSpriteTemplate, 240, 160, 1);
    healthboxRightSpriteId = CreateSpriteAtEnd(&sHealthboxSafariSpriteTemplate, 240, 160, 1);

    gSprites[healthboxLeftSpriteId].oam.shape = ST_OAM_SQUARE;
    gSprites[healthboxRightSpriteId].oam.shape = ST_OAM_SQUARE;

    gSprites[healthboxRightSpriteId].oam.tileNum += 64;

    gSprites[healthboxLeftSpriteId].oam.affineParam = healthboxRightSpriteId;
    gSprites[healthboxRightSpriteId].hOther_HealthBoxSpriteId = healthboxLeftSpriteId;

    gSprites[healthboxRightSpriteId].hOther_IndicatorSpriteId = 0xFF;

    gSprites[healthboxRightSpriteId].callback = SpriteCB_HealthBoxOther;

    return healthboxLeftSpriteId;
}

static const u8 *GetHealthboxElementGfxPtr(u8 elementId)
{
    return gHealthboxElementsGfxTable[elementId];
}

// Syncs the position of healthbar accordingly with the healthbox.
static void SpriteCB_HealthBar(struct Sprite *sprite)
{
    u8 healthboxSpriteId = sprite->hBar_HealthBoxSpriteId;

    switch (sprite->hBar_Data6)
    {
    case 0:
        sprite->pos1.x = gSprites[healthboxSpriteId].pos1.x + 42;
        sprite->pos1.y = gSprites[healthboxSpriteId].pos1.y + 16;
        break;
    case 1:
        sprite->pos1.x = gSprites[healthboxSpriteId].pos1.x + 61;
        sprite->pos1.y = gSprites[healthboxSpriteId].pos1.y + 16;
        break;
    }

    sprite->pos2.x = gSprites[healthboxSpriteId].pos2.x;
    sprite->pos2.y = gSprites[healthboxSpriteId].pos2.y;
}

static void SpriteCB_HealthBoxOther(struct Sprite *sprite)
{
    u8 healthboxMainSpriteId = sprite->hOther_HealthBoxSpriteId;

    sprite->pos1.x = gSprites[healthboxMainSpriteId].pos1.x + 64;
    sprite->pos1.y = gSprites[healthboxMainSpriteId].pos1.y;

    sprite->pos2.x = gSprites[healthboxMainSpriteId].pos2.x;
    sprite->pos2.y = gSprites[healthboxMainSpriteId].pos2.y;
}

void SetBattleBarStruct(u8 battlerId, u8 healthboxSpriteId, s32 maxVal, s32 oldVal, s32 receivedValue)
{
    gBattleSpritesDataPtr->battleBars[battlerId].healthboxSpriteId = healthboxSpriteId;
    gBattleSpritesDataPtr->battleBars[battlerId].maxValue = maxVal;
    gBattleSpritesDataPtr->battleBars[battlerId].oldValue = oldVal;
    gBattleSpritesDataPtr->battleBars[battlerId].receivedValue = receivedValue;
    gBattleSpritesDataPtr->battleBars[battlerId].currValue = -32768;
}

void SetHealthboxSpriteInvisible(u8 healthboxSpriteId)
{
    DestroyMegaIndicatorSprite(healthboxSpriteId);
    gSprites[healthboxSpriteId].invisible = TRUE;
    gSprites[gSprites[healthboxSpriteId].hMain_HealthBarSpriteId].invisible = TRUE;
}

void SetHealthboxSpriteVisible(u8 healthboxSpriteId)
{
    u8 battlerId = gSprites[healthboxSpriteId].hMain_Battler;

    gSprites[healthboxSpriteId].invisible = FALSE;
    gSprites[gSprites[healthboxSpriteId].hMain_HealthBarSpriteId].invisible = FALSE;
    if (gBattleStruct->mega.evolvedPartyIds[GetBattlerSide(battlerId)] & gBitTable[gBattlerPartyIndexes[battlerId]])
    {
        u8 spriteId = GetMegaIndicatorSpriteId(healthboxSpriteId);
        if (spriteId != 0xFF)
            gSprites[spriteId].invisible = FALSE;
        else
            CreateMegaIndicatorSprite(battlerId, 0);
    }
}

static void UpdateSpritePos(u8 spriteId, s16 x, s16 y)
{
    gSprites[spriteId].pos1.x = x;
    gSprites[spriteId].pos1.y = y;
}

void DestoryHealthboxSprite(u8 healthboxSpriteId)
{
    DestroyMegaIndicatorSprite(healthboxSpriteId);
    DestroySprite(&gSprites[gSprites[healthboxSpriteId].hMain_HealthBarSpriteId]);
    DestroySprite(&gSprites[healthboxSpriteId]);
}

void DummyBattleInterfaceFunc(u8 healthboxSpriteId, bool8 isDoubleBattleBattlerOnly)
{

}

static void TryToggleHealboxVisibility(u8 priority, u8 healthboxLeftSpriteId, u8 healthboxRightSpriteId, u8 healthbarSpriteId, u8 indicatorSpriteId)
{
    u8 spriteIds[4] = {healthboxLeftSpriteId, healthboxRightSpriteId, healthbarSpriteId, indicatorSpriteId};
    int i;
    
    switch (gBattleResources->bufferA[gBattleAnimAttacker][0])
    {
    case CONTROLLER_MOVEANIMATION:
        if (gBattleResources->bufferA[gBattleAnimAttacker][1] == MOVE_TRANSFORM)
            return;
        break;
    case CONTROLLER_BALLTHROWANIM:
        return;   //throwing ball does not hide hp boxes
    case CONTROLLER_BATTLEANIMATION:
        //check special anims that hide health boxes
        switch (gBattleResources->bufferA[gBattleAnimAttacker][1])
        {
        case B_ANIM_TURN_TRAP:
        case B_ANIM_LEECH_SEED_DRAIN:
        case B_ANIM_MON_HIT:
        case B_ANIM_SNATCH_MOVE:
        case B_ANIM_FUTURE_SIGHT_HIT:
        case B_ANIM_DOOM_DESIRE_HIT:
        case B_ANIM_WISH_HEAL:
        //new
        case B_ANIM_MEGA_EVOLUTION:
        case B_ANIM_TERRAIN_MISTY:
        case B_ANIM_TERRAIN_GRASSY:
        case B_ANIM_TERRAIN_ELECTRIC:
        case B_ANIM_TERRAIN_PSYCHIC:
            break;
        }
        return; //all other special anims dont hide
    default:
        return;
    }
    
    // if we've reached here, we should hide hp boxes
    for (i = 0; i < NELEMS(spriteIds); i++)
    {
        if (spriteIds[i] == 0xFF)
            continue;
        
        switch (priority)
        {
        case 0: //start of anim -> make invisible
            gSprites[spriteIds[i]].invisible = TRUE;
            break;
        case 1: //end of anim -> make visible
            gSprites[spriteIds[i]].invisible = FALSE;
            break;
        }
    }
}

void UpdateOamPriorityInAllHealthboxes(u8 priority)
{
    s32 i;
    
    for (i = 0; i < gBattlersCount; i++)
    {
        u8 healthboxLeftSpriteId = gHealthboxSpriteIds[i];
        u8 healthbarSpriteId = gSprites[gHealthboxSpriteIds[i]].hMain_HealthBarSpriteId;
        u8 indicatorSpriteId = GetMegaIndicatorSpriteId(healthboxLeftSpriteId);

        gSprites[healthboxLeftSpriteId].oam.priority = priority;
        gSprites[healthbarSpriteId].oam.priority = priority;
        if (indicatorSpriteId != 0xFF)
            gSprites[indicatorSpriteId].oam.priority = priority;
    }
}

void GetBattlerHealthboxCoords(u8 battler, s16 *x, s16 *y)
{
    *x = 0, *y = 0;

    if (!IsDoubleBattle())
    {
        if (GetBattlerSide(battler) != B_SIDE_PLAYER)
            *x = -22, *y = 10;
        else
            *x = 134, *y = 83;
    }
    else
    {
        switch (GetBattlerPosition(battler))
        {
        case B_POSITION_PLAYER_LEFT:
            *x = 130, *y = 83;
            break;
        case B_POSITION_PLAYER_RIGHT:
            *x = 134, *y = 60;
            break;
        case B_POSITION_OPPONENT_LEFT:
            *x = -18, *y = 23;
            break;
        case B_POSITION_OPPONENT_RIGHT:
            *x = -22, *y = 0;
            break;
        }
    }
}

void InitBattlerHealthboxCoords(u8 battler)
{
    s16 x, y;

    GetBattlerHealthboxCoords(battler, &x, &y);
    UpdateSpritePos(gHealthboxSpriteIds[battler], x, y);
}

static void UpdateLvlInHealthbox(u8 healthboxSpriteId, u8 lvl)
{
    u32 windowId, spriteTileNum;
    u8 *windowTileData;
    u8 text[16];
    u32 xPos, var1;
    u8 battler = gSprites[healthboxSpriteId].hMain_Battler;
    u8 side = GetBattlerSide(battler) == B_SIDE_PLAYER;

    text[0] = 0xF9;
    text[1] = 5;
    ConvertIntToDecimalStringN(text + 2, lvl, STR_CONV_MODE_LEFT_ALIGN, 3);
    windowTileData = AddTextPrinterAndCreateWindowOnHealthbox(text, 7, 2, 2, &windowId);
    spriteTileNum = gSprites[healthboxSpriteId].oam.tileNum * TILE_SIZE_4BPP;

    TextIntoHealthboxObject((void*)(OBJ_VRAM0 + spriteTileNum + 34 * 32), windowTileData, 3);
    RemoveWindowOnHealthbox(windowId);
}

void UpdateHpTextInHealthbox(u8 healthboxSpriteId, s16 value, u8 maxOrCurrent)
{}

static void UpdateHpTextInHealthboxInDoubles(u8 healthboxSpriteId, s16 value, u8 maxOrCurrent)
{}

// Prints mon's nature, catch and flee rate. Probably used to test pokeblock-related features.
static void PrintSafariMonInfo(u8 healthboxSpriteId, struct Pokemon *mon)
{
    u8 text[20];
    s32 j, spriteTileNum;
    u8 *barFontGfx;
    u8 i, var, nature, healthBarSpriteId;

    memcpy(text, sUnknown_0832C3C4, sizeof(sUnknown_0832C3C4));
    barFontGfx = &gMonSpritesGfxPtr->barFontGfx[0x520 + (GetBattlerPosition(gSprites[healthboxSpriteId].hMain_Battler) * 384)];
    var = 5;
    nature = GetNature(mon);
    StringCopy(text + 6, gNatureNamePointers[nature]);
    RenderTextFont9(barFontGfx, 9, text);

    for (j = 6, i = 0; i < var; i++, j++)
    {
        u8 elementId;

        if ((text[j] >= 55 && text[j] <= 74) || (text[j] >= 135 && text[j] <= 154))
            elementId = 44;
        else if ((text[j] >= 75 && text[j] <= 79) || (text[j] >= 155 && text[j] <= 159))
            elementId = 45;
        else
            elementId = 43;

        CpuCopy32(GetHealthboxElementGfxPtr(elementId), barFontGfx + (i * 64), 0x20);
    }

    for (j = 1; j < var + 1; j++)
    {
        spriteTileNum = (gSprites[healthboxSpriteId].oam.tileNum + (j - (j / 8 * 8)) + (j / 8 * 64)) * TILE_SIZE_4BPP;
        CpuCopy32(barFontGfx, (void*)(OBJ_VRAM0) + (spriteTileNum), 0x20);
        barFontGfx += 0x20;

        spriteTileNum = (8 + gSprites[healthboxSpriteId].oam.tileNum + (j - (j / 8 * 8)) + (j / 8 * 64)) * TILE_SIZE_4BPP;
        CpuCopy32(barFontGfx, (void*)(OBJ_VRAM0) + (spriteTileNum), 0x20);
        barFontGfx += 0x20;
    }

    healthBarSpriteId = gSprites[healthboxSpriteId].hMain_HealthBarSpriteId;
    ConvertIntToDecimalStringN(text + 6, gBattleStruct->safariCatchFactor, STR_CONV_MODE_RIGHT_ALIGN, 2);
    ConvertIntToDecimalStringN(text + 9, gBattleStruct->safariEscapeFactor, STR_CONV_MODE_RIGHT_ALIGN, 2);
    text[5] = CHAR_SPACE;
    text[8] = CHAR_SLASH;
    RenderTextFont9(gMonSpritesGfxPtr->barFontGfx, 9, text);

    j = healthBarSpriteId; // Needed to match for some reason.
    for (j = 0; j < 5; j++)
    {
        if (j <= 1)
        {
            CpuCopy32(&gMonSpritesGfxPtr->barFontGfx[0x40 * j + 0x20],
                      (void*)(OBJ_VRAM0) + (gSprites[healthBarSpriteId].oam.tileNum + 2 + j) * TILE_SIZE_4BPP,
                      32);
        }
        else
        {
            CpuCopy32(&gMonSpritesGfxPtr->barFontGfx[0x40 * j + 0x20],
                      (void*)(OBJ_VRAM0 + 0xC0) + (j + gSprites[healthBarSpriteId].oam.tileNum) * TILE_SIZE_4BPP,
                      32);
        }
    }
}

void SwapHpBarsWithHpText(void)
{}

// Mega Evolution gfx functions.
void ChangeMegaTriggerSprite(u8 spriteId, u8 animId)
{
    StartSpriteAnim(&gSprites[spriteId], animId);
}

// Z Move gfx functions.
void ChangeZMoveTriggerSprite(u8 spriteId, u8 animId)
{
    StartSpriteAnim(&gSprites[spriteId], animId);
}

#define SINGLES_MEGA_TRIGGER_POS_X_OPTIMAL (30)
#define SINGLES_MEGA_TRIGGER_POS_X_PRIORITY (31)
#define SINGLES_MEGA_TRIGGER_POS_X_SLIDE (15)
#define SINGLES_MEGA_TRIGGER_POS_Y_DIFF (-11)

#define DOUBLES_MEGA_TRIGGER_POS_X_OPTIMAL (30)
#define DOUBLES_MEGA_TRIGGER_POS_X_PRIORITY (31)
#define DOUBLES_MEGA_TRIGGER_POS_X_SLIDE (15)
#define DOUBLES_MEGA_TRIGGER_POS_Y_DIFF (-4)

#define tBattler    data[0]
#define tHide       data[1]

void CreateMegaTriggerSprite(u8 battlerId, u8 palId)
{
    LoadSpritePalette(&sSpritePalette_MegaTrigger);
    if (GetSpriteTileStartByTag(TAG_MEGA_TRIGGER_TILE) == 0xFFFF)
        LoadSpriteSheet(&sSpriteSheet_MegaTrigger);
    if (gBattleStruct->mega.triggerSpriteId == 0xFF)
    {
        if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
            gBattleStruct->mega.triggerSpriteId = CreateSprite(&sSpriteTemplate_MegaTrigger,
                                                             gSprites[gHealthboxSpriteIds[battlerId]].pos1.x - DOUBLES_MEGA_TRIGGER_POS_X_SLIDE,
                                                             gSprites[gHealthboxSpriteIds[battlerId]].pos1.y - DOUBLES_MEGA_TRIGGER_POS_Y_DIFF, 0);
        else
            gBattleStruct->mega.triggerSpriteId = CreateSprite(&sSpriteTemplate_MegaTrigger,
                                                             gSprites[gHealthboxSpriteIds[battlerId]].pos1.x - SINGLES_MEGA_TRIGGER_POS_X_SLIDE,
                                                             gSprites[gHealthboxSpriteIds[battlerId]].pos1.y - SINGLES_MEGA_TRIGGER_POS_Y_DIFF, 0);
    }
    gSprites[gBattleStruct->mega.triggerSpriteId].tBattler = battlerId;
    gSprites[gBattleStruct->mega.triggerSpriteId].tHide = FALSE;

    ChangeMegaTriggerSprite(gBattleStruct->mega.triggerSpriteId, palId);
}

void CreateZMoveTriggerSprite(u8 battlerId, u8 palId)
{
    LoadSpritePalette(&sSpritePalette_MegaTrigger);
    if (GetSpriteTileStartByTag(TAG_MEGA_TRIGGER_TILE) == 0xFFFF)
        LoadSpriteSheet(&sSpriteSheet_MegaTrigger);
    if (gBattleStruct->zMove.triggerSpriteId == 0xFF)
    {
        if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
            gBattleStruct->zMove.triggerSpriteId = CreateSprite(&sSpriteTemplate_MegaTrigger,
                                                             gSprites[gHealthboxSpriteIds[battlerId]].pos1.x - DOUBLES_MEGA_TRIGGER_POS_X_SLIDE,
                                                             gSprites[gHealthboxSpriteIds[battlerId]].pos1.y - DOUBLES_MEGA_TRIGGER_POS_Y_DIFF, 0);
        else
            gBattleStruct->zMove.triggerSpriteId = CreateSprite(&sSpriteTemplate_MegaTrigger,
                                                             gSprites[gHealthboxSpriteIds[battlerId]].pos1.x - SINGLES_MEGA_TRIGGER_POS_X_SLIDE,
                                                             gSprites[gHealthboxSpriteIds[battlerId]].pos1.y - SINGLES_MEGA_TRIGGER_POS_Y_DIFF, 0);
    }
    gSprites[gBattleStruct->zMove.triggerSpriteId].tBattler = battlerId;
    gSprites[gBattleStruct->zMove.triggerSpriteId].tHide = FALSE;

    ChangeZMoveTriggerSprite(gBattleStruct->zMove.triggerSpriteId, palId);
}

// Move box functions

void CreateAllMoveBoxes(void)
{
    u8 type, i;
    if (gBattleMoveBoxReset != gActiveBattler || gBattleMoveBoxReset == 0xFF)
    {
        DestroyMoveBoxes();
        for (i = 0; i < 4; i++)
        {
            if (gBattleMons[gActiveBattler].moves[i] == MOVE_NONE)
                break;
            GET_MOVE_TYPE(gBattleMons[gActiveBattler].moves[i], type)
            CreateMoveBox(type, i);
            StringCopy(gDisplayedStringBattle, gMoveDescriptionPointers[gBattleMons[gActiveBattler].moves[i] - 1]);
            ForceTextWrapping((u8*)gDisplayedStringBattle, 5, 100, -2);
            BattlePutTextOnWindow(gDisplayedStringBattle, 3 + i);
        }
        gBattleMoveBoxReset = gActiveBattler;
    }
    SetMoveScreenSplitIcons();
    PutWindowTilemap(3 + gMoveSelectionCursor[gActiveBattler]);
}

const u32 gMoveScreenPalette[] = INCBIN_U32("graphics/battle_interface/move_screen.gbapal.lz");
const u32 gMoveScreenTilemap[] = INCBIN_U32("graphics/battle_interface/move_screen.bin.lz");
const u32 gMoveScreenSplitIconsGfx[] = INCBIN_U32("graphics/battle_interface/split_icons.4bpp");
const u32 gMoveScreenScrollBarGfx[] = INCBIN_U32("graphics/battle_interface/move_screen_scroll_bar.4bpp");

void CreateMoveScreen(void)
{
    if (gBattleMoveScreenReset)
    {
        CopyToBgTilemapBuffer(2, gMoveScreenTilemap, 0, 0);
        CopyBgTilemapBufferToVram(2);
        LoadCompressedPalette(gMoveScreenPalette, 0xC0, 0x20);
        gBattleMoveScreenReset = 0;
    }
}

void DestroyMoveScreen(void)
{
    gBattleMoveScreenReset = 0xFF;
}

void SetMoveScreenSplitIcons(void)
{
    u8 splitA, splitB;
    u8 *src = (u8*)gMoveScreenSplitIconsGfx;

    splitA = GetBattleMoveSplit(gActiveBattler, gBattleMons[gActiveBattler].moves[gMoveSelectionState[gActiveBattler]]);
    if (gBattleMons[gActiveBattler].moves[1] == MOVE_NONE) // i.e. the mon only has one move
        splitB = 3;
    else
        splitB = GetBattleMoveSplit(gActiveBattler, gBattleMons[gActiveBattler].moves[gMoveSelectionState[gActiveBattler] + 1]);

    RequestSpriteCopy((src + 0x40 * splitA), (u8*)(VRAM + 162 * TILE_SIZE_4BPP), 0x40);
    RequestSpriteCopy((src + 0xC0 + (0x60 * splitB)), (u8*)(VRAM + 164 * TILE_SIZE_4BPP), 0x60);
}

void UpdateScrollBar(u8 totalMoveNo)
{
    u8 *src = (u8*)gMoveScreenScrollBarGfx;

    if (totalMoveNo == 3)
        src += 0xE0 * (1 + gMoveSelectionState[gActiveBattler]);
    else if (totalMoveNo == 4)
        src += 0xE0 * (3 + gMoveSelectionState[gActiveBattler]);

    RequestSpriteCopy(src, (u8*)(VRAM + 167 * TILE_SIZE_4BPP), 0xE0);

}

void UpdateTypeBg(void)
{
    u8 type = GetMoveType(gActiveBattler, gBattleMons[gActiveBattler].moves[gMoveSelectionCursor[gActiveBattler]], 1);

    if (type)
    {
        LoadPalette((u8*)gTypeBgBug_Pal + (type - 1) * 0x20, 0xD0, 0x20);
        RequestSpriteCopy((u8*)gTypeBgBug_Gfx + (type - 1) * 0x320, (u8 *)(VRAM + 137 * TILE_SIZE_4BPP), 0x320);
    }
    else
    {
        LZDecompressWram(gBattleTextboxTiles, gDecompressionBuffer);
        LoadPalette(&gTypeBgNormal_Pal, 0xD0, 0x20);
        RequestSpriteCopy((u8*)gDecompressionBuffer + 0x940, (u8 *)(VRAM + 137 * TILE_SIZE_4BPP), 0x320);
    }
}

void ResetMoveBoxes(void)
{
    u8 i;
    gBattleMoveBoxReset = 0xFF;
    for (i = 0; i < 4; i++)
    {
        gBattleMoveBoxSpriteIds[i] = 0;
    }
}

void DestroyMoveBoxes(void)
{
    u8 i;
    for (i = 0; i < 4; i++)
    {
        if (gBattleMoveBoxSpriteIds[i])
        {
            FreeSpritePaletteByTag(gSprites[gBattleMoveBoxSpriteIds[i]].template->paletteTag);
            FreeSpriteTilesByTag(gSprites[gBattleMoveBoxSpriteIds[i]].template->tileTag);
            FreeSpriteTilesByTag(TAG_MOVE_BOX_RIGHTHALF_TILE);
            DestroySprite(&gSprites[gBattleMoveBoxSpriteIds[i]]);
            gBattleMoveBoxSpriteIds[i] = 0;
        }
    }
    gBattleMoveBoxReset = 0xFF;
}

void DestroyMoveBoxCursor(void)
{
    u8 cursorId = GetSpriteIndexByTileTag(TAG_MOVE_BOX_CURSOR);
    if (cursorId != 0xFF)
    {
        FreeSpriteTilesByTag(TAG_MOVE_BOX_CURSOR);
        DestroySprite(&gSprites[cursorId]);
    }
}

void CreateMoveBox(u8 type, u8 index)
{
    LoadSpritePalette(&sSpritePalettes_BattleMoveBoxes[type]);
    LoadSpriteSheet(&sSpriteSheets_BattleMoveBoxes[type + index * 19]);
    LoadSpriteSheet(&sSpriteSheets_BattleMoveBoxes[76]);
    gBattleMoveBoxSpriteIds[index] = CreateSprite(&sBattleMoveBoxSpriteTemplates[type + index * 19], 2, 108 + (index % 2) * 23, 0);
    switch(index)
    {
    case 1:
        gSprites[gBattleMoveBoxSpriteIds[1]].pos1.y = 131 - (23 * gMoveSelectionState[gActiveBattler]);
        break;
    case 2:
        gSprites[gBattleMoveBoxSpriteIds[2]].pos1.y = 154 - (23 * gMoveSelectionState[gActiveBattler]);
        break;
    }
    SetSubspriteTables(&gSprites[gBattleMoveBoxSpriteIds[index]], sBattleMoveBoxSubspriteTable);
    gSprites[gBattleMoveBoxSpriteIds[index]].invisible = !(index == gMoveSelectionState[gActiveBattler] || index == gMoveSelectionState[gActiveBattler] + 1);
    MoveBox_PrintMoveName(index);
    MoveBox_PrintMovePP(index);
}

void CreateMoveBoxCursor(void)
{
    u8 index = GetSpriteIndexByTileTag(TAG_MOVE_BOX_CURSOR);
    u8 cursorParam = (gMoveSelectionCursor[gActiveBattler] > gMoveSelectionState[gActiveBattler]);
    if (index == 0xFF)
    {
        LoadSpriteSheet(&sSpriteSheets_BattleMoveBoxes[77]);
        index = CreateSprite(&sBattleMoveBoxCursor, 3, 113 + 23 * cursorParam, 0);
        gSprites[index].oam.affineParam = cursorParam;
    }
    SetSubspriteTables(&gSprites[index], sBattleMoveBoxCursorSubspriteTable);
    StartSpriteAnim(&gSprites[index], 0);
}

void ConfirmMoveBoxCursor(void)
{
    u8 cursorId = GetSpriteIndexByTileTag(TAG_MOVE_BOX_CURSOR);
    if (cursorId != 0xFF)
    {
        StartSpriteAnim(&gSprites[cursorId], 1);
        SetSubspriteTables(&gSprites[cursorId], sBattleMoveBoxCursorPausedSubspriteTable);
    }
}

void UpdateMoveBoxList(void)
{
    if (gBattleMoveBoxSpriteIds[0])
        gSprites[gBattleMoveBoxSpriteIds[0]].invisible = (gMoveSelectionState[gActiveBattler] > 0);

    if (gBattleMoveBoxSpriteIds[1])
    {
        gSprites[gBattleMoveBoxSpriteIds[1]].invisible = (gMoveSelectionState[gActiveBattler] > 1);
        gSprites[gBattleMoveBoxSpriteIds[1]].pos1.y = 131 - (23 * gMoveSelectionState[gActiveBattler]);
    }

    if (gBattleMoveBoxSpriteIds[2])
    {
        gSprites[gBattleMoveBoxSpriteIds[2]].invisible = (gMoveSelectionState[gActiveBattler] < 1);
        gSprites[gBattleMoveBoxSpriteIds[2]].pos1.y = 154 - (23 * gMoveSelectionState[gActiveBattler]);
    }

    if (gBattleMoveBoxSpriteIds[3])
        gSprites[gBattleMoveBoxSpriteIds[3]].invisible = (gMoveSelectionState[gActiveBattler] < 2);
}

void MoveBox_PrintMoveName(u8 index)
{
    u8 movename[MOVE_NAME_LENGTH + 1];
    u32 windowId, spriteTileNum;
    u8 *windowTileData;
    u16 *vramPtr, *src, *vramPtr2, *src2, *vramPtr3, *src3, *vramPtr4, *src4;
    u8 i, j;

    StringCopy(gDisplayedStringBattle, gMoveNames[gBattleMons[gActiveBattler].moves[index]]);
    windowTileData = AddTextPrinterAndCreateWindowOnMovebox(gDisplayedStringBattle, 4, 1, &windowId, 4, 0);
    spriteTileNum = gSprites[gBattleMoveBoxSpriteIds[index]].oam.tileNum * TILE_SIZE_4BPP;

    src = (u16*)windowTileData;
    src2 = src + 0x60;
    src3 = src + 0xD0;
    src4 = src + 0x130;

    vramPtr = (u16*)(OBJ_VRAM0 + spriteTileNum + 0x140);
    vramPtr2 = vramPtr + 0x1E0;
    vramPtr3 = vramPtr + 0x80;
    vramPtr4 = vramPtr + 0x260;

    for (i = 0; i < 112; i++)
    {
        if (i < 96)
        {
            for (j = 0; j < 13; j += 4)
            {
                if (*src & (0xF << j))
                {
                    *vramPtr |= (0xF << j);
                    *vramPtr &= ((*src & (0xF << j)) + 0xFFFF - (0xF << j));
                }
                if (*src3 & (0xF << j))
                {
                    *vramPtr3 |= (0xF << j);
                    *vramPtr3 &= ((*src3 & (0xF << j)) + 0xFFFF - (0xF << j));
                }
            }
            src++;
            src3++;
            vramPtr++;
            vramPtr3++;
        }
        for (j = 0; j < 13; j += 4)
        {
            if (*src2 & (0xF << j))
            {
                *vramPtr2 |= (0xF << j);
                *vramPtr2 &= ((*src2 & (0xF << j)) + 0xFFFF - (0xF << j));
            }
            if (*src4 & (0xF << j))
            {
                *vramPtr4 |= (0xF << j);
                *vramPtr4 &= ((*src4 & (0xF << j)) + 0xFFFF - (0xF << j));
            }
        }
        src2++;
        src4++;
        vramPtr2++;
        vramPtr4++;
    }
    RemoveWindow(windowId);

}

void MoveBox_PrintMovePP(u8 index)
{
    u8 text[5];
    u32 windowId, spriteTileNum;
    u8 *windowTileData;
    u16 *vramPtr, *src;
    u8 i, j;

    text[0] = 0x9C;
    ConvertIntToDecimalStringN(text + 1, gBattleMons[gActiveBattler].pp[index], STR_CONV_MODE_RIGHT_ALIGN, 3);
    windowTileData = AddTextPrinterAndCreateWindowOnMovebox(text, 5, 0, &windowId, 3, 1);
    spriteTileNum = gSprites[gBattleMoveBoxSpriteIds[index]].oam.tileNum * TILE_SIZE_4BPP;

    src = (u16*)windowTileData;
    vramPtr = (u16*)(OBJ_VRAM0 + spriteTileNum + 0x6A0);

    for (i = 0; i < 32; i++)
    {
        for (j = 0; j < 13; j += 4)
        {
            if (*src & (0xF << j))
            {
                *vramPtr |= (0xF << j);
                *vramPtr &= ((*src & (0xF << j)) + 0xFFFF - (0xF << j));
            }
        }
        src++;
        vramPtr++;
    }
    RemoveWindow(windowId);

}

const struct WindowTemplate sMoveBoxWindowTemplates[2] =
{
    {0, 0, 0, 13, 2, 0, 0},
    {0, 0, 0,  2, 1, 0, 0}
};

static u8* AddTextPrinterAndCreateWindowOnMovebox(const u8 *str, u32 x, u32 y, u32 *windowId, u8 fontId, u8 winTemplateId)
{
    u16 winId, printer;
    struct WindowTemplate winTemplate = sMoveBoxWindowTemplates[winTemplateId];

    winId = AddWindow(&winTemplate);
    AddTextPrinterParameterized4(winId, fontId, x, y, -2, 0, 0, -1, str);

    *windowId = winId;
    return (u8*)(GetWindowAttribute(winId, WINDOW_TILE_DATA));
}

static void SpriteCb_MegaTrigger(struct Sprite *sprite)
{
    s32 xSlide, xPriority, xOptimal;
    s32 yDiff;

    if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
    {
        xSlide = DOUBLES_MEGA_TRIGGER_POS_X_SLIDE;
        xPriority = DOUBLES_MEGA_TRIGGER_POS_X_PRIORITY;
        xOptimal = DOUBLES_MEGA_TRIGGER_POS_X_OPTIMAL;
        yDiff = DOUBLES_MEGA_TRIGGER_POS_Y_DIFF;
    }
    else
    {
        xSlide = SINGLES_MEGA_TRIGGER_POS_X_SLIDE;
        xPriority = SINGLES_MEGA_TRIGGER_POS_X_PRIORITY;
        xOptimal = SINGLES_MEGA_TRIGGER_POS_X_OPTIMAL;
        yDiff = SINGLES_MEGA_TRIGGER_POS_Y_DIFF;
    }

    if (sprite->tHide)
    {
        if (sprite->pos1.x != gSprites[gHealthboxSpriteIds[sprite->tBattler]].pos1.x - xSlide)
            sprite->pos1.x++;

        if (sprite->pos1.x >= gSprites[gHealthboxSpriteIds[sprite->tBattler]].pos1.x - xPriority)
            sprite->oam.priority = 2;
        else
            sprite->oam.priority = 1;

        sprite->pos1.y = gSprites[gHealthboxSpriteIds[sprite->tBattler]].pos1.y - yDiff;
        sprite->pos2.y = gSprites[gHealthboxSpriteIds[sprite->tBattler]].pos2.y - yDiff;
        if (sprite->pos1.x == gSprites[gHealthboxSpriteIds[sprite->tBattler]].pos1.x - xSlide)
            DestroyMegaTriggerSprite();
            DestroyZMoveTriggerSprite();
    }
    else
    {
        if (sprite->pos1.x != gSprites[gHealthboxSpriteIds[sprite->tBattler]].pos1.x - xOptimal)
            sprite->pos1.x--;

        if (sprite->pos1.x >= gSprites[gHealthboxSpriteIds[sprite->tBattler]].pos1.x - xPriority)
            sprite->oam.priority = 2;
        else
            sprite->oam.priority = 1;

        sprite->pos1.y = gSprites[gHealthboxSpriteIds[sprite->tBattler]].pos1.y - yDiff;
        sprite->pos2.y = gSprites[gHealthboxSpriteIds[sprite->tBattler]].pos2.y - yDiff;
    }
}

bool32 IsMegaTriggerSpriteActive(void)
{
    if (GetSpriteTileStartByTag(TAG_MEGA_TRIGGER_TILE) == 0xFFFF)
        return FALSE;
    else if (IndexOfSpritePaletteTag(TAG_MEGA_TRIGGER_PAL) != 0xFF)
        return TRUE;
    else
        return FALSE;
}

void HideMegaTriggerSprite(void)
{
    ChangeMegaTriggerSprite(gBattleStruct->mega.triggerSpriteId, 0);
    gSprites[gBattleStruct->mega.triggerSpriteId].tHide = TRUE;
}

void DestroyMegaTriggerSprite(void)
{
    FreeSpritePaletteByTag(TAG_MEGA_TRIGGER_PAL);
    FreeSpriteTilesByTag(TAG_MEGA_TRIGGER_TILE);
    if (gBattleStruct->mega.triggerSpriteId != 0xFF)
        DestroySprite(&gSprites[gBattleStruct->mega.triggerSpriteId]);
    gBattleStruct->mega.triggerSpriteId = 0xFF;
}

bool32 IsZMoveTriggerSpriteActive(void)
{
    if (GetSpriteTileStartByTag(TAG_MEGA_TRIGGER_TILE) == 0xFFFF)
        return FALSE;
    else if (IndexOfSpritePaletteTag(TAG_MEGA_TRIGGER_PAL) != 0xFF)
        return TRUE;
    else
        return FALSE;
}

void HideZMoveTriggerSprite(void)
{
    ChangeZMoveTriggerSprite(gBattleStruct->zMove.triggerSpriteId, 0);
    gSprites[gBattleStruct->zMove.triggerSpriteId].tHide = TRUE;
}

void DestroyZMoveTriggerSprite(void)
{
    FreeSpritePaletteByTag(TAG_MEGA_TRIGGER_PAL);
    FreeSpriteTilesByTag(TAG_MEGA_TRIGGER_TILE);
    if (gBattleStruct->zMove.triggerSpriteId != 0xFF)
        DestroySprite(&gSprites[gBattleStruct->zMove.triggerSpriteId]);
    gBattleStruct->zMove.triggerSpriteId = 0xFF;
}

static const s8 sIndicatorPosSingles[][2] =
{
    [B_POSITION_PLAYER_LEFT] = {53, -8},
    [B_POSITION_OPPONENT_LEFT] = {45, -8},
};

static const s8 sIndicatorPosDoubles[][2] =
{
    [B_POSITION_PLAYER_LEFT] = {53, -8},
    [B_POSITION_OPPONENT_LEFT] = {45, -8},
    [B_POSITION_PLAYER_RIGHT] = {53, -8},
    [B_POSITION_OPPONENT_RIGHT] = {45, -8},
};

u32 CreateMegaIndicatorSprite(u32 battlerId, u32 which)
{
    u32 spriteId, position;
    s16 x, y;

    LoadSpritePalette(&sSpritePalette_MegaIndicator);
    LoadSpriteSheet(&sSpriteSheet_MegaIndicator);

    position = GetBattlerPosition(battlerId);
    GetBattlerHealthboxCoords(battlerId, &x, &y);
    if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
    {
        x += sIndicatorPosDoubles[position][0];
        y += sIndicatorPosDoubles[position][1];
    }
    else
    {
        x += sIndicatorPosSingles[position][0];
        y += sIndicatorPosSingles[position][1];
    }
    spriteId = CreateSpriteAtEnd(&sSpriteTemplate_MegaIndicator, x, y, 0);
    gSprites[gHealthboxSpriteIds[battlerId]].hOther_IndicatorSpriteId = spriteId;

    gSprites[spriteId].tBattler = battlerId;
    return spriteId;
}

void DestroyMegaIndicatorSprite(u32 healthboxSpriteId)
{
    u32 i;
    s16 *spriteId = &gSprites[healthboxSpriteId].hOther_IndicatorSpriteId;

    if (*spriteId != 0xFF)
    {
        DestroySprite(&gSprites[*spriteId]);
        *spriteId = 0xFF;
    }

    for (i = 0; i < MAX_BATTLERS_COUNT; i++)
    {
        if (gSprites[gHealthboxSpriteIds[i]].hOther_IndicatorSpriteId != 0xFF)
            break;
    }
    // Free Sprite pal/tiles only if no indicator sprite is active for all battlers.
    if (i == MAX_BATTLERS_COUNT)
    {
        FreeSpritePaletteByTag(TAG_MEGA_INDICATOR_PAL);
        FreeSpriteTilesByTag(TAG_MEGA_INDICATOR_TILE);
    }
}

static void SpriteCb_MegaIndicator(struct Sprite *sprite)
{

}

#undef tBattler
#undef tHide

#define tBattler                data[0]
#define tSummaryBarSpriteId     data[1]
#define tBallIconSpriteId(n)    data[3 + n]
#define tIsBattleStart          data[10]
#define tData15                 data[15]

u8 CreatePartyStatusSummarySprites(u8 battlerId, struct HpAndStatus *partyInfo, u8 arg2, bool8 isBattleStart)
{
    bool8 isOpponent;
    s16 bar_X, bar_Y, bar_pos2_X, bar_data0;
    s32 i, j, var;
    u8 summaryBarSpriteId;
    u8 ballIconSpritesIds[PARTY_SIZE];
    u8 taskId;

    if (!arg2 || GetBattlerPosition(battlerId) != B_POSITION_OPPONENT_RIGHT)
    {
        if (GetBattlerSide(battlerId) == B_SIDE_PLAYER)
        {
            isOpponent = FALSE;
            bar_X = 136, bar_Y = 96;
            bar_pos2_X = 100;
            bar_data0 = -5;
        }
        else
        {
            isOpponent = TRUE;

            if (!arg2 || !IsDoubleBattle())
                bar_X = 104, bar_Y = 40;
            else
                bar_X = 104, bar_Y = 16;

            bar_pos2_X = -100;
            bar_data0 = 5;
        }
    }
    else
    {
        isOpponent = TRUE;
        bar_X = 104, bar_Y = 40;
        bar_pos2_X = -100;
        bar_data0 = 5;
    }

    LoadCompressedSpriteSheetUsingHeap(&sStatusSummaryBarSpriteSheet);
    LoadSpriteSheet(&sStatusSummaryBallsSpriteSheet);
    LoadSpritePalette(&sStatusSummaryBarSpritePal);
    LoadSpritePalette(&sStatusSummaryBallsSpritePal);

    summaryBarSpriteId = CreateSprite(&sStatusSummaryBarSpriteTemplates[isOpponent], bar_X, bar_Y, 10);
    SetSubspriteTables(&gSprites[summaryBarSpriteId], sStatusSummaryBar_SubspriteTable);
    gSprites[summaryBarSpriteId].pos2.x = bar_pos2_X;
    gSprites[summaryBarSpriteId].data[0] = bar_data0;

    if (isOpponent)
    {
        gSprites[summaryBarSpriteId].pos1.x -= 96;
        gSprites[summaryBarSpriteId].oam.matrixNum = ST_OAM_HFLIP;
    }
    else
    {
        gSprites[summaryBarSpriteId].pos1.x += 96;
    }

    for (i = 0; i < PARTY_SIZE; i++)
    {
        ballIconSpritesIds[i] = CreateSpriteAtEnd(&sStatusSummaryBallsSpriteTemplates[isOpponent], bar_X, bar_Y - 4, 9);

        if (!isBattleStart)
            gSprites[ballIconSpritesIds[i]].callback = SpriteCB_StatusSummaryBallsOnSwitchout;

        if (!isOpponent)
        {
            gSprites[ballIconSpritesIds[i]].pos2.x = 0;
            gSprites[ballIconSpritesIds[i]].pos2.y = 0;
        }

        gSprites[ballIconSpritesIds[i]].data[0] = summaryBarSpriteId;

        if (!isOpponent)
        {
            gSprites[ballIconSpritesIds[i]].pos1.x += 10 * i + 24;
            gSprites[ballIconSpritesIds[i]].data[1] = i * 7 + 10;
            gSprites[ballIconSpritesIds[i]].pos2.x = 120;
        }
        else
        {
            gSprites[ballIconSpritesIds[i]].pos1.x -= 10 * (5 - i) + 24;
            gSprites[ballIconSpritesIds[i]].data[1] = (6 - i) * 7 + 10;
            gSprites[ballIconSpritesIds[i]].pos2.x = -120;
        }

        gSprites[ballIconSpritesIds[i]].data[2] = isOpponent;
    }

    if (GetBattlerSide(battlerId) == B_SIDE_PLAYER)
    {
        if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
        {
            for (i = 0; i < PARTY_SIZE; i++)
            {
                if (partyInfo[i].hp == 0xFFFF) // empty slot or an egg
                {
                    gSprites[ballIconSpritesIds[i]].oam.tileNum += 1;
                    gSprites[ballIconSpritesIds[i]].data[7] = 1;
                }
                else if (partyInfo[i].hp == 0) // fainted mon
                {
                    gSprites[ballIconSpritesIds[i]].oam.tileNum += 3;
                }
                else if (partyInfo[i].status != 0) // mon with major status
                {
                    gSprites[ballIconSpritesIds[i]].oam.tileNum += 2;
                }
            }
        }
        else
        {
            for (i = 0, var = 5, j = 0; j < PARTY_SIZE; j++)
            {
                if (partyInfo[j].hp == 0xFFFF) // empty slot or an egg
                {
                    gSprites[ballIconSpritesIds[var]].oam.tileNum += 1;
                    gSprites[ballIconSpritesIds[var]].data[7] = 1;
                    var--;
                    continue;
                }
                else if (partyInfo[j].hp == 0) // fainted mon
                {
                    gSprites[ballIconSpritesIds[i]].oam.tileNum += 3;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_ARENA && gBattleStruct->arenaLostPlayerMons & gBitTable[j])
                {
                    gSprites[ballIconSpritesIds[i]].oam.tileNum += 3;
                }
                else if (partyInfo[j].status != 0) // mon with major status
                {
                    gSprites[ballIconSpritesIds[i]].oam.tileNum += 2;
                }
                i++;
            }
        }
    }
    else
    {
        if (gBattleTypeFlags & (BATTLE_TYPE_MULTI | BATTLE_TYPE_TWO_OPPONENTS))
        {
            for (var = 5, i = 0; i < PARTY_SIZE; i++)
            {
                if (partyInfo[i].hp == 0xFFFF) // empty slot or an egg
                {
                    gSprites[ballIconSpritesIds[var]].oam.tileNum += 1;
                    gSprites[ballIconSpritesIds[var]].data[7] = 1;
                }
                else if (partyInfo[i].hp == 0) // fainted mon
                {
                    gSprites[ballIconSpritesIds[var]].oam.tileNum += 3;
                }
                else if (partyInfo[i].status != 0) // mon with major status
                {
                    gSprites[ballIconSpritesIds[var]].oam.tileNum += 2;
                }
                var--;
            }
        }
        else
        {
            for (var = 0, i = 0, j = 0; j < PARTY_SIZE; j++)
            {
                if (partyInfo[j].hp == 0xFFFF) // empty slot or an egg
                {
                    gSprites[ballIconSpritesIds[i]].oam.tileNum += 1;
                    gSprites[ballIconSpritesIds[i]].data[7] = 1;
                    i++;
                    continue;
                }
                else if (partyInfo[j].hp == 0) // fainted mon
                {
                    gSprites[ballIconSpritesIds[5 - var]].oam.tileNum += 3;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_ARENA && gBattleStruct->arenaLostOpponentMons & gBitTable[j]) // hmm...?
                {
                    gSprites[ballIconSpritesIds[5 - var]].oam.tileNum += 3;
                }
                else if (partyInfo[j].status != 0) // mon with major status
                {
                    gSprites[ballIconSpritesIds[5 - var]].oam.tileNum += 2;
                }
                var++;
            }
        }
    }

    taskId = CreateTask(TaskDummy, 5);
    gTasks[taskId].tBattler = battlerId;
    gTasks[taskId].tSummaryBarSpriteId = summaryBarSpriteId;

    for (i = 0; i < PARTY_SIZE; i++)
        gTasks[taskId].tBallIconSpriteId(i) = ballIconSpritesIds[i];

    gTasks[taskId].tIsBattleStart = isBattleStart;

    if (isBattleStart)
    {
        gBattleSpritesDataPtr->animationData->field_9_x1C++;
    }

    PlaySE12WithPanning(SE_BALL_TRAY_ENTER, 0);
    return taskId;
}

void Task_HidePartyStatusSummary(u8 taskId)
{
    u8 ballIconSpriteIds[PARTY_SIZE];
    bool8 isBattleStart;
    u8 summaryBarSpriteId;
    u8 battlerId;
    s32 i;

    isBattleStart = gTasks[taskId].tIsBattleStart;
    summaryBarSpriteId = gTasks[taskId].tSummaryBarSpriteId;
    battlerId = gTasks[taskId].tBattler;

    for (i = 0; i < PARTY_SIZE; i++)
        ballIconSpriteIds[i] = gTasks[taskId].tBallIconSpriteId(i);

    SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT2_ALL | BLDCNT_EFFECT_BLEND);
    SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(16, 0));

    gTasks[taskId].tData15 = 16;

    for (i = 0; i < PARTY_SIZE; i++)
        gSprites[ballIconSpriteIds[i]].oam.objMode = ST_OAM_OBJ_BLEND;

    gSprites[summaryBarSpriteId].oam.objMode = ST_OAM_OBJ_BLEND;

    if (isBattleStart)
    {
        for (i = 0; i < PARTY_SIZE; i++)
        {
            if (GetBattlerSide(battlerId) != B_SIDE_PLAYER)
            {
                gSprites[ballIconSpriteIds[5 - i]].data[1] = 7 * i;
                gSprites[ballIconSpriteIds[5 - i]].data[3] = 0;
                gSprites[ballIconSpriteIds[5 - i]].data[4] = 0;
                gSprites[ballIconSpriteIds[5 - i]].callback = sub_8074158;
            }
            else
            {
                gSprites[ballIconSpriteIds[i]].data[1] = 7 * i;
                gSprites[ballIconSpriteIds[i]].data[3] = 0;
                gSprites[ballIconSpriteIds[i]].data[4] = 0;
                gSprites[ballIconSpriteIds[i]].callback = sub_8074158;
            }
        }
        gSprites[summaryBarSpriteId].data[0] /= 2;
        gSprites[summaryBarSpriteId].data[1] = 0;
        gSprites[summaryBarSpriteId].callback = sub_8074090;
        SetSubspriteTables(&gSprites[summaryBarSpriteId], sUnknown_0832C2CC);
        gTasks[taskId].func = sub_8073E08;
    }
    else
    {
        gTasks[taskId].func = sub_8073F98;
    }
}

static void sub_8073E08(u8 taskId)
{
    if ((gTasks[taskId].data[11]++ % 2) == 0)
    {
        if (--gTasks[taskId].tData15 < 0)
            return;

        SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(gTasks[taskId].data[15], 16 - gTasks[taskId].data[15]));
    }
    if (gTasks[taskId].tData15 == 0)
        gTasks[taskId].func = sub_8073E64;
}

static void sub_8073E64(u8 taskId)
{
    u8 ballIconSpriteIds[PARTY_SIZE];
    s32 i;

    u8 battlerId = gTasks[taskId].tBattler;
    if (--gTasks[taskId].tData15 == -1)
    {
        u8 summaryBarSpriteId = gTasks[taskId].tSummaryBarSpriteId;

        for (i = 0; i < PARTY_SIZE; i++)
            ballIconSpriteIds[i] = gTasks[taskId].tBallIconSpriteId(i);

        gBattleSpritesDataPtr->animationData->field_9_x1C--;
        if (gBattleSpritesDataPtr->animationData->field_9_x1C == 0)
        {
            DestroySpriteAndFreeResources(&gSprites[summaryBarSpriteId]);
            DestroySpriteAndFreeResources(&gSprites[ballIconSpriteIds[0]]);
        }
        else
        {
            FreeSpriteOamMatrix(&gSprites[summaryBarSpriteId]);
            DestroySprite(&gSprites[summaryBarSpriteId]);
            FreeSpriteOamMatrix(&gSprites[ballIconSpriteIds[0]]);
            DestroySprite(&gSprites[ballIconSpriteIds[0]]);
        }

        for (i = 1; i < PARTY_SIZE; i++)
            DestroySprite(&gSprites[ballIconSpriteIds[i]]);
    }
    else if (gTasks[taskId].tData15 == -3)
    {
        gBattleSpritesDataPtr->healthBoxesData[battlerId].partyStatusSummaryShown = 0;
        SetGpuReg(REG_OFFSET_BLDCNT, 0);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        DestroyTask(taskId);
    }
}

static void sub_8073F98(u8 taskId)
{
    u8 ballIconSpriteIds[PARTY_SIZE];
    s32 i;
    u8 battlerId = gTasks[taskId].tBattler;

    if (--gTasks[taskId].tData15 >= 0)
    {
        SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(gTasks[taskId].data[15], 16 - gTasks[taskId].data[15]));
    }
    else if (gTasks[taskId].tData15 == -1)
    {
        u8 summaryBarSpriteId = gTasks[taskId].tSummaryBarSpriteId;

        for (i = 0; i < PARTY_SIZE; i++)
            ballIconSpriteIds[i] = gTasks[taskId].tBallIconSpriteId(i);

        DestroySpriteAndFreeResources(&gSprites[summaryBarSpriteId]);
        DestroySpriteAndFreeResources(&gSprites[ballIconSpriteIds[0]]);

        for (i = 1; i < PARTY_SIZE; i++)
            DestroySprite(&gSprites[ballIconSpriteIds[i]]);
    }
    else if (gTasks[taskId].tData15 == -3)
    {
        gBattleSpritesDataPtr->healthBoxesData[battlerId].partyStatusSummaryShown = 0;
        SetGpuReg(REG_OFFSET_BLDCNT, 0);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        DestroyTask(taskId);
    }
}

#undef tBattler
#undef tSummaryBarSpriteId
#undef tBallIconSpriteId
#undef tIsBattleStart
#undef tData15

static void SpriteCB_StatusSummaryBar(struct Sprite *sprite)
{
    if (sprite->pos2.x != 0)
        sprite->pos2.x += sprite->data[0];
}

static void sub_8074090(struct Sprite *sprite)
{
    sprite->data[1] += 32;
    if (sprite->data[0] > 0)
        sprite->pos2.x += sprite->data[1] >> 4;
    else
        sprite->pos2.x -= sprite->data[1] >> 4;
    sprite->data[1] &= 0xF;
}

static void SpriteCB_StatusSummaryBallsOnBattleStart(struct Sprite *sprite)
{
    u8 var1;
    u16 var2;
    s8 pan;

    if (sprite->data[1] > 0)
    {
        sprite->data[1]--;
        return;
    }

    var1 = sprite->data[2];
    var2 = sprite->data[3];
    var2 += 56;
    sprite->data[3] = var2 & 0xFFF0;

    if (var1 != 0)
    {
        sprite->pos2.x += var2 >> 4;
        if (sprite->pos2.x > 0)
            sprite->pos2.x = 0;
    }
    else
    {
        sprite->pos2.x -= var2 >> 4;
        if (sprite->pos2.x < 0)
            sprite->pos2.x = 0;
    }

    if (sprite->pos2.x == 0)
    {
        pan = SOUND_PAN_TARGET;
        if (var1 != 0)
            pan = SOUND_PAN_ATTACKER;

        if (sprite->data[7] != 0)
            PlaySE2WithPanning(SE_BALL_TRAY_EXIT, pan);
        else
            PlaySE1WithPanning(SE_BALL_TRAY_BALL, pan);

        sprite->callback = SpriteCallbackDummy;
    }
}

static void sub_8074158(struct Sprite *sprite)
{
    u8 var1;
    u16 var2;

    if (sprite->data[1] > 0)
    {
        sprite->data[1]--;
        return;
    }
    var1 = sprite->data[2];
    var2 = sprite->data[3];
    var2 += 56;
    sprite->data[3] = var2 & 0xFFF0;
    if (var1 != 0)
        sprite->pos2.x += var2 >> 4;
    else
        sprite->pos2.x -= var2 >> 4;
    if (sprite->pos2.x + sprite->pos1.x > 248
     || sprite->pos2.x + sprite->pos1.x < -8)
    {
        sprite->invisible = TRUE;
        sprite->callback = SpriteCallbackDummy;
    }
}

static void SpriteCB_StatusSummaryBallsOnSwitchout(struct Sprite *sprite)
{
    u8 barSpriteId = sprite->data[0];

    sprite->pos2.x = gSprites[barSpriteId].pos2.x;
    sprite->pos2.y = gSprites[barSpriteId].pos2.y;
}

static void UpdateNickInHealthbox(u8 healthboxSpriteId, struct Pokemon *mon)
{
    u8 nickname[POKEMON_NAME_LENGTH + 1];
    void *ptr;
    const u8 *genderTxt;
    u32 windowId, spriteTileNum, species;
    u8 *windowTileData;
    u8 gender;
    struct Pokemon *illusionMon = GetIllusionMonPtr(gSprites[healthboxSpriteId].hMain_Battler);
    if (illusionMon != NULL)
        mon = illusionMon;

    StringCopy(gDisplayedStringBattle, gText_HighlightDarkGrey);
    GetMonData(mon, MON_DATA_NICKNAME, nickname);
    StringGetEnd10(nickname);
    ptr = StringAppend(gDisplayedStringBattle, nickname);

    gender = GetMonGender(mon);
    species = GetMonData(mon, MON_DATA_SPECIES);

    if ((species == SPECIES_NIDORAN_F || species == SPECIES_NIDORAN_M) && StringCompare(nickname, gSpeciesNames[species]) == 0)
        gender = 100;

    switch (gender)
    {
    case MON_MALE:
        StringCopy(ptr, gText_BlueMaleSymbol);
        break;
    case MON_FEMALE:
        StringCopy(ptr, gText_RedFemaleSymbol);
        break;
    }
    windowTileData = AddTextPrinterAndCreateWindowOnHealthbox(gDisplayedStringBattle, 0, 2, 0, &windowId);

    spriteTileNum = gSprites[healthboxSpriteId].oam.tileNum * TILE_SIZE_4BPP;

    TextIntoHealthboxObject((void*)(OBJ_VRAM0 + 0x60 + spriteTileNum), windowTileData, 5);
    TextIntoHealthboxObject((void*)(OBJ_VRAM0 + 0x400 + spriteTileNum), windowTileData + 5 * 32, 2);
    RemoveWindowOnHealthbox(windowId);
}

static void TryAddPokeballIconToHealthbox(u8 healthboxSpriteId)
{
    u8 battlerId, healthBarSpriteId;

    if (gBattleTypeFlags & BATTLE_TYPE_WALLY_TUTORIAL)
        return;
    if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)
        return;

    battlerId = gSprites[healthboxSpriteId].hMain_Battler;
    if (GetBattlerSide(battlerId) == B_SIDE_PLAYER)
        return;
    if (!GetSetPokedexFlag(SpeciesToNationalPokedexNum(GetMonData(&gEnemyParty[gBattlerPartyIndexes[battlerId]], MON_DATA_SPECIES)), FLAG_GET_CAUGHT))
        return;

    CpuCopy32(GetHealthboxElementGfxPtr(HEALTHBOX_GFX_CAUGHT_MARKER), (void*)(OBJ_VRAM0 + (gSprites[healthboxSpriteId].oam.tileNum + 53) * TILE_SIZE_4BPP), 32);
}

static void UpdateStatusIconInHealthbox(u8 healthboxSpriteId)
{
    u8 battlerId, side, i, offset;
    u32 status, spriteTileNum;
    const u8 *statusGfxPtr, *statusGfxPtr2;

    battlerId = gSprites[healthboxSpriteId].hMain_Battler;
    spriteTileNum = gSprites[healthboxSpriteId].oam.tileNum * TILE_SIZE_4BPP;
    side = GetBattlerSide(battlerId);

    if (side == B_SIDE_PLAYER)
        status = GetMonData(&gPlayerParty[gBattlerPartyIndexes[battlerId]], MON_DATA_STATUS);
    else
    {
        status = GetMonData(&gEnemyParty[gBattlerPartyIndexes[battlerId]], MON_DATA_STATUS);
        TryAddPokeballIconToHealthbox(healthboxSpriteId);
    }

    if (status & STATUS1_SLEEP)
        statusGfxPtr = GetHealthboxElementGfxPtr(HEALTHBOX_GFX_STATUS_SLP + side * 14);
    else if (status & STATUS1_FREEZE)
        statusGfxPtr = GetHealthboxElementGfxPtr(HEALTHBOX_GFX_STATUS_FRZ + side * 14);
    else if (status & STATUS1_PARALYSIS)
        statusGfxPtr = GetHealthboxElementGfxPtr(HEALTHBOX_GFX_STATUS_PAR + side * 14);
    else if (status & STATUS1_BURN)
        statusGfxPtr = GetHealthboxElementGfxPtr(HEALTHBOX_GFX_STATUS_BRN + side * 14);
    else if (status & STATUS1_POISON)
        statusGfxPtr = GetHealthboxElementGfxPtr(HEALTHBOX_GFX_STATUS_PSN + side * 14);
    else if (status & STATUS1_TOXIC_POISON)
        statusGfxPtr = GetHealthboxElementGfxPtr(HEALTHBOX_GFX_STATUS_TOX + side * 14);
    else
        statusGfxPtr = GetHealthboxElementGfxPtr(HEALTHBOX_GFX_STATUS_NONE + side * 14);

    statusGfxPtr2 = statusGfxPtr + 0x20;

    if (side == B_SIDE_PLAYER)
        offset = 50;
    else
        offset = 19;

    for (i = 1; i < 8; i++)
    {
        CpuCopy16(statusGfxPtr + i * 4, (void*)(OBJ_VRAM0 + spriteTileNum + offset * TILE_SIZE_4BPP + i * 4 + 2), 2);
        CpuCopy16(statusGfxPtr + i * 4 + 2, (void*)(OBJ_VRAM0 + spriteTileNum + (offset + 1) * TILE_SIZE_4BPP + i * 4), 2);
        CpuCopy16(statusGfxPtr2 + i * 4, (void*)(OBJ_VRAM0 + spriteTileNum + (offset + 1) * TILE_SIZE_4BPP + i * 4 + 2), 2);
        CpuCopy16(statusGfxPtr2 + i * 4 + 2, (void*)(OBJ_VRAM0 + spriteTileNum + (offset + 2) * TILE_SIZE_4BPP + i * 4), 2);
    }
}

static void UpdateSafariBallsTextOnHealthbox(u8 healthboxSpriteId)
{
    u32 windowId, spriteTileNum;
    u8 *windowTileData;

    windowTileData = AddTextPrinterAndCreateWindowOnHealthbox(gText_SafariBalls, 0, 3, 2, &windowId);
    spriteTileNum = gSprites[healthboxSpriteId].oam.tileNum * TILE_SIZE_4BPP;
    TextIntoHealthboxObject((void*)(OBJ_VRAM0 + 0x40) + spriteTileNum, windowTileData, 6);
    TextIntoHealthboxObject((void*)(OBJ_VRAM0 + 0x800) + spriteTileNum, windowTileData + 0xC0, 2);
    RemoveWindowOnHealthbox(windowId);
}

static void UpdateLeftNoOfBallsTextOnHealthbox(u8 healthboxSpriteId)
{
    u8 text[16];
    u8 *txtPtr;
    u32 windowId, spriteTileNum;
    u8 *windowTileData;

    txtPtr = StringCopy(text, gText_SafariBallLeft);
    ConvertIntToDecimalStringN(txtPtr, gNumSafariBalls, STR_CONV_MODE_LEFT_ALIGN, 2);

    windowTileData = AddTextPrinterAndCreateWindowOnHealthbox(text, GetStringRightAlignXOffset(0, text, 0x2F), 3, 2, &windowId);
    spriteTileNum = gSprites[healthboxSpriteId].oam.tileNum * TILE_SIZE_4BPP;
    SafariTextIntoHealthboxObject((void*)(OBJ_VRAM0 + 0x2C0) + spriteTileNum, windowTileData, 2);
    SafariTextIntoHealthboxObject((void*)(OBJ_VRAM0 + 0xA00) + spriteTileNum, windowTileData + 0x40, 4);
    RemoveWindowOnHealthbox(windowId);
}

void UpdateHealthboxAttribute(u8 healthboxSpriteId, struct Pokemon *mon, u8 elementId)
{
    s32 maxHp, currHp;
    u8 battlerId = gSprites[healthboxSpriteId].hMain_Battler;

    if (GetBattlerSide(gSprites[healthboxSpriteId].hMain_Battler) == B_SIDE_PLAYER)
    {
        u8 isDoubles;

        if (elementId == HEALTHBOX_LEVEL || elementId == HEALTHBOX_ALL)
            UpdateLvlInHealthbox(healthboxSpriteId, GetMonData(mon, MON_DATA_LEVEL));
        if (elementId == HEALTHBOX_CURRENT_HP || elementId == HEALTHBOX_ALL)
            UpdateHpTextInHealthbox(healthboxSpriteId, GetMonData(mon, MON_DATA_HP), HP_CURRENT);
        if (elementId == HEALTHBOX_MAX_HP || elementId == HEALTHBOX_ALL)
            UpdateHpTextInHealthbox(healthboxSpriteId, GetMonData(mon, MON_DATA_MAX_HP), HP_MAX);
        if (elementId == HEALTHBOX_HEALTH_BAR || elementId == HEALTHBOX_ALL)
        {
            LoadBattleBarGfx(0);
            maxHp = GetMonData(mon, MON_DATA_MAX_HP);
            currHp = GetMonData(mon, MON_DATA_HP);
            SetBattleBarStruct(battlerId, healthboxSpriteId, maxHp, currHp, 0);
            MoveBattleBar(battlerId, healthboxSpriteId, HEALTH_BAR, 0);
        }
        if (elementId == HEALTHBOX_EXP_BAR || elementId == HEALTHBOX_ALL)
        {
            u16 species;
            u32 exp, currLevelExp;
            s32 currExpBarValue, maxExpBarValue;
            u8 level;

            LoadBattleBarGfx(3);
            species = GetMonData(mon, MON_DATA_SPECIES);
            level = GetMonData(mon, MON_DATA_LEVEL);
            exp = GetMonData(mon, MON_DATA_EXP);
            currLevelExp = gExperienceTables[gBaseStats[species].growthRate][level];
            currExpBarValue = exp - currLevelExp;
            maxExpBarValue = gExperienceTables[gBaseStats[species].growthRate][level + 1] - currLevelExp;
            SetBattleBarStruct(battlerId, healthboxSpriteId, maxExpBarValue, currExpBarValue, 0);
            MoveBattleBar(battlerId, healthboxSpriteId, EXP_BAR, 0);
        }
        if (elementId == HEALTHBOX_NICK || elementId == HEALTHBOX_ALL)
            UpdateNickInHealthbox(healthboxSpriteId, mon);
        if (elementId == HEALTHBOX_STATUS_ICON || elementId == HEALTHBOX_ALL)
            UpdateStatusIconInHealthbox(healthboxSpriteId);
        if (elementId == HEALTHBOX_SAFARI_ALL_TEXT)
            UpdateSafariBallsTextOnHealthbox(healthboxSpriteId);
        if (elementId == HEALTHBOX_SAFARI_ALL_TEXT || elementId == HEALTHBOX_SAFARI_BALLS_TEXT)
            UpdateLeftNoOfBallsTextOnHealthbox(healthboxSpriteId);
    }
    else
    {
        if (elementId == HEALTHBOX_LEVEL || elementId == HEALTHBOX_ALL)
            UpdateLvlInHealthbox(healthboxSpriteId, GetMonData(mon, MON_DATA_LEVEL));
        if (gBattleSpritesDataPtr->battlerData[battlerId].hpNumbersNoBars && (elementId == HEALTHBOX_CURRENT_HP || elementId == HEALTHBOX_ALL))
            UpdateHpTextInHealthbox(healthboxSpriteId, GetMonData(mon, MON_DATA_HP), HP_CURRENT);
        if (gBattleSpritesDataPtr->battlerData[battlerId].hpNumbersNoBars && (elementId == HEALTHBOX_MAX_HP || elementId == HEALTHBOX_ALL))
            UpdateHpTextInHealthbox(healthboxSpriteId, GetMonData(mon, MON_DATA_MAX_HP), HP_MAX);
        if (elementId == HEALTHBOX_HEALTH_BAR || elementId == HEALTHBOX_ALL)
        {
            LoadBattleBarGfx(0);
            maxHp = GetMonData(mon, MON_DATA_MAX_HP);
            currHp = GetMonData(mon, MON_DATA_HP);
            SetBattleBarStruct(battlerId, healthboxSpriteId, maxHp, currHp, 0);
            MoveBattleBar(battlerId, healthboxSpriteId, HEALTH_BAR, 0);
        }
        if (elementId == HEALTHBOX_NICK || elementId == HEALTHBOX_ALL)
            UpdateNickInHealthbox(healthboxSpriteId, mon);
        if (elementId == HEALTHBOX_STATUS_ICON || elementId == HEALTHBOX_ALL)
            UpdateStatusIconInHealthbox(healthboxSpriteId);
    }
}

#define B_EXPBAR_PIXELS 50
#define B_HEALTHBAR_PIXELS 48

s32 MoveBattleBar(u8 battlerId, u8 healthboxSpriteId, u8 whichBar, u8 unused)
{
    s32 currentBarValue;

    if (whichBar == HEALTH_BAR) // health bar
    {
        currentBarValue = CalcNewBarValue(gBattleSpritesDataPtr->battleBars[battlerId].maxValue,
                    gBattleSpritesDataPtr->battleBars[battlerId].oldValue,
                    gBattleSpritesDataPtr->battleBars[battlerId].receivedValue,
                    &gBattleSpritesDataPtr->battleBars[battlerId].currValue,
                    B_HEALTHBAR_PIXELS, 1);
    }
    else // exp bar
    {
        u16 expFraction = GetScaledExpFraction(gBattleSpritesDataPtr->battleBars[battlerId].oldValue,
                    gBattleSpritesDataPtr->battleBars[battlerId].receivedValue,
                    gBattleSpritesDataPtr->battleBars[battlerId].maxValue, 50);
        if (expFraction == 0)
            expFraction = 1;
        expFraction = abs(gBattleSpritesDataPtr->battleBars[battlerId].receivedValue / expFraction);

        currentBarValue = CalcNewBarValue(gBattleSpritesDataPtr->battleBars[battlerId].maxValue,
                    gBattleSpritesDataPtr->battleBars[battlerId].oldValue,
                    gBattleSpritesDataPtr->battleBars[battlerId].receivedValue,
                    &gBattleSpritesDataPtr->battleBars[battlerId].currValue,
                    B_EXPBAR_PIXELS, expFraction);
    }

    if (whichBar == EXP_BAR || (whichBar == HEALTH_BAR && !gBattleSpritesDataPtr->battlerData[battlerId].hpNumbersNoBars))
        MoveBattleBarGraphically(battlerId, whichBar);

    if (currentBarValue == -1)
        gBattleSpritesDataPtr->battleBars[battlerId].currValue = 0;

    return currentBarValue;
}

static void MoveBattleBarGraphically(u8 battlerId, u8 whichBar)
{
    u8 array[8];
    u8 filledPixelsCount, level, healthbarSpriteId;
    u8 barElementId;
    u8 i;

    switch (whichBar)
    {
    case HEALTH_BAR:
        filledPixelsCount = CalcBarFilledPixels(gBattleSpritesDataPtr->battleBars[battlerId].maxValue,
                            gBattleSpritesDataPtr->battleBars[battlerId].oldValue,
                            gBattleSpritesDataPtr->battleBars[battlerId].receivedValue,
                            &gBattleSpritesDataPtr->battleBars[battlerId].currValue,
                            array, B_HEALTHBAR_PIXELS / 8);

        if (filledPixelsCount > (B_HEALTHBAR_PIXELS * 50 / 100)) // more than 50 % hp
            barElementId = HEALTHBOX_GFX_HP_BAR_GREEN;
        else if (filledPixelsCount > (B_HEALTHBAR_PIXELS * 20 / 100)) // more than 20% hp
            barElementId = HEALTHBOX_GFX_HP_BAR_YELLOW;
        else
            barElementId = HEALTHBOX_GFX_HP_BAR_RED; // 20 % or less

        for (i = 0; i < 6; i++)
        {
            healthbarSpriteId = gSprites[gBattleSpritesDataPtr->battleBars[battlerId].healthboxSpriteId].hMain_HealthBarSpriteId;
            CpuCopy32(GetHealthboxElementGfxPtr(barElementId) + array[i] * 32 + 12,
                      (void*)(OBJ_VRAM0 + (gSprites[healthbarSpriteId].oam.tileNum + 1 + i) * TILE_SIZE_4BPP + 12), 8);
        }
        break;
    case EXP_BAR:
        CalcExpBarFilledPixels(gBattleSpritesDataPtr->battleBars[battlerId].maxValue,
                    gBattleSpritesDataPtr->battleBars[battlerId].oldValue,
                    gBattleSpritesDataPtr->battleBars[battlerId].receivedValue,
                    &gBattleSpritesDataPtr->battleBars[battlerId].currValue,
                    array, B_EXPBAR_PIXELS);
        level = GetMonData(&gPlayerParty[gBattlerPartyIndexes[battlerId]], MON_DATA_LEVEL);
        if (level == MAX_LEVEL)
        {
            for (i = 0; i < 8; i++)
                array[i] = 0;
        }
        healthbarSpriteId = gSprites[gBattleSpritesDataPtr->battleBars[battlerId].healthboxSpriteId].hMain_HealthBarSpriteId;
        CpuCopy16(GetHealthboxElementGfxPtr(HEALTHBOX_GFX_EXP_BAR) + 9 * 32 + 8 + array[0] * 2,
                  (void*)(OBJ_VRAM0 + gSprites[healthbarSpriteId].oam.tileNum * TILE_SIZE_4BPP + 10), 2);
        CpuCopy16(GetHealthboxElementGfxPtr(HEALTHBOX_GFX_EXP_BAR) + 9 * 32 + 12 + array[0] * 2,
                  (void*)(OBJ_VRAM0 + gSprites[healthbarSpriteId].oam.tileNum * TILE_SIZE_4BPP + 14), 2);
        CpuCopy16(GetHealthboxElementGfxPtr(HEALTHBOX_GFX_EXP_BAR) + 9 * 32 + 16 + array[0] * 2,
                  (void*)(OBJ_VRAM0 + gSprites[healthbarSpriteId].oam.tileNum * TILE_SIZE_4BPP + 18), 2);
        CpuCopy16(GetHealthboxElementGfxPtr(HEALTHBOX_GFX_EXP_BAR) + 9 * 32 + 20 + array[0] * 2,
                  (void*)(OBJ_VRAM0 + gSprites[healthbarSpriteId].oam.tileNum * TILE_SIZE_4BPP + 22), 2);
        for (i = 1; i < 7; i++)
        {
            CpuCopy32(GetHealthboxElementGfxPtr(HEALTHBOX_GFX_EXP_BAR) + array[i] * 32 + 8,
                      (void*)(OBJ_VRAM0 + (gSprites[healthbarSpriteId].oam.tileNum + i) * TILE_SIZE_4BPP + 8), 4);
            CpuCopy32(GetHealthboxElementGfxPtr(HEALTHBOX_GFX_EXP_BAR) + array[i] * 32 + 20,
                      (void*)(OBJ_VRAM0 + (gSprites[healthbarSpriteId].oam.tileNum + i) * TILE_SIZE_4BPP + 20), 4);
        }
        CpuCopy16(GetHealthboxElementGfxPtr(HEALTHBOX_GFX_EXP_BAR) + 10 * 32 + 8 + array[7] * 2,
                  (void*)(OBJ_VRAM0 + (gSprites[healthbarSpriteId].oam.tileNum + 7) * TILE_SIZE_4BPP + 8), 2);
        CpuCopy16(GetHealthboxElementGfxPtr(HEALTHBOX_GFX_EXP_BAR) + 10 * 32 + 12 + array[7] * 2,
                  (void*)(OBJ_VRAM0 + (gSprites[healthbarSpriteId].oam.tileNum + 7) * TILE_SIZE_4BPP + 12), 2);
        CpuCopy16(GetHealthboxElementGfxPtr(HEALTHBOX_GFX_EXP_BAR) + 10 * 32 + 16 + array[7] * 2,
                  (void*)(OBJ_VRAM0 + (gSprites[healthbarSpriteId].oam.tileNum + 7) * TILE_SIZE_4BPP + 16), 2);
        CpuCopy16(GetHealthboxElementGfxPtr(HEALTHBOX_GFX_EXP_BAR) + 10 * 32 + 20 + array[7] * 2,
                  (void*)(OBJ_VRAM0 + (gSprites[healthbarSpriteId].oam.tileNum + 7) * TILE_SIZE_4BPP + 20), 2);
        break;
    }
}

static s32 CalcNewBarValue(s32 maxValue, s32 oldValue, s32 receivedValue, s32 *currValue, u8 scale, u16 toAdd)
{
    s32 ret, newValue;

    if (*currValue == -32768) // first function call
    {
        if (maxValue < scale)
            *currValue = Q_24_8(oldValue);
        else
            *currValue = oldValue;
    }

    newValue = oldValue - receivedValue;
    if (newValue < 0)
        newValue = 0;
    else if (newValue > maxValue)
        newValue = maxValue;

    if (maxValue < scale)
    {
        if (newValue == Q_24_8_TO_INT(*currValue) && (*currValue & 0xFF) == 0)
            return -1;
    }
    else
    {
        if (newValue == *currValue) // we're done, the bar's value has been updated
            return -1;
    }

    if (maxValue < scale) // handle cases of max var having less pixels than the whole bar
    {
        s32 toAdd = Q_24_8(maxValue) / scale;

        if (receivedValue < 0) // fill bar right
        {
            *currValue += toAdd;
            ret = Q_24_8_TO_INT(*currValue);
            if (ret >= newValue)
            {
                *currValue = Q_24_8(newValue);
                ret = newValue;
            }
        }
        else // move bar left
        {
            *currValue -= toAdd;
            ret = Q_24_8_TO_INT(*currValue);
            // try round up
            if ((*currValue & 0xFF) > 0)
                ret++;
            if (ret <= newValue)
            {
                *currValue = Q_24_8(newValue);
                ret = newValue;
            }
        }
    }
    else
    {
        if (receivedValue < 0) // fill bar right
        {
            *currValue += toAdd;
            if (*currValue > newValue)
                *currValue = newValue;
            ret = *currValue;
        }
        else // move bar left
        {
            *currValue -= toAdd;
            if (*currValue < newValue)
                *currValue = newValue;
            ret = *currValue;
        }
    }

    return ret;
}

static u8 CalcBarFilledPixels(s32 maxValue, s32 oldValue, s32 receivedValue, s32 *currValue, u8 *arg4, u8 scale)
{
    u8 pixels, filledPixels, totalPixels;
    u8 i;

    s32 newValue = oldValue - receivedValue;
    if (newValue < 0)
        newValue = 0;
    else if (newValue > maxValue)
        newValue = maxValue;

    totalPixels = scale * 8;

    for (i = 0; i < scale; i++)
        arg4[i] = 0;

    if (maxValue < totalPixels)
        pixels = (*currValue * totalPixels / maxValue) >> 8;
    else
        pixels = *currValue * totalPixels / maxValue;

    filledPixels = pixels;

    if (filledPixels == 0 && newValue > 0)
    {
        arg4[0] = 1;
        filledPixels = 1;
    }
    else
    {
        for (i = 0; i < scale; i++)
        {
            if (pixels >= 8)
            {
                arg4[i] = 8;
            }
            else
            {
                arg4[i] = pixels;
                break;
            }
            pixels -= 8;
        }
    }

    return filledPixels;
}

static void CalcExpBarFilledPixels(s32 maxValue, s32 oldValue, s32 receivedValue, s32 *currValue, u8 *arg4, u8 totalPixels)
{
    u8 i, pixels, filledPixels;

    s32 newValue = oldValue - receivedValue;
    if (newValue < 0)
        newValue = 0;
    else if (newValue > maxValue)
        newValue = maxValue;

    for (i = 0; i < 8; i++)
        arg4[i] = 0;

    if (maxValue < totalPixels)
        pixels = (*currValue * totalPixels / maxValue) >> 8;
    else
        pixels = *currValue * totalPixels / maxValue;

    filledPixels = pixels;

    if (newValue > 0)
    {
        arg4[0] = 1;
        if (filledPixels == 0)
            return;
        pixels--;
        for (i = 1; i < 7; i++)
        {
            if (pixels >= 8)
            {
                arg4[i] = 8;
            }
            else
            {
                arg4[i] = pixels;
                return;
            }
            pixels -= 8;
        }
        if (pixels >= 1)
            arg4[7] = 1;
    }
}

static u8 GetScaledExpFraction(s32 oldValue, s32 receivedValue, s32 maxValue, u8 scale)
{
    s32 newVal, result;
    s8 oldToMax, newToMax;

    newVal = oldValue - receivedValue;

    if (newVal < 0)
        newVal = 0;
    else if (newVal > maxValue)
        newVal = maxValue;

    oldToMax = oldValue * scale / maxValue;
    newToMax = newVal * scale / maxValue;
    result = oldToMax - newToMax;

    return abs(result);
}

u8 GetScaledHPFraction(s16 hp, s16 maxhp, u8 scale)
{
    u8 result = hp * scale / maxhp;

    if (result == 0 && hp > 0)
        return 1;

    return result;
}

u8 GetHPBarLevel(s16 hp, s16 maxhp)
{
    u8 result;

    if (hp == maxhp)
    {
        result = HP_BAR_FULL;
    }
    else
    {
        u8 fraction = GetScaledHPFraction(hp, maxhp, B_HEALTHBAR_PIXELS);
        if (fraction > (B_HEALTHBAR_PIXELS * 50 / 100)) // more than 50 % hp
            result = HP_BAR_GREEN;
        else if (fraction > (B_HEALTHBAR_PIXELS * 20 / 100)) // more than 20% hp
            result = HP_BAR_YELLOW;
        else if (fraction > 0)
            result = HP_BAR_RED;
        else
            result = HP_BAR_EMPTY;
    }

    return result;
}

static u8* AddTextPrinterAndCreateWindowOnHealthbox(const u8 *str, u32 x, u32 y, u32 bgColor, u32 *windowId)
{
    u16 winId;
    u8 color[3];
    struct WindowTemplate winTemplate = sHealthboxWindowTemplate;

    winId = AddWindow(&winTemplate);
    //FillWindowPixelBuffer(winId, PIXEL_FILL(bgColor));

    color[0] = bgColor;
    color[1] = 1;
    color[2] = 3;

    AddTextPrinterParameterized4(winId, 3, x, y, -1, 0, 0, -1, str);

    *windowId = winId;
    return (u8*)(GetWindowAttribute(winId, WINDOW_TILE_DATA));
}

static void RemoveWindowOnHealthbox(u32 windowId)
{
    RemoveWindow(windowId);
}

static void FillHealthboxObject(void *dest, u32 arg1, u32 arg2)
{
    CpuFill32(0x11111111 * arg1, dest, arg2 * TILE_SIZE_4BPP);
}

static void HpTextIntoHealthboxObject(void *dest, u8 *windowTileData, u32 windowWidth)
{
    CpuCopy32(windowTileData + 256, dest, windowWidth * TILE_SIZE_4BPP);
}

static void TextIntoHealthboxObject(void *dest, u8 *windowTileData, s32 windowWidth)
{
    CpuCopy32(windowTileData, dest, windowWidth * TILE_SIZE_4BPP);
// + 256 as that prevents the top 4 blank rows of sHealthboxWindowTemplate from being copied
    if (windowWidth > 0)
    {
        do
        {
            CpuCopy32(windowTileData + 256, dest + 256, 28);
            dest += 32, windowTileData += 32;
            windowWidth--;
        } while (windowWidth != 0);
    }
}

static void SafariTextIntoHealthboxObject(void *dest, u8 *windowTileData, u32 windowWidth)
{
    CpuCopy32(windowTileData, dest, windowWidth * TILE_SIZE_4BPP);
    CpuCopy32(windowTileData + 256, dest + 256, windowWidth * TILE_SIZE_4BPP);
}

#define ABILITY_POP_UP_TAG 0xD720

// for sprite
#define tOriginalX      data[0]
#define tHide           data[1]
#define tFrames         data[2]
#define tRightToLeft    data[3]
#define tBattlerId      data[4]
#define tIsMain         data[5]

// for task
#define tSpriteId1      data[6]
#define tSpriteId2      data[7]

static const u8 sAbilityPopUpGfx[] = INCBIN_U8("graphics/battle_interface/ability_pop_up.4bpp");
static const u16 sAbilityPopUpPalette[] = INCBIN_U16("graphics/battle_interface/ability_pop_up.gbapal");

static const struct SpriteSheet sSpriteSheet_AbilityPopUp =
{
    sAbilityPopUpGfx, sizeof(sAbilityPopUpGfx), ABILITY_POP_UP_TAG
};
static const struct SpritePalette sSpritePalette_AbilityPopUp =
{
    sAbilityPopUpPalette, ABILITY_POP_UP_TAG
};

static const struct OamData sOamData_AbilityPopUp =
{
    .y = 0,
    .affineMode = 0,
    .objMode = 0,
    .mosaic = 0,
    .bpp = 0,
    .shape = ST_OAM_H_RECTANGLE,
    .x = 0,
    .matrixNum = 0,
    .size = 3,
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
    .affineParam = 0,
};

static const union AnimCmd sSpriteAnim_AbilityPopUp1[] =
{
    ANIMCMD_FRAME(0, 0),
    ANIMCMD_END
};

static const union AnimCmd *const sSpriteAnimTable_AbilityPopUp1[] =
{
    sSpriteAnim_AbilityPopUp1
};

static const struct SpriteTemplate sSpriteTemplate_AbilityPopUp1 =
{
    .tileTag = ABILITY_POP_UP_TAG,
    .paletteTag = ABILITY_POP_UP_TAG,
    .oam = &sOamData_AbilityPopUp,
    .anims = sSpriteAnimTable_AbilityPopUp1,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCb_AbilityPopUp
};

static const union AnimCmd sSpriteAnim_AbilityPopUp2[] =
{
    ANIMCMD_FRAME(32, 0),
    ANIMCMD_END
};

static const union AnimCmd *const sSpriteAnimTable_AbilityPopUp2[] =
{
    sSpriteAnim_AbilityPopUp2
};

static const struct SpriteTemplate sSpriteTemplate_AbilityPopUp2 =
{
    .tileTag = ABILITY_POP_UP_TAG,
    .paletteTag = ABILITY_POP_UP_TAG,
    .oam = &sOamData_AbilityPopUp,
    .anims = sSpriteAnimTable_AbilityPopUp2,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCb_AbilityPopUp
};

#define ABILITY_POP_UP_POS_X_DIFF 64
#define ABILITY_POP_UP_POS_X_SLIDE 68

static const s16 sAbilityPopUpCoordsDoubles[MAX_BATTLERS_COUNT][2] =
{
    {29, 80}, // player left
    {204, 19}, // opponent left
    {29, 97}, // player right
    {204, 36}, // opponent right
};

static const s16 sAbilityPopUpCoordsSingles[MAX_BATTLERS_COUNT][2] =
{
    {29, 93}, // player
    {204, 23}, // opponent
};

static u8* AddTextPrinterAndCreateWindowOnAbilityPopUp(const u8 *str, u32 x, u32 y, u32 color1, u32 color2, u32 color3, u32 *windowId)
{
    u8 color[3] = {color1, color2, color3};
    struct WindowTemplate winTemplate = {0};
    winTemplate.width = 8;
    winTemplate.height = 2;

    *windowId = AddWindow(&winTemplate);
    FillWindowPixelBuffer(*windowId, (color1 << 4) | (color1));

    AddTextPrinterParameterized4(*windowId, 0, x, y, 0, 0, color, -1, str);
    return (u8*)(GetWindowAttribute(*windowId, WINDOW_TILE_DATA));
}

static void TextIntoAbilityPopUp(void *dest, u8 *windowTileData, s32 arg2, bool32 arg3)
{
    CpuCopy32(windowTileData + 256, dest + 256, arg2 * 32);
    if (arg2 > 0)
    {
        do
        {
            if (arg3)
                CpuCopy32(windowTileData + 16, dest + 16, 16);
            else
                CpuCopy32(windowTileData + 20, dest + 20, 12);
            dest += 32, windowTileData += 32;
            arg2--;
        } while (arg2 != 0);
    }
}

#define MAX_CHARS_PRINTED 12

static void PrintOnAbilityPopUp(const u8 *str, u8 *spriteTileData1, u8 *spriteTileData2, u32 x1, u32 x2, u32 y, u32 color1, u32 color2, u32 color3)
{
    u32 windowId, i;
    u8 *windowTileData;
    u8 text1[MAX_CHARS_PRINTED + 2];
    u8 text2[MAX_CHARS_PRINTED + 2];

    for (i = 0; i < MAX_CHARS_PRINTED + 1; i++)
    {
        text1[i] = str[i];
        if (text1[i] == EOS)
            break;
    }
    text1[i] = EOS;

    windowTileData = AddTextPrinterAndCreateWindowOnAbilityPopUp(text1, x1, y, color1, color2, color3, &windowId);
    TextIntoAbilityPopUp(spriteTileData1, windowTileData, 8, (y == 0));
    RemoveWindow(windowId);

    if (i == MAX_CHARS_PRINTED + 1)
    {
        for (i = 0; i < MAX_CHARS_PRINTED; i++)
        {
            text2[i] = str[MAX_CHARS_PRINTED + i];
            if (text2[i] == EOS)
                break;
        }
        text2[i] = EOS;

        windowTileData = AddTextPrinterAndCreateWindowOnAbilityPopUp(text2, x2, y, color1, color2, color3, &windowId);
        TextIntoAbilityPopUp(spriteTileData2, windowTileData, 1, (y == 0));
        RemoveWindow(windowId);
    }
}

static void PrintBattlerOnAbilityPopUp(u8 battlerId, u8 spriteId1, u8 spriteId2)
{
    PrintOnAbilityPopUp(gBattleMons[battlerId].nickname,
                        (void*)(OBJ_VRAM0) + (gSprites[spriteId1].oam.tileNum * 32),
                        (void*)(OBJ_VRAM0) + (gSprites[spriteId2].oam.tileNum * 32),
                        7, 0,
                        0,
                        2, 7, 1);
}

static void PrintAbilityOnAbilityPopUp(u32 ability, u8 spriteId1, u8 spriteId2)
{
    PrintOnAbilityPopUp(gAbilityNames[ability],
                        (void*)(OBJ_VRAM0) + (gSprites[spriteId1].oam.tileNum * 32) + 256,
                        (void*)(OBJ_VRAM0) + (gSprites[spriteId2].oam.tileNum * 32) + 256,
                        7, 1,
                        4,
                        7, 9, 1);
}

#define PIXEL_COORDS_TO_OFFSET(x, y)(			\
/*Add tiles by X*/								\
((y / 8) * 32 * 8)								\
/*Add tiles by X*/								\
+ ((x / 8) * 32)								\
/*Add pixels by Y*/								\
+ ((((y) - ((y / 8) * 8))) * 4)				    \
/*Add pixels by X*/								\
+ ((((x) - ((x / 8) * 8)) / 2)))

static const u16 sOverwrittenPixelsTable[][2] =
{
	{PIXEL_COORDS_TO_OFFSET(0, 0), 5},
	{PIXEL_COORDS_TO_OFFSET(0, 1), 5},
	{PIXEL_COORDS_TO_OFFSET(0, 2), 5},
	{PIXEL_COORDS_TO_OFFSET(0, 3), 5},
	{PIXEL_COORDS_TO_OFFSET(0, 4), 5},
	{PIXEL_COORDS_TO_OFFSET(0, 5), 5},
	{PIXEL_COORDS_TO_OFFSET(0, 6), 5},
	{PIXEL_COORDS_TO_OFFSET(0, 7), 3},
	{PIXEL_COORDS_TO_OFFSET(0, 8), 3},
	{PIXEL_COORDS_TO_OFFSET(0, 9), 3},
	{PIXEL_COORDS_TO_OFFSET(0, 10), 3},
	{PIXEL_COORDS_TO_OFFSET(0, 11), 3},
	{PIXEL_COORDS_TO_OFFSET(0, 12), 3},
	{PIXEL_COORDS_TO_OFFSET(0, 13), 8},

	{PIXEL_COORDS_TO_OFFSET(8, 13), 8},
	{PIXEL_COORDS_TO_OFFSET(16, 13), 8},
	{PIXEL_COORDS_TO_OFFSET(24, 13), 8},
	{PIXEL_COORDS_TO_OFFSET(32, 13), 8},
	{PIXEL_COORDS_TO_OFFSET(40, 13), 8},
	{PIXEL_COORDS_TO_OFFSET(48, 13), 8},
	{PIXEL_COORDS_TO_OFFSET(56, 13), 8},

    {PIXEL_COORDS_TO_OFFSET(0, 14), 8},
	{PIXEL_COORDS_TO_OFFSET(8, 14), 8},
	{PIXEL_COORDS_TO_OFFSET(16, 14), 8},
	{PIXEL_COORDS_TO_OFFSET(24, 14), 8},
	{PIXEL_COORDS_TO_OFFSET(32, 14), 8},
	{PIXEL_COORDS_TO_OFFSET(40, 14), 8},
	{PIXEL_COORDS_TO_OFFSET(48, 14), 8},
	{PIXEL_COORDS_TO_OFFSET(56, 14), 8},

	{PIXEL_COORDS_TO_OFFSET(0, 15), 3},
	{PIXEL_COORDS_TO_OFFSET(0, 16), 3},
	{PIXEL_COORDS_TO_OFFSET(0, 17), 3},
	{PIXEL_COORDS_TO_OFFSET(0, 18), 3},
	{PIXEL_COORDS_TO_OFFSET(0, 19), 3},
	{PIXEL_COORDS_TO_OFFSET(0, 20), 3},
	{PIXEL_COORDS_TO_OFFSET(0, 21), 3},
	{PIXEL_COORDS_TO_OFFSET(0, 22), 3},
	{PIXEL_COORDS_TO_OFFSET(0, 23), 3},
	{PIXEL_COORDS_TO_OFFSET(0, 24), 3},
	{PIXEL_COORDS_TO_OFFSET(0, 25), 3},
	{PIXEL_COORDS_TO_OFFSET(0, 26), 3},
};

static inline void CopyPixels(u8 *dest, const u8 *src, u32 pixelCount)
{
	u32 i = 0;

	if (pixelCount & 1)
	{
		while (pixelCount != 0)
		{
			dest[i] &= ~(0xF);
			dest[i] |= (src[i] & 0xF);
			if (--pixelCount != 0)
			{
				dest[i] &= ~(0xF0);
				dest[i] |= (src[i] & 0xF0);
				pixelCount--;
			}
			i++;
		}
	}
	else
	{
		for (i = 0; i < pixelCount / 2; i++)
			dest[i] = src[i];
	}
}

static void RestoreOverwrittenPixels(u8 *tiles)
{
	u32 i;
	u8 *buffer = Alloc(sizeof(sAbilityPopUpGfx) * 2);

	CpuCopy32(tiles, buffer, sizeof(sAbilityPopUpGfx));

	for (i = 0; i < ARRAY_COUNT(sOverwrittenPixelsTable); i++)
	{
		CopyPixels(buffer + sOverwrittenPixelsTable[i][0],
				   sAbilityPopUpGfx + sOverwrittenPixelsTable[i][0],
				   sOverwrittenPixelsTable[i][1]);
	}

	CpuCopy32(buffer, tiles, sizeof(sAbilityPopUpGfx));
	Free(buffer);
}

void CreateAbilityPopUp(u8 battlerId, u32 ability, bool32 isDoubleBattle)
{
    const s16 (*coords)[2];
    u8 spriteId1, spriteId2, battlerPosition, taskId;

    if (!B_ABILITY_POP_UP)
        return;

    if (!gBattleStruct->activeAbilityPopUps)
    {
        LoadSpriteSheet(&sSpriteSheet_AbilityPopUp);
        LoadSpritePalette(&sSpritePalette_AbilityPopUp);
    }
    gBattleStruct->activeAbilityPopUps |= gBitTable[battlerId];
    battlerPosition = GetBattlerPosition(battlerId);

    if (isDoubleBattle)
        coords = sAbilityPopUpCoordsDoubles;
    else
        coords = sAbilityPopUpCoordsSingles;

    if ((battlerPosition & BIT_SIDE) == B_SIDE_PLAYER)
    {
        spriteId1 = CreateSprite(&sSpriteTemplate_AbilityPopUp1,
                                coords[battlerPosition][0] - ABILITY_POP_UP_POS_X_SLIDE,
                                coords[battlerPosition][1], 0);
        spriteId2 = CreateSprite(&sSpriteTemplate_AbilityPopUp2,
                                coords[battlerPosition][0] - ABILITY_POP_UP_POS_X_SLIDE + ABILITY_POP_UP_POS_X_DIFF,
                                coords[battlerPosition][1], 0);

        gSprites[spriteId1].tOriginalX = coords[battlerPosition][0];
        gSprites[spriteId2].tOriginalX = coords[battlerPosition][0] + ABILITY_POP_UP_POS_X_DIFF;

        gSprites[spriteId1].tRightToLeft = TRUE;
        gSprites[spriteId2].tRightToLeft = TRUE;
    }
    else
    {
        spriteId1 = CreateSprite(&sSpriteTemplate_AbilityPopUp1,
                                coords[battlerPosition][0] + ABILITY_POP_UP_POS_X_SLIDE,
                                coords[battlerPosition][1], 0);
        spriteId2 = CreateSprite(&sSpriteTemplate_AbilityPopUp2,
                                coords[battlerPosition][0] + ABILITY_POP_UP_POS_X_SLIDE + ABILITY_POP_UP_POS_X_DIFF,
                                coords[battlerPosition][1], 0);

        gSprites[spriteId1].tOriginalX = coords[battlerPosition][0];
        gSprites[spriteId2].tOriginalX = coords[battlerPosition][0] + ABILITY_POP_UP_POS_X_DIFF;

        gSprites[spriteId1].tRightToLeft = FALSE;
        gSprites[spriteId2].tRightToLeft = FALSE;
    }

    taskId = CreateTask(Task_FreeAbilityPopUpGfx, 5);
    gTasks[taskId].tSpriteId1 = spriteId1;
    gTasks[taskId].tSpriteId2 = spriteId2;

    gSprites[spriteId1].tIsMain = TRUE;
    gSprites[spriteId1].tBattlerId = battlerId;
    gSprites[spriteId2].tBattlerId = battlerId;

    StartSpriteAnim(&gSprites[spriteId1], 0);
    StartSpriteAnim(&gSprites[spriteId2], 0);

    PrintBattlerOnAbilityPopUp(battlerId, spriteId1, spriteId2);
    PrintAbilityOnAbilityPopUp(ability, spriteId1, spriteId2);
    RestoreOverwrittenPixels((void*)(OBJ_VRAM0) + (gSprites[spriteId1].oam.tileNum * 32));
}

#define FRAMES_TO_WAIT 48

static void SpriteCb_AbilityPopUp(struct Sprite *sprite)
{
    if (!sprite->tHide) // Show
    {
        if (sprite->tIsMain && ++sprite->tFrames == 4)
            PlaySE(SE_SELECT);
        if ((!sprite->tRightToLeft && (sprite->pos1.x -= 4) <= sprite->tOriginalX)
            || (sprite->tRightToLeft && (sprite->pos1.x += 4) >= sprite->tOriginalX)
           )
        {
            sprite->pos1.x = sprite->tOriginalX;
            sprite->tHide = TRUE;
            sprite->tFrames = FRAMES_TO_WAIT;
        }
    }
    else // Hide
    {
        if (sprite->tFrames == 0)
        {
            if ((!sprite->tRightToLeft && (sprite->pos1.x += 4) >= sprite->tOriginalX + ABILITY_POP_UP_POS_X_SLIDE)
                ||(sprite->tRightToLeft && (sprite->pos1.x -= 4) <= sprite->tOriginalX - ABILITY_POP_UP_POS_X_SLIDE)
               )
            {
                gBattleStruct->activeAbilityPopUps &= ~(gBitTable[sprite->tBattlerId]);
                DestroySprite(sprite);
            }
        }
        else
        {
            sprite->tFrames--;
        }
    }
}

static void Task_FreeAbilityPopUpGfx(u8 taskId)
{
    if (!gSprites[gTasks[taskId].tSpriteId1].inUse
        && !gSprites[gTasks[taskId].tSpriteId2].inUse
        && !gBattleStruct->activeAbilityPopUps)
    {
        FreeSpriteTilesByTag(ABILITY_POP_UP_TAG);
        FreeSpritePaletteByTag(ABILITY_POP_UP_TAG);
        DestroyTask(taskId);
    }
}