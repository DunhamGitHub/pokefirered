#include "global.h"
#include "malloc.h"
#include "bg.h"
#include "decompress.h"
#include "gpu_regs.h"
#include "palette.h"
#include "task.h"
#include "text.h"
#include "menu.h"
#include "menu_helpers.h"
#include "new_menu_helpers.h"
#include "list_menu.h"
#include "item.h"
#include "string_util.h"
#include "party_menu.h"
#include "data2.h"
#include "scanline_effect.h"
#include "sound.h"
#include "menu_indicators.h"
#include "constants/items.h"
#include "constants/songs.h"

struct UnkStruct_203B10C
{
    void (* unk_00)(void);
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u16 unk_08;
    u16 unk_0a;
};

struct UnkStruct_203B118
{
    void (* unk_00)(void);
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 unk_07;
    u8 unk_08;
    u16 unk_0a;
    u8 filler_0c[6];
    s16 unk_12;
    u8 filler_14[8];
};

struct UnkStruct_203B11C
{
    struct ItemSlot bagPocket_TMHM[BAG_TMHM_COUNT];
    struct ItemSlot bagPocket_KeyItems[BAG_KEYITEMS_COUNT];
    u16 unk_160;
    u16 unk_162;
};

EWRAM_DATA struct UnkStruct_203B10C gUnknown_203B10C = {};
EWRAM_DATA struct UnkStruct_203B118 * gUnknown_203B118 = NULL;
EWRAM_DATA struct UnkStruct_203B11C * gUnknown_203B11C = NULL;
EWRAM_DATA void * gUnknown_203B120 = NULL; // tilemap buffer
EWRAM_DATA struct ListMenuItem * gUnknown_203B124 = NULL;
EWRAM_DATA u8 (* gUnknown_203B128)[29] = NULL;
EWRAM_DATA u16 * gUnknown_203B12C = NULL;

void sub_8131894(void);
bool8 sub_81318C0(void);
void sub_8131A8C(void);
void sub_8131AB8(void);
bool8 sub_8131B20(void);
void sub_8131C10(void);
void sub_8131C50(void);
void sub_8131D48(u8 * dest, u16 itemId);
void sub_8131E18(s32 itemIndex, bool8 onInit, struct ListMenu *list);
void sub_8131E68(u8 windowId, s32 itemId, u8 y);
void sub_8131F0C(s32 itemIndex);
void sub_8131FB0(u8 a0, u8 a1);
void sub_8132018(void);
void sub_81320BC(void);
void sub_8132120(void);
void sub_8132170(void);
void sub_813226C(u8 taskId);
void sub_81322D4(u8 taskId);
void sub_8132F20(u8 taskId);
void sub_8133244(void);
void sub_81332EC(u8 windowId, u8 fontId, const u8 * str, u8 x, u8 y, u8 letterSpacing, u8 lineSpacing, u8 speed, u8 colorIdx);
void sub_81333C4(void);
void sub_8133404(void);
void sub_8133444(u16 itemId);
void sub_81335B0(u8 windowId, u8 x, u8 y);
u8 sub_813368C(u16 itemId);
void sub_81337E4(u8 a0, u16 itemId);
void sub_81338A8(void);

extern const struct BgTemplate gUnknown_8463134[3];
extern const u32 gUnknown_8E845D8[];
extern const u32 gUnknown_8E84A24[];
extern const u32 gUnknown_8E84B70[];
extern const u32 gUnknown_8E84CB0[];
extern const u32 gUnknown_8E84D20[];
extern const struct CompressedSpriteSheet gUnknown_8463218;
extern const u8 gUnknown_8463178[];
extern const u8 gUnknown_846317C[];

extern const u8 gUnknown_8416226[];
extern const u8 gFameCheckerText_ListMenuCursor[];
extern const u8 gUnknown_84162B9[];
extern const u8 gUnknown_84166DB[];
extern const u8 gUnknown_84166E1[];
extern const u8 gUnknown_84166FF[];
extern const u8 gUnknown_8416703[];

void sub_81317F8(u8 a0, void (* a1)(void), u8 a2)
{
    sub_8131A8C();
    gUnknown_203B118 = Alloc(sizeof(struct UnkStruct_203B118));
    gUnknown_203B118->unk_00 = 0;
    gUnknown_203B118->unk_08 = 0xFF;
    gUnknown_203B118->unk_07 = 0xFF;
    if (a0 != 5)
        gUnknown_203B10C.unk_04 = a0;
    if (a1 != NULL)
        gUnknown_203B10C.unk_00 = a1;
    if (a2 != 0xFF)
        gUnknown_203B10C.unk_05 = a2;
    gTextFlags.flag_2 = FALSE;
    SetMainCallback2(sub_8131894);
}

void sub_8131864(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    do_scheduled_bg_tilemap_copies_to_vram();
    UpdatePaletteFade();
}

void sub_8131880(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

void sub_8131894(void)
{
    while (1)
    {
        if (sub_80BF72C() == TRUE)
            break;
        if (sub_81318C0() == TRUE)
            break;
        if (sub_80BF708() == TRUE)
            break;
    }
}

bool8 sub_81318C0(void)
{
    u8 taskId;

    switch (gMain.state)
    {
    case 0:
        sub_80BF768();
        clear_scheduled_bg_copies_to_vram();
        gMain.state++;
        break;
    case 1:
        ScanlineEffect_Stop();
        gMain.state++;
        break;
    case 2:
        FreeAllSpritePalettes();
        gMain.state++;
        break;
    case 3:
        ResetPaletteFade();
        gMain.state++;
        break;
    case 4:
        ResetSpriteData();
        gMain.state++;
        break;
    case 5:
        ResetTasks();
        gMain.state++;
        break;
    case 6:
        sub_8131AB8();
        gUnknown_203B118->unk_12 = 0;
        gMain.state++;
        break;
    case 7:
        sub_8133244();
        gMain.state++;
        break;
    case 8:
        if (sub_8131B20())
            gMain.state++;
        break;
    case 9:
        sub_809A5E4(&gBagPockets[POCKET_TM_CASE - 1]);
        gMain.state++;
        break;
    case 10:
        sub_81320BC();
        sub_8132120();
        sub_8132170();
        gMain.state++;
        break;
    case 11:
        sub_8133404();
        gMain.state++;
        break;
    case 12:
        sub_8131C10();
        sub_8131C50();
        gMain.state++;
        break;
    case 13:
        sub_81333C4();
        gMain.state++;
        break;
    case 14:
        if (gUnknown_203B10C.unk_04 == 4)
            taskId = CreateTask(sub_8132F20, 0);
        else
            taskId = CreateTask(sub_81322D4, 0);
        gTasks[taskId].data[0] = ListMenuInit(&gUnknown_3005E70, gUnknown_203B10C.unk_0a, gUnknown_203B10C.unk_08);
        gMain.state++;
        break;
    case 15:
        sub_8132018();
        gMain.state++;
        break;
    case 16:
        gUnknown_203B118->unk_04 = sub_813368C(sub_809A798(POCKET_TM_CASE, gUnknown_203B10C.unk_0a + gUnknown_203B10C.unk_08));
        gMain.state++;
        break;
    case 17:
        BlendPalettes(0xFFFFFFFF, 16, 0);
        gMain.state++;
        break;
    case 18:
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, RGB_BLACK);
        gMain.state++;
        break;
    default:
        SetVBlankCallback(sub_8131880);
        SetMainCallback2(sub_8131864);
        return TRUE;
    }

    return FALSE;
}

void sub_8131A8C(void)
{
    gUnknown_203B118 = NULL;
    gUnknown_203B120 = NULL;
    gUnknown_203B124 = NULL;
    gUnknown_203B128 = NULL;
    gUnknown_203B12C = NULL;
}

void sub_8131AB8(void)
{
    void ** ptr;
    sub_80BF7C8();
    ptr = &gUnknown_203B120;
    *ptr = AllocZeroed(0x800);
    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, gUnknown_8463134, NELEMS(gUnknown_8463134));
    SetBgTilemapBuffer(2, *ptr);
    schedule_bg_copy_tilemap_to_vram(1);
    schedule_bg_copy_tilemap_to_vram(2);
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_1D_MAP | DISPCNT_OBJ_ON);
    SetGpuReg(REG_OFFSET_BLDCNT, 0);
    ShowBg(0);
    ShowBg(1);
    ShowBg(2);
}

bool8 sub_8131B20(void)
{
    switch (gUnknown_203B118->unk_12)
    {
    case 0:
        reset_temp_tile_data_buffers();
        decompress_and_copy_tile_data_to_vram(1, gUnknown_8E845D8, 0, 0, 0);
        gUnknown_203B118->unk_12++;
        break;
    case 1:
        if (free_temp_tile_data_buffers_if_possible() != TRUE)
        {
            LZDecompressWram(gUnknown_8E84A24, gUnknown_203B120);
            gUnknown_203B118->unk_12++;
        }
        break;
    case 2:
        LZDecompressWram(gUnknown_8E84B70, GetBgTilemapBuffer(1));
        gUnknown_203B118->unk_12++;
        break;
    case 3:
        if (gSaveBlock2Ptr->playerGender == MALE)
            LoadCompressedPalette(gUnknown_8E84CB0, 0, 0x80);
        else
            LoadCompressedPalette(gUnknown_8E84D20, 0, 0x80);
        gUnknown_203B118->unk_12++;
        break;
    case 4:
        LoadCompressedObjectPic(&gUnknown_8463218);
        gUnknown_203B118->unk_12++;
        break;
    default:
        sub_81338A8();
        gUnknown_203B118->unk_12 = 0;
        return TRUE;
    }

    return FALSE;
}

void sub_8131C10(void)
{
    struct BagPocket * pocket = &gBagPockets[POCKET_TM_CASE - 1];
    gUnknown_203B124 = Alloc((pocket->capacity + 1) * sizeof(struct ListMenuItem));
    gUnknown_203B128 = Alloc(gUnknown_203B118->unk_06 * 29);
}

void sub_8131C50(void)
{
    struct BagPocket * pocket = &gBagPockets[POCKET_TM_CASE - 1];
    u16 i;

    for (i = 0; i < gUnknown_203B118->unk_06; i++)
    {
        sub_8131D48(gUnknown_203B128[i], pocket->itemSlots[i].itemId);
        gUnknown_203B124[i].unk_00 = gUnknown_203B128[i];
        gUnknown_203B124[i].unk_04 = i;
    }
    gUnknown_203B124[i].unk_00 = gUnknown_84166DB;
    gUnknown_203B124[i].unk_04 = -2;
    gUnknown_3005E70.items = gUnknown_203B124;
    gUnknown_3005E70.totalItems = gUnknown_203B118->unk_06 + 1;
    gUnknown_3005E70.windowId = 0;
    gUnknown_3005E70.header_X = 0;
    gUnknown_3005E70.item_X = 8;
    gUnknown_3005E70.cursor_X = 0;
    gUnknown_3005E70.lettersSpacing = 0;
    gUnknown_3005E70.itemVerticalPadding = 2;
    gUnknown_3005E70.upText_Y = 2;
    gUnknown_3005E70.maxShowed = gUnknown_203B118->unk_05;
    gUnknown_3005E70.fontId = 2;
    gUnknown_3005E70.cursorPal = 2;
    gUnknown_3005E70.fillValue = 0;
    gUnknown_3005E70.cursorShadowPal = 3;
    gUnknown_3005E70.moveCursorFunc = sub_8131E18;
    gUnknown_3005E70.itemPrintFunc = sub_8131E68;
    gUnknown_3005E70.cursorKind = 0;
    gUnknown_3005E70.scrollMultiple = 0;
}

void sub_8131D48(u8 * dest, u16 itemId)
{
    StringCopy(gStringVar4, gUnknown_84166FF);
    if (itemId >= ITEM_HM01)
    {
        StringAppend(gStringVar4, gUnknown_8463178);
        StringAppend(gStringVar4, gUnknown_8416226);
        ConvertIntToDecimalStringN(gStringVar1, itemId - ITEM_HM01 + 1, STR_CONV_MODE_LEADING_ZEROS, 1);
        StringAppend(gStringVar4, gStringVar1);
    }
    else
    {
        StringAppend(gStringVar4, gUnknown_8416226);
        ConvertIntToDecimalStringN(gStringVar1, itemId - ITEM_TM01 + 1, STR_CONV_MODE_LEADING_ZEROS, 2);
        StringAppend(gStringVar4, gStringVar1);
    }
    StringAppend(gStringVar4, gUnknown_846317C);
    StringAppend(gStringVar4, gUnknown_8416703);
    StringAppend(gStringVar4, gMoveNames[ItemIdToBattleMoveId(itemId)]);
    StringCopy(dest, gStringVar4);
}

void sub_8131E18(s32 itemIndex, bool8 onInit, struct ListMenu *list)
{
    u16 itemId;

    if (itemIndex == -2)
        itemId = 0;
    else
        itemId = sub_809A798(POCKET_TM_CASE, itemIndex);

    if (onInit != TRUE)
    {
        PlaySE(SE_SELECT);
        sub_81337E4(gUnknown_203B118->unk_04, itemId);
    }
    sub_8131F0C(itemIndex);
    sub_8133444(itemId);
}

void sub_8131E68(u8 windowId, s32 itemId, u8 y)
{
    if (itemId != -2)
    {
        if (!itemid_is_unique(sub_809A798(POCKET_TM_CASE, itemId)))
        {
            ConvertIntToDecimalStringN(gStringVar1, sub_809A7B4(POCKET_TM_CASE, itemId), STR_CONV_MODE_RIGHT_ALIGN, 3);
            StringExpandPlaceholders(gStringVar4, gUnknown_84162B9);
            sub_81332EC(windowId, 0, gStringVar4, 0x7E, y, 0, 0, 0xFF, 1);
        }
        else
        {
            sub_81335B0(windowId, 8, y);
        }
    }
}

void sub_8131F0C(s32 itemIndex)
{
    const u8 * str;
    if (itemIndex != -2)
    {
        str = ItemId_GetDescription(sub_809A798(POCKET_TM_CASE, itemIndex));
    }
    else
    {
        str = gUnknown_84166E1;
    }
    FillWindowPixelBuffer(1, 0);
    sub_81332EC(1, 2, str, 2, 3, 1, 0, 0, 0);
}

void sub_8131F64(s32 a0)
{
    sub_80F6B08(2, 0, 12, 30, 8, 2 * a0 + 1);
    schedule_bg_copy_tilemap_to_vram(2);
}

void sub_8131F90(u8 a0, u8 a1)
{
    sub_8131FB0(ListMenuGetYCoordForPrintingArrowCursor(a0), a1);
}

void sub_8131FB0(u8 a0, u8 a1)
{
    if (a1 == 0xFF)
    {
        FillWindowPixelRect(0, 0, 0, a0, GetFontAttribute(2, 0), GetFontAttribute(2, 1));
        CopyWindowToVram(0, 2);
    }
    else
    {
        sub_81332EC(0, 2, gFameCheckerText_ListMenuCursor, 0, a0, 0, 0, 0, a1);
    }
}

void sub_8132018(void)
{
    gUnknown_203B118->unk_08 = AddScrollIndicatorArrowPairParametrized(2, 0xA0, 0x08, 0x58, gUnknown_203B118->unk_06 - gUnknown_203B118->unk_05 + 1, 0x6E, 0x6E, &gUnknown_203B10C.unk_0a);
}

void sub_8132054(void)
{
    gUnknown_203B118->unk_0a = 1;
    gUnknown_203B118->unk_08 = AddScrollIndicatorArrowPairParametrized(2, 0x98, 0x48, 0x68, 2, 0x6E, 0x6E, &gUnknown_203B118->unk_0a);
}

void sub_813208C(void)
{
    if (gUnknown_203B118->unk_08 != 0xFF)
    {
        RemoveScrollIndicatorArrowPair(gUnknown_203B118->unk_08);
        gUnknown_203B118->unk_08 = 0xFF;
    }
}

void sub_81320AC(void)
{
    gUnknown_203B10C.unk_08 = 0;
    gUnknown_203B10C.unk_0a = 0;
}

void sub_81320BC(void)
{
    struct BagPocket * pocket = &gBagPockets[POCKET_TM_CASE - 1];
    u16 i;

    sub_809A584(pocket->itemSlots, pocket->capacity);
    gUnknown_203B118->unk_06 = 0;
    for (i = 0; i < pocket->capacity; i++)
    {
        if (pocket->itemSlots[i].itemId == ITEM_NONE)
            break;
        gUnknown_203B118->unk_06++;
    }
    gUnknown_203B118->unk_05 = min(gUnknown_203B118->unk_06 + 1, 5);
}

void sub_8132120(void)
{
    if (gUnknown_203B10C.unk_0a != 0)
    {
        if (gUnknown_203B10C.unk_0a + gUnknown_203B118->unk_05 > gUnknown_203B118->unk_06 + 1)
            gUnknown_203B10C.unk_0a = gUnknown_203B118->unk_06 + 1 - gUnknown_203B118->unk_05;
    }
    if (gUnknown_203B10C.unk_0a + gUnknown_203B10C.unk_08 >= gUnknown_203B118->unk_06 + 1)
    {
        if (gUnknown_203B118->unk_06 + 1 < 2)
            gUnknown_203B10C.unk_08 = 0;
        else
            gUnknown_203B10C.unk_08 = gUnknown_203B118->unk_06;
    }
}

void sub_8132170(void)
{
    u8 i;
    if (gUnknown_203B10C.unk_08 > 3)
    {
        for (i = 0; i <= gUnknown_203B10C.unk_08 - 3 && gUnknown_203B10C.unk_0a + gUnknown_203B118->unk_05 != gUnknown_203B118->unk_06 + 1; i++)
        {
            do {} while (0);
            gUnknown_203B10C.unk_08--;
            gUnknown_203B10C.unk_0a++;
        }
    }
}

void sub_81321D4(void)
{
    if (gUnknown_203B118 != NULL)
        Free(gUnknown_203B118);
    if (gUnknown_203B120 != NULL)
        Free(gUnknown_203B120);
    if (gUnknown_203B124 != NULL)
        Free(gUnknown_203B124);
    if (gUnknown_203B128 != NULL)
        Free(gUnknown_203B128);
    if (gUnknown_203B12C != NULL)
        Free(gUnknown_203B12C);
    FreeAllWindowBuffers();
}

void sub_8132230(u8 taskId)
{
    BeginNormalPaletteFade(0xFFFFFFFF, -2, 0, 16, RGB_BLACK);
    gTasks[taskId].func = sub_813226C;
}

void sub_813226C(u8 taskId)
{
    s16 * data = gTasks[taskId].data;

    if (!gPaletteFade.active)
    {
        sub_810713C(data[0], &gUnknown_203B10C.unk_0a, &gUnknown_203B10C.unk_08);
        if (gUnknown_203B118->unk_00 != NULL)
            SetMainCallback2(gUnknown_203B118->unk_00);
        else
            SetMainCallback2(gUnknown_203B10C.unk_00);
        sub_813208C();
        sub_81321D4();
        DestroyTask(taskId);
    }
}
