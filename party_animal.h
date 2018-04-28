// Class for the part animal that inherits from the werewolf class

class party_animal : public werewolf 
{
	public:
		party_animal(string name, place &loc, int thresh) : werewolf(nm, loc, thresh);
		virtual void party_animal::eat_person(person *person);
};

void party_animal::eat_person(person *pers) {
	if (pers->has_item("beer")) {
		thing *beer = pers->
		cout << get_name() << "says OH! IS THAT A BEER!? ";
		// Person loses Beer from their inventory
		pers->drop(beer);
		// Party_Animal takes beer
		take(beer);
		cout << get_name() << ": Takes your beer and proceeds to drink it" << endl;
		cout << get_name() << ": Seems to be feeling woozey" << endl;
	}
	else {
		werewolf::eat_person(pers);
	}
}