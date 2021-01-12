#pragma once

#include <fstream>
#include "ElectionsLoader.h"
#include "List.h"
#include "Utilities.h"

enum class ElectionsMenu { ADD_DISTRICT = 1, ADD_CITIZEN, ADD_PARTY, ADD_CANDIDATE, PRINT_DISTRICTS, PRINT_CITIZENS, PRINT_PARTIES, VOTE, RESULTS, EXIT, SAVE, LOAD };

enum class MainMenu { NEW = 1, LOAD, EXIT };

void mainMenu();
elections::Elections* loadElections();
elections::Elections* createNewRound();
void start(elections::Elections** election);
void options(elections::Elections** election, ElectionsMenu choice);
void newDistrict(elections::Elections& election);
void newParty(elections::Elections& election);
void newCitizen(elections::Elections& election);
void setCitizenAsCandidate(elections::Elections& election);
void vote(elections::Elections& election);
void saveToFile(elections::Elections& election);
void printStatistics(elections::Elections& election);
void printResults(elections::Elections& election);
void finish(elections::Elections& election);


