int get_pmtQuasiContiguousIndex(int pmtID ) const
{
    int idx = -1 ;
    if(pmtID<18000)           //  0:18000 for LPMT 
    {
        idx = pmtID ;
    }
    else if( pmtID<300000 )    //  18000:22000  for vetoPMT   (space for 4000)  
    {
        idx = 18000 + pmtID - vetoPMTidStart  ;  // hmm do not know where veto pmtID start
    }
    else if(pmtID>=300000)     //  22000:47600   for SPMT     (nominally 25600, but with headroom for more)
    {
        idx = 18000 + 4000 + pmtID - 300000 ;
    }

    assert( idx > -1 && idx < 65536); 

    int quasiContiguousIdx = idx ; 
    int pmtID_check = get_pmtId_from_quasiContiguousIndex( quasiContiguousIdx ); 
    assert(  pmtID_check == pmtID ); 

    return quasiContiguousIdx  ;
}


int get_pmtId_from_quasiContiguousIndex( int quasiContiguousIdx ) const 
{
     int idx = quasiContiguousIdx ; 
     int pmtId = -1 ; 
     if( idx < 18000 )
     {
          pmtId = idx ; 
     }
     else if( idx < 18000 + 4000 )
     {
          pmtId = idx - 18000 + vetoPMTidStart  ; 
     }
     else if( idx < 18000 + 4000 + 25600 )
     {
          pmtId = idx - ( 18000 + 4000 ) + 3000000 ; 
     }

     int idx_check = get_pmtQuasiContiguousIndex( pmtId ); 
     assert( idx_check == idx ); 

     return pmtId ; 
}









/**
get_pmtContiguousIndex
------------------------

Returns the index of the pmtID within the sorted list of all 
pmtID providing a strictly contiguous(no gaps) index.  
If the pmtID argument is not in the list of all pmtIDs 
then -1 is returned. 

**/

int get_pmtContiguousIndex(int pmtID) const
{
    const std::vector<int>& a = m_all_pmtID ; 
    size_t idx = std::distance( a.begin(), std::find( a.begin(), a.end(), pmtID )) ; 
    return idx < a.size() ? int(idx) : -1 ; 
}

/**
get_pmtId_from_ContiguousIndex
-------------------------------

Returns the pmtID corresponding to the index provided.
If the index is out of range of the list of all pmtID then -1 is returned. 

**/

int get_pmtId_from_ContiguousIndex(int idx) const
{
    const std::vector<int>& a = m_all_pmtID ; 
    return idx > -1 && idx < a.size() ? a[idx] : -1 ; 
}

/**
getQEData
-------------

Assuming there is a member vector *m_all_pmtID* 
with the pmtID ints sorted in ascending order.

**/

void getQEData(std::vector<double>& qe_data, double en0, double en1, unsigned num_edep  ) const 
{
    const std::vector<int>& a = m_all_pmtID ; 

    qe_data.clear();
    qe_data.resize( num_idx*num_edep );  
 
    double* qe_data_ = qe_data.data() ;   

    for(int idx=0 ; idx < a.size() ; idx++ )
    {   
       int pmtID = a[idx] ; 
       int idx_check = get_pmtContiguousIndex(pmtID); 
       assert( idx == idx_check );   

       for(unsigned j=0 ; j < num_edep ; j++)
       {   
           double efrac = double(j)/double(num_edep) ; 
           double edep = en0 + (en1 - en0)*efrac ; 
           double qe = get_pmtid_qe(pmtID,edep);

           qe_data_[ idx*num_edep + j ] = qe ;    
       }   
    }   
}


const std::vector<int>& get_all_pmtID() const
{
    return m_all_pmtID ; 
}


/**

Using a strictly contiguous index with absolutely no gaps simplifies the above methods 
and also has another crucial advantage in that it allows the mapping between 
JUNO specific pmtID and the non-detector specific (contiguous) sensor index 
to be done without having access to the service.  

This is because Opticks can grab the sorted list of all pmtIDs from the 
service once and subsequently use that list in Opticks non-detector specific 
code where there is no way to access the JUNO specific service. 

As a result during the Opticks translation of geometry when it traverses
all the volumes and finds ones that are sensitive it can use the copyNo 
of the volumes (which is pmtID) together with the sorted list of 
of all pmtID to get the contiguous index.   So the Opticks
geometry can be labelled with this contiguous index allowing the 
appropriate values from the GPU QE and CE textures to be accessed. 


**/





