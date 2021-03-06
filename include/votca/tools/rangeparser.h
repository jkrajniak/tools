/*
 * Copyright 2009-2020 The VOTCA Development Team (http://www.votca.org)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef VOTCA_TOOLS_RANGEPARSER_H
#define VOTCA_TOOLS_RANGEPARSER_H

// Standard includes
#include <list>
#include <ostream>
#include <string>

// Local VOTCA includes
#include "types.h"

namespace votca {
namespace tools {

/**
 * \brief RangeParser
 *
 * parse strings like min:step:max, not flexible enough yet to be really useful
 */
class RangeParser {
 public:
  RangeParser();

  void Parse(std::string str);

  void Add(Index begin, Index end, Index stride = 1);

 private:
  struct block_t {
    block_t() = default;
    block_t(const Index &begin, const Index &end, const Index &stride)
        : _begin(begin), _end(end), _stride(stride) {}

    Index _begin, _end, _stride;
  };

 public:
  struct iterator {
    iterator() = default;

    Index operator*() const { return _current; }

    RangeParser::iterator &operator++();

    bool operator==(const RangeParser::iterator &);
    bool operator!=(const RangeParser::iterator &);

   private:
    RangeParser *_parent;

    iterator(RangeParser *, std::list<block_t>::iterator);
    std::list<block_t>::iterator _block;
    Index _current;

    friend class RangeParser;
  };

  RangeParser::iterator begin();
  RangeParser::iterator end();

 private:
  void ParseBlock(std::string str);

  std::list<block_t> _blocks;

  friend std::ostream &operator<<(std::ostream &out, const RangeParser &rp);
};

inline void RangeParser::Add(Index begin, Index end, Index stride) {
  _blocks.push_back(block_t(begin, end, stride));
}

inline RangeParser::iterator RangeParser::begin() {
  return RangeParser::iterator(this, _blocks.begin());
}

inline RangeParser::iterator RangeParser::end() {
  return RangeParser::iterator(this, _blocks.end());
}

inline RangeParser::iterator::iterator(RangeParser *parent,
                                       std::list<block_t>::iterator block)
    : _parent(parent), _block(block) {
  if (block != parent->_blocks.end()) {
    _current = (*block)._begin;
  } else {
    _current = -1;
  }
}

inline bool RangeParser::iterator::operator==(const RangeParser::iterator &i) {
  return (_block == i._block) && (_current == i._current);
}

inline bool RangeParser::iterator::operator!=(const RangeParser::iterator &i) {
  return !((_block == i._block) && (_current == i._current));
}

inline std::ostream &operator<<(std::ostream &out, const RangeParser &rp) {
  std::list<RangeParser::block_t>::const_iterator iter(rp._blocks.begin());
  for (; iter != rp._blocks.end(); ++iter) {
    if (iter != rp._blocks.begin()) {
      out << ",";
    }
    if (iter->_begin == iter->_end) {
      out << iter->_begin;
    } else if (iter->_stride == 1) {
      out << iter->_begin << ":" << iter->_end;
    } else {
      out << iter->_begin << ":" << iter->_stride << ":" << iter->_end;
    }
  }
  return out;
}

}  // namespace tools
}  // namespace votca

#endif  // VOTCA_TOOLS_RANGEPARSER_H
