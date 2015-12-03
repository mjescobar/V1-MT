------ README.txt --------

This repository contains the tools to learn and to reproduce the results reported in:

"A model of motion direction content of V1 suppressive surrounds explains motion integration 
for type I and II plaid motion patterns"
Escobar MJ, Toledo P, Kornprobst P and Masson GS
Frontiers in Computational Neuroscience (under review)

The main content of this repository is organized as follows:

GA-FilterResponse:
	Definition of the APIs needed to convolve the input image with a certain spatiotemporal filter. This APIs use the ABFilter-v1.5 library.

GA-CalculateFilterResponse:
	For a given spatiotemporal filter bank (Adelson-Bergen) it computes the convolution between this filter bank and an input video. The convolution result, for each time-step, is stored in a text file.

GA-Tools:
	Tools developed to monitor memory usage.

GA-V1MTSimulator:
	Definition of V1 and MT neurons, together with, the utils to create V1 and MT networks 

GA-V1MTSS:
	Main folder where the V1-MT network is created and evaluated for a given input current profile.	

GA-V1MTSS_FilterResponse:
	Main folder where the V1-MT network is created and evaluated for a given input current profile computed for a given bank of filters.	

These last two folders are the most important to reproduce the figures after GA learning. 
Inside each folder, you will find their own README.txt files
