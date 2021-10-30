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


A stree within Hama instance is exceeding limit.  Added primIdx dumping.::

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







