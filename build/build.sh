#!/bin/bash
set -Eeuo pipefail
DIR="$(dirname "$(readlink -f "$0")")" #directory of shell script
function build() {
    cd "$DIR/../$1/"
    mkdir -p "$DIR/$1"
    # we need to call pdflatex twice to get the table of contents ... 
    # damn this is ugly. breaks on @,&,|,\n or $ in path names
    find -maxdepth 1 -type f -iname '*.tex' -print0 | xargs -I@ -r -0 -n 1 sh -c "pdflatex -output-directory '$DIR/$1' @ && pdflatex -output-directory '$DIR/$1' @"
    find -maxdepth 1 -type f -iname '*.md' | sed "s|\\(.*\\)\\.md|pandoc '\\1.md' -o '$DIR/$1/\\1.pdf'|" | sh
}
build slides
build tasks
build task_solutions
