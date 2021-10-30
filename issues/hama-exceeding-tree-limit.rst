hama-exceeding-tree-limit
===========================



::

    2021-10-30 02:52:35.804 FATAL [51280] [ORng::setSkipAhead@155] skipahead 0
    [New Thread 0x7ffd660f7700 (LWP 59116)]
    // evaluative_csg repeat_index 3 tranOffset 9 numParts 511 perfect tree height 8 exceeds current limit
    // evaluative_csg repeat_index 3 tranOffset 18 numParts 511 perfect tree height 8 exceeds current limit
    // evaluative_csg repeat_index 3 tranOffset 9 numParts 511 perfect tree height 8 exceeds current limit
    // evaluative_csg repeat_index 3 tranOffset 18 numParts 511 perfect tree height 8 exceeds current limit
    // evaluative_csg repeat_index 3 tranOffset 9 numParts 511 perfect tree height 8 exceeds current limit
    // evaluative_csg repeat_index 3 tranOffset 18 numParts 511 perfect tree height 8 exceeds current limit


    2021-10-30 22:57:37.726 FATAL [100986] [ORng::setSkipAhead@155] skipahead 0
    [New Thread 0x7ffd660f7700 (LWP 108133)]
    // evaluative_csg repeat_index 3 primIdx 3 tranOffset 9 numParts 511 perfect tree height 8 exceeds current limit
    // evaluative_csg repeat_index 3 primIdx 4 tranOffset 18 numParts 511 perfect tree height 8 exceeds current limit
    // evaluative_csg repeat_index 3 primIdx 3 tranOffset 9 numParts 511 perfect tree height 8 exceeds current limit
    // evaluative_csg repeat_index 3 primIdx 4 tranOffset 18 numParts 511 perfect tree height 8 exceeds current limit
    // evaluative_csg repeat_index 3 primIdx 3 tranOffset 9 numParts 511 perfect tree height 8 exceeds current limit
    // evaluative_csg repeat_index 3 primIdx 4 tranOffset 18 numParts 511 perfect tree height 8 exceeds current limit
    2021-10-30 22:57:37.912 INFO  [100986] [OPropagator::launch@285] 0 : (0;10965,1)  launch time 0.186613
    2021-10-30 22:57:37.913 INFO  [100986] [OpIndexer::indexSequenceCompute@237] OpIndexer::indexSequenceCompute
    2021-10-30 22:57:37.929 INFO  [100986] [OEvent::downloadHits@505]  nhit 4209 --dbghit N hitmask 0x40 SD SURFACE_DETECT



mm 3 has 1301 parts, because the tubs intersection is not handled in balancing::

    2021-10-30 22:55:34.176 INFO  [100986] [OGeo::makeOGeometry@683] ugeocode [A]
    2021-10-30 22:55:34.176 INFO  [100986] [OGeo::makeAnalyticGeometry@767]  skip GParts::close 
    2021-10-30 22:55:34.176 INFO  [100986] [OGeo::makeAnalyticGeometry@770] mm 3 verbosity: 0   pts:  GParts  primflag         flagnodetree numParts 1301 numPrim    7
    2021-10-30 22:55:34.176 INFO  [100986] [OGeo::makeAnalyticGeometry@797]  mmidx 3 numInstances 5000 numPrim 7 idBuf 5000,7,4
    2021-10-30 22:55:34.177 INFO  [100986] [OGeo::makeMaterial@590] [
    2021-10-30 22:55:34.177 INFO  [100986] [OGeo::makeMaterial@598]  angular 0 ch_module closest_hit_propagate.cu ch_func closest_hit_propagate
    2021-10-30 22:55:34.177 INFO  [100986] [OGeo::makeMaterial@605] ]
    2021-10-30 22:55:34.319 INFO  [100986] [OGeo::convertMergedMesh@367] ) 3 numInstances 5000
    2021-10-30 22:55:34.319 INFO  [100986] [OGeo::convertMergedMesh@334] ( 4



::


    2021-10-30 22:54:02.448 FATAL [100986] [NTreeBalance<T>::create_balanced@109] unable_to_balance : balancing not-implemented for trees of this structure  treeidx 110
    2021-10-30 22:54:02.448 ERROR [100986] [NTreeProcess<T>::init@163]  unable_to_balance treeidx 110 NTreeAnalyse::Desc 
    NTreeAnalyse height 8 count 17
                                                                  in    

                                                          un          cy

                                                  un          cy        

                                          un          cy                

                                  un          zs                        

                          un          cy                                

                  un          co                                        

          un          zs                                                

      zs      cy                                                        


    inorder (left-to-right) 
     [ 0:zs] P HamamatsuR12860_PMT_20inch_pmt_solid_I_ellipsoid 
     [ 0:un] C un 
     [ 0:cy] P HamamatsuR12860_PMT_20inch_pmt_solid_II_difference 
     [ 0:un] C un 
     [ 0:zs] P HamamatsuR12860_PMT_20inch_pmt_solid_III_ellipsoid 
     [ 0:un] C un 
     [ 0:co] P HamamatsuR12860_PMT_20inch_pmt_solid_IV0_zp_cone 
     [ 0:un] C un 
     [ 0:cy] P HamamatsuR12860_PMT_20inch_pmt_solid_V_difference 
     [ 0:un] C un 
     [ 0:zs] P HamamatsuR12860_PMT_20inch_pmt_solid_VI_ellipsoid 
     [ 0:un] C un 
     [ 0:cy] P HamamatsuR12860_PMT_20inch_pmt_solid_VIII_difference 
     [ 0:un] C un 
     [ 0:cy] P HamamatsuR12860_PMT_20inch_pmt_solid_IX0_zp_cylinder 
     [ 0:in] C in 
     [ 0:cy] P CutPMT_HamaPMT_Solid_difference 





A tree within Hama instance is exceeding limit.  Added primIdx dumping.::

    0707 static __device__
     708 void evaluative_csg( const Prim& prim, const int primIdx )   // primIdx just used for identity access
     709 {
     710     unsigned partOffset = prim.partOffset() ;
     711     unsigned numParts   = prim.numParts() ;
     712     unsigned tranOffset = prim.tranOffset() ;
     713  
     714     Part pt0 = partBuffer[partOffset + 0] ; 
     715     unsigned boundary = pt0.boundary() ;
     716  
     717  
     718     unsigned height = TREE_HEIGHT(numParts) ; // 1->0, 3->1, 7->2, 15->3, 31->4 
     719  
     720 #ifdef USE_TWIDDLE_POSTORDER
     721     if(height > 7) 
     722     {    
     723         rtPrintf("// evaluative_csg repeat_index %d primIdx %d tranOffset %u numParts %u perfect tree height %u exceeds current limit\n", repeat_index, primIdx, tranOffset, numParts, height )      ;    
     724         return ;
     725     }    


    425 RT_PROGRAM void intersect(int primIdx)
    426 {
    427     const Prim& prim    = primBuffer[primIdx];    // Prim wraps int4 
    428 
    429     unsigned partOffset  = prim.partOffset() ;
    430     unsigned numParts    = prim.numParts() ;
    431     unsigned primFlag    = prim.primFlag() ;
    432 
    433     if(primFlag == CSG_FLAGNODETREE)
    434     {    
    435         evaluative_csg( prim, primIdx );
    436     }    







