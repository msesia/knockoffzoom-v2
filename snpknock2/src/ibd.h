#ifndef _IBD_H
#define _IBD_H

#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "utils.h"
#include "utils_graph.h"

using namespace std;

class IbdSeg {
  public:
  // Constructors/destructors
  IbdSeg();
  IbdSeg(const set<unsigned int> & indices_, unsigned int nonempty_, unsigned int j_min_, unsigned int j_max_, unsigned int bp_min_, unsigned int bp_max_);
  IbdSeg(const IbdSeg& obj);

  // Methods
  bool operator< (const IbdSeg & obj) const;
  bool operator== (const IbdSeg & obj) const;
  int overlaps_with (const IbdSeg & obj) const;
  int touches_with(const IbdSeg & obj) const;
  bool close_to(const IbdSeg & obj, unsigned int min_dist, bool same_indices) const;
  void print() const;
  IbdSeg find_shared(const IbdSeg & obj) const;
  vector<IbdSeg> subtract(const IbdSeg & obj) const;
  unsigned int length() const;
  unsigned int size() const;
  IbdSeg shave_from_start() const;
  IbdSeg shave_from_end() const;
  
  // Data
  set<unsigned int> indices;
  unsigned int j_min, j_max;
  unsigned int bp_min, bp_max;
  unsigned int nonempty;
};

class IbdCluster {
  public:
  // Constructors/destructors
  IbdCluster(const set<IbdSeg> & segments_);
  void print() const;
  unsigned int size() const;
  void get(unsigned int k, IbdSeg & placeholder) const;

  private:
  // Data
  set<IbdSeg> segments;

  // Methods
  void tidy();
  void tidy_overlapping(const IbdSeg & s1, const IbdSeg & s2, unsigned int min_length);
  void tidy_touching(const IbdSeg & s1, const IbdSeg & s2, unsigned int min_length);
  void merge_close(const IbdSeg & s1, const IbdSeg & s2);
  void expand_close(const IbdSeg & s1, const IbdSeg & s2);

  pair<set<IbdSeg>::iterator,set<IbdSeg>::iterator> find_overlapping_segments() const;
  pair<set<IbdSeg>::iterator,set<IbdSeg>::iterator> find_touching_segments() const;
  pair<set<IbdSeg>::iterator,set<IbdSeg>::iterator> find_close_segments(unsigned int min_dist, bool same_indices) const;
  set<IbdSeg>::iterator find_short_segments(unsigned int min_length) const;

};

#endif
