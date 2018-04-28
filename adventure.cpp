// adventure.cpp  a basic text adventure game using objects and inheritance

#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int NUM_DIRECTIONS = 6;

enum direction { north, south, east, west, up, down };

string dirstrings[NUM_DIRECTIONS] = { "north", "south", "east", "west", "up", "down" };

string direction_to_string(direction dir)
{
	return dirstrings[dir];
}

direction string_to_direction(string s)
{
	for (int i = 0; i<NUM_DIRECTIONS; i++)
		if (dirstrings[i] == s)
			return static_cast<direction>(i);
	cout << "Error: invalid string given to string_to_direction";
	exit(1);
}

enum kind { named_obj, thing_obj, place_obj, person_obj };

#include "named_obj.h"
#include "thing.h"
#include "place.h"
#include "person.h"
#include "werewolf.h"
#include "party_animal.h"

vector<thing*> all_things;
vector<person*> all_people;

void can_go(place &from, direction dir, place &to)
{
	from.add_neighbor(dir, &to);
}

void install_thing(thing &thng, place &loc)
{
	all_things.push_back(&thng);
	loc.add_thing(&thng);
}

thing *string_to_thing(string s)
{
	for (int i = 0; i<all_things.size(); i++)
		if (all_things[i]->get_name() == s)
			return all_things[i];
	cout << "Error: invalid string given to string_to_thing";
	exit(1);
}

void install_person(person &persn)
{
	all_people.push_back(&persn);
}

void clock()
{
	for (int i = 0; i<all_people.size(); i++)
		all_people[i]->clock();
}

int main()
{
	place mccormick("McCormick Hall Lobby");
	place bakeless("Bakeless Hall Lobby");
	place computer_lab("Computer Lab");
	place basement("Basement");
	place professors_office("Professor's Office");
	place roof_computer_lab("Roof of Computer Lab");
	place roof_prof_office("Roof of Professors OFfice");

	can_go(professors_office, up, roof_prof_office);
	can_go(roof_prof_office, down, professors_office);
	can_go(computer_lab, up, roof_computer_lab);
	can_go(roof_computer_lab, down, computer_lab);
	//can_go(mccormick, south, bakeless);
	can_go(mccormick, south, quad); //bonus
	can_go(quad, south,bakeless); //bonus
	//can_go(bakeless, north, mccormick);
	can_go(bakeless, north, quad); //bonus
	can_go(quad, north, mccormick); //bonus
	can_go(quad, down, pit); //bonus
	can_go(bakeless, up, computer_lab);
	can_go(computer_lab, down, bakeless);
	can_go(bakeless, down, basement);
	can_go(basement, up, bakeless);
	can_go(mccormick, up, professors_office);
	can_go(professors_office, down, mccormick);

	person me("Erik", mccormick, 10000);
	install_person(me);
	person veronica("Veronica", mccormick, 2);
	install_person(veronica);
	werewolf cujo("Cujo", roof_computer_lab, 3);
	install_person(cujo);
	party_animal spuds("Spuds", basement, 8);
	install_person(spuds);

	thing disk("disk");
	install_thing(disk, computer_lab);
	thing beer("beer");
	install_thing(beer, professors_office);
	thing jetpack("jetpack");
	install_thing(jetpack, basement);

	string command, arg;
	me.look();

	//main loop
	while (true)
	{
		cout << "> ";
		cin >> command;
		if (command == "quit")
			return 0;
		else if (command == "look")
			me.look();
		else if (command == "go")
		{
			cin >> arg;
			me.go_look(string_to_direction(arg));
		}
		else if (command == "fly") {
			place* currPlace = me.get_location();
			if (*currPlace == roof_computer_lab && jetpack.owned()) {
				me.move_to(&roof_prof_office);
			}
			else if (*currPlace == roof_prof_office && jetpack.owned()) {
				me.move_to(&roof_computer_lab);
			}
			else {
				cout << "You want to believe you can fly.... but sadly that is not the case." << endl;
			}
		}
		else if (command == "take")
		{
			cin >> arg;
			me.take(string_to_thing(arg));
		}
		else if (command == "wait")
			cout << "Time passes" << endl;
		else
			cout << "Unknown command (ignored)." << endl;
		clock();
		getline(cin, arg);  // read away rest of line
	}
}
