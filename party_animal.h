// Class for the part animal that inherits from the werewolf class

class party_animal : public werewolf 
{
	public:
		party_animal(string name, place &loc, int thresh) : werewolf(nm, loc, thresh);
		virtual void party_animal::eat_person(person *person);
};

void party_animal::eat_person(person *pers) {
	if (pers->has_item("beer") {

	}
}