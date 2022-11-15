#ifndef utils_hh
#define utils_hh

#ifdef PMTSIM_STANDALONE
#define LogError std::cerr
#endif


#include <cctype>
#include <vector>
#include <sstream>
#include <boost/filesystem.hpp>
#include <boost/tokenizer.hpp>
#include "boost/tuple/tuple.hpp"
#include "boost/tuple/tuple_io.hpp"

#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4Types.hh"
static const bool MYDEBUG = false;

static std::map<std::string, G4double> unit2value = {
{"g/cm2/MeV",1*g/cm2/MeV},
{"(g/cm2/MeV)*(g/cm2/MeV)",1*(g/cm2/MeV)*(g/cm2/MeV)}
};

template<typename T1>
bool with_units(T1& val, std::string unit) {
    // detect
    if (MYDEBUG) std::cout << "(I) detect unit: " << unit << std::endl;
    // remove start * or /
    bool op = true; // by default, multiply
    if (unit[0] == '*') {
        unit.erase(0, 1);
    } else if (unit[0] == '/') {
        op = false;
        unit.erase(0, 1);
    }
    if (MYDEBUG) std::cout << "(II) detect unit: " << unit << std::endl;
    
    double unit_val = 0;
    if(unit2value.count(unit)){
       unit_val = unit2value[unit];
    }    
    else{
       unit_val = G4UnitDefinition::GetValueOf(unit);
    }

    if(!unit_val){
       LogError<<"can't find unit "<<unit<<" in MCParamsFileSvc::unit2value. Please register it at first!!!"<<std::endl;
       exit(-1);
    }
    if (MYDEBUG) std::cout << "(III) detect unit: " << unit << " " << unit_val << std::endl;

    if (op) {
        val *= unit_val;
    } else {
        val /= unit_val;
    }
    if (MYDEBUG) std::cout << "(IV) detect unit: " << unit << " final value: " << val << std::endl;

    return true;
}
template<>
inline bool with_units(std::string& /* val */, std::string /*unit*/) {
    std::cout << "string val don't support arithmetic." << std::endl;
    return false;
}

// template function helper
template<typename T1, typename T2>
bool get_implv1(const std::string& path, 
        std::vector< boost::tuple<T1, T2> >& props)
{
    namespace fs = boost::filesystem;
   
    fs::path fullp(path);
    
    typename boost::tuple<T1, T2> elem;

    std::ifstream ifs(fullp.string().c_str());
    while (ifs.good()) {
            std::string temp_line;
            std::getline(ifs, temp_line);

            // skip comments, starts with '#'
            temp_line.erase( std::find( temp_line.begin(), temp_line.end(), '#' ), temp_line.end() );

            // std::cout << "TEMP LINE: " << temp_line << std::endl;
            std::stringstream ss;
            ss << temp_line;
            // ============================
            // First Element
            // ============================
            ss >> elem.template get<0>();
            // ss >> elem;
            if (ss.fail()) { continue; }

            char c = ss.get();
            while (isspace(c)) {
                c = ss.get();
                if (ss.fail()) { return false; }
            }
            ss.unget();
            if (!isdigit(c)) {
                // could be unit
                std::string unit_1st;
                ss >> unit_1st;
                if (!ss.fail()) {
                     with_units(elem.template get<0>(), unit_1st);
                }
            }

            // ============================
            // Second Element
            // ============================
            ss >> elem.template get<1>();
            if (ss.fail()) { continue; }
            // try detect unit
            std::string unit_2nd;
            ss >> unit_2nd;
            if (!ss.fail()) {
                with_units(elem.template get<1>(), unit_2nd);
            }

            // std::cout << "After parsed: " << elem << std::endl;
            props.push_back(elem);
        }
    return true;
}

// Parse the whole string as stringstream
template<typename T1, typename T2>
bool parse_implv1(const char* strcontent, 
        std::vector< boost::tuple<T1, T2> >& props)
{
    std::stringstream ifs(strcontent);

    typename boost::tuple<T1, T2> elem;


    while (ifs.good()) {
        std::string temp_line;
        std::getline(ifs, temp_line);

        // skip comments, starts with '#'
        temp_line.erase( std::find( temp_line.begin(), temp_line.end(), '#' ), temp_line.end() );

        // std::cout << "TEMP LINE: " << temp_line << std::endl;
        std::stringstream ss;
        ss << temp_line;
        // ============================
        // First Element
        // ============================
        ss >> elem.template get<0>();
        // ss >> elem;
        if (ss.fail()) { continue; }

        char c = ss.get();
        while (isspace(c)) {
            c = ss.get();
            if (ss.fail()) { return false; }
        }
        ss.unget();
        if (!isdigit(c)) {
            // could be unit
            std::string unit_1st;
            ss >> unit_1st;
            if (!ss.fail()) {
                with_units(elem.template get<0>(), unit_1st);
            }
        }

        // ============================
        // Second Element
        // ============================
        ss >> elem.template get<1>();
        if (ss.fail()) { continue; }
        // try detect unit
        std::string unit_2nd;
        ss >> unit_2nd;
        if (!ss.fail()) {
            with_units(elem.template get<1>(), unit_2nd);
        }

        // std::cout << "After parsed: " << elem << std::endl;
        props.push_back(elem);
    }


    return true;
}

#endif
