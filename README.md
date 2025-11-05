JSON Lib
===
A simple C++ header-only library for reading and saving JSON files.  
Developed in C++17 and compatible with earlier versions.  
(Tested on Linux but should also work on Windows.)

## Files Explanation

The library is divided into 5 files:

* **Json.hpp** — *Contains functions for saving to and loading from a file.*
* **Struct.hpp** — *Contains the **Dictionnary** structure used to hold the JSON data.*
* **Serializer.hpp** — *Contains functions to convert a Dictionnary into a string or write it to a specific file descriptor.*
* **Parser.hpp** — *Contains the function that parses a string into a Dictionnary, along with all its helper functions.*
* **Utils.hpp** — *Contains various helper functions such as `trim`, and color definitions for printing the Dictionnary.*

The entire library resides within the **JSONLib** namespace and its sub-namespaces **Parser**, **Serializer**, and **Utils**.

## How to Use

There are three main functions provided:

---

### LoadJSON

*Json.hpp*
```cpp
Dictionnary LoadJSON(const std::string &path)
```
Creates a Dictionnary by reading the JSON file located at path and returns it.

#### Parameters
* **path**: *The path of the file to read.*

#### Exemple

```cpp
int main()
{
    const std::string path = "./Test/simple.json";
    JSONLib::Dictionnary dict = JSONLib::LoadJSON(path);
}
```
Where `Test/simple.json` looks like this:

```json
{
    "testing": {
        "5" : "77777777"
    }
}
```

### ExportToJSON

*json.hpp*
```cpp
void ExportToJSON(const Dictionnary &dict, const std::string &savePath)
```

Takes a Dictionnary as a parameter and saves it to the given savePath (overwriting the file if it already exists).

#### Parameters
* **dict**: *The Dictionnary to export.*
* **savePath**: *The path to save the file.*

#### Exemple

```cpp
int main()
{
    const std::string iPath = "./Test/simple.json";
    const std::string oPath = "./Test/target.json";
    JSONLib::Dictionnary dict = JSONLib::LoadJSON(iPath);
    JSONLib::ExportToJSON(dict, oPath);
}
```
Where `Test/simple.json` looks like this:

```json
{
    "testing": {
        "5" : "77777777"
    }
}
```

### WriteDictToFD

*json.hpp*
```cpp
void WriteDictToFD(std::ostream &fd, const Dictionnary &dict, size_t offset = 0, bool colored = true)
```

Takes a Dictionnary and a file descriptor to write the Dictionnary into.

#### Parametres
* **fd**: *The file descriptor to write the Dictionnary to. Accepts any class inheriting from **ostream** (**std::cout**, **std::cerr**, **std::stringstream**, **std::ofstream**, etc.).*
* **dict**: *The Dictionnary to write.*
* **offset**: *The indentation in spaces for the first element of the Dictionnary (and +4 for each nested level).*
* **colored**: *Whether to use the colors defined in Utils when writing.*

#### Exemple

```cpp
int main()
{
    const std::string path = "./Test/simple.json";
    JSONLib::Dictionnary dict = JSONLib::LoadJSON(path);
    JSONLib::Serializer::WriteDictToFD(std::cout, dict, 0, true);
}
```
Where `Test/simple.json` looks like this:
```json
{
    "testing": {
        "5" : "77777777"
    }
}
```
