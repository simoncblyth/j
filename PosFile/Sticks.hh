#pragma once
struct Sticks
{
    static const char* TABLE ; 
    static const char* GetClass(  const char* member) ; 
    static const char* GetPosFile(const char* member) ; 
    static const char* GetRadius( const char* member) ; 
    static const char* GetNote(  const char* member) ; 
    static void Dump(const char* member); 
};

const char* Sticks::TABLE = R"LITERAL(
+-----------------------------+----------------------------------+-------------------------+------------------------+----------------------+
|  member                     |  class                           | pos_file                | radius                 |  notes               |
+=============================+==================================+=========================+========================+======================+
| m_strut_name                | StrutAcrylicConstruction         | m_strut_pos_file        | strut_r                |                      |
+-----------------------------+----------------------------------+-------------------------+------------------------+----------------------+
| m_strut2_name               | StrutBar2AcrylicConstruction     | m_strut2_pos_file       | strut2_r               |                      |
+-----------------------------+----------------------------------+-------------------------+------------------------+----------------------+
| m_strutballhead_name        | StrutBallheadAcrylicConstruction | m_fastener_pos_file     | strutballhead_r        |                      |
+-----------------------------+----------------------------------+-------------------------+------------------------+                      |
| m_fastener_name             | FastenerAcrylicConstruction      | m_fastener_pos_file     | fastener_r             | 4 users of           |
+-----------------------------+----------------------------------+-------------------------+------------------------+ one pos_file         |
| m_upper_name                | UpperAcrylicConstruction         | m_fastener_pos_file     | upper_r                |                      |
+-----------------------------+----------------------------------+-------------------------+------------------------+                      |
| m_addition_name             | AdditionAcrylicConstruction      | m_fastener_pos_file     | addition_r             |                      |
+-----------------------------+----------------------------------+-------------------------+------------------------+----------------------+
| m_xjanchor_name             | XJanchorConstruction             | m_xjanchor_pos_file     | xjanchor_r             |                      |
+-----------------------------+----------------------------------+-------------------------+------------------------+----------------------+
| m_xjfixture_name            | XJfixtureConstruction            | m_xjanchor_pos_file     | xjfixture_r            | out of pattern, bug? |
+-----------------------------+----------------------------------+-------------------------+------------------------+----------------------+
| m_sjclsanchor_name          | SJCLSanchorConstruction          | m_sjclsanchor_pos_file  | sjclsanchor_r          |                      |
+-----------------------------+----------------------------------+-------------------------+------------------------+----------------------+
| m_sjfixture_name            | SJFixtureConstruction            | m_sjfixture_pos_file    | sjfixture_r            |                      |
+-----------------------------+----------------------------------+-------------------------+------------------------+----------------------+
| m_sjreceiver_name           | SJReceiverConstruction           | m_sjreceiver_pos_file   | sjreceiver_r           |                      |
+-----------------------------+----------------------------------+-------------------------+------------------------+----------------------+
| m_sjreceiver_fastener_name  | XJfixtureConstruction            | m_sjreceiver_pos_file   | sjreceiver_fastener_r  | out of pattern, bug? |
+-----------------------------+----------------------------------+-------------------------+------------------------+----------------------+
)LITERAL" ; 

#include "Table.hh"

inline const char* Sticks::GetClass(  const char* member) { return Table::Get(TABLE, member, 1, 2) ; }
inline const char* Sticks::GetPosFile(const char* member) { return Table::Get(TABLE, member, 1, 3) ; }
inline const char* Sticks::GetRadius( const char* member) { return Table::Get(TABLE, member, 1, 4) ; }
inline const char* Sticks::GetNote(  const char* member)  { return Table::Get(TABLE, member, 1, 5) ; }

inline void Sticks::Dump(const char* member)
{
    int column_match = 1 ; 
    int num_columns = 6 ; 
    Table::DumpColumns(TABLE,  member, column_match, num_columns ); 
}
 
