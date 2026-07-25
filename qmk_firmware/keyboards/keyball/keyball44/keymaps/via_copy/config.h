/*
This is the c configuration file for the keymap

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

#pragma once

// ============================================================
// もともとのKeyball設定(そのまま維持)
// ============================================================
#define TAP_CODE_DELAY 5                    // キー送信の押下→解放間に5ms(入力取りこぼし防止)
#define POINTING_DEVICE_AUTO_MOUSE_ENABLE   // ボールを動かすと自動でマウスレイヤーへ
#define AUTO_MOUSE_DEFAULT_LAYER 1          // その行き先はレイヤー1
#define DYNAMIC_KEYMAP_LAYER_COUNT 8
// ============================================================
// urob式HRMの判定設定
// ============================================================
#define TAPPING_TERM 280      // urob: tapping-term-ms = 280(長め。位置ルールに判定を委ねる)
#define PERMISSIVE_HOLD       // urob: flavor = "balanced"
#define QUICK_TAP_TERM 175    // urob: quick-tap-ms = 175(タップ直後の再押下はキーリピート)
#define ACHORDION_STREAK      // urob: require-prior-idle 相当(連続タイピング中はtap優先)
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY

// OLED: 左手(スレーブ)側でレイヤー/修飾キーを表示するための状態同期
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_MODS_ENABLE
// 左手(スレーブ)側のBongo Catが両手の入力に反応するための同期
#define SPLIT_ACTIVITY_ENABLE