#!/usr/bin/bash
sx=30
sy=30
for window in $(xdotool search -name .)
do
  xdotool windowmove $window $sx $sy
  xdotool windowunmap $window
  xdotool windowmap $window
  sx=$(($sx + 40))
  sy=$(($sy + 40))
done

