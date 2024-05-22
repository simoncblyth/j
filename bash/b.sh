#!/bin/bash



main(){
  echo $FUNCNAME $*
}
notmain(){
  echo $FUNCNAME $*
}



if [[ "${BASH_SOURCE[0]}" == "${0}" ]]; then
    main "$@"
else
   notmain "$@"
fi

