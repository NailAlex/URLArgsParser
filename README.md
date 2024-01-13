# URLArgsParser

## Parse arguments in incoming URL for Arduino WEB projects.

by Niskorodnov Alexander aka NailAlex(NailMan)

License: MIT License
https://mit-license.org/ 

The library allows you to parse incoming URL requests from the client and receive the number of dynamic arguments passed and their “key:value” pair for subsequent processing.

Supporting all Arduino platforms and ESP-modules. 

Download the latest version (version 1.0) here :
https://github.com/NailAlex/URLArgsParser


## HOW TO USE

```c++
String URLArgsParser::arg_value(int i);
```

Get parsed and stored argument value with given index.

```c++
String URLArgsParser::arg_key(int i);
```

Get parsed and stored argument key name with given index.

```c++
int URLArgsParser::args();
```

Get count of stored key:value pairs.

```c++
bool URLArgsParser::hasArg(const String& name);
```

Check key name for exists.


```c++
bool URLArgsParser::hasArg(const String& name);
```

Check key name for exists.

```c++
void URLArgsParser::parseArguments(const String& url)
```

Parse income URL string with argiments in GET/POST/PUT HTTP request.


## History

(Jan 2024) v1.0 First release. 