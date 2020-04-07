pkill ibus-daemon &
ssh-add $HOME/.ssh/* &
xrdb -load $HOME/.Xdefaults
#xdotool keydown Super Shift key F5 keyup Super Shift
numlockx on &
nitrogen --restore
compton &
dunst &
telegram -startintray &
#volumeicon &
nm-applet &
unclutter &
xset -dpms
xset s off
dwmblocks &
