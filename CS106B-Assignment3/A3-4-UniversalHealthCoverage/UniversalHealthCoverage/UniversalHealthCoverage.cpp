/* File: UniversalHealthCoverage.cpp
 *
 * A program that determines whether or not it is possible to provide
 * coverage to everyone using a fixed number of hospitals.
 */
#include <iostream>
#include <string>
#include "set.h"
#include "vector.h"
#include "console.h"
using namespace std;

/* Function: canOfferUniversalCoverage(Set<string>& cities,
 *                                     Vector< Set<string> >& locations,
 *                                     int numHospitals,
 *                                     Vector< Set<string> >& result);
 * Usage: if (canOfferUniversalCoverage(cities, locations, 4, result)
 * ==================================================================
 * Given a set of cities, a list of what cities various hospitals can
 * cover, and a number of hospitals, returns whether or not it's
 * possible to provide coverage to all cities with the given number of
 * hospitals.  If so, one specific way to do this is handed back in the
 * result parameter.
 */
bool canOfferUniversalCoverage(Set<string>& cities,
                               Vector< Set<string> >& locations,
                               int numHospitals,
                               Vector< Set<string> >& result);


int main() {
    /* Set up the cities and locations */
    Set<string> cities;
    cities += "A", "B", "C", "D", "E";
    
    Set<string> hospital1;
    hospital1 += "A", "B", "C";
    
    Set<string> hospital2;
	hospital2 += "A", "C","D";
    
    Set<string> hospital3;
    hospital3 += "B";
    
    Set<string> hospital4;
    hospital4 += "C", "E";
    
    Vector<Set<string> > locations;
    locations += hospital1, hospital2, hospital3, hospital4;
    
    int numHospitals = 4;
    Vector<Set<string> > result;
    if (canOfferUniversalCoverage(cities, locations, numHospitals, result)) {
        cout << "Yes, it can offer universal coverage!" << endl;
		cout << "Result: "<<endl;
		int i=1;
		foreach(Set<string> set in result){
			cout<<"location "<<i<<" : ";
			foreach(string str in set){
				cout<<str<<" ";
			}
			cout<<endl;
			i++;
		}
    } else {
        cout << "No, it cannot offer universal coverage." << endl;
    }
    
	    
    return 0;
}

bool canOfferUniversalCoverage(Set<string>& cities,
                               Vector< Set<string> >& locations,
                               int numHospitals,
                               Vector< Set<string> >& result) {



	if(cities.isEmpty())
		return true;

	if(locations.isEmpty() || numHospitals==0 )
		return false;
	
	for(int i=0;i<locations.size();i++){

		Set<string> location =locations[i];
		Vector< Set<string> > rest=locations;
		rest.removeAt(i);
		Set<string> leftCities= cities-location;
		result.add(location);
		
		/*
		bug fixing 
		cout<<"no. hos "<<numHospitals<<endl;
		cout<<"location choosed i "<<i<<endl;
		cout<<"cities.size "<<cities.size()<<endl;
		cout<<"result.size "<<result.size()<<endl;
		cout<<endl;*/

		if(canOfferUniversalCoverage(leftCities,rest,numHospitals-1,result)) return true;

		result.removeAt(result.size()-1);

	}
	

	return false;
 
}


