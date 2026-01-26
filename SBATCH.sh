#!/usr/bin/env bash
find . -name '*.sh' -exec grep -l SBATCH {} \;
