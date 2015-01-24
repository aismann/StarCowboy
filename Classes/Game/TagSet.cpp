
#include "TagSet.h"

const TagSet                    TagSet::null;
TagSet::TagBit                  TagSet::_sNextBit = 1;
std::map<std::string, TagSet*>* TagSet::_sTagMap;