// Copyright 2020 Olga Molchun olgamolchun5@gmail.com
#include "Investigation.hpp"

Investigation::Investigation() {
  const size_of_cache cache;
    buffer_info.size_min = 0.5 * cache.l1;
    buffer_info.size_current = buffer_info.size_min;
    buffer_info.size_max = 1.5 * cache.l3;
}

void Investigation::start() {
  size_t numberOfElements = buffer_info.size_min / sizeof(int);
  size_t degree = std::log2(buffer_info.size_min);
  while (buffer_info.size_current <= buffer_info.size_max) {
    auto *experiment = new Experiment(numberOfElements);
    experiment->start();
    results.push_back(experiment);
    degree++;
      buffer_info.size_current = pow(2, degree);
    numberOfElements = buffer_info.size_current / sizeof(int);
  }
  if (buffer_info.size_current != buffer_info.size_max) {
    auto *experiment = new Experiment(buffer_info.size_max / sizeof(int));
    experiment->start();
    results.push_back(experiment);
  }
}
void Investigation::make_report(std::ofstream &file) {
  file << "investigation:\n";
  file << "\ttravel_variant: Direct\n";
  file << "\texperiments:\n";
  for (size_t i = 0; i < results.size(); i++) {
    file << "\t- experiment:\n";
    file << "\t\tnumber: " << i + 1 << "\n";
    file << "\t\tinput data:\n";
    file << "\t\t\tbuffer size: \""
         << results[i]->get_cardinality() * sizeof(int) / 1024 << " kB\"\n";
    file << "\t\tresults:\n";
    file << "\t\t\tduration: \"" << results[i]->get_time().duration_straight
         << " ms\"\n";
  }
  file << "\n";
  file << "investigation:\n";
  file << "\ttravel_variant: Reverse\n";
  file << "\texperiments:\n";
  for (size_t i = 0; i < results.size(); i++) {
    file << "\t- experiment:\n";
    file << "\t\tnumber: " << i + 1 << "\n";
    file << "\t\tinput data:\n";
    file << "\t\t\tbuffer size: \""
         << results[i]->get_cardinality() * sizeof(int) / 1024 << " kB\"\n";
    file << "\t\tresults:\n";
    file << "\t\t\tduration: \"" << results[i]->get_time().duration_reverse
         << " ms\"\n";
  }
  file << "\n";
  file << "investigation:\n";
  file << "\ttravel_variant: Random\n";
  file << "\texperiments:\n";
  for (size_t i = 0; i < results.size(); i++) {
    file << "\t- experiment:\n";
    file << "\t\tnumber: " << i + 1 << "\n";
    file << "\t\tinput data:\n";
    file << "\t\t\tbuffer size: \""
         << results[i]->get_cardinality() * sizeof(int) / 1024 << " kB\"\n";
    file << "\t\tresults:\n";
    file << "\t\t\tduration: \"" << results[i]->get_time().duration_random
         << " ms\"\n";
  }
  file << "\n";
}

Investigation::~Investigation() {
  for (auto element : results) {
    delete element;
  }
  results.clear();
}
