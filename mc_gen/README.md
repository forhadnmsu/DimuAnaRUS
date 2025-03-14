# Event Generation and Reconstruction with RUS

This module allows you to perform event generation and reconstruction using the **`Fun4AllSim.C`** macro. Similar to the [SimChainDev module](https://github.com/E1039-Collaboration/e1039-analysis/tree/master/SimChainDev), this script facilitates event simulation, but with an **additional feature**: support for the **RUS file manager** for input and output handling.


## Steps to Run MC Simulations:

1. **Compile the script** (if you haven’t done so already):
    ```bash
    cd DimuAnaRUS/mc_gen 
    source ../setup.sh    
    cmake-this
    make-this
    ```
2. **Run a test job locally** and check the output files:
    ```bash
    root -b 'Fun4AllSim.C(5)'
    ```
3. **If everything looks correct**, run the job on the Rivanna HPC with a few events:
    ```bash
    ./jobscript.sh test 1 10
    ```
4. **For large-scale submissions**, compute the event processing as explained in the following link:  
   [SpinQuest Monte Carlo Generation on Rivanna](https://confluence.admin.virginia.edu/display/twist/SpinQuest+Monte+Carlo+Generation+on+Rivanna),  
   and submit a job using the following example:
    ```bash
    ./jobscript.sh DYTarget 100 100
    ```
5. **Check your output files** at:
    ```bash
    /sfs/weka/scratch/<user_name>/MC


RUS file options in Fun4AllSim.C:

	DimuAnaRUS* dimuAna = new DimuAnaRUS();
        dimuAna->SetTreeName("tree");  //set tree name
	dimuAna->SetMCTrueMode(true); // if you dont need true particle info, set it to false
        dimuAna->SetSaveOnlyDimuon(true); //set it false if you are not saving dimuons
        dimuAna->SetRecoMode(true); //set it false if you dont need recontructions
        dimuAna->SetOutputFileName("RUS.root");
        se->registerSubsystem(dimuAna);
