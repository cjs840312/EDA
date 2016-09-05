#ifndef KEY_DEF_H
#define KEY_DEF_H

//#include <climits>

enum ParseChar
{

//   LINE_BEGIN_KEY   = 1,          // Ctrl-a
//   LINE_END_KEY     = 5,          // Ctrl-e
   INPUT_END_KEY    = 4,          // Ctrl-d

   TAB_KEY          = 9 ,  // Ctrl-i or Tab   = int('\t')
   NEWLINE_KEY      = 10,  // Ctrl-m or Enter = int('\n')
   ESC_KEY          = 27,
   BACK_SPACE_KEY   = 127,

 // 27 -> 91 -> {UP=65, DOWN=66, RIGHT=67, LEFT=68}
 // 27 -> 91 -> { INSERT=50, DELETE=51, PgUp=53, PgDown=54 } -> 126
 // 27 -> 79 -> { HOME=72, END=70 }   
   COMBO_KEY_FLAG     = 1 << 8,

   COMBO_KEY_INT1     = 91,
   COMBO_KEY_INT2     = 79,

   COMBO_INSERT_KEY   = 50 + COMBO_KEY_FLAG,
   COMBO_DELETE_KEY   = 51 + COMBO_KEY_FLAG,
   COMBO_PG_UP_KEY    = 53 + COMBO_KEY_FLAG,
   COMBO_PG_DOWN_KEY  = 54 + COMBO_KEY_FLAG,

   COMBO_UP_KEY       = 65 + COMBO_KEY_FLAG,
   COMBO_DOWN_KEY     = 66 + COMBO_KEY_FLAG,
   COMBO_RIGHT_KEY    = 67 + COMBO_KEY_FLAG,
   COMBO_LEFT_KEY     = 68 + COMBO_KEY_FLAG,

   COMBO_END_KEY      = 70 + COMBO_KEY_FLAG,
   COMBO_HOME_KEY     = 72 + COMBO_KEY_FLAG,
   

   COMBO_KEY_DUMMY    = 126,

   ARROW_KEY_BEGIN  = COMBO_UP_KEY,
   ARROW_KEY_END    = COMBO_LEFT_KEY,
   MOD_KEY_BEGIN    = COMBO_INSERT_KEY,
   MOD_KEY_END      = COMBO_PG_DOWN_KEY,

   UNDEFINED_KEY  = ( 1<<30 ),
//   UNDEFINED_KEY  = INT_MAX,

   // For output only, you don't need to modify this part
   BEEP_CHAR        = 7,
//   BACK_SPACE_CHAR  = 8,

   // dummy end
//   PARSE_CHAR_END
};
#endif
