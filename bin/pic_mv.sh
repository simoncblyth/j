#!/bin/bash
usage(){ cat << EOU
~/Pictures/pic_mv.sh
======================

* https://help.gnome.org/users/gnome-help/stable/screen-shot-record.html.en

To capture screenshots into ~/Pictures:

* Fn+PrintScreen (blue keys) : Screen flashes and dated png of full screen appears in ~/Pictures/
* Alt+Fn+PrintScreen (just window, not full screen)
  

Rename .png within ~/Pictures changing spaces in names to underscores::

   ~/Pictures/pic_mv.sh

To open png::

    gio open Screenshot_from_2025-05-08_19-58-08.png

EOU
}

cd ~/Pictures

for l in *.png
do
    m="${l// /_}"
    m=${m/Screenshot_from_}  
    m=${m//-}
    if [ "$m" != "$l" ]; then
        mv "$l" "$m"
    fi 
done



