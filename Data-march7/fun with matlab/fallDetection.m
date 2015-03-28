M = load('csvFiles/ADL.csv');
get_plot_stuff(M, 1, 'Activities of Daily Living');

M = load('csvFiles/Fall1.csv');
get_plot_stuff(M, 2, 'Lateral fall with bent legs');

M = load('csvFiles/Fall1MB.csv');
get_plot_stuff(M, 3, 'Forward fall with bent legs');

M = load('csvFiles/Fall1MBack.csv');
get_plot_stuff(M, 4, 'Backwards fall with bent legs');

M = load('csvFiles/fall1R.csv');
get_plot_stuff(M, 5, 'Lateral fall with bent legs (R)');

M = load('csvFiles/Fall2MB.csv');
get_plot_stuff(M, 6, 'Forward fall with bent legs + ADL');

M = load('csvFiles/Fall2T.csv');
get_plot_stuff(M, 7, 'Lateral fall with bent legs (T)');

M = load('csvFiles/Fall3MGrad.csv');
get_plot_stuff(M, 8, 'Gradual fall + struggle to get up + head rolling');
