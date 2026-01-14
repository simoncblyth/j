#!/bin/bash 

usage(){ cat << EOU

Use this to copy betwee j/<branch> and the junosw branch directory
without fiddling with git::

   ~/j/oj_copy.sh 

EOU
}

js_base=$HOME/junosw
js_branch=$(cd $js_base ; git branch --show-current)
j_base=$HOME/j/$js_branch

names="Examples/Tutorial/share/opticks_juno.sh oj_initialize.sh"


defarg=info
arg=${1:-$defarg}

vv="js_base js_branch j_base PWD defarg arg names"
for v in $vv ; do printf "# %30s : %s\n" "$v" "${!v}" ; done


for name in $names
do
    j_path=$j_base/$(basename $name) 
    js_path=$js_base/$name

    js2j="cp $js_path $j_path   # JS2J "
    j2js="cp $j_path $js_path   # J2JS "
    jdif="diff $j_path $js_path # JDIF"

    cc="js2j j2js jdif"
    for c in $cc ; do printf "# %30s : %s\n" "$c" "${!c}" ; done

    if [ "$arg" == "J2JS" ]; then

         echo $j2js
         eval $j2js

    elif [ "$arg" == "JS2J" ]; then

        echo $js2j
        eval $js2j

    elif [ "$arg" == "JDIF" ]; then

       echo $jdif
       eval $jdif

    fi
done



