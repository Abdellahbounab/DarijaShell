minishell-$ cd ../ env | grep -v -E '^_=' | sort
minishell-$ pwd
/Users/achakkaf/Desktop/minishell

bash-3.2$ cd ../ env | grep -v -E '^_=' | sort
bash-3.2$ pwd
/Users/achakkaf/Desktop

-------------------------------------------------

minishell-$ exit -9223372036854775809
exit
achakkaf@c1r7p6 minishell % echo $?
0

bash-3.2$  exit -9223372036854775809
exit
bash: exit: -9223372036854775809: numeric argument required
achakkaf@c1r7p6 minishell % echo $?
255

-------------------------------------------------

minishell-$ exit "        42           "
exit : numeric argument required
achakkaf@c1r7p6 minishell % echo $?
255

bash-3.2$ exit "        42           "
exit
achakkaf@c1r7p6 minishell % echo $?
42

-------------------------------------------------

minishell-$ exit +
exit
achakkaf@c1r7p6 minishell % echo $?
0

bash-3.2$ exit +
exit
bash: exit: +: numeric argument required
achakkaf@c1r7p6 minishell % echo $?
255

-------------------------------------------------

minishell-$ exit -
exit
achakkaf@c1r7p6 minishell % echo $?
0

bash-3.2$ exit -
exit
bash: exit: -: numeric argument required
achakkaf@c1r7p6 minishell % echo $?
255

-------------------------------------------------

minishell-$ export 1 _+ _OK _2? _OK2=VAR =NG OK3=sd
export : not a valid identifier
minishell-$ env | grep OK3

bash-3.2$ export 1 _+ _OK _2? _OK2=VAR =NG OK3=sd
bash: export: `1': not a valid identifier
bash: export: `_+': not a valid identifier
bash: export: `_2?': not a valid identifier
bash: export: `=NG': not a valid identifier
bash-3.2$ env | grep OK3
OK3=sd

-------------------------------------------------

minishell-$ export APPEND=1; export APPEND+=2; export | grep APPEND
minishell(7881,0x112aaadc0) malloc: *** error for object 0x7fb4116041f0: pointer being freed was not allocated
minishell(7881,0x112aaadc0) malloc: *** set a breakpoint in malloc_error_break to debug

-------------------------------------------------

minishell-$ export APPEND_NONE=; export APPEND_NONE=; export APPEND_NONE+=; 
minishell(6412,0x112aaadc0) malloc: *** error for object 0x7fb4128041d0: pointer being freed was not allocated
minishell(6412,0x112aaadc0) malloc: *** set a breakpoint in malloc_error_break to debug
zsh: abort      ./minishell

-------------------------------------------------

minishell-$ export PATH
minishell-$ export | grep PATH
grep: command not found

bash-3.2$ export PATH
bash-3.2$ export | grep PATH
declare -x PATH="/Users/achakkaf/goinfre/homebrew/bin:/Users/achakkaf/goinfre/homebrew/bin:/Users/achakkaf/goinfre/homebrew/bin:/Users/achakkaf/goinfre/homebrew/bin:/Users/achakkaf/goinfre/homebrew/bin:/Users/achakkaf/goinfre/homebrew/bin:/Users/achakkaf/goinfre/homebrew/bin:/Users/achakkaf/goinfre/homebrew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin"

-------------------------------------------------

minishell-$ unset PWD
minishell-$ cd ..
minishell-$ export | grep PWD
        declare -x OLDPWD="/Users/achakkaf/Desktop/minishell"
        declare -x PWD="/Users/achakkaf/Desktop"

bash-3.2$  unset PWD
bash-3.2$ cd ..
bash-3.2$ export | grep PWD
declare -x OLDPWD=""

-------------------------------------------------

minishell-$ unset OLDPWD
minishell-$ cd ..
minishell-$ export | grep OLDPWD
        declare -x OLDPWD="/Users/achakkaf/Desktop"

bash-3.2$ unset OLDPWD
bash-3.2$  cd ..
bash-3.2$  export | grep OLDPWD

-------------------------------------------------

minishell-$ unset PWD
minishell-$ cd ..
minishell-$ export PWD=new_value
minishell-$ export | grep PWD
        declare -x OLDPWD="/Users/achakkaf/Desktop/minishell"
        declare -x PWD="new_value"

bash-3.2$ unset PWD; cd ..; export PWD=new_value; export | grep PWD
declare -x OLDPWD=""
declare -x PWD="new_value"

-------------------------------------------------

minishell-$ export =
minishell-$ echo $?
0

bash-3.2$ export =
bash: export: `=': not a valid identifier
bash-3.2$ echo $?
1

-------------------------------------------------

minishell-$ echo $OLDPWD
/Users/achakkaf/Desktop
minishell-$ 

bash-3.2$ echo $OLDPWD

bash-3.2$ 

-------------------------------------------------





minishell -$ <<"eof" cat
> salam
> eof
> "eof" 
> eof
> "eof" 
> "eof"

# this have to be handled in the lexer or parser