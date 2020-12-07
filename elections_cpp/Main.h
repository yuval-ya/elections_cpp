#pragma once

#include "Elections.h"

const int MAX_SIZE = 100;

void start(Elections& election);
bool options(Elections& election, int choice);
bool new_district(Elections& election);
bool new_party(Elections& election);
bool new_citizen(Elections& election);
bool set_citizen_as_candidate(Elections& election);
bool vote(Elections& election);
void print_statistics(Elections& election);
void print_results(Elections& election);
void finish(Elections& election);