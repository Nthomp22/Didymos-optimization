<h1> Config File Specifications/Information </h1>
Last Updated: June 22nd, 2020

<h2>The config file allows empty rows and comments ("//" at start of comment line) for formatting the presentation of the contents</h2>
<h2>For changing what config file is used, the file address can be changed where cudaConstants is declared within the main function</h2>
<h2>If config file address is invalid, will output to terminal that is the case.  Also assumption is made that the config file contains valid values for all variables</h2>
<h2>Default address is "genetic.config", must be in same folder as the .exe file


<h2>Variables in the Config File (WIP)</h2>

| Variable Name              	| Data Type  	| Units 	| Usage                                                                                                                                                      	|   	|
|----------------------------	|------------	|-------	|------------------------------------------------------------------------------------------------------------------------------------------------------------	|---	|
| time_seed                  	| int/string 	| None  	| Sets the seed used in random generation, either specify a seed to use or place "NONE" for the seed to be time(0)                                           	|   	|
| random_start               	| boolean    	| None  	| If true, sets initial generation's individuals to hold parameters with random values, if false it initializes the individuals from a file                  	|   	|
| initial_start_file_address 	| string     	| None  	| If random_start is false, the program uses this address to get parameter values for the initial individuals with the assumption that the file hold 14 sets 	|   	|
| pos_threshold              	| double     	| AU      	| Sets the maximum positional difference of the spacecraft to the asteriod at end of its trajectory path                                                    	|   	|
| speed_threshold            	| double     	| AU/s  	| (Currently not used?) Sets the minimum velocity difference with the asteriod that the spacecraft must obtain at the end of its trajectory path 	|   	|
| write_freq                 	| int        	| None  	| Sets number of generations to process before writing information onto files, 1 is to write every generation 	|   	|
| disp_freq                  	| int        	| None  	| Sets number of gnerations to process before outputting to console terminal, 1 is to display output every generation 	|   	|
| best_count                 	| int        	| None  	| How many individuals must converge to a solution before ending the algorithm 	|   	|
| change_check               	| int        	| None  	| For how many generations until it checks to see if the best individual has changed, if no change the anneal value is reduced 	|   	|
| anneal_initial             	| double     	| None  	| The initial anneal value, anneal impacts the maximum possible mutation value when generating a new individual (does not impact probability) 	|   	|
| mutation_rate              	| double     	| None  	| The probability of a mutation occurring when generating a new individual, gurantees at least one gene is changed 	|   	|
| double_mutation_rate       	| double     	| None  	| Probability that if a mutation is occurring that it affects two genes 	|   	|
| triple_mutation_rate       	| double     	| None  	| Probability that if a mutation is occurring that it affects 3 genes 	|   	|
| gamma_mutate_scale           	| double     	| None  	| Affects the maximum mutation range for gamma values 	|   	|
| tau_mutate_scale           	| double     	| None  	| Affects the maximum mutation range for tau values 	|   	|
| coast_mutate_scale           	| double     	| None  	| Affects the maximum mutation range for coast values 	|   	|
| triptime_mutate_scale 	    | double     	| None  	| Affects the maximum mutation range for triptime values 	|   	|
| zeta_mutate_scale          	| double     	| None  	| Affects the maximum mutation range for zeta values 	|   	|
| alpha_mutate_scale           	| double     	| None  	| Affects the maximum mutation range for alpha values 	|   	|
| thruster_type                	| int        	| None  	| Determine what thruster is used, 0 for none and 1 for NEXT ion thruster 	|   	|
| dry_mass                     	| int        	| kg      	| Set the mass of the spacecraft without fuel 	|   	|
| wet_mass                     	| int        	| kg      	| Set the mass of the spacecraft with fuel 	|   	|
| coast_threshold             	| double     	| None  	| In a range from 0 to 1, 1 sets the spacecraft to coast at all times while 0 sets the spacecraft to always have thruster on 	|   	|
| c3energy                     	| double     	| m^2/s^2  	| The specific energy of the spacecraft when leaving earth's sphere of influence, determines the magnitude of the escape velocity that is stored in v_escape 	|   	|
| v_escape                     	| double     	| AU/s  	| The magnitude of the initial velocity of the spacecraft when leaving earth's sphere of influence, not in config file but rather derived from c3energy 	|   	|
| r_fin_ast           	        | double     	| AU      	| The radius position of the asteriod at impact date, relative to the Sun 	|   	|
| theta_fin_ast        	        | double     	| Radians  	| The theta angle position of the asteriod at impact date, relative to the Sun 	|   	|
| z_fin_ast           	        | double     	| AU      	| The z (off-plane offset) position of the asteriod at impact date, relative to the Sun 	|   	|
| vr_fin_ast           	        | double     	| AU/s  	| The velocity of the radius component of the asteriod at impact date, relative to the Sun 	|   	|
| vtheta_fin_ast      	        | double     	| Rad/s  	| The velocity of the theta angle component of the asteriod at impact date, relative to the Sun 	|   	|
| vz_fin_ast           	        | double     	| AU/s  	| The velocity of the z component of the asteriod at impact date, relative to the Sun 	|   	|
| r_fin_earth           	    | double     	| AU     	| The radius position of the earth at impact date, relative to the Sun 	|   	|
| theta_fin_earth          	    | double     	| Radians  	| The theta angle position of the earth at impact date, relative to the Sun 	|   	|
| z_fin_earth           	    | double     	| AU      	| The z (off-plane offset) position of the earth at impact date, relative to the Sun and used to plot it's path backwards in time for launch positions of the spacecraft 	|   	|
| vr_fin_earth           	    | double     	| AU/s  	| The velocity of the radius component of the earth at impact date, relative to the Sun and used to plot it's path backwards in time for launch positions of the spacecraft 	|   	|
| vtheta_fin_earth         	    | double     	| Rad/s  	| The velocity of the theta angle component of the earth at impact date, relative to the Sun and used to plot it's path backwards in time for launch positions of the spacecraft 	|   	|
| vz_fin_earth           	    | double     	| AU/s  	| The velocity of the z component of the earth at impact date, relative to the Sun and used to plot it's path backwards in time for launch positions of the spacecraft 	|   	|