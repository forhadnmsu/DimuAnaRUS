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
| `eventID`          | `int`              | Unique identifier for the event      |
| `runID`            | `int`              | Identifier for the current run       |
| `spillID`          | `int`              | Identifier for the spill in the run  |
| `fpgaTriggers`     | `int[5]`           | Array of FPGA trigger counts         |
| `nimTriggers`      | `int[5]`           | Array of NIM trigger counts          |
| `rfIntensities`    | `int[33]`          | Array for QIE RF intensities         |

## Hit-Level Variables
| Variable Name           | Type                     | Description                                  |
|-------------------------|--------------------------|----------------------------------------------|
| `detectorIDs`           | `std::vector<int>`       | Detector IDs for all hits                    |
| `elementIDs`            | `std::vector<int>`       | Element IDs associated with each hit         |
| `driftDistances`        | `std::vector<double>`    | Drift distances for each hit                 |
| `tdcTimes`              | `std::vector<double>`    | TDC timing values for each hit               |
| `hitInTime`             | `std::vector<bool>`      | Flags indicating if hits are within time     |

## Trigger-Level Hit Variables
| Variable Name              | Type                     | Description                                  |
|----------------------------|--------------------------|----------------------------------------------|
| `trigDetectorIDs`          | `std::vector<int>`       | Detector IDs for triggered hits              |
| `trigElementIDs`           | `std::vector<int>`       | Element IDs for triggered hits               |
| `trigDriftDistances`       | `std::vector<double>`    | Drift distances for triggered hits           |
| `trigTdcTimes`             | `std::vector<double>`    | TDC timing values for triggered hits         |
| `trigHitInTimes`           | `std::vector<bool>`      | Flags indicating if triggered hits are in    |
|			     |				|   time					       |		

## Track-Level Variables
| Variable Name              | Type                     | Description                                  |
|----------------------------|--------------------------|----------------------------------------------|
| `mc_track_id`              | `std::vector<int>`       | Track IDs for Monte Carlo tracks             |
| `mc_track_charges`         | `std::vector<int>`       | Charges of the Monte Carlo tracks            |
| `mc_pos_vtx_x`             | `std::vector<double>`    | X-coordinate of the production vertex        |
| `mc_pos_vtx_y`             | `std::vector<double>`    | Y-coordinate of the production vertex        |
| `mc_pos_vtx_z`             | `std::vector<double>`    | Z-coordinate of the production vertex        |
| `mc_mom_vtx_px`            | `std::vector<double>`    | X-component of the momentum at the vertex    |
| `mc_mom_vtx_py`            | `std::vector<double>`    | Y-component of the momentum at the vertex    |
| `mc_mom_vtx_pz`            | `std::vector<double>`    | Z-component of the momentum at the vertex    |

``` Compilation before running the Fun4All macro 
source setup.sh
cmake-this
make-this
```

### Uses
If you want to analyze and keep the output in RUS format:

1. **Single DST File**  
   To convert a single DST file to RUS format, you can use the `Fun4Test.C` macro.  
   Note: This macro is not configured to perform reconstruction or vertexing. Instead, it uses a vertexed DST file for post-processing into RUS format.  

   ```bash
   cd Convert
   root -b Fun4Test.C

2. **Processing Multiple DST Files**  
   If you have many DST files and want to process them locally or on the grid, use the following command:  

   ```bash
   ./gridsub.sh -j 1-5 -g -o

	1. `-j 1-5`: Specifies the range of input DST files to process (from the 1st row to the 5th one).
 	2. `-g`: Enables grid mode for processing.
	3. `-o`: Overwrites existing files.

