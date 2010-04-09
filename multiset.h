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
	multiSet multiSet:: operator + (alphabet);
	multiSet multiSet:: operator + (multiSet);
	bool multiSet:: operator == (multiSet );
	friend ostream& operator << (ostream& , multiSet& );
	friend istream& operator >> (istream& , multiSet& );
};
