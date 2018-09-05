path=$(dirname $0)
path=${path/\./$(pwd)}
cmd_py="command script import "$path"/ExFormatters.py"
cmd_lldb="command source "$path"/ExFormatters.lldb"
p_init=~/.lldbinit

if [ -s $p_init ];
then
    sed -i "" "$ a\\
    $cmd_py" $p_init
    sed -i "" "$ a\\
    $cmd_lldb" $p_init
    awk '!x[$0]++' $p_init > $p_init"_new"
    mv $p_init"_new" $p_init
else
    echo "$cmd_py\n$cmd_lldb" > $p_init
fi


