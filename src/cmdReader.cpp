#include <cassert>
#include <cstring>
#include "cmdReader.h"

using namespace std;

//----------------------------------------------------------------------
//    Extrenal funcitons
//----------------------------------------------------------------------
void mybeep();
char mygetc(istream&);
ParseChar getChar(istream&);


//----------------------------------------------------------------------
//    Member Function for class Parser
//----------------------------------------------------------------------
void
CmdParser::readCmd()
{
   if (_dofile.is_open())
   {
      readCmdInt(_dofile);
      _dofile.close();
   }
   else
      readCmdInt(cin);
}

void
CmdParser::readCmdInt(istream& istr)
{
    resetBufAndPrintPrompt();

    while (true)
    {
        ParseChar pch = getChar(istr);

        if (pch == INPUT_END_KEY) 
        	break;
        switch (pch)
        {

//        case LINE_BEGIN_KEY :
        case COMBO_HOME_KEY       :
            moveBufPtr(_readBuf);
            break;
//        case LINE_END_KEY   :
        case COMBO_END_KEY        :
            moveBufPtr(_readBufEnd);
            break;
        case BACK_SPACE_KEY :
            if(moveBufPtr(_readBufPtr-1))
               deleteChar();
            break;
        case COMBO_DELETE_KEY     :
            deleteChar();
            break;
        case NEWLINE_KEY    :
            addHistory();
            cout << char(NEWLINE_KEY);
            resetBufAndPrintPrompt();
            break;
        case COMBO_UP_KEY   :
            moveToHistory(_historyIdx - 1);
            break;
        case COMBO_DOWN_KEY :
            moveToHistory(_historyIdx + 1);
            break;
        case COMBO_RIGHT_KEY:
            moveBufPtr(_readBufPtr+1);
            break;
        case COMBO_LEFT_KEY :
            moveBufPtr(_readBufPtr-1);
            break;
        case COMBO_PG_UP_KEY      :
            moveToHistory(_historyIdx - PG_OFFSET);
            break;
        case COMBO_PG_DOWN_KEY    :
            moveToHistory(_historyIdx + PG_OFFSET);
            break;
        case TAB_KEY        : 
            insertChar(' ',TAB_POSITION-((_readBufPtr-_readBuf)%TAB_POSITION));
            break;
        case COMBO_INSERT_KEY     : // not yet supported; fall through to UNDEFINE
        case UNDEFINED_KEY:
            mybeep();
            break;
        default:  // printable character
            insertChar(char(pch));
            break;

        }

    }
     
}


bool
CmdParser::moveBufPtr(char* const ptr)
{
   if(ptr>=_readBuf && ptr<=_readBufEnd)
   {
      if(ptr<=_readBufPtr)
      {
         for(char* n=_readBufPtr;ptr<n;n--)
             cout<<'\b';
      }
      else
         {
             for(char* n=_readBufPtr;n<ptr;n++)
             cout<<*n;
         }

      _readBufPtr=ptr;
         return true;
   }
   else
   {
     mybeep();
     return false;
   }
}


bool
CmdParser::deleteChar()
{
    // TODO...
    if(_readBufPtr==_readBufEnd)
    {
        mybeep() ;
        return false;
    }
    else
    {
        for(char* n=_readBufPtr; n<=_readBufEnd; n++)
        {
            *n=*(n+1);
        }
        _readBufEnd--;

        for(char* n=_readBufPtr; n<_readBufEnd; n++)
        {
            cout<<*n;
        }
        cout<<' '<<'\b';
        for(char* n=_readBufPtr; n<_readBufEnd; n++)
        {
            cout<<'\b';
        }

    }
    return true;
}


void
CmdParser::insertChar(char ch, int repeat)
{
    // TODO...
    assert(repeat >= 1);
    for(int m=0 ; m<repeat; m++)
    {
        for(char* n=_readBufEnd; n>=_readBufPtr; n--)
        {
            *(n+1)=*n;
        }
        *(_readBufPtr)=ch;

        _readBufEnd++;
        cout <<ch;
        _readBufPtr++;

        for(char* n=_readBufPtr; n<_readBufEnd; n++)
        {
            cout<<*n;
        }

        for(char* n=_readBufPtr; n<_readBufEnd; n++)
        {
            cout<<'\b';
        }

    }


}


void
CmdParser::deleteLine()
{
    // TODO...
    for(char* n=_readBufPtr; n>_readBuf; n--)
        {
            cout<<'\b';
        }
    for(char* n=_readBuf; n<_readBufEnd; n++)
        {
            cout<<' ';
        }
    for(char* n=_readBufEnd; n>_readBuf; n--)
        {
            cout<<'\b';
        }

    _readBufPtr = _readBufEnd = _readBuf;
    *_readBufEnd = 0;

}


// This functions moves _historyIdx to index and display _history[index]
// on the screen.
//
// Need to consider:
// If moving up... (i.e. index < _historyIdx)
// 1. If already at top (i.e. _historyIdx == 0), beep and do nothing.
// 2. If at bottom, temporarily record _readBuf to history.
//    (Do not remove spaces, and set _tempCmdStored to "true")
// 3. If index < 0, let index = 0.
//
// If moving down... (i.e. index > _historyIdx)
// 1. If already at bottom, beep and do nothing
// 2. If index >= _history.size(), let index = _history.size() - 1.
//
// Assign _historyIdx to index at the end.
//
// [Note] index should not = _historyIdx
//
void
CmdParser::moveToHistory(int index)
{
    if(index <_historyIdx)
    {
        if (index<0)
            index=0;
        if(_historyIdx==0)
            mybeep();
        else
        {
            if (!_tempCmdStored && _historyIdx==_history.size())
               {
                    _history.push_back(_readBuf);
                    _tempCmdStored=true;
                }
            else if(_tempCmdStored && _historyIdx==_history.size()-1)
                _history.back()=_readBuf;

            deleteLine();
            _historyIdx=index;
            retrieveHistory();
        }
    }
    else
    {
        if ((!_tempCmdStored  &&_historyIdx==_history.size())||(_tempCmdStored  &&_historyIdx==_history.size()-1))
           mybeep();
        else
        {
            if (index>_history.size())
                index = _history.size() - 1;

            deleteLine();
            _historyIdx=index;
            retrieveHistory();
        }

    }


}


// This function adds the string in _readBuf to the _history.
// The size of _history may or may not change. Depending on whether
// there is a temp history string.
//
// 1. Remove ' ' at the beginning and end of _readBuf
// 2. If not a null string, add string to _history.
//    Be sure you are adding to the right entry of _history.
// 3. If it is a null string, don't add anything to _history.
// 4. Make sure to clean up "temp recorded string" (added earlier by up/pgUp,
//    and reset _tempCmdStored to false
// 5. Reset _historyIdx to _history.size() // for future insertion
//
void
CmdParser::addHistory()
{
    int first=0;
    int last =_readBufEnd-_readBuf;
    while(*(_readBuf+first)==' ')
        first++;
    while(*(_readBuf+last-1)==' ')
        last--;
    for(int n=0;n<last-first;n++)
        _readBuf[n]=_readBuf[n+first];
        _readBuf[last]='\0';


    if( *_readBuf!='\0')
    {
        if(!_tempCmdStored)
        _history.push_back(_readBuf);
        else
        {
            _history.back()=_readBuf;
            _tempCmdStored=false;
        }

    }
    else if(_tempCmdStored)
        {
            _history.erase(_history.end()-1);
            _tempCmdStored=false;
        }
    _historyIdx=_history.size();

}


// 1. Replace current line with _history[_historyIdx] on the screen
// 2. Set _readBufPtr and _readBufEnd to end of line
//
// [Note] Do not change _history.size().
//
void
CmdParser::retrieveHistory()
{
    deleteLine();
    strcpy(_readBuf, _history[_historyIdx].c_str());
    cout << _readBuf;
    _readBufPtr = _readBufEnd = _readBuf + _history[_historyIdx].size();
}