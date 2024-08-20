echo "working directory"
read dirname
if [ -n "$dirname" ]
then
    if [ -d "$dirname" ] && [ -x "$dirname" ]
    then
        cd "$dirname"
    else
        echo "directory is not accessible."
        exit 1
    fi
else
    dirname=$PWD
fi
for dir in *
do
    newname=`echo $dir | tr "[a-z] [A-Z]" "[A-Z] [a-z]"`
    mv $dir $newname
done
