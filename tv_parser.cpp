
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

// ============== Parser Implementation start =======================

// error print helper
#define STRINGIZE_DETAIL(x) #x
#define STRINGIZE(x) STRINGIZE_DETAIL(x)
#define FILE_LINE __FILE__ "(" STRINGIZE(__LINE__) "): "
class tv_parser
{
    public:
       bool init(const unsigned char* bytes, int size);
       void print() const;
    private:
        enum {Type_0=0, Type_1=1, Type_2=2, Type_3=3};
        struct type_value_t
        {
            type_value_t(unsigned char type, unsigned char value) :
                 _type(type),
                 _value(value) {}
            virtual void print() const=0;

            unsigned char _type;
            unsigned char _value;
        };
        struct type_0_value_t : public type_value_t
        {
            type_0_value_t(unsigned char type, unsigned char value) : type_value_t(type, value){}
            void print() const;
        };
        struct type_1_value_t : public type_value_t
        {
            type_1_value_t(unsigned char type, unsigned char value) : type_value_t(type, value){}
            void print() const;
        };
        struct type_2_value_t : public type_value_t
        {
            type_2_value_t(unsigned char type, unsigned char value) : type_value_t(type, value){}
            void print() const;
        };
        struct type_3_value_t : public type_value_t
        {
            type_3_value_t(unsigned char type, unsigned char value) : type_value_t(type, value){}
            void print() const;
        };

    vector<shared_ptr<type_value_t> > _tv_vector;
};

// parse binary input array
bool tv_parser::init(const unsigned char* bytes, int size)
{
    // sanity check
    if (bytes == nullptr || size <= 0)
    {
        cerr << FILE_LINE << "ERROR : bad input data" << endl;
        return false;
    }
    if (size < 2)
    {
        cerr << FILE_LINE << "ERROR: unsufficient data" << endl;
        return false;
    }
    if (size % 2)
    {
        cerr << FILE_LINE << "WARNING : last value is missing for type " <<  (unsigned)bytes[size-1] << endl;
    }
    // empty vector of tv pairs
    _tv_vector.clear();

   for (int i=0; i+1 < size; i += 2)
   {
      const unsigned char& type  = bytes[i];
      const unsigned char& value = bytes[i+1];
      // add Type-Value pairs to corresponded objects
      switch(type)
        {
        case Type_0: _tv_vector.push_back(shared_ptr<type_value_t>(new type_0_value_t(type, value)));
                     break;
        case Type_1: _tv_vector.push_back(shared_ptr<type_value_t>(new type_1_value_t(type, value)));
                     break;
        case Type_2: _tv_vector.push_back(shared_ptr<type_value_t>(new type_2_value_t(type, value)));
                     break;
        case Type_3: _tv_vector.push_back(shared_ptr<type_value_t>(new type_3_value_t(type, value)));
                     break;
        default:     cerr << FILE_LINE << "ERROR: unexpected Type " << (unsigned)type << endl;
        }
   }
    if (_tv_vector.empty())
    {
        cerr << FILE_LINE << "WARNING: no Type-Values were parsed" << endl;
        return false;
    }
    return true;
}

// print parsed TypeValue pairs
void tv_parser::print() const
{
    for (auto tv : _tv_vector)
        tv->print();
}

// Type specific print member functions
void tv_parser::type_0_value_t::print() const
{
     cout << "type: 0 value: " << (unsigned)_value << endl;
}

void tv_parser::type_1_value_t::print() const
{
     cout << "type: 1 value: " << (unsigned)_value << endl;
}

void tv_parser::type_2_value_t::print() const
{
     cout << "type: 2 value: " << (unsigned)_value << endl;
}

void tv_parser::type_3_value_t::print() const
{
     cout << "type: 3 value: " << (unsigned)_value << endl;
}

// ============== Parser Implementation end =======================

// Test functioin helper
int test(const char* test_name, const unsigned char* bytes, int size)
{
    cout << "-----------------------------------------------------------" << endl;
    cout << "Testing: " <<  test_name << endl;
    tv_parser parser;
    if (parser.init(bytes, size))
        parser.print();
    return 0;
}

int main()
{
    unsigned char bytes[] = {3, 253, 0, 126, 0, 53, 3, 181, 2, 12};
    test("Sample data", bytes, sizeof(bytes));
    test("Bad input data", 0, sizeof(bytes));
    test("Bad input data size", bytes, -1);
    unsigned char bytes1[] = {1, 253, 0};
    test("Last value is missing", bytes1, sizeof(bytes1));
    unsigned char bytes2[] = {1};
    test("Insufficient input array", bytes2, sizeof(bytes2));
    unsigned char bytes3[] = {5, 253, 0, 126};
    test("Bad tag", bytes3, sizeof(bytes3));
    cout << "-----------------------------------------------------------" << endl;

    // tv_parser parser;
    // if (parser.init(bytes, sizeof (bytes)))
    //     parser.print();
    return 0;
}