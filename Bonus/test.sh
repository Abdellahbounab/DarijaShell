#the output subshell () in out
(cat -e Makefile && ls )>out
# error bash: syntax error near unexpected token `ls'
ls > out | ((ls -e && cat -e Makefile) ls) echo hello 

#run ls
(ls)
#do nothing (acauly it run in backgound)
((ls))

#  3928 ttys004    0:00.07 bash
#  5500 ttys004    0:00.00 bash
#  5502 ttys004    0:00.00 sleep 10
(sleep 10 && echo hello) | (echo HI)

#  3928 ttys004    0:00.07 bash
#  5536 ttys004    0:00.00 sleep 10
sleep 10 && echo hello | echo HI


unset HOME && echo $HOME