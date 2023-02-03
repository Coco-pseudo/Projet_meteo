





set xlabel 'longitude'
set ylabel 'latitude' 
set view map
set dgrid3d 100,100,2
unset key
unset surface
set pm3d at b 
set terminal png size 1000,750 enhanced font "Helvetica,20"
set output "CarteInter.png"
splot "ValeursRetours.csv" 




