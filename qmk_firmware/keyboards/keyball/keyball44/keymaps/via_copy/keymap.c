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
 
// hold中の修飾キーを反転表示(HRMの効き具合が目で見える)
static void render_mods(void) {
    uint8_t mods = get_mods();
    oled_write_P(PSTR("S"), mods & MOD_MASK_SHIFT);
    oled_write_P(PSTR("C"), mods & MOD_MASK_CTRL);
    oled_write_P(PSTR("A"), mods & MOD_MASK_ALT);
    oled_write_P(PSTR("G"), mods & MOD_MASK_GUI);
}
 
// 右手(マスター)側: キー情報/ボール情報/レイヤー情報 + レイヤー名/修飾キー
void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
    render_layer_name();
    oled_write_P(PSTR(" "), false);
    render_mods();
}
 
// 左手(スレーブ)側: Bongo Cat(両手のタイピングに反応)
void render_bongocat(void);
void oledkit_render_logo_user(void) {
    render_bongocat();
}
#endif

// ============================================================
// urob式HRM (Achordion)
// ============================================================
#include "features/achordion.h"
 
// ============================================================
// AML: ボールを動かしたらクリックするまで留まる /
//      クリック後は短時間で解除
// ============================================================
#define AML_TIMEOUT_STAY 60000        // ボール操作後の滞在時間(実質「クリック待ち」)
#define AML_TIMEOUT_AFTER_CLICK 300   // クリック後にレイヤーを解除するまでの時間
 
static bool aml_stay_mode = false;
 
// ボールが動いたら「クリック待ち」モードへ(長いタイムアウト)
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if ((mouse_report.x != 0 || mouse_report.y != 0) && !aml_stay_mode) {
        set_auto_mouse_timeout(AML_TIMEOUT_STAY);
        aml_stay_mode = true;
    }
    return mouse_report;
}
 
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (!process_achordion(keycode, record)) { return false; }
 
    // マウスボタンが押されたら「解除待ち」モードへ(短いタイムアウト)
    if (record->event.pressed &&
        keycode >= KC_MS_BTN1 && keycode <= KC_MS_BTN8) {
        set_auto_mouse_timeout(AML_TIMEOUT_AFTER_CLICK);
        aml_stay_mode = false;
    }
    return true;
}
 
void matrix_scan_user(void) {
    achordion_task();
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
 
// 親指のLayer-Tapは即hold(hold-preferred相当)
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t* record) {
    if (IS_QK_LAYER_TAP(keycode)) { return true; }
    return false;
}
 
// urob式: 反対の手ルール+親指例外+同手モッド重ね
bool achordion_chord(uint16_t tap_hold_keycode, keyrecord_t* tap_hold_record,
                     uint16_t other_keycode, keyrecord_t* other_record) {
    uint8_t row = other_record->event.key.row;
    if (row == 3 || row == 7) { return true; }
    if (IS_QK_MOD_TAP(other_keycode)) { return true; }
    return achordion_opposite_hands(tap_hold_record, other_record);
}
 
// urob式: 連続タイピング中はtap優先
uint16_t achordion_streak_chord_timeout(uint16_t tap_hold_keycode,
                                        uint16_t next_keycode) {
    if (IS_QK_LAYER_TAP(tap_hold_keycode)) { return 0; }
    uint8_t mods = mod_config(QK_MOD_TAP_GET_MODS(tap_hold_keycode));
    if (mods & (MOD_LSFT | MOD_RSFT)) { return 100; }
    return 150;
}
 
// Shift/Ctrlは判定確定前から効かせる(Ctrl+クリック対応)
bool achordion_eager_mod(uint8_t mod) {
    switch (mod) {
        case MOD_LSFT: case MOD_RSFT:
        case MOD_LCTL: case MOD_RCTL:
            return true;
        default:
            return false;
    }
}
 