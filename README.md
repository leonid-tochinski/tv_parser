# tv_parser - simple Type-Value parser
by Leonid Tochinski

C and C++ versions present

run make to build both C and C++ targets 

```
./tv_parser_c
-----------------------------------------------------------
Testing: Sample data
5 Type-Values were parsed
type: 3 value: 253
type: 0 value: 126
type: 0 value: 53
type: 3 value: 181
type: 2 value: 12
-----------------------------------------------------------
Testing: Bad input data
tv_parser_c.c(59):  ERROR: bad input params
-----------------------------------------------------------
Testing: Bad input data size
tv_parser_c.c(59):  ERROR: bad input params
-----------------------------------------------------------
Testing: Last value is missing
tv_parser_c.c(70):  WARNING : last value is missing for type 0
1 Type-Values were parsed
type: 1 value: 253
-----------------------------------------------------------
Testing: Insufficient input array
tv_parser_c.c(65):  ERROR: unsufficient data
-----------------------------------------------------------
Testing: Bad Type
tv_parser_c.c(84):  WARNING: unexpected Type 5
1 Type-Values were parsed
type: 0 value: 126
-----------------------------------------------------------
```

```
./tv_parser
-----------------------------------------------------------
Testing: Sample data
type: 3 value: 253
type: 0 value: 126
type: 0 value: 53
type: 3 value: 181
type: 2 value: 12
-----------------------------------------------------------
Testing: Bad input data
tv_parser.cpp(91): ERROR : bad input data
-----------------------------------------------------------
Testing: Bad input data size
tv_parser.cpp(91): ERROR : bad input data
-----------------------------------------------------------
Testing: Last value is missing
tv_parser.cpp(101): WARNING : last value is missing for type 0
type: 1 value: 253
-----------------------------------------------------------
Testing: Insufficient input array
tv_parser.cpp(96): ERROR: unsufficient data
-----------------------------------------------------------
Testing: Bad Type
tv_parser.cpp(121): ERROR: unexpected Type 5
type: 0 value: 126
-----------------------------------------------------------
```
