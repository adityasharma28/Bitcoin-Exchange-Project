# Bitcoin-Exchange-Project
This project is about Bitcoin exchange rate that will fetch the most up-to-date exchange rates for different currencies and report them to the user. For this, we will use an interesting library stack including some of the STL. To work on this project, I'm going to employ the use of two libraries, libcurl and JSON for modern C++. We will use the libcurl to make the web calls to the JSON API and then we will use the JSON parser to read the response and build the data structures for us to use to access this data.

Libcurl can be found here "https://curl.haxx.se/download.html".
Libcurl is actually a C library and not
a C++ library, so we will use some of the
C++ STL utilities to make it more C++
friendly. For the JSON parsing, we will be
using the library nlohmann/json found
 at GitHub. This is a C++ 11 style
JSON parsing and building library that is
available as a single header file. To
download curl, go to the website curl dot
haxx dot SE slash download HTML ,and then go to the download page
and click download. Or if you're more
familiar with Git and GitHub, you can
just clone the repository and copy the
file into the working directory. Once you
have that file into your working
directory, also create another file
called Bitcoin.CPP. So in order to get
started, you should have Bitcoin cpp and
JSON HPP.
