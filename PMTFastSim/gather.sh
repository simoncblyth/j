#!/bin/bash -l 

usage(){ cat << EOU


   Matrix.h  : TComplex.h              # MATRIX, Matrix
   Matrix.cc : Matrix.h  

   Material.h  : TComplex.h 
   Material.cc : Material.h            #  static material map 

   Layer.h   : Matrix.h Material.h      # Layer, ThickLayer, ThinLayer 
   Layer.cc  : Layer.h  



   OpticalSystem.h  :   Layer.h         # vector of layers with ThickLayer top_layer bot_layer    
   OpticalSystem.cc :   TString.h       # TMath::Sin TMath::Cos TMath::Sqrt TComplex::Sqrt TString?Form 


   MultiFilmModel.h  :  TComplex.h           #   ART
   MultiFilmModel.cc :  MultiFilmModel.h Matrix.h OpticalSystem.h    # contains optical_system and Matrix Ms Mp  TComplex::Conjugate
                 

   junoPMTOpticalModel.h  : many G4 headers, Sniper, Svcs and MultiFilmSimSvc/MultiFilmModel.h   m_multi_film_model
   junoPMTOpticalModel.cc : m_multi_film_model = new MultiFilmModel(4);





EOU
}




gather()
{
    local srcbase=$JUNOTOP/junosw
    local dstbase=$HOME/j/PMTFastSim
    cd $srcbase
    local path
    local name
    local src
    local dst
    local cmd

    for path in $(jcl $*) ; do
       path=${path:2}  # remove ./ prefix
       name=$(basename $path)
       src=$srcbase/$path
       dst=$dstbase/$name
       if [ -f "$dst" ]; then
            #cmd="echo $dst already gathered : delete it and rerun to copy again"
            cmd="echo -n"
       else
            cmd="cp $src $dst"  
       fi
       #echo path $path name $name src $src dst $dst 
       echo $cmd 
    done
}

gather MultiFilmModel Matrix OpticalSystem Layer Material


