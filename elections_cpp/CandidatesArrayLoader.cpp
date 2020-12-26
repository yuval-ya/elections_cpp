#include "CandidatesArrayLoader.h"
#include "CandidatesArray.h"

namespace elections {

void CandidatesArrayLoader::save(std::ostream& out,const CandidatesArray& arr) {

    int size = arr.getLength();
    out.write(rcastcc(&size), sizeof(size));
    for (int i = 0; i < size; i++){
        int districtID = arr[i].district->getId();
        out.write(rcastcc(&districtID), sizeof(districtID));
        arr[i].candidateList.saveID(out);
    }
}


void CandidatesArrayLoader::load(std::istream& in, CandidatesArray& arr) {

}

}