#include "alphabet.h"

using namespace std;

class multiSet{
  private :
    int count_array[129];
	public :
    multiSet();
    multiSet(char *);
    multiSet(alphabet *);
	bool reset();
	void display();
    int& operator [] (char);
	multiSet operator + (alphabet);
	multiSet operator + (multiSet);
	bool operator == (multiSet );
	friend ostream& operator << (ostream& , multiSet& );
	friend istream& operator >> (istream& , multiSet& );
};
