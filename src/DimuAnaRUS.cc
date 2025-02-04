#include <fstream>
#include <iomanip>
#include <TSystem.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <interface_main/SQRun.h>
#include <interface_main/SQHitVector.h>
#include <interface_main/SQEvent.h>
#include <interface_main/SQRun.h>
#include <interface_main/SQTrackVector.h>
#include <interface_main/SQDimuonVector.h>
#include <ktracker/SRecEvent.h>
#include <fun4all/Fun4AllReturnCodes.h>
#include <phool/PHNodeIterator.h>
#include <phool/PHIODataNode.h>
#include <phool/getClass.h>
#include <geom_svc/GeomSvc.h>
#include "DimuAnaRUS.h"
using namespace std;

DimuAnaRUS::DimuAnaRUS(const std::string& name)
  : SubsysReco  (name),
    m_file(0),
    m_tree(0),
    m_tree_name("tree"),
    m_file_name("output.root"),
    m_evt(0),
    m_sp_map(0),
    m_hit_vec(0),
    m_sq_trk_vec(0),
    true_dimu_mode(false),
    m_sq_dim_vec(0),
    saveDimuonOnly(false),
    true_mode(false),
    reco_mode(false),
    data_trig_mode(false),
    mc_trig_mode(false)
{
  ;
}

DimuAnaRUS::~DimuAnaRUS()
{
  ;
}

int DimuAnaRUS::Init(PHCompositeNode* startNode)
{
  return Fun4AllReturnCodes::EVENT_OK;
}

int DimuAnaRUS::InitRun(PHCompositeNode* startNode)
{
	m_file = new TFile(m_file_name.c_str(), "RECREATE");

	if (!m_file || m_file->IsZombie()) {
		std::cerr << "Error: Could not create file " << m_file_name << std::endl;
		exit(1);
	} else {
		std::cout << "File " << m_file->GetName() << " opened successfully." << std::endl;
	}

	m_tree = new TTree(m_tree_name.c_str(), "Tree for storing events");
	if (!m_tree) {
		std::cerr << "Error: Could not create tree " << m_tree_name << std::endl;
		exit(1);
	} else {
		std::cout << "Tree " << m_tree->GetName() << " created successfully." << std::endl;
	}

	m_tree->Branch("runID", &runID, "runID/I");
	m_tree->Branch("spillID", &spillID, "spillID/I");
	m_tree->Branch("eventID", &eventID, "eventID/I");
	m_tree->Branch("rfID", &rfID, "rfID/I");
	m_tree->Branch("turnID", &turnID, "turnID/I");
	m_tree->Branch("rfIntensity", rfIntensity, "rfIntensity[33]/I");
	m_tree->Branch("fpgaTrigger", fpgaTrigger, "fpgaTrigger[5]/I");
	m_tree->Branch("nimTrigger", nimTrigger, "nimTrigger[5]/I");

	m_tree->Branch("detectorID", &detectorID);
	m_tree->Branch("elementID", &elementID);
	m_tree->Branch("tdcTime", &tdcTime);
	m_tree->Branch("driftDistance", &driftDistance);
	m_tree->Branch("hitsInTime", &hitsInTime);

	if (true_mode==true){
		m_tree->Branch("trueTrackID", &trueTrackID);
		m_tree->Branch("trueTrackCharges", &trueTrackCharges);
		m_tree->Branch("trueVtxPosX", &trueVtxPosX);
		m_tree->Branch("trueVtxPosY", &trueVtxPosY);
		m_tree->Branch("trueVtxPosZ", &trueVtxPosZ);
		m_tree->Branch("trueVtxMomPx", &trueVtxMomPx);
		m_tree->Branch("trueVtxMomPy", &trueVtxMomPy);
		m_tree->Branch("trueVtxMomPz", &trueVtxMomPz);

		m_tree->Branch("trueSt1PosX", &trueSt1PosX);
		m_tree->Branch("trueSt1PosY", &trueSt1PosY);
		m_tree->Branch("trueSt1PosZ", &trueSt1PosZ);
		m_tree->Branch("trueSt1MomPx", &trueSt1MomPx);
		m_tree->Branch("trueSt1MomPy", &trueSt1MomPy);
		m_tree->Branch("trueSt1MomPz", &trueSt1MomPz);

		m_tree->Branch("trueSt3PosX", &trueSt3PosX);
		m_tree->Branch("trueSt3PosY", &trueSt3PosY);
		m_tree->Branch("trueSt3PosZ", &trueSt3PosZ);
		m_tree->Branch("trueSt3MomPx", &trueSt3MomPx);
		m_tree->Branch("trueSt3MomPy", &trueSt3MomPy);
		m_tree->Branch("trueSt3MomPz", &trueSt3MomPz);

		if(true_dimu_mode==true){

			// Set the branch addresses for the variables
			m_tree->SetBranchAddress("trueDimuonPdgId", &trueDimuonPdgId);
			m_tree->SetBranchAddress("trueDimuonId", &trueDimuonId);
			m_tree->SetBranchAddress("trueDimuonVtxX", &trueDimuonVtxX);
			m_tree->SetBranchAddress("trueDimuonVtxY", &trueDimuonVtxY);
			m_tree->SetBranchAddress("trueDimuonVtxZ", &trueDimuonVtxZ);
			m_tree->SetBranchAddress("trueDimuonVtxPx", &trueDimuonVtxPx);
			m_tree->SetBranchAddress("trueDimuonVtxPy", &trueDimuonVtxPy);
			m_tree->SetBranchAddress("trueDimuonVtxPz", &trueDimuonVtxPz);
			m_tree->SetBranchAddress("trueDimuonVtxM", &trueDimuonVtxM);
			m_tree->SetBranchAddress("trueDimuonPosPx", &trueDimuonPosPx);
			m_tree->SetBranchAddress("trueDimuonPosPy", &trueDimuonPosPy);
			m_tree->SetBranchAddress("trueDimuonPosPz", &trueDimuonPosPz);
			m_tree->SetBranchAddress("trueDimuonNegPx", &trueDimuonNegPx);
			m_tree->SetBranchAddress("trueDimuonNegPy", &trueDimuonNegPy);
			m_tree->SetBranchAddress("trueDimuonNegPz", &trueDimuonNegPz);
		}

	}
	if (reco_mode==true){
		m_tree->Branch("dimuonVtxX", &dimuonVtxX);
		m_tree->Branch("dimuonVtxY", &dimuonVtxY);
		m_tree->Branch("dimuonVtxZ", &dimuonVtxZ);
		m_tree->Branch("dimuonVtxPx", &dimuonVtxPx);
		m_tree->Branch("dimuonVtxPy", &dimuonVtxPy);
		m_tree->Branch("dimuonVtxPz", &dimuonVtxPz);
		m_tree->Branch("dimuonMass", &dimuonMass);
		m_tree->Branch("dimuonX1", &dimuonX1);
		m_tree->Branch("dimuonX2", &dimuonX2);
		m_tree->Branch("dimuonXf", &dimuonXf);

		m_tree->Branch("muPlusVtxX", &muPlusVtxX);
		m_tree->Branch("muPlusVtxY", &muPlusVtxY);
		m_tree->Branch("muPlusVtxZ", &muPlusVtxZ);
		m_tree->Branch("muMinusVtxX", &muMinusVtxX);
		m_tree->Branch("muMinusVtxY", &muMinusVtxY);
		m_tree->Branch("muMinusVtxZ", &muMinusVtxZ);

		m_tree->Branch("muPlusVtxPx", &muPlusVtxPx);
		m_tree->Branch("muPlusVtxPy", &muPlusVtxPy);
		m_tree->Branch("muPlusVtxPz", &muPlusVtxPz);
		m_tree->Branch("muMinusVtxPx", &muMinusVtxPx);
		m_tree->Branch("muMinusVtxPy", &muMinusVtxPy);
		m_tree->Branch("muMinusVtxPz", &muMinusVtxPz);
		m_tree->Branch("top_bot", &top_bot);
		m_tree->Branch("bot_top", &bot_top);
	}

	if(true_dimu_mode){ 
		m_true_vec_dim  = findNode::getClass<SQDimuonVector>(startNode, "SQTruthDimuonVector");
		if (!m_true_vec_dim) {
			return Fun4AllReturnCodes::ABORTEVENT;
		}

	}
	if (true_mode) {
		m_vec_trk = findNode::getClass<SQTrackVector>(startNode, "SQTruthTrackVector");
		if (!m_vec_trk) {
			return Fun4AllReturnCodes::ABORTEVENT;
		}
	}

	if (reco_mode) {
		m_sq_trk_vec = findNode::getClass<SQTrackVector>(startNode, "SQRecTrackVector");
		m_sq_dim_vec = findNode::getClass<SQDimuonVector>(startNode, "SQRecDimuonVector_PM");

		if (!m_sq_trk_vec) {
			std::cerr << "Error: m_sq_trk_vec is null!" << std::endl;
			return Fun4AllReturnCodes::ABORTEVENT;
		}

		if (!m_sq_dim_vec) {
			std::cerr << "Error: m_sq_dim_vec is null!" << std::endl;
			return Fun4AllReturnCodes::ABORTEVENT;
		}
	}
	m_evt = findNode::getClass<SQEvent>(startNode, "SQEvent");
	m_hit_vec = findNode::getClass<SQHitVector>(startNode, "SQHitVector");
	if (!m_evt || !m_hit_vec) {
		return Fun4AllReturnCodes::ABORTEVENT;
	}

	if(reco_mode ==true && data_trig_mode ==true){
		cout << "inside the data roadset mode: "<<endl;
		SQRun* sq_run = findNode::getClass<SQRun>(startNode, "SQRun");
		if (!sq_run) std::cout << "Error: SQRun  is null!" << std::endl;
		if (!sq_run) return Fun4AllReturnCodes::ABORTEVENT;
		int LBtop = sq_run->get_v1495_id(2);
		int LBbot = sq_run->get_v1495_id(3);
		int ret = m_rs.LoadConfig(LBtop, LBbot);
		if (ret != 0) {
			cout << "!!WARNING!!  OnlMonTrigEP::InitRunOnlMon():  roadset.LoadConfig returned " << ret << ".\n";
		}
		cout <<"Roadset " << m_rs.str(1) << endl;

	}

	cout << "beginning of mc trig "<< endl;
	if(reco_mode ==true && mc_trig_mode ==true){
		int ret = m_rs.LoadConfig(131);
		if (ret != 0) {
			cout << "!!WARNING!!  OnlMonTrigEP::InitRunOnlMon():  roadset.LoadConfig returned " << ret << ".\n";
		}
		//cout <<"Roadset " << m_rs.str(1) << endl;
	}
	return Fun4AllReturnCodes::EVENT_OK;
}


int DimuAnaRUS::process_event(PHCompositeNode* startNode)
{
	ResetBranches();
/*
	if (! m_evt->get_trigger(SQEvent::MATRIX1)) {
		return Fun4AllReturnCodes::EVENT_OK;
 	 }
*/

	if (saveDimuonOnly && m_sq_dim_vec->empty()) {
		return 0;  // Skip this event if no dimuons are present and the mode is enabled
        }

	runID = m_evt->get_run_id();
	spillID = m_evt->get_spill_id();
	eventID = m_evt->get_event_id();
	rfID = m_evt->get_qie_rf_id();
	turnID = m_evt->get_qie_turn_id();

	fpgaTrigger[0] = m_evt->get_trigger(SQEvent::MATRIX1);
	fpgaTrigger[1] = m_evt->get_trigger(SQEvent::MATRIX2);
	fpgaTrigger[2] = m_evt->get_trigger(SQEvent::MATRIX3);
	fpgaTrigger[3] = m_evt->get_trigger(SQEvent::MATRIX4);
	fpgaTrigger[4] = m_evt->get_trigger(SQEvent::MATRIX5);

	nimTrigger[0] = m_evt->get_trigger(SQEvent::NIM1);
	nimTrigger[1] = m_evt->get_trigger(SQEvent::NIM2);
	nimTrigger[2] = m_evt->get_trigger(SQEvent::NIM3);
	nimTrigger[3] = m_evt->get_trigger(SQEvent::NIM4);
	nimTrigger[4] = m_evt->get_trigger(SQEvent::NIM5);
	for (int i = -16; i <= 16; ++i) {
    	rfIntensity[i + 16] = m_evt->get_qie_rf_intensity(i);
}

if (m_hit_vec) {
    for (int ihit = 0; ihit < m_hit_vec->size(); ++ihit) {
        SQHit* hit = m_hit_vec->at(ihit);
        detectorID.push_back(hit->get_detector_id());
        elementID.push_back(hit->get_element_id());
        tdcTime.push_back(hit->get_tdc_time());
        driftDistance.push_back(hit->get_drift_distance());
        hitsInTime.push_back(hit->is_in_time());
    }
}

if(true_mode == true){
	for (unsigned int ii = 0; ii < m_vec_trk->size(); ii++) {
		SQTrack* trk = m_vec_trk->at(ii);

		trueTrackCharges.push_back(trk->get_charge());
		trueTrackID.push_back(trk->get_track_id());
		trueVtxPosX.push_back(trk->get_pos_vtx().X());
		trueVtxPosY.push_back(trk->get_pos_vtx().Y());
		trueVtxPosZ.push_back(trk->get_pos_vtx().Z());
		trueVtxMomPx.push_back(trk->get_mom_vtx().Px());
		trueVtxMomPy.push_back(trk->get_mom_vtx().Py());
		trueVtxMomPz.push_back(trk->get_mom_vtx().Pz());

		trueSt1PosX.push_back(trk->get_pos_st1().X());
		trueSt1PosY.push_back(trk->get_pos_st1().Y());
		trueSt1PosZ.push_back(trk->get_pos_st1().Z());
		trueSt1MomPx.push_back(trk->get_mom_st1().Px());
		trueSt1MomPy.push_back(trk->get_mom_st1().Py());
		trueSt1MomPz.push_back(trk->get_mom_st1().Pz());

		trueSt3PosX.push_back(trk->get_pos_st3().X());
		trueSt3PosY.push_back(trk->get_pos_st3().Y());
		trueSt3PosZ.push_back(trk->get_pos_st3().Z());
		trueSt3MomPx.push_back(trk->get_mom_st3().Px());
		trueSt3MomPy.push_back(trk->get_mom_st3().Py());
		trueSt3MomPz.push_back(trk->get_mom_st3().Pz());
	}

	if(true_dimu_mode==true){
		for (unsigned int ii = 0; ii < m_true_vec_dim->size(); ii++) {
			SQDimuon* dim = m_true_vec_dim->at(ii);
			trueDimuonId.push_back(dim->get_dimuon_id());
			trueDimuonPdgId.push_back(dim->get_pdg_id());
			trueDimuonVtxX.push_back(dim->get_pos().X());
			trueDimuonVtxY.push_back(dim->get_pos().Y());
			trueDimuonVtxZ.push_back(dim->get_pos().Z());
			trueDimuonVtxPx.push_back(dim->get_mom().Px());
			trueDimuonVtxPy.push_back(dim->get_mom().Py());
			trueDimuonVtxPz.push_back(dim->get_mom().Pz()); 
			trueDimuonVtxM.push_back(dim->get_mom().M()); 

			trueDimuonPosPx.push_back(dim->get_mom_pos().Px());
			trueDimuonPosPy.push_back(dim->get_mom_pos().Py());
			trueDimuonPosPz.push_back(dim->get_mom_pos().Pz());
			trueDimuonNegPx.push_back(dim->get_mom_neg().Px());
			trueDimuonNegPy.push_back(dim->get_mom_neg().Py());
			trueDimuonNegPz.push_back(dim->get_mom_neg().Pz());
		}
	}
}

cout << "reco mode: "<< reco_mode << endl;
std::cout << "Size of m_sq_dim_vec: " << m_sq_dim_vec->size() << std::endl;

if(reco_mode == true){
    for (auto it = m_sq_dim_vec->begin(); it != m_sq_dim_vec->end(); it++) {
	    SRecDimuon& sdim = dynamic_cast<SRecDimuon&>(**it);
	    sdim.calcVariables(); //eventually need to assign 1 or 2 depending on the target or dump; more at https://github.com/E1039-Collaboration/e1039-core/pull/149
	    int trk_id_pos = sdim.get_track_id_pos();
	    int trk_id_neg = sdim.get_track_id_neg();
	    SRecTrack& trk_pos = dynamic_cast<SRecTrack&>(*(m_sq_trk_vec->at(trk_id_pos))); 
	    SRecTrack& trk_neg = dynamic_cast<SRecTrack&>(*(m_sq_trk_vec->at(trk_id_neg))); 
	    // Fill dimuon vectors
	    dimuonVtxX.push_back(sdim.get_pos().X());
	    dimuonVtxY.push_back(sdim.get_pos().Y());
	    dimuonVtxZ.push_back(sdim.get_pos().Z());
	    dimuonVtxPx.push_back(sdim.get_mom().Px());
	    dimuonVtxPy.push_back(sdim.get_mom().Py());
	    dimuonVtxPz.push_back(sdim.get_mom().Pz());
	    dimuonMass.push_back(sdim.get_mom().M());
	    dimuonX1.push_back(sdim.x1);
	    dimuonX2.push_back(sdim.x2);
	    dimuonXf.push_back(sdim.xF);
	    // Fill mu_plus vectors
	    muPlusVtxX.push_back(trk_pos.get_pos_vtx().X());
	    muPlusVtxY.push_back(trk_pos.get_pos_vtx().Y());
	    muPlusVtxZ.push_back(trk_pos.get_pos_vtx().Z());
	    muPlusVtxPx.push_back(trk_pos.get_mom_vtx().X());
	    muPlusVtxPy.push_back(trk_pos.get_mom_vtx().Y());
	    muPlusVtxPz.push_back(trk_pos.get_mom_vtx().Z());
	    // Fill mu_minus vectors
	    muMinusVtxX.push_back(trk_neg.get_pos_vtx().X());
	    muMinusVtxY.push_back(trk_neg.get_pos_vtx().Y());
	    muMinusVtxZ.push_back(trk_neg.get_pos_vtx().Z());
	    muMinusVtxPx.push_back(trk_neg.get_mom_vtx().X());
	    muMinusVtxPy.push_back(trk_neg.get_mom_vtx().Y());
	    muMinusVtxPz.push_back(trk_neg.get_mom_vtx().Z());
	    bool pos_top = m_rs.PosTop()->FindRoad(trk_pos.getTriggerRoad());
	    bool pos_bot = m_rs.PosBot()->FindRoad(trk_pos.getTriggerRoad());
	    bool neg_top = m_rs.NegTop()->FindRoad(trk_neg.getTriggerRoad());
	    bool neg_bot = m_rs.NegBot()->FindRoad(trk_neg.getTriggerRoad());
	    bool top_bot_ = pos_top && neg_bot;
	    bool bot_top_ =  pos_bot && neg_top;
	    top_bot.push_back(top_bot_);
	    bot_top.push_back(bot_top_);
    }   
}
	m_tree->Fill();
	return Fun4AllReturnCodes::EVENT_OK;
}

int DimuAnaRUS::End(PHCompositeNode* startNode)
{
  m_file->cd();
  m_file->Write();
  m_file->Close();  
  return Fun4AllReturnCodes::EVENT_OK;
}


void DimuAnaRUS::ResetBranches() {
	detectorID.clear();
	elementID.clear();
	tdcTime.clear();
	driftDistance.clear();
	hitsInTime.clear();
	//mc events
	trueTrackCharges.clear();
	trueTrackID.clear();
	trueVtxPosX.clear();
	trueVtxPosY.clear();
	trueVtxPosZ.clear();
	trueVtxMomPx.clear();
	trueVtxMomPy.clear();
	trueVtxMomPz.clear();

	trueSt1PosX.clear();
	trueSt1PosY.clear();
	trueSt1PosZ.clear();
	trueSt1MomPx.clear();
	trueSt1MomPy.clear();
	trueSt1MomPz.clear();

	trueSt3PosX.clear();
	trueSt3PosY.clear();
	trueSt3PosZ.clear();
	trueSt3MomPx.clear();
	trueSt3MomPy.clear();
	trueSt3MomPz.clear();

	trueDimuonPdgId.clear();
	trueDimuonId.clear();
	trueDimuonVtxX.clear();
	trueDimuonVtxY.clear();
	trueDimuonVtxZ.clear();
	trueDimuonVtxPx.clear();
	trueDimuonVtxPy.clear();
	trueDimuonVtxPz.clear();
	trueDimuonVtxM.clear();
	trueDimuonPosPx.clear();
	trueDimuonPosPy.clear();
	trueDimuonPosPz.clear();
	trueDimuonNegPx.clear();
	trueDimuonNegPy.clear();
	trueDimuonNegPz.clear();

	//reco variables
	dimuonVtxX.clear();
	dimuonVtxY.clear();
	dimuonVtxZ.clear();
	dimuonVtxPx.clear();
	dimuonVtxPy.clear();
	dimuonVtxPz.clear();
	dimuonMass.clear();
	dimuonX1.clear();
	dimuonX2.clear();
	dimuonXf.clear();
	muPlusVtxX.clear();
	muPlusVtxY.clear();
	muPlusVtxZ.clear();
	muMinusVtxX.clear();
	muMinusVtxY.clear();
	muMinusVtxZ.clear();
	muPlusVtxPx.clear();
	muPlusVtxPy.clear();
	muPlusVtxPz.clear();
	muMinusVtxPx.clear();
	muMinusVtxPy.clear();
	muMinusVtxPz.clear();
}
