#include "Party.h"

int Party::total_parties = 0;

Party::Party(const String& name, int candidate_id) : 
	_name(name), _candidate_id(candidate_id), _id(++total_parties)
{

}
Party::~Party() {
	
}