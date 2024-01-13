/*
The MIT License (MIT)

Copyright (c) 2018 NailAlex aka NailMan

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/*  * * * * * * * * * * * * * * * * * * * * * * * * * * *
 Code by NailAlex aka NailMan
 http://nailalex.dyndns.org
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */ 

/*  * * * * * * * * * * * * * * * * * * * * * * * * * * *
 Version: 1.1
+ Initial Event Class and check time func with ZeroPoint correct
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */ 


#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "URLArgsParser.h" 


////////////////////////////////////////

URLArgsParser::URLArgsParser(void)
{
 _currentArgCount = 0;
 _currentArgs = nullptr;
 _postArgsLen = 0;
 _postArgs=nullptr;
 _currentArgCount = 0;
}

////////////////////////////////////////

String URLArgsParser::arg_value(int i)
{
  if (i < _currentArgCount)
    return _currentArgs[i].value;
  return String();
}

////////////////////////////////////////

String URLArgsParser::arg_key(int i)
{
  if (i < _currentArgCount)
    return _currentArgs[i].key;
  return String();
}

////////////////////////////////////////

int URLArgsParser::args()
{
  return _currentArgCount;
}

////////////////////////////////////////

bool URLArgsParser::hasArg(const String& name)
{
  for (int i = 0; i < _currentArgCount; ++i)
  {
    if (_currentArgs[i].key == name)
      return true;
  }

  return false;
}

////////////////////////////////////////

String URLArgsParser::_prepareURL(const String& url)
{
 if ((url.indexOf(" ")>-1) || (url.indexOf("HTTP/1.1")>-1))
 {
  //cut header
  int start_pos = url.indexOf(" ")+3;
  int end_pos = url.indexOf("HTTP/")-1;
  String url_cut = url.substring(start_pos, end_pos);
  return url_cut;
 }
 else return String();
}

////////////////////////////////////////

String URLArgsParser::urlDecode(const String& text)
{
  String       decoded    = "";
  char         temp[]     = "0x00";
  unsigned int len  = text.length();
  unsigned int i    = 0;

  while (i < len)
  {
    char decodedChar;
    char encodedChar = text.charAt(i++);

    if ((encodedChar == '%') && (i + 1 < len))
    {
      temp[2] = text.charAt(i++);
      temp[3] = text.charAt(i++);

      decodedChar = strtol(temp, NULL, 16);
    }
    else
    {
      if (encodedChar == '+')
      {
        decodedChar = ' ';
      }
      else
      {
        decodedChar = encodedChar;  // normal ascii char
      }
    }

    decoded += decodedChar;
  }

  return decoded;
}

////////////////////////////////////////

void URLArgsParser::parseArguments(const String& url)
{
  String data = _prepareURL(url);
  
  if (_currentArgs)
    delete[] _currentArgs;

  _currentArgs = 0;

  if (data.length() == 0)
  {
    _currentArgCount = 0;
    _currentArgs = new RequestArgument[1];

    return;
  }

  _currentArgCount = 1;

  for (int i = 0; i < (int)data.length(); )
  {
    i = data.indexOf('&', i);

    if (i == -1)
      break;

    ++i;
    ++_currentArgCount;
  }

  _currentArgs = new RequestArgument[_currentArgCount + 1];

  int pos = 0;
  int iarg;

  for (iarg = 0; iarg < _currentArgCount;)
  {
    int equal_sign_index = data.indexOf('=', pos);
    int next_arg_index = data.indexOf('&', pos);

    if ((equal_sign_index == -1) || ((equal_sign_index > next_arg_index) && (next_arg_index != -1)))
    {
      if (next_arg_index == -1)
        break;

      pos = next_arg_index + 1;

      continue;
    }

    RequestArgument& arg = _currentArgs[iarg];
    arg.key = urlDecode(data.substring(pos, equal_sign_index));
    arg.value = urlDecode(data.substring(equal_sign_index + 1, next_arg_index));

    ++iarg;

    if (next_arg_index == -1)
      break;

    pos = next_arg_index + 1;
  }

  _currentArgCount = iarg;
}
