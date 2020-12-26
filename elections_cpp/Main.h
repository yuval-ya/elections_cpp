#pragma once

#include "Elections.h"

enum class ElectionsMenu { ADD_DISTRICT = 1, ADD_CITIZEN, ADD_PARTY, ADD_CANDIDATE, PRINT_DISTRICTS, PRINT_CITIZENS, PRINT_PARTIES, VOTE, RESULTS, EXIT, SAVE, LOAD };

enum class MainMenu { NEW = 1, LOAD, EXIT };

const int MAX_SIZE = 100;

void start(elections::Elections* election);
bool options(elections::Elections* election, ElectionsMenu choice);
bool newDistrict(elections::Elections& election);
bool newParty(elections::Elections& election);
bool newCitizen(elections::Elections& election);
bool setCitizenAsCandidate(elections::Elections& election);
bool vote(elections::Elections& election);
bool saveToFile(elections::Elections& election);
void printStatistics(elections::Elections& election);
void printResults(elections::Elections& election);
void finish(elections::Elections& election);
elections::Elections* loadElections();

