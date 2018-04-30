// a place may contain things and has exits and adjoining places (neighbors)
class place : public named_object
{
public:
	place(string nm)
		: named_object(nm), things(0), neighbors(NUM_DIRECTIONS, NULL), exits(0) {}
	vector<named_object*> get_things() const { return things; }
	vector<direction> get_exits() const { return exits; }
	vector<place*> get_neighbors() const { return neighbors; }
	place *neighbor_towards(direction dir) const { return neighbors[dir]; }
	void add_thing(named_object *thng) { things.push_back(thng); }
	void remove_thing(named_object *thng);
	bool contains_thing(string thing) const;
	void add_neighbor(direction dir, place *nbr)
	{
		neighbors[dir] = nbr; exits.push_back(dir);
	}
	kind get_kind() { return place_obj; }
private:
	vector<named_object*> things;
	vector<place*> neighbors;
	vector<direction> exits;
};

void place::remove_thing(named_object *thng)
{
	for (int i = 0; i<things.size(); i++)
		if (things[i]->get_name() == thng->get_name())
		{
			for (int j = i + 1; j<things.size(); j++)
				things[j - 1] = things[j];
			things.pop_back();
		}
}
/*
* Function checks to see if a person can pick
* up a item from in the room. This fixes the
* error where objects could be picked up from
* anywhere. Requires parameter thing, and
* returns true or false.
*/
bool place::contains_thing(string thing) const {
	for (int i = 0; i < things.size(); i++)
	{
		if (things[i]->get_name() == thing)
			return true;
	}
	return false;
}
/*
* Equals operator that allows the comparison
* of two places, returns true or false.
*/
bool operator==(place loc1, place loc2)
{
	return loc1.get_name() == loc2.get_name();
}
place heaven("Heaven");
