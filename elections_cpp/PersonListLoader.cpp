#include "PersonListLoader.h"
#include "PersonList.h"
#include "DistrictArray.h"

namespace elections {

 void PersonListLoader::load(std::istream& in, PersonList& personList, DistrictArray& districtsArr) {
    int numOfPerson;
    in.read(rcastc(&numOfPerson), sizeof(numOfPerson));
    for (int i = 0; i < numOfPerson; i++) {
        int districtID = 0, vote = 0, candidate = 0;

        PersonPtr person = new Person(in, districtID, vote, candidate);
        District& district = districtsArr.get(districtID);
        person->setDistrict(&district);

        personList.addPerson(person);
        district.getVoters().addPerson(person);
    }
}   

}
