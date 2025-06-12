#!/bin/bash

session="raylib_pac"

tmux has-session -t $session 2>/dev/null

if [ $? == 0 ]; then
  tmux attach-session -t $session
  exit 1
fi

window1="nvim"
window2="build_debug"
window3="git"

tmux new-session -d -s $session -n $window1
tmux send-keys -t $session:$window1 "nvim ." C-m

tmux new-window -t $session -n $window2
tmux send-keys -t $session:$window2 "cd build_debug" C-m

tmux new-window -t $session -n $window3

tmux select-window -t $session:$window1

tmux attach-session -t $session
