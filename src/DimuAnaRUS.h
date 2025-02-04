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

	void SetMCTrueMode(bool enable) { true_mode = enable; }
	void SetMCDimuonMode(bool enable) { true_dimu_mode = enable; }
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
	int rfIntensity[33];
	int fpgaTrigger[5] = {0};
	int nimTrigger[5] = {0};

	std::vector<int> detectorID;
	std::vector<int> elementID;
	std::vector<double> tdcTime;
	std::vector<double> driftDistance;
	std::vector<bool> hitsInTime;
	// MC track data
	// True track data
	std::vector<int> trueTrackCharges;
	std::vector<int> trueTrackID;
	std::vector<double> trueVtxPosX;
	std::vector<double> trueVtxPosY;
	std::vector<double> trueVtxPosZ;
	std::vector<double> trueVtxMomPx;
	std::vector<double> trueVtxMomPy;
	std::vector<double> trueVtxMomPz;

	std::vector<double> trueSt1PosX;
	std::vector<double> trueSt1PosY;
	std::vector<double> trueSt1PosZ;
	std::vector<double> trueSt1MomPx;
	std::vector<double> trueSt1MomPy;
	std::vector<double> trueSt1MomPz;

	std::vector<double> trueSt3PosX;
	std::vector<double> trueSt3PosY;
	std::vector<double> trueSt3PosZ;
	std::vector<double> trueSt3MomPx;
	std::vector<double> trueSt3MomPy;
	std::vector<double> trueSt3MomPz;

	std::vector<int> trueDimuonPdgId;
	std::vector<int> trueDimuonId;
	std::vector<double> trueDimuonVtxX;
	std::vector<double> trueDimuonVtxY;
	std::vector<double> trueDimuonVtxZ;

	std::vector<double> trueDimuonVtxPx;
	std::vector<double> trueDimuonVtxPy;
	std::vector<double> trueDimuonVtxPz;
	std::vector<double> trueDimuonVtxM;

	std::vector<double> trueDimuonPosPx;
	std::vector<double> trueDimuonPosPy;
	std::vector<double> trueDimuonPosPz;

	std::vector<double> trueDimuonNegPx;
	std::vector<double> trueDimuonNegPy;
	std::vector<double> trueDimuonNegPz;


	//Dimuon variables for MC or Data
	// Dimuon variables for MC or Data
	std::vector<double> dimuonVtxX;
	std::vector<double> dimuonVtxY;
	std::vector<double> dimuonVtxZ;
	std::vector<double> dimuonVtxPx;
	std::vector<double> dimuonVtxPy;
	std::vector<double> dimuonVtxPz;
	std::vector<double> dimuonMass;
	std::vector<double> dimuonX1;
	std::vector<double> dimuonX2;
	std::vector<double> dimuonXf;

	std::vector<double> muPlusVtxX;
	std::vector<double> muPlusVtxY;
	std::vector<double> muPlusVtxZ;
	std::vector<double> muMinusVtxX;
	std::vector<double> muMinusVtxY;
	std::vector<double> muMinusVtxZ;

	std::vector<double> muPlusVtxPx;
	std::vector<double> muPlusVtxPy;
	std::vector<double> muPlusVtxPz;
	std::vector<double> muMinusVtxPx;
	std::vector<double> muMinusVtxPy;
	std::vector<double> muMinusVtxPz;

	std::vector<double> muPlusChi2Target;
	std::vector<double> muPlusChi2Dump;
	std::vector<double> muPlusChi2Upstream;

	std::vector<double> muMinusChi2Target;
	std::vector<double> muMinusChi2Dump;
	std::vector<double> muMinusChi2Upstream;

	std::vector<bool> top_bot;
	std::vector<bool> bot_top;
};

#endif // _DimuAnaRUS.h_
