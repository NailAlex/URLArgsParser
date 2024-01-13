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

#ifndef URLArgsParser_h
#define URLArgsParser_h 

#include <inttypes.h> 


struct RequestArgument {
  String   key;
  String   value;
};


class URLArgsParser {
  public:
  //methods
  String            arg_value(int i);
  String            arg_key(int i);
  int               args();
  bool              hasArg(const String& name);
  String            urlDecode(const String& text);
  void              parseArguments(const String& url); 
  // Contructor
  URLArgsParser(void);
  private:
  //parameters
  int               _currentArgCount;
  RequestArgument*  _currentArgs      = nullptr;
  int               _postArgsLen;
  RequestArgument*  _postArgs         = nullptr;    
  String              _prepareURL(const String& url);
};


#endif
