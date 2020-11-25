#include "Person.h"

Person::Person(const String& name, int idnum, int year, int district_num) :
_name(name), _id(idnum), _birth_year(year), _district_num(district_num), _voted(false)
{
}
