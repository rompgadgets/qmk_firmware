 /* Copyright 2020 Naoki Katahira
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 2 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  */

#include QMK_KEYBOARD_H
#include <stdio.h>

//extern uint8_t is_master;

enum layer_number {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
};

char wpm_str[15];

uint8_t curr_left = 0;
uint8_t curr_right = 0;

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  ~   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |LOWER | LGUI | Alt  | /Space  /       \Enter \  |BackSP| RGUI |RAISE |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `-------------------''-------'           '------''--------------------'
 */

 [_QWERTY] = LAYOUT(
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
  KC_LCTRL, KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC,  KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,
                      LOWER, KC_LGUI,  KC_LALT, KC_SPC,   KC_ENT,   KC_BSPC,  KC_RGUI, RAISE
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   !  |   @  |   #  |   $  |   %  |                    |   ^  |   &  |   *  |   (  |   )  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   1  |   2  |   3  |   4  |   5  |-------.    ,-------|   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|   |  |   `  |   +  |   {  |   }  |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |LOWER | LGUI | Alt  | /Space  /       \Enter \  |BackSP| RGUI |RAISE |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `-------------------''-------'           '------''--------------------'
 */
[_LOWER] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______,_______, _______, _______,
  _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
  _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, KC_PIPE, KC_GRAVE, KC_PLUS, KC_LCBR, KC_RCBR, _______,
                             _______, _______, _______, _______, _______,  _______, _______, _______
),
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      | Left | Down |  Up  |Right |      |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|   +  |   =  |   [  |   ]  |   \  |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |LOWER | LGUI | Alt  | /Space  /       \Enter \  |BackSP| RGUI |RAISE |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `-------------------''-------'           '------''--------------------'
 */

[_RAISE] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, _______,
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                       KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  _______, _______, _______, _______, _______, _______,                     XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX,
  _______, _______, _______, _______, _______, _______,   _______, _______, KC_PLUS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, _______,
                             _______, _______, _______,  _______, _______,  _______, _______, _______
),

/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |LOWER | LGUI | Alt  | /Space  /       \Enter \  |BackSP| RGUI |RAISE |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_ADJUST] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                             _______, _______, _______, _______, _______,  _______, _______, _______
  )
};

#ifdef OLED_DRIVER_ENABLE

void matrix_change_user(bool local, bool remote) {
    if(local)
        curr_right++;

    if(remote)
        curr_left++;
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _RAISE, _LOWER, _ADJUST);
    return state;
}

static void render_logo(void) {
/*    static const char PROGMEM logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };*/

    static const char PROGMEM logo[] = {
// 'hype2', 128x32px
0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x7f, 0xff, 
0xff, 0xff, 0x7f, 0x1f, 0x1f, 0xff, 0xff, 0xff, 0x7f, 0x7f, 0x7f, 0x3f, 0x3f, 0x3f, 0xbf, 0xbf, 
0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0x3f, 0x3f, 0xff, 0xff, 0x7f, 0x7f, 0x3f, 0xbf, 
0xbf, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0xff, 0x0f, 0x0f, 0x0f, 0x0f, 0x8f, 0x8f, 
0x8f, 0x8f, 0x8f, 0x0f, 0x0f, 0x0f, 0x0f, 0xff, 0xff, 0x0f, 0x0f, 0x0f, 0x0f, 0x8f, 0x8f, 0x8f, 
0x8f, 0x8f, 0x8f, 0x8f, 0x0f, 0x0f, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x07, 0x07, 
0x07, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 
0xfe, 0xfe, 0xfe, 0xff, 0x00, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0x7f, 0x00, 0xbf, 0xbf, 
0x9f, 0xdf, 0xc7, 0xf3, 0xfb, 0xf9, 0xfc, 0x86, 0xb6, 0xb3, 0x39, 0x3c, 0xbe, 0xbf, 0x9f, 0xdf, 
0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x0f, 0x0f, 0x0f, 
0x0f, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x7f, 
0x7f, 0x7f, 0x7f, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x7f, 0x7f, 
0x7f, 0x7f, 0x7f, 0x7f, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xef, 0xcf, 
0x9f, 0x3f, 0x7f, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0x7b, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0x7f, 0x3f, 0x8f, 0xef, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 
0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xf8, 
0xf8, 0xf8, 0xf8, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xe0, 0xc0, 
0x80, 0x04, 0x0c, 0x1c, 0x3c, 0x7c, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xfc, 0xf8, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfc, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 
0xfc, 0xfe, 0xff, 0xff, 0xff, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 
0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xff, 0xe0, 0xe0, 0xe0, 0xe0, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xe0, 0xe0, 0xe0, 0xe0, 0xff, 0xff, 0xe0, 0xe0, 0xe0, 0xe0, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xfe, 0xfc, 0xf8, 0xf0, 0xe0, 0xe1, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
   };

   oled_write_raw_P(logo, sizeof(logo));
//oled_write_P(logo, false);
}

char keylog_str[24] = {};
char keylogs_str[21] = {};
int keylogs_str_idx = 0;

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);

  // update keylogs
  if (keylogs_str_idx == sizeof(keylogs_str) - 1) {
    keylogs_str_idx = 0;
    for (int i = 0; i < sizeof(keylogs_str) - 1; i++) {
      keylogs_str[i] = ' ';
    }
  }

  keylogs_str[keylogs_str_idx] = name;
  keylogs_str_idx++;
}

const char *read_keylog(void) {
  return keylog_str;
}

const char *read_keylogs(void) {
  return keylogs_str;
}
//new

void oled_task_user(void) {
  if (is_keyboard_master()) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    //oled_write_ln_P(PSTR("Left: "), false);

    switch (get_highest_layer(layer_state)) {
    case _QWERTY:
        oled_write_ln_P(PSTR("Default"), false);
        break;
    case _RAISE:
        oled_write_ln_P(PSTR("Raise"), false);
        break;
    case _LOWER:
        oled_write_ln_P(PSTR("Lower"), false);
        break;
    case _ADJUST:
        oled_write_ln_P(PSTR("Adjust"), false);
        break;
    default:
        oled_write_ln_P(PSTR("Undefined"), false);
    }

    //oled_write_ln(read_keylog(), false);
    //oled_write_ln(read_keylogs(), false);

#ifdef WPM_ENABLE
    // Write WPM
    sprintf(wpm_str, "WPM: %03d", get_current_wpm()); 
    //sprintf(wpm_str, "WPM: %03d L: %03d R: %03d", get_current_wpm(), get_current_left(), get_current_right());
    //sprintf(wpm_str, "L: %03d R: %03d", get_current_left(), get_current_right());
    oled_write_ln(wpm_str, false);
    
    // first atempt on page 4 of the OLED
    /*oled_set_cursor(get_current_left()%20, 1);
    oled_write_char(255, true);
    oled_advance_page(true);
    oled_write_ln_P(PSTR("Right: "), false);
    oled_set_cursor(get_current_right()%20, 3);
    oled_write_char(255, true);
    oled_advance_page(true);
    */
    uint8_t i = 0;
    //uint8_t i,j = 0;
    //uint8_t pagelimit = 2;
    uint8_t leftbar = curr_left % OLED_DISPLAY_WIDTH; 
    uint8_t rightbar = curr_right % OLED_DISPLAY_WIDTH; 

    //TODO: do this more efficiently by just removinmg the "cool down amount"
    if(leftbar == 0)
    {
        for(i = 0; i < OLED_DISPLAY_WIDTH; i++)
        {
            oled_write_raw_byte(0, i + (2 * OLED_DISPLAY_WIDTH));
        } 
    }

    if(rightbar == 0)
    {
        for(i = 0; i < OLED_DISPLAY_WIDTH; i++)
        {
            oled_write_raw_byte(0, i + (3 * OLED_DISPLAY_WIDTH));
        }
    }

    for(i = 0; i < leftbar; i++)
    {
        oled_write_raw_byte(0x3f, i + (2 * OLED_DISPLAY_WIDTH));
    } 

    for(i = 0; i < rightbar; i++)
    {
        oled_write_raw_byte(252, i + (3 * OLED_DISPLAY_WIDTH));
    }
#endif
  } else {
      render_logo();
  }
}
#endif // OLED_DRIVER_ENABLE

//Attempt to fix the OLED behavior on laptop sleep
void suspend_power_down_user(void) {
    oled_off();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  /*if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
     set_keylog(keycode, record);
#endif
    // set_timelog();
  }*/
  return true;
}
