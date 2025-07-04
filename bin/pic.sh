#!/bin/bash
usage(){ cat << EOU
pic.sh
=======

Invoke this with::

    pic(){ ~/Pictures/pic.sh $* ; }

cur
    sources the cur ~/.opticks/CUR.sh file if existing
    NB thats distinct from ~/.opticks/GEOM/CUR.sh
copy
    copies last Screenshot 


Workflow
---------

1. get into enabled fullscreen app on workstation, eg::

     lo
     ssst.sh ref   

2. open tunnel from laptop to workstation, *tuna*
3. ssh into workstation from laptop "ssh A"
4. within app on workstation setup view and take screenshot
   with "prt sc" function key
5. within "ssh A" session use "pic" function to copy the
   screenshot into directory within BASE


Changing timestamp with touch
------------------------------

::

    touch --date="20250702 17:56:20" /home/blyth/.opticks/CUR.sh
    date --date="20250703 22:07:06" +"%s"

Notes
------

Requires the wayland clipboard::

    sudo dnf install wl-clipboard

EOU

}

SDIR=~/Pictures
[ ! -d $SDIR ] && echo $BASH_SOURCE NO SDIR $SDIR && exit 1 

cd $SDIR

./pic_mv.sh   # remove spaces from names of all png

path=$(ls -1t *.png | head -1)


cur=$HOME/.opticks/CUR.sh
BASE=$HOME/simoncblyth.github.io/env/presentation

allarg="vi_ls_cur_info_open_clip_idx_copy_s5p_s5t"
defarg="cur_info_copy"
arg=${1:-$defarg}

if [ -f $cur ]; then
   tcur=$(stat --format=%Y $cur)
   dcur=$(date -d@$tcur)
   source $cur
else
   cur_msg=cur_DOES_NOT_EXIST
fi
 

vv="BASH_SOURCE BASH_VERSION PWD path BASE allarg defarg arg cur tcur dcur cur_msg CUR"

if [ "${arg/vi}" != "$arg" ]; then
    cmd="vi pic.sh"
    echo $cmd
    eval $cmd
fi 

if [ "${arg/ls}" != "$arg" ]; then
   if [ -f $cur ]; then
       for png in $(ls -1rt *.png) 
       do
            tpng=$(stat --format=%Y $png)
            dpng=$(date -d@$tpng)
            if [ $tpng -gt $tcur ]; then
               tpng_valid=YES
            else
               tpng_valid=NO
            fi  
            printf "# %25s : %s : %s : %s\n" $png $tpng "$dpng" $tpng_valid
       done
   fi
fi 

if [ "${arg/info}" != "$arg" ]; then
   for v in $vv ; do printf "# %30s : %s\n" "$v" "${!v}" ; done
fi


if [ "${arg/open}" != "$arg" ]; then
    cmd="gio open $path"
    echo $cmd
    eval $cmd
fi

if [ "${arg/clip}" != "$arg" ]; then
    cmd="wl-copy -p $path  # copy path to wayland clipboard"
    echo $cmd
    eval $cmd
fi


if [ "${arg/idx}" != "$arg"  ]; then
    if [ -f .index.rst.swp ]; then
        echo $BASH_SOURCE - ALREADY EDITING index.rst
    else
        cmd="vi index.rst"
        echo $cmd
        eval $cmd
    fi
fi



if [ "${arg/copy}" != "$arg" -a -f "$cur" ]; then

   cmd0="mkdir -p $BASE/$CUR"
   echo $cmd0

   for png in $(ls -1rt *.png) 
   do
       tpng=$(stat --format=%Y $png)
       if [ $tpng -gt $tcur ]; then
           cmd1="cp $SDIR/$png $BASE/$CUR/$png"
           echo $cmd1
       fi
   done
fi


s5_()
{
    local cmd=$1
    local relp=$2
    local titl=$(echo $relp | tr "/" "_")

    if [ "$cmd" == "P" ]; then

        printf "    $titl\n"
        printf "    $relp 1280px_720px\n"
        printf "\n"

    elif [ "$cmd" == "T" ]; then

        local n=$(( ${#titl} + 7 ))
        printf "\n"
        printf ":i:\`$titl\` \n"
        for (( i=1 ; i < $n ; i++ )) do printf "-" ; done
        printf "\n\n" 

    fi
}

s5()
{
   printf "[s5$1\n\n"
   for png in $(ls -1rt *.png)
   do
       tpng=$(stat --format=%Y $png)
       [ $tpng -gt $tcur ] && s5_ $1 $CUR/$png
   done
   printf "]s5$1\n"
}


if [ "${arg/s5p}" != "$arg" -a -f $cur ]; then
   s5 P 
fi

if [ "${arg/s5t}" != "$arg" -a -f $cur ]; then
   s5 T
fi


exit 0

