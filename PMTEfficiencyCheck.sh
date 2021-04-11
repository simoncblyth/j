#!/bin/bash 
name=$(basename $0)
cmd="ipython -i ${name/.sh}.py"
echo $cmd
eval $cmd


