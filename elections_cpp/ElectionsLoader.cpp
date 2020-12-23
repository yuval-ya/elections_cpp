#include "ElectionsLoader.h"
#include <typeinfo>

namespace elections {

	Elections* ElectionsLoader::load(std::istream& in) {
		ElectionsType type;
		in.read(rcastc(&type), sizeof(type));

		switch (type)
		{
		case ElectionsType::RERGULAR:
			return new Elections(in);
			break;
		case ElectionsType::SIMPLE:
			return new SimpleElections(in);
			break;
		default:
			return nullptr;
			break;
		}

	}

	bool ElectionsLoader::save(std::ostream& out, Elections* elections) {
		ElectionsType type;
		if (typeid(*elections) == typeid(Elections))
			type = ElectionsType::RERGULAR;
		else if (typeid(*elections) == typeid(SimpleElections))
			type = ElectionsType::SIMPLE;
		else
			return false;

		out.write(rcastcc(&type), sizeof(type));
		return elections->save(out);
	}

	void personListLoader(std::istream& in, PersonList& personList, DistrictArray& districtsArr) {
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