// Class for the party animal that inherits from the werewolf class
class party_animal : public werewolf 
{
	public:
		party_animal(string name, place &loc, int thresh) : werewolf(name, loc, thresh) {};
		virtual void party_animal::eat_person(person *person);
};
/*
* Overriden function that will stop the party animal
* from eating a person if there is a beer in their
* inventory at the time that they are encountered
*/
void party_animal::eat_person(person *pers) {
	if (pers->has_item("beer")) {
		thing *beer = pers->get_item("beer");
		cout << get_name() << " says YOOO PASS ME THAT BREWSKI " << pers->get_name() << "!" << endl;
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