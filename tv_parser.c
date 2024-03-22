
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
#include <stdio.h>
#include <stdbool.h>

// error print helper macros
#define STRINGIZE_DETAIL(x) #x
#define STRINGIZE(x) STRINGIZE_DETAIL(x)
#define FILE_LINE __FILE__ "(" STRINGIZE(__LINE__) "): "

// Type-Value entry
typedef struct
{
    unsigned char type;
    unsigned char value;
} type_value_t;

// supported types
enum {Type_1=0, Type_2=1, Type_3=2, Type_4=3};

//
bool tv_parser(const unsigned char* bytes, int size, type_value_t* tv_vector, int* tv_vector_size)
{
    // sanity check
    if (bytes == NULL || size <= 0)
    {
        fprintf(stderr,"%s ERROR: bad input params\n", FILE_LINE);
        return false;
    }
    if (size % 2)
    {
        fprintf(stderr,"%s WARNING : last value is missing\n", FILE_LINE);
    }
    if (tv_vector == NULL || *tv_vector_size < size/2)
    {
         fprintf(stderr,"%s ERROR: output Type-Value array doesn't have enough space\n", FILE_LINE);
         return false;
    }
    // parse Type-Value vector
    type_value_t* tv_ptr = tv_vector;
    for (int i=0; i+1 < size; i += 2)
    {
        if (bytes[i] > Type_4)
        {
            fprintf(stderr,"%s WARNING: unexpected Type %u\n", FILE_LINE, (unsigned)bytes[i]);
            continue;
        }
        tv_ptr->type  = bytes[i];
        tv_ptr->value = bytes[i+1];
        ++tv_ptr;
    }
    *tv_vector_size = tv_ptr - tv_vector;
    if (!*tv_vector_size)
    {
        fprintf(stderr,"%s WARNING : no Type-Values were parsed\n", FILE_LINE);
        return false;
    }
    printf("%d Type-Values were parsed\n", *tv_vector_size);
    return true;
}

void print_type_0(const type_value_t* tv)
{
    printf("type: 0 value: %d\n", (unsigned)tv->value);
}

void print_type_1(const type_value_t* tv)
{
    printf("type: 1 value: %d\n", (unsigned)tv->value);
}

void print_type_2(const type_value_t* tv)
{
    printf("type: 2 value: %d\n", (unsigned)tv->value);
}

void print_type_3(const type_value_t* tv)
{
    printf("type: 3 value: %d\n", (unsigned)tv->value);
}

typedef void (*print_func_t)(const type_value_t* tv);
print_func_t print_func[] =
{
    print_type_0,
    print_type_1,
    print_type_2,
    print_type_3
};

void print_tv(const type_value_t* tv_vector, int tv_vector_size)
{
    // sanity check
   if (tv_vector == NULL || tv_vector_size <= 0)
   {
      fprintf(stderr,"%s ERROR: bad input params\n", FILE_LINE);
      return;
   }
   for (int i = 0; i < tv_vector_size; ++i)
   {
       if (tv_vector[i].type > Type_4)
       {
           fprintf(stderr,"%s WARNING: unexpected Type %u\n", FILE_LINE, (unsigned)tv_vector[i].type);
           continue;
        }
    (*print_func[tv_vector[i].type])(&tv_vector[i]);
   }
}

int main()
{
    unsigned char bytes[] = {3, 253, 0, 126, 0, 53, 3, 181, 2, 12};
    int tv_vector_size = sizeof(bytes)/2;
    type_value_t tv_vector[tv_vector_size];
    tv_parser(bytes, sizeof (bytes), tv_vector, &tv_vector_size);
    print_tv(tv_vector, tv_vector_size);
    return 0;
}