set title '% de Tiempo de Funciones vs BSIZE'
set xlabel 'Block Size'; set ylabel '% de tiempo de ejecución'
set logscale x; set grid
set term png; set out 'blocking.png'
plot 'total_report.txt' u 1:2 w l t 'index1d', 'total_report.txt' u 1:3 w l t 'fill', 'total_report.txt' u 1:4 w l t 'direct transpose', 'total_report.txt' u 1:5 w l t 'cached transpose'