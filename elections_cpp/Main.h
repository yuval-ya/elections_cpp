#pragma once

#include "Elections.h"

const int MAX_SIZE = 100;

void start(elections::Elections& election);
bool options(elections::Elections& election, int choice);
bool newDistrict(elections::Elections& election);
bool newParty(elections::Elections& election);
bool newCitizen(elections::Elections& election);
bool setCitizenAsCandidate(elections::Elections& election);
bool vote(elections::Elections& election);
void printStatistics(elections::Elections& election);
void printResults(elections::Elections& election);
void finish(elections::Elections& election);
