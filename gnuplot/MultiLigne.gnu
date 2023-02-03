


set datafile separator ";"

color1="#3352FF"
color2="#F0521C"

plot 'ValeursRetours2.csv' using  1:2 smooth cspline lw 2 lt rgb color2 title "données 1" , 'ValeursRetours2.csv' using 1:3 smooth cspline lw 2 lt rgb color1 title "données 2"


