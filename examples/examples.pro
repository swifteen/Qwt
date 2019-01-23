TEMPLATE = subdirs

SUBDIRS = \
	simple_plot \
	cpuplot \
	curvdemo1 	\
	curvdemo2 \
	data_plot \
    event_filter \
	realtime_plot \
	bode \
	radio \
	dials \
	sliders

unix:SUBDIRS += linux
