
The library provides two methods: init() and getResult() from the static main class ShortBread
Make sure you use the init() before any other call as the dictionary is downloaded during this function call.

The init() method will call the Dictionary init() that downloads the dictionary
from the given URL (https://www.wordgamedictionary.com/enable/download/enable.txt)
and sorts the words by length into a std::map

The getResult() takes the start and end words as argument (std::string) and after checking for
invalid inputs, calls the private shortBreadAlgo() recursive method, which parses the graph
where nodes are words, and edges are created when 2 words differ from one letter only.
The function return a std::vector of std::string containing the answer. The vector will be empty in case
the input validation fails or no solution was found for the given valid start and end words.

Details of implementation can be found in the code itself in the form of comments.

The libcurl and libcurl4-openssl-dev library must be installed on the target OS before compilation.

Compile with:
$ sudo make clean && make && make install && make install_headers

The shared library file will be added to /usr/lib/libshort-bread.so
The headers will be installed in /usr/include/short-bread/

Follow the Makefile in https://github.com/SoucheSouche/short-bread-test.git for information on how to include the
short-bread library into your project. 