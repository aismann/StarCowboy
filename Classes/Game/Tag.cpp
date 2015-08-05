
#include "Tag.h"

const Tag                    Tag::null;
Tag::Bit                     Tag::_sNextBit = 1;
std::map<std::string, Tag*>* Tag::_sTagMap;