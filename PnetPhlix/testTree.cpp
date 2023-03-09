//#include "treemm.h"
//#include <string>
//#include <iostream>
//
//int main() {
//	TreeMultimap<std::string, int> tmm;
//	tmm.insert("carey", 5);
//	tmm.insert("carey", 6);
//	tmm.insert("carey", 7);
//	tmm.insert("david", 25);
//	tmm.insert("david", 425);
//	TreeMultimap<std::string, int>::Iterator it = tmm.find("carey");
//	// prints 5, 6, and 7 in some order
//	while (it.is_valid()) {
//		std::cout << it.get_value() << std::endl;
//		it.advance();
//	}
//	/*Iterator*/ it = tmm.find("laura");
//	// it = tmm.find("laura");
//	if (!it.is_valid())
//		std::cout << "laura is not in the multimap!\n";
//}