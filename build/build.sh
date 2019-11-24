#!/bin/bash
set -Eeuo pipefail

DIR="$(dirname "$(readlink -f "$0")")" #directory of shell script
function file_newer(){
    file_1_commit=$(git log --follow -n 1 --pretty=format:"%h" -- $1)
    file_2_commit=$(git log --follow -n 1 --pretty=format:"%h" -- $2)
    latest=$(git log --pretty=format:"%h" | grep "$file_1_commit\\|$file_2_commit" | head -n 1)
    test "$file_1_commit" == "$latest"
}
function build() {
    cd "$DIR/../$1/"
    mkdir -p "$DIR/$1"
    # we need to call pdflatex twice to get the table of contents ... 
    for texfile in ./*.tex ; do
        [ -e "$texfile" ] || continue
        filename="${texfile%.*}"
        printf "\ncompiling $texfile ...\n"
        if [ $build_all = true ] || file_newer "$texfile" "$DIR/$1/$filename.pdf"; then
            pdflatex --interaction=batchmode -output-directory "$DIR/$1" $texfile && 
                pdflatex --interaction=batchmode -output-directory "$DIR/$1" $texfile || :        
        fi
    done

    for mdfile in ./*.md ; do
        [ -e "$mdfile" ] || continue
        echo "compiling $mdfile ..."
        filename="${mdfile%.*}"
        if [ $build_all = true ] || file_newer "$mdfile" -nt "$DIR/$1/$filename.pdf"; then
            pandoc "$mdfile" -o "$filename.pdf"
        fi
    done
}

build_all=false
if [ "$#" -gt "0" ]; then
    if [ "$1" == "-a" ] || [ "$1" == "--all" ] ; then
        build_all=true
    fi
fi

build slides
build tasks
build task_solutions
