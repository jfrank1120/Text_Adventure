class person;  // a forward declaration

// a thing is something that can be owned
class thing : public named_object
{
public:
	thing(string nm) : named_object(nm), owner(NULL) {}
	bool ownable() const { return true; }
	bool owned() const { return (owner != NULL); }
	person *get_owner() const { return owner; }
	void change_owner(person *new_owner) { owner = new_owner; }
	kind get_kind() { return thing_obj; }
private:
	person *owner;
};