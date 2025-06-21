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
class SQMCEvent;

class DimuAnaRUS: public SubsysReco {
	SQEvent* m_evt;
	SQMCEvent* m_evt_true;
	SQSpillMap* m_sp_map;
	SQHitVector* m_hit_vec;
	SQTrackVector * m_vec_trk;
	SQTrackVector*  m_sq_trk_vec;
	SQDimuonVector* m_sq_dim_vec;
	SQDimuonVector* m_true_vec_dim;
	SQRun* sq_run;

	std::string m_file_name;
	std::string m_tree_name;
	TFile*      m_file;
	TTree*      m_tree;
	public:

	UtilTrigger::TrigRoadset m_rs;
	bool true_mode;
	bool reco_mode;
	bool data_trig_mode;
	bool mc_trig_mode;
	bool saveDimuonOnly;
	bool true_dimu_mode;
	int proc_id;
	int SourceFlag;
    bool sqhit_flag;
    bool reco_dimu_mode;

	void SetMCTrueMode(bool enable) { true_mode = enable; }
	void SetMCDimuonMode(bool enable) { true_dimu_mode = enable; }
	void SetRecoMode(bool enable) { reco_mode = enable; }
	void SetRecoDimuMode(bool enable) { reco_dimu_mode = enable; }
	void SetDataTriggerEmu(bool enable) { 
		data_trig_mode = enable; 
		mc_trig_mode = !enable; // Automatically disable mc_trig_mode when data_trig_mode is enabled
	}   

	void SetMCTriggerEmu(bool enable) { 
		mc_trig_mode = enable; 
		data_trig_mode = !enable; // Automatically disable data_trig_mode when mc_trig_mode is enabled
	}   

	void SetSaveOnlyDimuon(bool enable) { saveDimuonOnly = enable; }
	void SetSourceFlag(int flag) { SourceFlag = flag; }
	void SetProcessId(int proc_id_) { proc_id = proc_id_; }

	unsigned int EncodeProcess(int processID, int sourceFlag);
	static int DecodeSourceFlag(unsigned int encoded);
	static int DecodeProcessID(unsigned int encoded);

	DimuAnaRUS(const std::string& name="DimuAnaRUS");
	virtual ~DimuAnaRUS();
	int Init(PHCompositeNode *startNode);
	int InitRun(PHCompositeNode *startNode);
	int process_event(PHCompositeNode *startNode);
	int End(PHCompositeNode *startNode);
	void SetOutputFileName(const std::string name) { m_file_name = name; }
    void EnableSQHit(bool enable) { sqhit_flag = enable; }

	void SetTreeName(const std::string& name) { m_tree_name = name; }
	void SetFileName(const std::string& name) { m_file_name = name; }
	void ResetHitBranches();
	void ResetTrueBranches();
	void ResetRecoBranches();
	void ResetRecoDimuBranches();

	private:

	// Scalar variables
	int eventID;
	/*
	int runID;
	int spillID;
	int eventID;
	int rfID;
	int turnID;
	int rfIntensity[33];
	int fpgaTrigger[5] = {0};
	int nimTrigger[5] = {0};
	*/

	std::vector<int> hitID;
	std::vector<int> processID;
	std::vector<int> hit_trackID;
	std::vector<int> detectorID;
	std::vector<int> elementID;
	std::vector<double> tdcTime;
	std::vector<double> driftDistance;
	//std::vector<bool> hitsInTime;
	// True track data

	std::vector<int> gCharge, trackID;

	std::vector<double>
    gvx, gvy, gvz,
    gpx, gpy, gpz,
    gx_st1, gy_st1, gz_st1,
    gpx_st1, gpy_st1, gpz_st1,
    gx_st3, gy_st3, gz_st3,
    gpx_st3, gpy_st3, gpz_st3;

    std::vector<double>
    rec_dimuon_id, rec_dimuon_true_id, rec_track_id_pos, rec_track_id_neg;

	std::vector<double>
    rec_x_dimuon, rec_y_dimuon, rec_z_dimuon,
    rec_px_pos, rec_py_pos, rec_pz_pos,
    rec_px_neg, rec_py_neg, rec_pz_neg,
    rec_px_pos_tgt, rec_py_pos_tgt, rec_pz_pos_tgt,
    rec_px_neg_tgt, rec_py_neg_tgt, rec_pz_neg_tgt,
    rec_px_pos_dump, rec_py_pos_dump, rec_pz_pos_dump,
    rec_px_neg_dump, rec_py_neg_dump, rec_pz_neg_dump;

	std::vector<int>
    rec_track_id,          
    rec_charge,            
    rec_num_hits;          

	std::vector<double>
    rec_vx, rec_vy, rec_vz,
    rec_px, rec_py, rec_pz,
    rec_x_st1, rec_y_st1, rec_z_st1,
    rec_px_st1, rec_py_st1, rec_pz_st1,
    rec_x_st3, rec_y_st3, rec_z_st3,
    rec_px_st3, rec_py_st3, rec_pz_st3,
    rec_chisq, rec_chisq_target, rec_chisq_dump, rec_chisq_upstream,
    rec_x_tgt, rec_y_tgt, rec_z_tgt,
    rec_px_tgt, rec_py_tgt, rec_pz_tgt,
    rec_x_dump, rec_y_dump, rec_z_dump,
    rec_px_dump, rec_py_dump, rec_pz_dump;
};

#endif // _DimuAnaRUS.h_
