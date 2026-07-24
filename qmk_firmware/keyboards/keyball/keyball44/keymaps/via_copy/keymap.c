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

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif

#ifdef COMBO_ENABLE
enum combos {
    JK_LCLICK,   // J + K → 左クリック
    KL_RCLICK,   // K + L → 右クリック
    JL_MCLICK,   // J + L → ホイールクリック
    QW_TAB,      // Q + W → Tab
    COMBO_LENGTH
};
 
uint16_t COMBO_LEN = COMBO_LENGTH;
 
const uint16_t PROGMEM combo_jk[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM combo_kl[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM combo_jl[] = {KC_J, KC_L, COMBO_END};
const uint16_t PROGMEM combo_qw[] = {KC_Q, KC_W, COMBO_END};
 
combo_t key_combos[] = {
    [JK_LCLICK] = COMBO(combo_jk, KC_BTN1),
    [KL_RCLICK] = COMBO(combo_kl, KC_BTN2),
    [JL_MCLICK] = COMBO(combo_jl, KC_BTN3),
    [QW_TAB]    = COMBO(combo_qw, KC_TAB),
};
#endif  // COMBO_ENABLE

// ============================================================
// urob式HRM (Achordion) — ここから末尾まで追記
// ============================================================
#include "features/achordion.h"

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (!process_achordion(keycode, record)) { return false; }
    return true;
}

void matrix_scan_user(void) {
    achordion_task();
}

// ------------------------------------------------------------
// hold-trigger-key-positions + hold-trigger-on-release 相当
// 基本は「反対の手のキーとの組み合わせのみhold」、例外が2つ
// ------------------------------------------------------------
bool achordion_chord(uint16_t tap_hold_keycode, keyrecord_t* tap_hold_record,
                     uint16_t other_keycode, keyrecord_t* other_record) {
    uint8_t row = other_record->event.key.row;

    // 例外1: 相手が親指キーなら同じ手でもholdを許可
    // Keyball44: 左手 row 0-3 / 右手 row 4-7、親指列は row 3 と 7
    if (row == 3 || row == 7) { return true; }

    // 例外2: 相手もMod-Tap(HRM)なら同じ手でもholdを許可
    // → 片手でCtrl+Shift等のモッド重ねが可能に
    if (IS_QK_MOD_TAP(other_keycode)) { return true; }

    // 原則: 反対の手のみhold
    return achordion_opposite_hands(tap_hold_record, other_record);
}

// ------------------------------------------------------------
// require-prior-idle-ms 相当(タイピングの流れの中ではtap優先)
// ------------------------------------------------------------
uint16_t achordion_streak_chord_timeout(uint16_t tap_hold_keycode,
                                        uint16_t next_keycode) {
    // レイヤータップ(親指)は対象外:即レイヤーが効くように
    if (IS_QK_LAYER_TAP(tap_hold_keycode)) { return 0; }

    // Shiftは文中でも多用するので短め、他の修飾キーは150ms
    uint8_t mods = mod_config(QK_MOD_TAP_GET_MODS(tap_hold_keycode));
    if (mods & (MOD_LSFT | MOD_RSFT)) { return 100; }
    return 150;
}

// ------------------------------------------------------------
// hold-while-undecided 相当:Shift/Ctrlは判定確定前から効かせる
// (Ctrl+クリック等のマウス併用向け。不要ならこの関数ごと削除可)
// ------------------------------------------------------------
bool achordion_eager_mod(uint8_t mod) {
    switch (mod) {
        case MOD_LSFT: case MOD_RSFT:
        case MOD_LCTL: case MOD_RCTL:
            return true;
        default:
            return false;
    }
}
// 親指のLayer-Tapは「他のキーが押されたら即hold」= ZMKのhold-preferred相当
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t* record) {
    if (IS_QK_LAYER_TAP(keycode)) { return true; }
    return false;  // HRM(Mod-Tap)はbalancedのまま
}