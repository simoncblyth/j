LSExpDetectorConstruction_setupCD_Sticks
=========================================



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
| m_xjfixture_name            | XJfixtureConstruction            | *m_xjanchor_pos_file*   | xjfixture_r            | out of pattern, bug? | 
+-----------------------------+----------------------------------+-------------------------+------------------------+----------------------+    
| m_sjclsanchor_name          | SJCLSanchorConstruction          | m_sjclsanchor_pos_file  | sjclsanchor_r          |                      |
+-----------------------------+----------------------------------+-------------------------+------------------------+----------------------+
| m_sjfixture_name            | SJFixtureConstruction            | m_sjfixture_pos_file    | sjfixture_r            |                      |
+-----------------------------+----------------------------------+-------------------------+------------------------+----------------------+
| m_sjreceiver_name           | SJReceiverConstruction           | m_sjreceiver_pos_file   | sjreceiver_r           |                      |
+-----------------------------+----------------------------------+-------------------------+------------------------+----------------------+
| m_sjreceiver_fastener_name  | *XJfixtureConstruction*          | *m_sjreceiver_pos_file* | sjreceiver_fastener_r  | out of pattern, bug? |
+-----------------------------+----------------------------------+-------------------------+------------------------+----------------------+


   declProp              csv

   StrutPosFile          Strut_Acrylic.csv             370
   Strut2PosFile         StrutBar2_Acrylic.csv         220
   FastenerPosFile       Strut_Anchor_Acrylic.csv      590
   XJanchorPosFile       XJanchor.csv                  56
   SJCLSanchorPosFile    SJCLSanchor.csv               2
   SJReceiverPosFile     SJReceiverPos.csv             8
   SJFixturePosFile      SJFixturePos.csv              36




