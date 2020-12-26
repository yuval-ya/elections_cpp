#include "ElectionsLoader.h"
#include "SimpleElections.h"
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

}