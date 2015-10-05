// This is start of the header guard.  READ_H can be any unique name. It is an include guard to avoid duplicate copies of the headerfile 
#ifndef FILEIO_H
#define FILEIO_H
#include <string>

// This is the content of the .h file, which is where the declarations go
int readHeader(std::string fileName);

int trim(std::string fileName);

int strToint(std::string num);

// This is the end of the header guard
#endif
