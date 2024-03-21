
/*
a. Parse a one-dimensional binary byte-array sequence that contains a series of Type-Value pairs;
   a 1-byte Type field followed by a 1-byte Value field.

b. The Type field’s value can range from 0-3.  The Value field’s value can range from 0-255.
   One example sequence could be: 3, 253, 0, 126, 0, 53, 3, 181, 2, 12.

c. As each Type-Value pair is extracted by the parser, the Type and Value fields must be printed
   to stdout.  The requirement is that a unique print method must be called based on the
   Type field (0-3).  For clarity, there should be four different print methods, one for each
   possible Type value.  Efficiently call the print method associated with its respective Type value.

d. Ensure error and bounds checking is performed.

e. Be prepared to discuss how the code architecture might change if the Type field could
   range from 0-255.

f. Be prepared to discuss how the code architecture might change if the binary byte sequence
   contained a series of three fields: 1-byte Type, 1-byte Length (n), n-byte Value.

g. Be prepared to discuss how the code architecture might change if Value field’s constraints could
   differ depending on the Type field.  For example, the Value field for Type 0 could be restricted
   to values of 0-9, while the Value field for the Type 1 could be restricted to values of 10-19, etc.
*/

#include <iostream>
#include <vector>
#include <memory>

using namespace std;


struct type_value_t
{
    unsigned char type;
    unsigned char value;
};


// struct type1_value_t : public type_value_t
// {
//     void print() const {};
// };



// error print helper
#define STRINGIZE_DETAIL(x) #x
#define STRINGIZE(x) STRINGIZE_DETAIL(x)
#define FILE_LINE __FILE__ "(" STRINGIZE(__LINE__) "): "

enum {Type_1=0, Type_2=1, Type_3=2, Type_4=3};

bool tv_parser(const unsigned char* bytes, int size, vector<type_value_t>& tv_vector )
{
    // sanity check
    if (bytes == nullptr)
    {
        cerr << FILE_LINE << "ERROR : bad input data" << endl;
        return false;
    }
    if (size % 2)
    {
        cerr << FILE_LINE << "WARNING : last value is missing" << endl;
    }

    type_value_t tv;
    for (int i=0; i+1 < size; i += 2)
    {
        if (bytes[i] & ~0x03)
            {
                cerr << FILE_LINE << "ERROR: unexpected Type " << (unsigned)bytes[i] << endl;
                continue;
            }
        tv.type  = bytes[i];
        tv.value = bytes[i+1];
        tv_vector.push_back(tv);
    }
    if (tv_vector.empty())
    {
        cerr << FILE_LINE << "WARNING: no Type-Values were parsed" << endl;
    }

    return true;
}

bool print_tv(const vector<type_value_t>& tv_vector)
{
   for (auto tv : tv_vector)
   {
       switch(tv.type)
       {
       case Type_1:
            cout << "type: 1 value: " << (unsigned)tv.value << endl; break;
       case Type_2:
            cout << "type: 2 value: " << (unsigned)tv.value << endl; break;
       case Type_3:
            cout << "type: 3 value: " << (unsigned)tv.value << endl; break;
       case Type_4:
            cout << "type: 4 value: " << (unsigned)tv.value << endl; break;
       default:
            cerr << FILE_LINE << "ERROR : Unknown Type "  << (unsigned)tv.type << endl;
            return false;
       }
   }
   return true;
}



int main(int argc, char *argv[])
{
    unsigned char bytes[] = {5, 253, 0, 126, 0, 53, 3, 181, 2, 12};
    vector<type_value_t> tv_vector;
    tv_parser(bytes, sizeof (bytes), tv_vector);
    print_tv(tv_vector);

    return 0;
}