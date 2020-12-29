// Copyright 2020 Olga Molchun olgamolchun5@gmail.com
#ifndef INCLUDE_EXPERIMENT_HPP_
#define INCLUDE_EXPERIMENT_HPP_

#include <algorithm>
#include <chrono>
#include <ctime>
#include <iostream>
#include <random>
#include <string>
#include <utility>
#include <vector>

const size_t kcycles = 1000;

struct ExperimentsTimes {
  double duration_straight;
  double duration_reverse;
  double duration_random;
};
class Experiment {
 public:
  static int counter_of_experiments;
  explicit Experiment(const size_t &numbers_of_elements);
  void start();
  [[nodiscard]] size_t get_cardinality() const;
  [[nodiscard]] const ExperimentsTimes &get_time() const;
  ~Experiment();

 private:
  ExperimentsTimes time;
  int *buffer;
  size_t cardinality;
  std::vector<size_t> indexes_for_warming;
  std::vector<size_t> indexes_for_buffer;
  int do_something(int value);
  void warming_up_cache();
  auto looping_by_array();
  void pass_direct();
  void pass_reverse();
  void pass_random();
};
#endif  // INCLUDE_EXPERIMENT_HPP_
