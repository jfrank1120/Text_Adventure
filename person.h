// a person has a collection of possessions and can look, take things, go in a direction, etc.
class person : public named_object
{
public:
	person(string nm, place &loc, int thresh)
		: named_object(nm), location(&loc), threshold(thresh), restlessness(0)
	{
		location->add_thing(this);
	}
	place* get_location() const { return location; }
	vector<thing*> get_possessions() const { return possessions; }
	void look() const;
	void inventory() const {};
	virtual string get_greeting() const { return greeting; }
	virtual void greet_others();
	virtual void greeted_by(person *persn);
	virtual void go(direction dir);
	void move_to(place *new_place);
	void go_look(direction dir);
	void take(thing *thng);
	void drop(thing *thng);
	void clock();
	virtual void act();
	kind get_kind() { return person_obj; }
protected:
	static const string greeting;
	int restlessness;
	int threshold;
	place *location;
	vector<thing*> possessions;
};

const string person::greeting = " hello ";

void person::look() const
{
	cout << "You are in " << location->get_name() << endl;
	cout << "You see ";
	if ((location->get_things()).size() == 1)
		cout << "nothing of interest";
	else
	{
		for (int i = 0; i<location->get_things().size(); i++)
			if ((location->get_things())[i]->get_name() != get_name())
				cout << (location->get_things())[i]->get_name() << " ";
	}
	cout << endl;
}

void announce_move(string name, place *from, place *to)
{
	cout << name << " moves from " << from->get_name() << " to ";
	cout << to->get_name() << endl;
}

void person::move_to(place *new_place)
{
	announce_move(get_name(), location, new_place);
	location->remove_thing(this);
	location = new_place;
	location->add_thing(this);
}

void person::go(direction dir)
{
	if ((location->get_neighbors())[dir] == NULL)
		cout << "You can't go " << direction_to_string(dir) << endl;
	else
	{
		move_to((location->get_neighbors())[dir]);
		greet_others();
	}
}

void person::greet_others()
{
	string name;
	named_object *pobj;
	for (int i = 0; i<location->get_things().size(); i++)
	{
		pobj = (location->get_things())[i];
		name = pobj->get_name();
		if (pobj->get_kind() == person_obj && name != get_name())
		{
			cout << get_name() << " says" << greeting << name << endl;
			static_cast<person*>(pobj)->greeted_by(this);
		}
	}
}

void person::greeted_by(person *persn)
{
	cout << get_name() << " says" << get_greeting() << persn->get_name() << endl;
}

void person::take(thing *thng)
{
	location->remove_thing(thng);
	possessions.push_back(thng);
	thng->change_owner(this);
	cout << thng->get_name() << " taken by " << get_name() << endl;
}

void person::go_look(direction dir)
{
	if ((location->get_neighbors())[dir] == NULL)
		cout << "You can't go " << direction_to_string(dir) << endl;
	else
	{
		move_to((location->get_neighbors())[dir]);
		look();
		greet_others();
	}
}

void person::clock()
{
	restlessness++;
	if (restlessness >= threshold)
	{
		restlessness = 0;
		act();
	}
}

void person::act()
{
	int num_exits = location->get_exits().size();
	if (num_exits == 0)
		return;
	int index = rand() % num_exits; // pick a random exit
	direction dir = (location->get_exits())[index];
	go(dir);
}
