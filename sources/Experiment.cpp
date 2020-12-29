// Copyright 2020 Olga Molchun olgamolchun5@gmail.com
#include "Experiment.hpp"

int Experiment::counter_of_experiments = 0;

Experiment::Experiment(const size_t &numbers_of_elements)
    : time{}, cardinality{numbers_of_elements} {

  counter_of_experiments++;

  buffer = new int[cardinality];
  std::mt19937 generator(clock());
  for (size_t i = 0; i < cardinality; ++i)
    buffer[i] = generator();

  for (size_t i = 0; i < cardinality; i += 16)
    indexes_for_warming.push_back(i);

  for (size_t i = 0; i < cardinality; i++)
    indexes_for_buffer.push_back(i);

}

void Experiment::start() {
  std::cout << "_____________________________________" << std::endl;
  std::cout << "Experiment № " << counter_of_experiments << std::endl;
  std::cout << "Numbers of elements: " << cardinality << std::endl;
  pass_direct();
  pass_reverse();
  pass_random();
}

Experiment::~Experiment() { delete[] buffer; }

int Experiment::do_something(int value) { return value; }

void Experiment::warming_up_cache() {
  for (const size_t &i : indexes_for_warming) {
      do_something(buffer[i]);
  }
}

auto Experiment::looping_by_array() {
  auto start = std::chrono::high_resolution_clock::now();
  for (size_t i = 0; i < kcycles; ++i) {
    for (const size_t &j : indexes_for_buffer)
        do_something(buffer[j]);
  }
  auto end = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
      .count();
}

void Experiment::pass_direct() {
    warming_up_cache();
  time.duration_straight = looping_by_array();
  std::cout << "Straight bypass duration: " << time.duration_straight << " ms"
            << std::endl;
}
void Experiment::pass_reverse() {
  std::reverse(indexes_for_warming.begin(), indexes_for_warming.end());
  warming_up_cache();
  std::reverse(indexes_for_buffer.begin(), indexes_for_buffer.end());
  time.duration_reverse = looping_by_array();
  std::cout << "Reverse bypass duration: " << time.duration_reverse << " ms"
            << std::endl;
}

void Experiment::pass_random() {
  std::mt19937 g(clock());
  std::shuffle(indexes_for_warming.begin(), indexes_for_warming.end(), g);
  warming_up_cache();
  std::shuffle(indexes_for_buffer.begin(), indexes_for_buffer.end(), g);
  time.duration_random = looping_by_array();
  std::cout << "Random bypass duration: " << time.duration_random << " ms"
            << std::endl;
}

size_t Experiment::get_cardinality() const { return cardinality; }

const ExperimentsTimes &Experiment::get_time() const { return time; }
