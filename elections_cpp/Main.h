#pragma once

#include "Elections.h"

const int MAX_SIZE = 100;

void start(elections::Elections& election);
bool options(elections::Elections& election, int choice);
bool new_district(elections::Elections& election);
bool new_party(elections::Elections& election);
bool new_citizen(elections::Elections& election);
bool set_citizen_as_candidate(elections::Elections& election);
bool vote(elections::Elections& election);
void print_statistics(elections::Elections& election);
void print_results(elections::Elections& election);
void finish(elections::Elections& election);