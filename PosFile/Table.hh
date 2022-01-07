#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

struct Table
{
    static char* Trim(const char *str) ; 
    static void TrimSplit( const char* str, char delim,   std::vector<std::string>& elem ); 
    static const char* Get( const char* table, const char* key, int column_match, int column_get ); 
    static void Dump(const char* table);
    static void DumpColumns(const char* table, const char* key, int column_match, int num_columns ); 
}; 


inline char* Table::Trim(const char *str) 
{
    char* s = strdup(str); 
    char* e = s + strlen(s) - 1 ;

    while(*s == ' ') s++ ;
    while (e > s && *e == ' ') e-- ;   
    *(e+1) = '\0';

    return s ;
}

inline void Table::TrimSplit( const char* str, char delim,   std::vector<std::string>& elem )
{
    std::stringstream ss; 
    ss.str(str)  ;
    std::string s;
    while (std::getline(ss, s, delim)) elem.push_back(Trim(s.c_str())) ;  
}


inline void Table::Dump(const char* table)
{
    std::stringstream ss(table) ; 
    std::string s ; 
    while(std::getline(ss, s))
    {
        std::vector<std::string> elem ; 
        TrimSplit(s.c_str(), '|', elem ); 
        if( elem.size() != 6 ) continue ; 

        std::cout << std::setw(5) << elem.size() << " " <<  s << std::endl ; 
        for(unsigned i=0 ; i < elem.size() ; i++ ) std::cout << "[" << elem[i] << "]" << std::endl ; 
    }
}

inline void Table::DumpColumns(const char* table, const char* key, int column_match, int num_columns )
{
    std::cout 
        << " key " << key 
        << " column_match " << column_match
        << " num_columns " << num_columns
        << std::endl
        ; 
    for( int column=0 ; column < num_columns ; column++ )
    { 
        const char* val = Get(table, key, column_match, column ); 
        std::cout 
            << std::setw(5) << column  
            << " : "
            << ( val ? val : "-" ) 
            << std::endl
            ; 
    }
}


inline const char* Table::Get(const char* table, const char* key, int column_match, int column_get )
{
    const char* ret = nullptr ; 
    std::stringstream ss(table) ; 
    std::string s ; 
    while(std::getline(ss, s))
    {
        std::vector<std::string> column ; 
        TrimSplit(s.c_str(), '|', column ); 
        int num_column = column.size(); 
        if(column_match < 0 ) column_match += num_column ; 
        if(column_get < 0 )   column_get += num_column ; 
        if(!(column_match < num_column && column_get < num_column )) continue ; 

        const char* matcher = column[column_match].c_str(); 
        if( strcmp(matcher, key)==0 ) ret = strdup(column[column_get].c_str()) ;  
    }
    return ret ; 
}




