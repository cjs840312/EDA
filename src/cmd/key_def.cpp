#include <iostream>
#include <termios.h>
#include "key_def.h"
using namespace std;


struct termios stored_settings;

void reset_keypress(void)
{
  tcsetattr(0,TCSANOW,&stored_settings);
}

void set_keypress(void)
{
   struct termios new_settings;
   tcgetattr(0,&stored_settings);
   new_settings = stored_settings;
   new_settings.c_lflag &= (~ICANON);
   new_settings.c_lflag &= (~ECHO);
   new_settings.c_cc[VTIME] = 0;
   tcgetattr(0,&stored_settings);
   new_settings.c_cc[VMIN] = 1;
   tcsetattr(0,TCSANOW,&new_settings);
}

char mygetc(istream& istr)
{
   char ch;
   set_keypress();
   istr.unsetf(ios_base::skipws);
   istr >> ch;
   istr.setf(ios_base::skipws);
   reset_keypress();
   return ch;
}

void mybeep(){ cout << char(BEEP_CHAR); }

ParseChar getChar(istream& istr)
{
   char ch = mygetc(istr);

   if (istr.eof())
      return INPUT_END_KEY;
   
   switch (ch) 
   {
//      case LINE_BEGIN_KEY:  // Ctrl-a
//      case LINE_END_KEY:    // Ctrl-e
//      case INPUT_END_KEY:   // Ctrl-d
      case TAB_KEY:         // Tab   or Ctrl-i
      case NEWLINE_KEY:     // Enter or ctrl-m
      case BACK_SPACE_KEY:  // Backspace
         return ParseChar(ch);

      case ESC_KEY: 
      {
         char combo = mygetc(istr);
         if (combo == char(COMBO_KEY_INT1)) 
         {
            char key = mygetc(istr);
            
            if ((key >= char(MOD_KEY_BEGIN)) && (key <= char(MOD_KEY_END)))
            {
               if (mygetc(istr) == COMBO_KEY_DUMMY)
                  return ParseChar( int(key) + COMBO_KEY_FLAG );
            }
            else if (key >= char(ARROW_KEY_BEGIN) && key <= char(ARROW_KEY_END))
               return ParseChar( int(key) + COMBO_KEY_FLAG );
         }
         else if(combo == char(COMBO_KEY_INT2))
         {
            char key = mygetc(istr);
            if ( key == char(COMBO_HOME_KEY) || key==char(COMBO_END_KEY))
               return ParseChar( int(key) + COMBO_KEY_FLAG );
         }
         
         return ParseChar(UNDEFINED_KEY);
      }
      // For the remaining printable or undefined keys
      default:
         if (isprint(ch))
            return ParseChar(ch);
         else
            return ParseChar(UNDEFINED_KEY);
   }
}
