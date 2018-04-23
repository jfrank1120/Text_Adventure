// base class for persons, places, and things, which are all kinds of named_objects
class named_object
{
public:
	named_object(string nm) { name = nm; }
	string get_name() const { return name; }
	virtual kind get_kind() { return named_obj; }
private:
	string name;
};
