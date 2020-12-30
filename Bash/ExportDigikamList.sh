#!/usr/bin/bash
HELPSTRING='Read a picture list from digikam and copy the files in a directory, appending an increasing number to the filename.\nUsage: ExportDigikamList.sh [OPTARGS] PICTURELIST\nOptional arguments are:\n-d: the destination directory. Defaults to the current working directory.\n-h: Print this help message.'
while getopts hd: opt
do
  case $opt in 
    d) DIR=`realpath $OPTARG`;;
    h) echo -e $HELPSTRING; exit 0
  esac
done
shift $[ $OPTIND - 1 ]
[ -z ${DIR} ] && DIR=`pwd`
[ -z $1 ] && echo 'Error: Please provide a picture list as argument (-h for help).' && exit 1
LIST=`realpath $1`
FILES=`gawk -F '"' '/Image url=/{print $2}' $LIST | cut -c8-`

IFS=$'\n'
FILES=($FILES)
NUM=${#FILES[@]}
for ((i=0; i<NUM; i++)) do
    cp ${FILES[i]} ${DIR}/Pic${i}_$(basename ${FILES[i]})
done
exit 0