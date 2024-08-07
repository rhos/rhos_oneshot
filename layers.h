#pragma once

#define LAYER_LIST \
LAYER_X(BASE,   "< LAT >") \
LAYER_X(EXTRA,  "< CYR >") \
LAYER_X(GAME,   "< GMG >") \
LAYER_X(NAVB,   "< NAV >") \
LAYER_X(NUMB,   "< NUM >") \
LAYER_X(FUNB,   "< FUN >") \
LAYER_X(LFTB,   "< LFT >") \
LAYER_X(NAV,    "< NAV >") \
LAYER_X(NUM,    "< NUM >") \
LAYER_X(FUN,    "< FUN >") \
LAYER_X(LFT,    "< LFT >") \
LAYER_X(LCK,    "< LCK >")

#define OSMOD_LIST \
OSMOD_X(LSFT) \
OSMOD_X(LCTL) \
OSMOD_X(LALT) \
OSMOD_X(LGUI) \
OSMOD_X(ALGR)

#define OSLAYER_LIST \
OSLAYER_X(NAV, NAV) \
OSLAYER_X(NUM, NUM) \
OSLAYER_X(LFT, LFT) \
OSLAYER_X(LCK, LCK)

enum keycodes {
    OS_CNCL = SAFE_RANGE,
    OS_GRP,
    SW_ALT,
    SW_CTL,

#define OSMOD_X(OSMOD) OS_##OSMOD,
OSMOD_LIST
#undef OSMOD_X

#define OSLAYER_X(OSKEY, OSLAYER) OSL_##OSKEY,
OSLAYER_LIST
#undef OSLAYER_X
};

#define U_UNDO  C(KC_Z)
#define U_CUT   C(KC_X)
#define U_COPY  C(KC_C)
#define U_PSTE  C(KC_V)

#define D_EXTRA DF(U_EXTRA)
#define D_BASE  DF(U_BASE)
#define D_GAME  DF(U_GAME)
#define D_NAVB  DF(U_NAVB)
#define D_NUMB  DF(U_NUMB)
#define D_FUNB  DF(U_FUNB)
#define D_LFTB  DF(U_LFTB)

#define U_LNCH  G(A(KC_L))
#define U_TERM  G(A(KC_T))
#define U_SWTC  G(A(KC_S))
#define U_FIND  G(A(KC_F))
#define U_CLIP  G(A(KC_C))

#define LAYER_BASE \
  /*┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐         ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐*/\
      OSL_LFT , KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    ,           KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    , KC_BSLS ,  \
  /*├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤         ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤*/\
      OSL_NUM , KC_A    , KC_S    , KC_D    , KC_F    , KC_G    ,           KC_H    , KC_J    , KC_K    , KC_L    , KC_SCLN , KC_QUOT ,  \
  /*├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤         ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤*/\
      OS_ALGR , KC_Z    , KC_X    , KC_C    , KC_V    , KC_B    ,           KC_N    , KC_M    , KC_COMM , KC_DOT  , KC_SLSH , D_EXTRA ,  \
  /*└─────────┴─────────┴─────────┴─┬───────┴─┬───────┴─┬───────┴─┐     ┌─┴───────┬─┴───────┬─┴───────┬─┴─────────┴─────────┴─────────┘*/\
                                      KC_ESC  , OSL_NAV , KC_SPC  ,       OS_LSFT , OSL_NUM , OS_CNCL                                    \
  /*                                └─────────┴─────────┴─────────┘     └─────────┴─────────┴─────────┘                                */

#define LAYER_EXTRA \
  /*┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐         ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐*/\
      OSL_LFT , KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    ,           KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    , KC_LBRC ,  \
  /*├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤         ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤*/\
      OSL_NUM , KC_A    , KC_S    , KC_D    , KC_F    , KC_G    ,           KC_H    , KC_J    , KC_K    , KC_L    , KC_SCLN , KC_QUOT ,  \
  /*├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤         ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤*/\
      OS_ALGR , KC_Z    , KC_X    , KC_C    , KC_V    , KC_B    ,           KC_N    , KC_M    , KC_COMM , KC_DOT  , KC_SLSH , D_BASE  ,  \
  /*└─────────┴─────────┴─────────┴─┬───────┴─┬───────┴─┬───────┴─┐     ┌─┴───────┬─┴───────┬─┴───────┬─┴─────────┴─────────┴─────────┘*/\
                                      KC_ESC  , OSL_NAV , KC_SPC  ,       OS_LSFT , OSL_NUM , OS_CNCL                                    \
  /*                                └─────────┴─────────┴─────────┘     └─────────┴─────────┴─────────┘                                */

#define LAYER_GAME \
  /*┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐         ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐*/\
      OSL_LFT , KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    ,           KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    , KC_LBRC ,  \
  /*├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤         ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤*/\
      OSL_NUM , KC_A    , KC_S    , KC_D    , KC_F    , KC_G    ,           KC_H    , KC_J    , KC_K    , KC_L    , KC_SCLN , KC_QUOT ,  \
  /*├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤         ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤*/\
      KC_LSFT , KC_Z    , KC_X    , KC_C    , KC_V    , KC_B    ,           KC_N    , KC_M    , KC_COMM , KC_DOT  , KC_SLSH , KC_NO   ,  \
  /*└─────────┴─────────┴─────────┴─┬───────┴─┬───────┴─┬───────┴─┐     ┌─┴───────┬─┴───────┬─┴───────┬─┴─────────┴─────────┴─────────┘*/\
                                      KC_ESC  , OSL_NAV , KC_SPC  ,       KC_NO   , KC_NO   , KC_NO                                      \
  /*                                └─────────┴─────────┴─────────┘     └─────────┴─────────┴─────────┘                                */

#define LAYER_NAV \
  /*┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐         ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐*/\
      OSL_LFT , U_SWTC  , SW_ALT  , SW_CTL  , U_TERM  , U_CLIP  ,           KC_CAPS , KC_APP  , KC_ENT  , KC_TAB  , KC_DEL  , KC_VOLU ,  \
  /*├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤         ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤*/\
      OSL_NUM , OS_LALT , OS_LSFT , OS_LCTL , OS_LGUI , U_LNCH  ,           KC_LEFT , KC_DOWN , KC_UP   , KC_RGHT , KC_BSPC , KC_VOLD ,  \
  /*├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤         ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤*/\
      OSL_LCK , U_UNDO  , U_CUT   , U_COPY  , U_PSTE  , U_FIND  ,           KC_HOME , KC_PGDN , KC_PGUP , KC_END  , KC_INS  , KC_MUTE ,  \
  /*└─────────┴─────────┴─────────┴─┬───────┴─┬───────┴─┬───────┴─┐     ┌─┴───────┬─┴───────┬─┴───────┬─┴─────────┴─────────┴─────────┘*/\
                                      KC_ESC  , OSL_NAV , KC_SPC  ,       OS_LSFT , OSL_NUM , OS_CNCL                                    \
  /*                                └─────────┴─────────┴─────────┘     └─────────┴─────────┴─────────┘                                */
#define LAYER_NAVB \
    LAYER_NAV

#define LAYER_NUM \
  /*┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐         ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐*/\
      OSL_LFT , KC_MINS , KC_7    , KC_8    , KC_9    , KC_GRV  ,           KC_LCBR , KC_RCBR , KC_LPRN , KC_RPRN , KC_UNDS , KC_BSLS ,  \
  /*├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤         ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤*/\
      OSL_NUM , KC_0    , KC_4    , KC_5    , KC_6    , KC_EQL  ,           KC_EXLM , OS_LGUI , OS_LCTL , OS_LSFT , OS_LALT , KC_QUOT ,  \
  /*├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤         ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤*/\
      OS_ALGR , KC_DOT  , KC_1    , KC_2    , KC_3    , KC_SLSH ,           KC_LBRC , KC_RBRC , KC_LT   , KC_GT   , KC_QUES , KC_SCLN ,  \
  /*└─────────┴─────────┴─────────┴─┬───────┴─┬───────┴─┬───────┴─┐     ┌─┴───────┬─┴───────┬─┴───────┬─┴─────────┴─────────┴─────────┘*/\
                                      KC_ESC  , OSL_NAV , KC_SPC  ,       OS_LSFT , OSL_NUM , OS_CNCL                                    \
  /*                                └─────────┴─────────┴─────────┘     └─────────┴─────────┴─────────┘                                */
#define LAYER_NUMB \
    LAYER_NUM

#define LAYER_FUN \
  /*┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐         ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐*/\
      OSL_LFT , KC_F12  , KC_F7   , KC_F8   , KC_F9   , KC_NO   ,           KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO   ,  \
  /*├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤         ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤*/\
      OSL_NUM , KC_F11  , KC_F4   , KC_F5   , KC_F6   , KC_NO   ,           KC_NO   , OS_LGUI , OS_LCTL , OS_LSFT , OS_LALT , KC_NO   ,  \
  /*├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤         ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤*/\
      KC_NO   , KC_F10  , KC_F1   , KC_F2   , KC_F3   , KC_NO   ,           KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO   ,  \
  /*└─────────┴─────────┴─────────┴─┬───────┴─┬───────┴─┬───────┴─┐     ┌─┴───────┬─┴───────┬─┴───────┬─┴─────────┴─────────┴─────────┘*/\
                                      KC_ESC  , OSL_NAV , KC_SPC  ,       OS_LSFT , OSL_NUM , OS_CNCL                                    \
  /*                                └─────────┴─────────┴─────────┘     └─────────┴─────────┴─────────┘                                */
#define LAYER_FUNB \
    LAYER_FUN

#define LAYER_LFT \
  /*┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐         ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐*/\
      OSL_LFT , KC_DEL  , KC_TAB  , KC_UP   , KC_ENT  , KC_PGUP ,           KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO   ,  \
  /*├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤         ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤*/\
      OSL_NUM , KC_BSPC , KC_LEFT , KC_DOWN , KC_RGHT , KC_PGDN ,           KC_MS_L , KC_MS_D , KC_MS_U , KC_MS_R , KC_BTN4 , KC_NO   ,  \
  /*├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤         ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤*/\
      KC_NO   , KC_NO   , KC_HOME , KC_NO   , KC_END  , KC_PSCR ,           KC_WH_L , KC_WH_D , KC_WH_U , KC_WH_R , KC_BTN5 , KC_NO   ,  \
  /*└─────────┴─────────┴─────────┴─┬───────┴─┬───────┴─┬───────┴─┐     ┌─┴───────┬─┴───────┬─┴───────┬─┴─────────┴─────────┴─────────┘*/\
                                      KC_ESC  , OSL_NAV , KC_SPC  ,       KC_BTN2 , KC_BTN1 , KC_BTN3                                    \
  /*                                └─────────┴─────────┴─────────┘     └─────────┴─────────┴─────────┘                                */
#define LAYER_LFTB \
    LAYER_LFT

#define LAYER_LCK \
  /*┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐         ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐*/\
      D_LFTB  , KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO   ,           KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO   , QK_RBT  ,  \
  /*├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤         ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤*/\
      D_NUMB  , D_NAVB  , D_GAME  , D_BASE  , D_FUNB  , KC_NO   ,           KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO   , QK_BOOT ,  \
  /*├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤         ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤*/\
      OSL_LCK , KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO   ,           KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO   , OS_GRP  ,  \
  /*└─────────┴─────────┴─────────┴─┬───────┴─┬───────┴─┬───────┴─┐     ┌─┴───────┬─┴───────┬─┴───────┬─┴─────────┴─────────┴─────────┘*/\
                                      KC_NO   , OSL_NAV , KC_NO   ,       KC_NO   , KC_NO   , KC_NO                                      \
  /*                                └─────────┴─────────┴─────────┘     └─────────┴─────────┴─────────┘                                */
