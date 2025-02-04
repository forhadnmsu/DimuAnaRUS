## Goal
The goal of this `DimuAnaRUS` module is to get the input data from a ROOT file (in DST format) and convert them into RUS (ROOT Universal Structure) format. This includes triggers, hits, true/reconstructed track or dimuon information, and event details. It supports a wide range of data formats such as integers, doubles, and booleans, and can store this data in flat, vector, or array formats.

### Instructions for Adding Reconstructed Variables to RUS File
To include true track or reconstructed variables in your RUS file, follow these steps:

1. **Set the appropriate dimuon road option:**
   - For simulated data, set `SetMCTriggerEmu()` to `true`.
   - For experimental data, set `SetDataTriggerEmu()` to `true`. The `SetDataTriggerEmu()` and `SetMCTriggerEmu()` functions are mutually exclusive, so if you set one to `true`, the other will automatically be set to `false`.
	- These functions ensure that the dimuons are satisfied in the `top-bot` or `bot-top` roads.

2. **Enable reconstruction mode:**
   - Set `SetRecoMode()` to `true` to add the reconstructed variables.
   - Set `SetMCMode()` to `true` to add the MC true variables.

### Example Usage in the Macro `Fun4All.C` locaed in the Convert/work_reco/mc_gen directory:

```cpp
	DimuAnaRUS* dimuAna = new DimuAnaRUS();
	dimuAna->SetTreeName("tree");
	dimuAna->SetMCMode(false);
	dimuAna->SetDataTriggerEmu(true);
	tree->SetSaveOnlyDimuon(true);
	tree->SetRecoMode(true);
	se->registerSubsystem(dimuAna);
	se->registerSubsystem(new DimuAnaRUS());

# Updated Variable Names and Types
## Event-Level Variables
| Variable Name      | Type               | Description                          |   
|--------------------|--------------------|--------------------------------------|
| `runID`            | `int`              | Identifier for the current run       |   
| `spillID`          | `int`              | Identifier for the spill in the run  |
| `eventID`          | `int`              | Unique identifier for the event      |   
| `rfID`             | `int`              | Identifier for the RF                |   
| `turnID`           | `int`              | Identifier for the Turn                |   
| `fpgaTrigger`      | `int[5]`           | Array of FPGA trigger                |   
| `nimTrigger`       | `int[5]`           | Array of NIM trigger                 |   
| `rfIntensity`      | `int[33]`          | Array for QIE RF intensities         |   

## Hit-Level Variables
| Variable Name          | Type                     | Description                                  |   
|------------------------|--------------------------|----------------------------------------------|
| `hitID`                | `std::vector<int>`       | Hit IDs for all hits                         |   
| `detectorID`           | `std::vector<int>`       | Detector IDs for all hits                    |   
| `elementID`            | `std::vector<int>`       | Element IDs associated with each hit         |   
| `driftDistance`        | `std::vector<double>`    | Drift distances for each hit                 |   
| `tdcTime`              | `std::vector<double>`    | TDC timing values for each hit               |   
| `hitInTime`            | `std::vector<bool>`      | Flags indicating if hits are within time     |   

## Monte Carlo Track Variables

| Variable Name            | Type                | Description                                     |
|--------------------------|---------------------|-------------------------------------------------|
| `trueTrackID`           | `std::vector<int>`  | Track IDs for Monte Carlo tracks               |
| `trueTrackCharges`      | `std::vector<int>`  | Charges of the Monte Carlo tracks              |
| `trueVtxPosX`          | `std::vector<double>` | X-coordinate of the production vertex         |
| `trueVtxPosY`          | `std::vector<double>` | Y-coordinate of the production vertex         |
| `trueVtxPosZ`          | `std::vector<double>` | Z-coordinate of the production vertex         |
| `trueVtxMomPx`         | `std::vector<double>` | X-component of the momentum at the vertex     |
| `trueVtxMomPy`         | `std::vector<double>` | Y-component of the momentum at the vertex     |
| `trueVtxMomPz`         | `std::vector<double>` | Z-component of the momentum at the vertex     |
| `trueSt1PosX`          | `std::vector<double>` | X-coordinate at station 1                     |
| `trueSt1PosY`          | `std::vector<double>` | Y-coordinate at station 1                     |
| `trueSt1PosZ`          | `std::vector<double>` | Z-coordinate at station 1                     |
| `trueSt1MomPx`         | `std::vector<double>` | X-component of the momentum at station 1      |
| `trueSt1MomPy`         | `std::vector<double>` | Y-component of the momentum at station 1      |
| `trueSt1MomPz`         | `std::vector<double>` | Z-component of the momentum at station 1      |
| `trueSt3PosX`          | `std::vector<double>` | X-coordinate at station 3                     |
| `trueSt3PosY`          | `std::vector<double>` | Y-coordinate at station 3                     |
| `trueSt3PosZ`          | `std::vector<double>` | Z-coordinate at station 3                     |
| `trueSt3MomPx`         | `std::vector<double>` | X-component of the momentum at station 3      |
| `trueSt3MomPy`         | `std::vector<double>` | Y-component of the momentum at station 3      |
| `trueSt3MomPz`         | `std::vector<double>` | Z-component of the momentum at station 3      |

## Dimuon-Level Variables

| Variable Name            | Type                | Description                                     |
|--------------------------|---------------------|-------------------------------------------------|
| `trueDimuonPdgId`       | `std::vector<int>`  | PDG ID of the dimuon                           |
| `trueDimuonId`          | `std::vector<int>`  | Dimuon ID                                      |
| `trueDimuonVtxX`        | `std::vector<double>` | X-coordinate of the dimuon vertex            |
| `trueDimuonVtxY`        | `std::vector<double>` | Y-coordinate of the dimuon vertex            |
| `trueDimuonVtxZ`        | `std::vector<double>` | Z-coordinate of the dimuon vertex            |
| `trueDimuonVtxPx`       | `std::vector<double>` | X-component of the dimuon momentum at vertex |
| `trueDimuonVtxPy`       | `std::vector<double>` | Y-component of the dimuon momentum at vertex |
| `trueDimuonVtxPz`       | `std::vector<double>` | Z-component of the dimuon momentum at vertex |
| `trueDimuonVtxM`        | `std::vector<double>` | Mass of the dimuon                            |
| `trueDimuonPosPx`       | `std::vector<double>` | X-momentum of the positive dimuon track      |
| `trueDimuonPosPy`       | `std::vector<double>` | Y-momentum of the positive dimuon track      |
| `trueDimuonPosPz`       | `std::vector<double>` | Z-momentum of the positive dimuon track      |
| `trueDimuonNegPx`       | `std::vector<double>` | X-momentum of the negative dimuon track      |
| `trueDimuonNegPy`       | `std::vector<double>` | Y-momentum of the negative dimuon track      |
| `trueDimuonNegPz`       | `std::vector<double>` | Z-momentum of the negative dimuon track      |

  ## Dimuon-Reco-Level Variables
  | Variable Name            | Type                | Description                                     |
  |--------------------------|---------------------|--------------------------------------------------|
|`dimuonVtxX`          | `std::vector<double>` | X-coordinate of the dimuon vertex                 |
|`dimuonVtxY`          | `std::vector<double>` | Y-coordinate of the dimuon vertex                 |
|`dimuonVtxZ`          | `std::vector<double>` | Z-coordinate of the dimuon vertex                 |
|`dimuonVtxPx`         | `std::vector<double>` | X-component of the dimuon vertex momentum         |
|`dimuonVtxPy`         | `std::vector<double>` | Y-component of the dimuon vertex momentum         |
|`dimuonVtxPz`         | `std::vector<double>` | Z-component of the dimuon vertex momentum         |
|`dimuonMass`          | `std::vector<double>` | Mass of the dimuon system                         |
|`dimuonX1`            | `std::vector<double>` | X1 kinematic variable for the dimuon              |
|`dimuonX2`            | `std::vector<double>` | X2 kinematic variable for the dimuon              |
|`dimuonXf`            | `std::vector<double>` | Xf kinematic variable for the dimuon              |
|`muPlusVtxX`          | `std::vector<double>` | X-coordinate of the positive muon vertex          |
|`muPlusVtxY`          | `std::vector<double>` | Y-coordinate of the positive muon vertex          |
|`muPlusVtxZ`          | `std::vector<double>` | Z-coordinate of the positive muon vertex          |
|`muMinusVtxX`         | `std::vector<double>` | X-coordinate of the negative muon vertex          |
|`muMinusVtxY`         | `std::vector<double>` | Y-coordinate of the negative muon vertex          |
|`muMinusVtxZ`         | `std::vector<double>` | Z-coordinate of the negative muon vertex          |
|`muPlusVtxPx`         | `std::vector<double>` | X-component of the positive muon vertex momentum  |
|`muPlusVtxPy`         | `std::vector<double>` | Y-component of the positive muon vertex momentum  |
|`muPlusVtxPz`         | `std::vector<double>` | Z-component of the positive muon vertex momentum  |
|`muMinusVtxPx`        | `std::vector<double>` | X-component of the negative muon vertex momentum  |
|`muMinusVtxPy`        | `std::vector<double>` | Y-component of the negative muon vertex momentum  |   
|`muMinusVtxPz`        | `std::vector<double>` | Z-component of the negative muon vertex momentum  |   
|`top_bot`             | `std::vector<bool>`   | Flag indicating top to bottom relation            |   
|`bot_top`             | `std::vector<bool>`   | Flag indicating bottom to top relation            |   
                                                                                                      
                                                                                                      
``` Compilation before running the Fun4All macro                                                      
source setup.sh                                                                                       
cmake-this                                                                                            
make-this                                                                                             
```                                                                                                   
### Uses                                                                                              
If you want to analyze and keep the output in RUS format:                                             
                                                                                                      
1. **Single DST File**                                                                                
   To convert a single DST file to RUS format, you can use the `Fun4Test.C` macro.                    
   Note: This macro is not configured to perform reconstruction or vertexing. Instead, it uses a v    ertexed DST file for post-processing into RUS format.  
                                                                                                      
   ```bash                                                                                            
   cd Convert                                                                                         
   root -b Fun4Test.C                                                                                 
                                                                                                      
2. **Processing Multiple DST Files**                                                                  
   If you have many DST files and want to process them locally or on the grid, use the following c    ommand:  

   ```bash
   ./gridsub.sh -j 1-5 -g -o

	1. `-j 1-5`: Specifies the range of input DST files to process (from the 1st row to the 5th one).
 	2. `-g`: Enables grid mode for processing.
	3. `-o`: Overwrites existing files.
