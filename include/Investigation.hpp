#ifndef INCLUDE_INVESTIGATION_HPP_
#define INCLUDE_INVESTIGATION_HPP_

#include "Experiment.hpp"

#include <fstream>
#include <vector>


const size_t kbytes = 1024;
// Intel Core i7-9750H
// in bytes
struct size_of_cache{
 public:
  const size_t l1 = 384 * kbytes;
  const size_t l2 = 1536 * kbytes;
  const size_t l3 = 9216 * kbytes;
};

struct BufferSize {
  double size_min;
  double size_current;
  double size_max;
};

class Investigation {
 public:
  Investigation();
  void start();
  void make_report(std::ofstream &file);
  virtual ~Investigation();

 private:
  BufferSize buffer_info{};
  std::vector<Experiment *> results;
};
#endif  // INCLUDE_INVESTIGATION_HPP_
