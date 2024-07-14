

minishell-$ echo "$PATH"
"/Users/achakkaf/goinfre/homebrew/bin:/Users/achakkaf/goinfre/homebrew/bin:/Users/achakkaf/goinfre/homebrew/bin:/Users/achakkaf/goinfre/homebrew/bin:/Users/achakkaf/goinfre/homebrew/bin:/Users/achakkaf/goinfre/homebrew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin"
minishell-$ echo "$ $ $ $ $ $ "
"$ $ $ $ $ $ $ $ $ " $ $ " $ " "

echo "$ $ $ $" # problem in double quote doesn't filter



minishell -$ <<"eof" cat
> salam
> eof
> "eof" 
> eof
> "eof" 
> "eof"

# this have to be handled in the lexer or parser