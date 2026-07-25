/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include "quantum.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default (VIA)
  [0] = LAYOUT_universal(
    KC_ESC   , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                                        KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , KC_DEL   ,
    KC_TAB   , KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                                        KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  , S(KC_7)  ,
    KC_LSFT  , KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,                                        KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  , KC_INT1  ,
              KC_LALT,KC_LGUI,LCTL_T(KC_LNG2)     ,LT(1,KC_SPC),LT(3,KC_LNG1),                  KC_BSPC,LT(2,KC_ENT), RCTL_T(KC_LNG2),     KC_RALT  , KC_PSCR
  ),

  [1] = LAYOUT_universal(
    SSNP_FRE ,  KC_F1   , KC_F2    , KC_F3   , KC_F4    , KC_F5    ,                                         KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   , KC_F11   ,
    SSNP_VRT ,  _______ , _______  , KC_UP   , KC_ENT   , KC_DEL   ,                                         KC_PGUP  , KC_BTN1  , KC_UP    , KC_BTN2  , KC_BTN3  , KC_F12   ,
    SSNP_HOR ,  _______ , KC_LEFT  , KC_DOWN , KC_RGHT  , KC_BSPC  ,                                         KC_PGDN  , KC_LEFT  , KC_DOWN  , KC_RGHT  , _______  , _______  ,
                  _______  , _______ , _______  ,         _______  , _______  ,                   _______  , _______  , _______       , _______  , _______
  ),

  [2] = LAYOUT_universal(
    _______  ,S(KC_QUOT), KC_7     , KC_8    , KC_9     , S(KC_8)  ,                                         S(KC_9)  , S(KC_1)  , S(KC_6)  , KC_LBRC  , S(KC_4)  , _______  ,
    _______  ,S(KC_SCLN), KC_4     , KC_5    , KC_6     , KC_RBRC  ,                                         KC_NUHS  , KC_MINS  , S(KC_EQL), S(KC_3)  , KC_QUOT  , S(KC_2)  ,
    _______  ,S(KC_MINS), KC_1     , KC_2    , KC_3     ,S(KC_RBRC),                                        S(KC_NUHS),S(KC_INT1), KC_EQL   ,S(KC_LBRC),S(KC_SLSH),S(KC_INT3),
                  KC_0     , KC_DOT  , _______  ,         _______  , _______  ,                   KC_DEL   , _______  , _______       , _______  , _______
  ),

  [3] = LAYOUT_universal(
    RGB_TOG  , AML_TO   , AML_I50  , AML_D50  , _______  , _______  ,                                        RGB_M_P  , RGB_M_B  , RGB_M_R  , RGB_M_SW , RGB_M_SN , RGB_M_K  ,
    RGB_MOD  , RGB_HUI  , RGB_SAI  , RGB_VAI  , _______  , SCRL_DVI ,                                        RGB_M_X  , RGB_M_G  , RGB_M_T  , RGB_M_TW , _______  , _______  ,
    RGB_RMOD , RGB_HUD  , RGB_SAD  , RGB_VAD  , _______  , SCRL_DVD ,                                        CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , _______  , KBC_SAVE ,
                  QK_BOOT  , KBC_RST  , _______  ,        _______  , _______  ,                   _______  , _______  , _______       , KBC_RST  , QK_BOOT
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 3);
    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

// oledkitはロゴ表示のためスレーブ側を180度回転させるが、
// 左右で同じ内容を表示する構成にしたので回転を揃える
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return rotation;
}

// レイヤー名(自分のレイヤー構成に合わせて書き換え)
static void render_layer_name(void) {
    oled_write_P(PSTR("Ly:"), false);
    switch (get_highest_layer(layer_state)) {
        case 0:  oled_write_P(PSTR("Base "), false); break;
        case 1:  oled_write_P(PSTR("Mouse"), false); break;
        case 2:  oled_write_P(PSTR("Num  "), false); break;
        case 3:  oled_write_P(PSTR("Sym  "), false); break;
        default: oled_write_P(PSTR("?    "), false); break;
    }
}

// hold中の修飾キーを反転表示(HRMの効きが目で見える)
static void render_mods(void) {
    uint8_t mods = get_mods() | get_oneshot_mods();
    oled_write_P(PSTR("S"), mods & MOD_MASK_SHIFT);
    oled_write_P(PSTR("C"), mods & MOD_MASK_CTRL);
    oled_write_P(PSTR("A"), mods & MOD_MASK_ALT);
    oled_write_P(PSTR("G"), mods & MOD_MASK_GUI);
}

// 両面共通: Luna(犬) + レイヤー名/修飾キー
// Shiftで吠える / Ctrlで忍び足 / WPMで歩く・走る / Spaceでジャンプ(右のみ)
void render_luna(void);
static void render_luna_screen(void) {
    render_luna();
    oled_set_cursor(7, 1);
    render_layer_name();
    oled_set_cursor(7, 2);
    oled_write_P(PSTR("Mods:"), false);
    render_mods();
}

void oledkit_render_info_user(void) { render_luna_screen(); }  // 右手(マスター)
void oledkit_render_logo_user(void) { render_luna_screen(); }  // 左手(スレーブ)
#endif


// ============================================================
// Swapper: 1キーAlt+Tab (Callum式)
// タップごとに次のウィンドウへ。他のキーを押すか
// レイヤーキーを離すとAltが解放されて確定。
// RemapではUSER00(0x7E40)をレイヤー内の好きな位置に割り当てる。
// ============================================================
enum custom_keycodes {
    SW_WIN = QK_USER_0,   // Remap: USER00 (0x7E40) Alt+Tab
    SW_TAB,               // Remap: USER01 (0x7E41) Ctrl+Tab
};

static bool sw_win_active = false;
static bool sw_tab_active = false;

// Callumのupdate_swapper: trigger自身ならTab連打、
// 他のキーイベントが来たら修飾キーを解放して確定
static bool update_swapper(bool *active, uint16_t modish, uint16_t tabish,
                           uint16_t trigger, uint16_t keycode,
                           keyrecord_t *record) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            if (!*active) {
                *active = true;
                register_code(modish);
            }
            register_code(tabish);
        } else {
            unregister_code(tabish);
        }
        return true;
    }
    if (*active) {
        unregister_code(modish);
        *active = false;
    }
    return false;
}

// ============================================================
// コンボ: 左クリック+右クリック同時押し → ホイールクリック
// (マウスレイヤーのJ=BTN1, K=BTN2を同時押しでBTN3)
// ============================================================
const uint16_t PROGMEM middle_click_combo[] = {KC_BTN1, KC_BTN2, COMBO_END};
combo_t key_combos[] = {
    COMBO(middle_click_combo, KC_BTN3),
};

// ============================================================
// AML: ボールを動かしたらクリックするまで留まる /
//      クリック後は短時間で解除
// ============================================================
#define AML_TIMEOUT_STAY 60000
#define AML_TIMEOUT_AFTER_CLICK 300

static bool aml_stay_mode = false;

// AMLを起動時に常時有効化
// (KeyballはAMLのON/OFFをEEPROMで管理し、デフォルトOFF。
//  この構成はAML前提なのでEEPROMの状態に関係なく強制ONにする)
void keyboard_post_init_user(void) {
    set_auto_mouse_enable(true);
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if ((mouse_report.x != 0 || mouse_report.y != 0) && !aml_stay_mode) {
        set_auto_mouse_timeout(AML_TIMEOUT_STAY);
        aml_stay_mode = true;
    }
    return mouse_report;
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    // Swapper (|=で両方の解放判定を必ず実行する)
    bool swapped = false;
    swapped |= update_swapper(&sw_win_active, KC_LALT, KC_TAB, SW_WIN, keycode, record);
    swapped |= update_swapper(&sw_tab_active, KC_LCTL, KC_TAB, SW_TAB, keycode, record);
    if (swapped) { return false; }

    // Space(単体キー/LT・MTのtap側)でLunaがジャンプ
    {
        uint16_t base = (IS_QK_LAYER_TAP(keycode) || IS_QK_MOD_TAP(keycode))
                            ? (keycode & 0xFF) : keycode;
        if (base == KC_SPC) {
            extern void luna_jump(void);
            extern void luna_land(void);
            if (record->event.pressed) { luna_jump(); } else { luna_land(); }
        }
    }

    // マウスボタンが押されたら「解除待ち」モードへ(短いタイムアウト)
    if (record->event.pressed &&
        keycode >= KC_MS_BTN1 && keycode <= KC_MS_BTN8) {
        set_auto_mouse_timeout(AML_TIMEOUT_AFTER_CLICK);
        aml_stay_mode = false;
    }
    return true;
}

// ボールの微振動での誤発動を防ぐ閾値
bool auto_mouse_activation(report_mouse_t mouse_report) {
    return abs(mouse_report.x) + abs(mouse_report.y) >= 3;
}

// スクロールモードキーはマウス操作扱い(押してもレイヤー維持)
bool is_mouse_record_user(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case SCRL_MO:
            return true;
    }
    return false;
}

// Layer-Tapの即hold(hold-preferred相当)は親指キーのみ。
// 文字キー上のLT(例: L長押しでマウスレイヤー)は流れ打ちで
// 誤発動するため除外し、時間判定+PERMISSIVE_HOLDに任せる
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t* record) {
    if (IS_QK_LAYER_TAP(keycode)) {
        uint16_t tap = keycode & 0xFF;
        if (tap >= KC_A && tap <= KC_Z) { return false; }
        return true;
    }
    return false;
}

