minishell-$ export HOME=NO_SUCH_FILE 
minishell-$ cd
minishell-$ pwd
/Users/achakkaf/Desktop

bash-3.2$ export HOME=NO_SUCH_FILE
bash-3.2$ cd
bash: cd: NO_SUCH_FILE: No such file or directory


minishell-$ echo "$PATH"
"/Users/achakkaf/goinfre/homebrew/bin:/Users/achakkaf/goinfre/homebrew/bin:/Users/achakkaf/goinfre/homebrew/bin:/Users/achakkaf/goinfre/homebrew/bin:/Users/achakkaf/goinfre/homebrew/bin:/Users/achakkaf/goinfre/homebrew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin"
minishell-$ echo "$ $ $ $ $ $ "
"$ $ $ $ $ $ $ $ $ " $ $ " $ " "

echo "$ $ $ $" # problem in double quote doesn't filter

