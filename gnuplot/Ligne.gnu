
set datafile separator ";"
set xlabel 'Jour-heure'
set ylabel 'Température/pression'
#set xr [2010:2011]
#set yr [1:*] 
#set xtics auto
#set ytics auto

set xr [:]

color1= "#2b63ff"


set xdata time
set timefmt "%Y-%m-%dT%H:%M:00+0*:00" 
#show timefmt



plot 'ValeursRetours2.csv' using 2:3  with linespoints lt rgb color1 title "température moyenne"

