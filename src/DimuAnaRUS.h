#ifndef _DIMU_ANA_RUS_H_
#define _DIMU_ANA_RUS_H_
#include <fun4all/SubsysReco.h>
#include <UtilAna/TrigRoadset.h>

class TFile;
class TTree;
class SQRun;
class SQSpillMap;
class SQEvent;
class SQHitVector;
class SQTrackVector;
class SQDimuonVector;

class DimuAnaRUS: public SubsysReco {
	SQEvent* m_evt;
	SQSpillMap* m_sp_map;
	SQHitVector* m_hit_vec;
	SQTrackVector * m_vec_trk;
	SQTrackVector*  m_sq_trk_vec;
	SQDimuonVector* m_sq_dim_vec;
	SQRun* sq_run;

	std::string m_file_name;
	std::string m_tree_name;
	TFile*      m_file;
	TTree*      m_tree;
	public:

	UtilTrigger::TrigRoadset m_rs;
        bool mc_mode;
        bool reco_mode;
        bool data_trig_mode;
        bool mc_trig_mode;
        bool saveDimuonOnly;

        void SetMCMode(bool enable) { mc_mode = enable; }
        void SetRecoMode(bool enable) { reco_mode = enable; }
        void SetDataTriggerEmu(bool enable) { 
                data_trig_mode = enable; 
                mc_trig_mode = !enable; // Automatically disable mc_trig_mode when data_trig_mode is enabled
        }   

        void SetMCTriggerEmu(bool enable) { 
                mc_trig_mode = enable; 
                data_trig_mode = !enable; // Automatically disable data_trig_mode when mc_trig_mode is enabled
        }   

        void SetSaveOnlyDimuon(bool enable) { saveDimuonOnly = enable; }


	DimuAnaRUS(const std::string& name="DimuAnaRUS");
	virtual ~DimuAnaRUS();
	int Init(PHCompositeNode *startNode);
	int InitRun(PHCompositeNode *startNode);
	int process_event(PHCompositeNode *startNode);
	int End(PHCompositeNode *startNode);
	void SetOutputFileName(const std::string name) { m_file_name = name; }

	void SetTreeName(const std::string& name) { m_tree_name = name; }
	void SetFileName(const std::string& name) { m_file_name = name; }
	void ResetBranches();

	private:

	// Scalar variables
	int runID;
	int spillID;
	int eventID;
	int rfID;
	int turnID;
	int rfIntensities[33];
	int fpgaTriggers[5] = {0};
	int nimTriggers[5] = {0};

	std::vector<int> detectorIDs;
	std::vector<int> elementIDs;
	std::vector<double> tdcTimes;
	std::vector<double> driftDistances;
	std::vector<bool> hitsInTime;
	// MC track data
	std::vector<int> mc_track_charges;
	std::vector<int> mc_track_id;
	std::vector<double> mc_pos_vtx_x;
	std::vector<double> mc_pos_vtx_y;
	std::vector<double> mc_pos_vtx_z;
	std::vector<double> mc_mom_vtx_px;
	std::vector<double> mc_mom_vtx_py;
	std::vector<double> mc_mom_vtx_pz;

	//Dimuon variables for MC or Data
	std::vector<double> dimuon_vtx_x;
	std::vector<double> dimuon_vtx_y;
	std::vector<double> dimuon_vtx_z;
	std::vector<double> dimuon_vtx_px;
	std::vector<double> dimuon_vtx_py;
	std::vector<double> dimuon_vtx_pz;
	std::vector<double> dimuon_mass;
	std::vector<double> dimuon_x1;
	std::vector<double> dimuon_x2;
	std::vector<double> dimuon_xF;

	std::vector<double> mu_plus_vtx_x;
	std::vector<double> mu_plus_vtx_y;
	std::vector<double> mu_plus_vtx_z;
	std::vector<double> mu_minus_vtx_x;
	std::vector<double> mu_minus_vtx_y;
	std::vector<double> mu_minus_vtx_z;

	std::vector<double> mu_plus_vtx_px;
	std::vector<double> mu_plus_vtx_py;
	std::vector<double> mu_plus_vtx_pz;
	std::vector<double> mu_minus_vtx_px;
	std::vector<double> mu_minus_vtx_py;
	std::vector<double> mu_minus_vtx_pz;

	std::vector<double> mu_plus_chi2_target;
	std::vector<double> mu_plus_chi2_dump;
	std::vector<double> mu_plus_chi2_upstream;

	std::vector<double> mu_minus_chi2_target;
	std::vector<double> mu_minus_chi2_dump;
	std::vector<double> mu_minus_chi2_upstream;

	std::vector<bool> top_bot;
	std::vector<bool> bot_top;

};

#endif // _DimuAnaRUS.h_
