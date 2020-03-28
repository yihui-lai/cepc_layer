#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"
#include "TRandom.h"
#include "TList.h"

//produce the ana file
//change the tag and energy below to analyse different root files

//const float sampling_fraction = 100 / 2.1;
void ana_dream()
{
    char inputfilename[120];
    char outputfilename[120];
    char tempfilename[120];
    const char *parti[2];
    parti[0] = "electron";
    parti[1] = "pion";

    ///////////////////////////////////////////
    //chnage the following parameters
    ///////////////////////////////////////////
    int select_particle = 1;                  //0 for e-, 1 for pi-
    char tag[40] = "_"; //tag
    double ene = 1;                          //energy

    ///////////////////////////////////////////
    //end
    ///////////////////////////////////////////

    sprintf(outputfilename, "%s_%s_%gGeV_ana.root", tag, parti[select_particle], ene);
    sprintf(inputfilename, "%s_%s_%gGeV.root", tag, parti[select_particle], ene);
    bool Count_CherenPhoton_in_scinti = false;

    double min_norm = 0;
    double max_norm = 1.1;
    int nbin_norm = 6000;
    TH1F *hTotalE = new TH1F("hTotalE", "energy total world /true", nbin_norm, min_norm, max_norm);

    TH1F *hecalE = new TH1F("hecalE", "ecal energy /true", nbin_norm, min_norm, max_norm);
    TH1F *hecal_absorbE = new TH1F("hecal_absorbE", "energy in absorb fiber/true", nbin_norm, min_norm, max_norm);
    TH1F *hecal_scintiE = new TH1F("hecal_scintiE", "energy in scinti fiber/true", nbin_norm, min_norm, max_norm);
    TH1F *hscintiE = new TH1F("hscintiE", "Ion energy in scinti fiber/true", nbin_norm, min_norm, max_norm);
    TH1F *hecal_cherenE = new TH1F("hecal_cherenE", "energy in cheren fiber/true", nbin_norm, min_norm, max_norm);

    //pi-, e+, e-, gamma, pi+, k+, n, p
    //the total energy deposition in each part of the Dream detector
    //how different particels deposit Ion energy in scinti fibers
    TH1F *hscintiE_en = new TH1F("hscintiE_en", "electron scintillating fiber energy /true", nbin_norm, min_norm, max_norm);
    TH1F *hscintiE_en_ion = new TH1F("hscintiE_en_ion", "electron scintillating fiber Ionenergy /true", nbin_norm, min_norm, max_norm);
    TH1F *hcherenE_en = new TH1F("hcherenE_en", " electron cherenkov fiber energy /true", nbin_norm, min_norm, max_norm);

    TH1F *hscintiE_ep = new TH1F("hscintiE_ep", "positron scintillating fiber energy /true", nbin_norm, min_norm, max_norm);
    TH1F *hscintiE_ep_ion = new TH1F("hscintiE_ep_ion", "positron scintillating fiber Ionenergy /true", nbin_norm, min_norm, max_norm);
    TH1F *hcherenE_ep = new TH1F("hcherenE_ep", " positron cherenkov fiber energy /true", nbin_norm, min_norm, max_norm);

    TH1F *hscintiE_gamma = new TH1F("hscintiE_gamma", "photon scintillating fiber energy /true", nbin_norm, min_norm, max_norm);
    TH1F *hscintiE_gamma_ion = new TH1F("hscintiE_gamma_ion", "photon scintillating fiber Ionenergy /true", nbin_norm, min_norm, max_norm);
    TH1F *hcherenE_gamma = new TH1F("hcherenE_gamma", " photon cherenkov fiber energy /true", nbin_norm, min_norm, max_norm);

    TH1F *hscintiE_n = new TH1F("hscintiE_n", "neutron scintillating fiber energy /true", nbin_norm, min_norm, max_norm);
    TH1F *hscintiE_n_ion = new TH1F("hscintiE_n_ion", "neutron scintillating fiber Ionenergy /true", nbin_norm, min_norm, max_norm);
    TH1F *hcherenE_n = new TH1F("hcherenE_n", " neutron cherenkov fiber energy /true", nbin_norm, min_norm, max_norm);

    TH1F *hscintiE_p = new TH1F("hscintiE_p", "proton scintillating fiber energy /true", nbin_norm, min_norm, max_norm);
    TH1F *hscintiE_p_ion = new TH1F("hscintiE_p_ion", "proton scintillating fiber Ionenergy /true", nbin_norm, min_norm, max_norm);
    TH1F *hcherenE_p = new TH1F("hcherenE_p", " proton cherenkov fiber energy /true", nbin_norm, min_norm, max_norm);

    TH1F *hscintiE_pin = new TH1F("hscintiE_pin", "pion- scintillating fiber energy /true", nbin_norm, min_norm, max_norm);
    TH1F *hscintiE_pin_ion = new TH1F("hscintiE_pin_ion", "pion- scintillating fiber Ionenergy /true", nbin_norm, min_norm, max_norm);
    TH1F *hcherenE_pin = new TH1F("hcherenE_pin", " pion- cherenkov fiber energy /true", nbin_norm, min_norm, max_norm);

    TH1F *hscintiE_pip = new TH1F("hscintiE_pip", "pion+ scintillating fiber energy /true", nbin_norm, min_norm, max_norm);
    TH1F *hscintiE_pip_ion = new TH1F("hscintiE_pip_ion", "pion+ scintillating fiber Ionenergy /true", nbin_norm, min_norm, max_norm);
    TH1F *hcherenE_pip = new TH1F("hcherenE_pip", " pion+ cherenkov fiber energy /true", nbin_norm, min_norm, max_norm);

    //the cherenkov photons generated inside of cherenkov fibers
    double max_n = 4000000;
    int max_nn = max_n / 5000;
    TH1F *hcherenN = new TH1F("hcherenN", "number cerenkov photons", max_nn, 0, max_n);
    TH1F *hcherenN_en = new TH1F("hcherenN_en", "number cerenkov photons", max_nn, 0, max_n);
    TH1F *hcherenN_ep = new TH1F("hcherenN_ep", "number cerenkov photons", max_nn, 0, max_n);
    TH1F *hcherenN_gamma = new TH1F("hcherenN_gamma", "number cerenkov photons", max_nn, 0, max_n);
    TH1F *hcherenN_n = new TH1F("hcherenN_n", "number cerenkov photons", max_nn, 0, max_n);
    TH1F *hcherenN_p = new TH1F("hcherenN_p", "number cerenkov photons", max_nn, 0, max_n);
    TH1F *hcherenN_pin = new TH1F("hcherenN_pin", "number cerenkov photons", max_nn, 0, max_n);
    TH1F *hcherenN_pip = new TH1F("hcherenN_pip", "number cerenkov photons", max_nn, 0, max_n);

    // the total energy distribution in space and time
    TH2F *h_localtime_z_st = new TH2F("h_localtime_z_st", "", 2501, 0., 5002., 5010, 0., 5.01);
    TH2F *h_localtime_z_st_en = new TH2F("h_localtime_z_st_en", "", 2501, 0., 5002., 5010, 0., 5.01);
    TH2F *h_localtime_z_st_ep = new TH2F("h_localtime_z_st_ep", "", 2501, 0., 5002., 5010, 0., 5.01);
    TH2F *h_localtime_z_st_gamma = new TH2F("h_localtime_z_st_gamma", "", 2501, 0., 5002., 5010, 0., 5.01);
    TH2F *h_localtime_z_st_n = new TH2F("h_localtime_z_st_n", "", 2501, 0., 5002., 5010, 0., 5.01);
    TH2F *h_localtime_z_st_p = new TH2F("h_localtime_z_st_p", "", 2501, 0., 5002., 5010, 0., 5.01);
    TH2F *h_localtime_z_st_pin = new TH2F("h_localtime_z_st_pin", "", 2501, 0., 5002., 5010, 0., 5.01);
    TH2F *h_localtime_z_st_pip = new TH2F("h_localtime_z_st_pip", "", 2501, 0., 5002., 5010, 0., 5.01);
    TH1F *h_parentID_Edep = new TH1F("h_parentID_Edep", "", 10000, -5000, 5000);

    double eventnumber = 0;
    std::cout << "running on normal files" << std::endl;
    cout << "Try to open file " << inputfilename << endl;
    TFile *f = new TFile(inputfilename);

    if (f->IsOpen())
    {
        if (f->IsZombie() || f->TestBit(TFile::kRecovered))
        {
            cout << "*****************************************Zombie File*****************************************" << endl;
        }
        else
        {
            printf("File opened successfully\n");
        }
    }
    else
    {
        printf("File fail to open\n");
    }

    TTree *t1 = (TTree *)f->Get("tree");
    //list->Add(t1);

    vector<float> *inputMomentum = new vector<float>;
    float depositedEnergyEscapeWorld;
    float depositedEnergyTotal, depositedEnergyWorld;
    float depositedEnergyTiming_f, depositedEnergyTiming_r;
    float depositedEnergyECAL_f[3], depositedEnergyECAL_r[3];
    float depositedEnergyHCALAct, depositedEnergyHCALPas;
    float depositedEnergyServices;
    float depositedEnergyTimingGap;
    float depositedEnergyEcalGap;
    float depositedEnergyEcalDet;
    float depositedEnergySolenoid;

    float depositedElecEnergyTotal, depositedElecEnergyWorld;
    float depositedElecEnergyTiming_f, depositedElecEnergyTiming_r;
    float depositedElecEnergyECAL_f[3], depositedElecEnergyECAL_r[3];
    float depositedElecEnergyHCALAct, depositedElecEnergyHCALPas;
    float depositedElecEnergyServices;
    float depositedElecEnergyTimingGap;
    float depositedElecEnergyEcalGap;
    float depositedElecEnergyEcalDet;
    float depositedElecEnergySolenoid;

    float depositedIonEnergyTotal, depositedIonEnergyWorld;
    float depositedIonEnergyTiming_f, depositedIonEnergyTiming_r;
    float depositedIonEnergyECAL_f[3], depositedIonEnergyECAL_r[3]; //absorb, scinti, cheren
    float depositedIonEnergyHCALAct, depositedIonEnergyHCALPas;
    float depositedIonEnergyServices;
    float depositedIonEnergyTimingGap;
    float depositedIonEnergyEcalGap;
    float depositedIonEnergyEcalDet;
    float depositedIonEnergySolenoid;

    float depositedEnergyECAL_absorb_f_particleID[8];
    float depositedEnergyECAL_absorb_r_particleID[8];
    float depositedIonEnergyECAL_absorb_f_particleID[8];
    float depositedIonEnergyECAL_absorb_r_particleID[8];

    float depositedEnergyECAL_scinti_f_particleID[8];
    float depositedEnergyECAL_scinti_r_particleID[8];
    float depositedIonEnergyECAL_scinti_f_particleID[8];
    float depositedIonEnergyECAL_scinti_r_particleID[8];

    float depositedEnergyECAL_cheren_f_particleID[8];
    float depositedEnergyECAL_cheren_r_particleID[8];
    float depositedIonEnergyECAL_cheren_f_particleID[8];
    float depositedIonEnergyECAL_cheren_r_particleID[8];

    int tot_phot_cer_Timing_f_total;
    int tot_phot_cer_Timing_r_total;

    int tot_phot_cer_ECAL_scinti_f_total;
    int tot_phot_cer_ECAL_scinti_r_total;
    int tot_phot_cer_ECAL_scinti_f_particleID[8]; //cer in front cheren fiber
    int tot_phot_cer_ECAL_scinti_r_particleID[8]; //cer in rear cheren fiber
    int tot_phot_cer_ECAL_cheren_f_total;
    int tot_phot_cer_ECAL_cheren_r_total;
    int tot_phot_cer_ECAL_cheren_f_particleID[8]; //cer in front cheren fiber
    int tot_phot_cer_ECAL_cheren_r_particleID[8]; //cer in rear cheren fiber

    int tot_phot_cer_HCAL;

    t1->SetBranchAddress("inputMomentum", &inputMomentum);

    t1->SetBranchAddress("depositedEnergyEscapeWorld", &depositedEnergyEscapeWorld);

    t1->SetBranchAddress("depositedEnergyTotal", &depositedEnergyTotal);
    t1->SetBranchAddress("depositedEnergyWorld", &depositedEnergyWorld);
    t1->SetBranchAddress("depositedEnergyTiming_f", &depositedEnergyTiming_f);
    t1->SetBranchAddress("depositedEnergyTiming_r", &depositedEnergyTiming_r);
    t1->SetBranchAddress("depositedEnergyECAL_f", &depositedEnergyECAL_f);
    t1->SetBranchAddress("depositedEnergyECAL_r", &depositedEnergyECAL_r);
    t1->SetBranchAddress("depositedEnergyHCALAct", &depositedEnergyHCALAct);
    t1->SetBranchAddress("depositedEnergyHCALPas", &depositedEnergyHCALPas);
    t1->SetBranchAddress("depositedEnergyServices", &depositedEnergyServices);
    t1->SetBranchAddress("depositedEnergyTimingGap", &depositedEnergyTimingGap);
    t1->SetBranchAddress("depositedEnergyEcalGap", &depositedEnergyEcalGap);
    t1->SetBranchAddress("depositedEnergyEcalDet", &depositedEnergyEcalDet);
    t1->SetBranchAddress("depositedEnergySolenoid", &depositedEnergySolenoid);

    t1->SetBranchAddress("depositedElecEnergyTotal", &depositedElecEnergyTotal);
    t1->SetBranchAddress("depositedElecEnergyWorld", &depositedElecEnergyWorld);
    t1->SetBranchAddress("depositedElecEnergyTiming_f", &depositedElecEnergyTiming_f);
    t1->SetBranchAddress("depositedElecEnergyTiming_r", &depositedElecEnergyTiming_r);
    t1->SetBranchAddress("depositedElecEnergyECAL_f", &depositedElecEnergyECAL_f);
    t1->SetBranchAddress("depositedElecEnergyECAL_r", &depositedElecEnergyECAL_r);
    t1->SetBranchAddress("depositedElecEnergyHCALAct", &depositedElecEnergyHCALAct);
    t1->SetBranchAddress("depositedElecEnergyHCALPas", &depositedElecEnergyHCALPas);
    t1->SetBranchAddress("depositedElecEnergyServices", &depositedElecEnergyServices);
    t1->SetBranchAddress("depositedElecEnergyTimingGap", &depositedElecEnergyTimingGap);
    t1->SetBranchAddress("depositedElecEnergyEcalGap", &depositedElecEnergyEcalGap);
    t1->SetBranchAddress("depositedElecEnergyEcalDet", &depositedElecEnergyEcalDet);
    t1->SetBranchAddress("depositedElecEnergySolenoid", &depositedElecEnergySolenoid);

    t1->SetBranchAddress("depositedIonEnergyTotal", &depositedIonEnergyTotal);
    t1->SetBranchAddress("depositedIonEnergyWorld", &depositedIonEnergyWorld);
    t1->SetBranchAddress("depositedIonEnergyTiming_f", &depositedIonEnergyTiming_f);
    t1->SetBranchAddress("depositedIonEnergyTiming_r", &depositedIonEnergyTiming_r);
    t1->SetBranchAddress("depositedIonEnergyECAL_f", &depositedIonEnergyECAL_f);
    t1->SetBranchAddress("depositedIonEnergyECAL_r", &depositedIonEnergyECAL_r);
    t1->SetBranchAddress("depositedIonEnergyHCALAct", &depositedIonEnergyHCALAct);
    t1->SetBranchAddress("depositedIonEnergyHCALPas", &depositedIonEnergyHCALPas);
    t1->SetBranchAddress("depositedIonEnergyServices", &depositedIonEnergyServices);
    t1->SetBranchAddress("depositedIonEnergyTimingGap", &depositedIonEnergyTimingGap);
    t1->SetBranchAddress("depositedIonEnergyEcalGap", &depositedIonEnergyEcalGap);
    t1->SetBranchAddress("depositedIonEnergyEcalDet", &depositedIonEnergyEcalDet);
    t1->SetBranchAddress("depositedIonEnergySolenoid", &depositedIonEnergySolenoid);

    t1->SetBranchAddress("depositedEnergyECAL_absorb_f_particleID", &depositedEnergyECAL_absorb_f_particleID);
    t1->SetBranchAddress("depositedEnergyECAL_absorb_r_particleID", &depositedEnergyECAL_absorb_r_particleID);
    t1->SetBranchAddress("depositedEnergyECAL_scinti_f_particleID", &depositedEnergyECAL_scinti_f_particleID);
    t1->SetBranchAddress("depositedEnergyECAL_scinti_r_particleID", &depositedEnergyECAL_scinti_r_particleID);
    t1->SetBranchAddress("depositedEnergyECAL_cheren_f_particleID", &depositedEnergyECAL_cheren_f_particleID);
    t1->SetBranchAddress("depositedEnergyECAL_cheren_r_particleID", &depositedEnergyECAL_cheren_r_particleID);

    t1->SetBranchAddress("depositedIonEnergyECAL_absorb_f_particleID", &depositedIonEnergyECAL_absorb_f_particleID);
    t1->SetBranchAddress("depositedIonEnergyECAL_absorb_r_particleID", &depositedIonEnergyECAL_absorb_r_particleID);
    t1->SetBranchAddress("depositedIonEnergyECAL_scinti_f_particleID", &depositedIonEnergyECAL_scinti_f_particleID);
    t1->SetBranchAddress("depositedIonEnergyECAL_scinti_r_particleID", &depositedIonEnergyECAL_scinti_r_particleID);
    t1->SetBranchAddress("depositedIonEnergyECAL_cheren_f_particleID", &depositedIonEnergyECAL_cheren_f_particleID);
    t1->SetBranchAddress("depositedIonEnergyECAL_cheren_r_particleID", &depositedIonEnergyECAL_cheren_r_particleID);

    t1->SetBranchAddress("tot_phot_cer_Timing_f_total", &tot_phot_cer_Timing_f_total);
    t1->SetBranchAddress("tot_phot_cer_Timing_r_total", &tot_phot_cer_Timing_r_total);
    t1->SetBranchAddress("tot_phot_cer_ECAL_scinti_f_total", &tot_phot_cer_ECAL_scinti_f_total);
    t1->SetBranchAddress("tot_phot_cer_ECAL_scinti_r_total", &tot_phot_cer_ECAL_scinti_r_total);
    t1->SetBranchAddress("tot_phot_cer_ECAL_cheren_f_total", &tot_phot_cer_ECAL_cheren_f_total);
    t1->SetBranchAddress("tot_phot_cer_ECAL_cheren_r_total", &tot_phot_cer_ECAL_cheren_r_total);
    t1->SetBranchAddress("tot_phot_cer_ECAL_scinti_f_particleID", &tot_phot_cer_ECAL_scinti_f_particleID);
    t1->SetBranchAddress("tot_phot_cer_ECAL_scinti_r_particleID", &tot_phot_cer_ECAL_scinti_r_particleID);
    t1->SetBranchAddress("tot_phot_cer_ECAL_cheren_f_particleID", &tot_phot_cer_ECAL_cheren_f_particleID);
    t1->SetBranchAddress("tot_phot_cer_ECAL_cheren_r_particleID", &tot_phot_cer_ECAL_cheren_r_particleID);
    t1->SetBranchAddress("tot_phot_cer_HCAL", &tot_phot_cer_HCAL);

    Int_t nentries = (Int_t)t1->GetEntries();
    eventnumber += nentries;
    for (Int_t i = 0; i < nentries; i++)
    {
        t1->GetEntry(i);
        float trueE = 9999999.;
        if ((*inputMomentum)[3] > 0)
            trueE = (*inputMomentum)[3];

        //float eee = depositedEnergyTiming_f + depositedEnergyTiming_r + depositedEnergyECAL_f + depositedEnergyECAL_r + depositedEnergyHCALAct + depositedEnergyHCALPas + depositedEnergyWorld + depositedEnergyServices + depositedEnergyTimingGap + depositedEnergyEcalGap + depositedEnergyEcalDet + depositedEnergySolenoid;
        //float fff = depositedEnergyTotal + depositedEnergyEscapeWorld;
        //float ecaltotal = depositedEnergyTiming_f + depositedEnergyTiming_r + depositedEnergyECAL_f + depositedEnergyECAL_r;
        //hHcalPasE->Fill(depositedEnergyHCALPas / trueE);
        //hHcalActE->Fill((depositedEnergyHCALAct - depositedIonEnergyHCALAct) / trueE);
        //hEcalHcal->Fill(depositedEnergyHCALPas / trueE, ecaltotal / trueE);
        /*
             hEcalEcalem->Fill(yyy / trueE, yy2 / trueE);
             if (yyy > 0)
             hEcalfEcalem->Fill(yyy / trueE, yy2 / yyy);
             if (depositedEnergyHCALAct > 0)
             hHCALActPas->Fill(depositedEnergyHCALPas / depositedEnergyHCALAct);
             hcerTimingf->Fill(tot_phot_cer_Timing_f_total);
             hcerTimingr->Fill(tot_phot_cer_Timing_r_total);
             hcerECALf->Fill(tot_phot_cer_ECAL_f_total);
             hcerECALr->Fill(tot_phot_cer_ECAL_r_total);
             hcerHCAL->Fill(tot_phot_cer_HCAL);
             */

        float estE = depositedIonEnergyECAL_f[1] + depositedIonEnergyECAL_r[1]; //ion energy in scinti

        hTotalE->Fill(depositedEnergyTotal / trueE);
        float yyy = depositedEnergyECAL_f[0] + depositedEnergyECAL_r[0] + depositedEnergyECAL_f[1] + depositedEnergyECAL_r[1] + depositedEnergyECAL_f[2] + depositedEnergyECAL_r[2];
        //total energy in ecal
        hecalE->Fill(yyy / trueE);
        hecal_absorbE->Fill((depositedEnergyECAL_f[0] + depositedEnergyECAL_r[0]) / trueE);
        hecal_scintiE->Fill((depositedEnergyECAL_f[1] + depositedEnergyECAL_r[1]) / trueE);
        hscintiE->Fill(estE / trueE);
        hecal_cherenE->Fill((depositedEnergyECAL_f[2] + depositedEnergyECAL_r[2]) / trueE);

        /**********************************************/
        /*********** add the corresponding value to the hist *********************/
        //pi-, e+, e-, gamma, pi+, k+, n, p

        hscintiE_en->Fill((depositedEnergyECAL_scinti_f_particleID[2] + depositedEnergyECAL_scinti_r_particleID[2]) / trueE);
        hscintiE_en_ion->Fill((depositedIonEnergyECAL_scinti_f_particleID[2] + depositedIonEnergyECAL_scinti_r_particleID[2]) / trueE);
        hcherenE_en->Fill((depositedEnergyECAL_cheren_f_particleID[2] + depositedEnergyECAL_cheren_r_particleID[2]) / trueE);

        hscintiE_ep->Fill((depositedEnergyECAL_scinti_f_particleID[1] + depositedEnergyECAL_scinti_r_particleID[1]) / trueE);
        hscintiE_ep_ion->Fill((depositedIonEnergyECAL_scinti_f_particleID[1] + depositedIonEnergyECAL_scinti_r_particleID[1]) / trueE);
        hcherenE_ep->Fill((depositedEnergyECAL_cheren_f_particleID[1] + depositedEnergyECAL_cheren_r_particleID[1]) / trueE);

        hscintiE_gamma->Fill((depositedEnergyECAL_scinti_f_particleID[3] + depositedEnergyECAL_scinti_r_particleID[3]) / trueE);
        hscintiE_gamma_ion->Fill((depositedIonEnergyECAL_scinti_f_particleID[3] + depositedIonEnergyECAL_scinti_r_particleID[3]) / trueE);
        hcherenE_gamma->Fill((depositedEnergyECAL_cheren_f_particleID[3] + depositedEnergyECAL_cheren_r_particleID[3]) / trueE);

        hscintiE_n->Fill((depositedEnergyECAL_scinti_f_particleID[6] + depositedEnergyECAL_scinti_r_particleID[6]) / trueE);
        hscintiE_n_ion->Fill((depositedIonEnergyECAL_scinti_f_particleID[6] + depositedIonEnergyECAL_scinti_r_particleID[6]) / trueE);
        hcherenE_n->Fill((depositedEnergyECAL_cheren_f_particleID[6] + depositedEnergyECAL_cheren_r_particleID[6]) / trueE);

        hscintiE_p->Fill((depositedEnergyECAL_scinti_f_particleID[7] + depositedEnergyECAL_scinti_r_particleID[7]) / trueE);
        hscintiE_p_ion->Fill((depositedIonEnergyECAL_scinti_f_particleID[7] + depositedIonEnergyECAL_scinti_r_particleID[7]) / trueE);
        hcherenE_p->Fill((depositedEnergyECAL_cheren_f_particleID[7] + depositedEnergyECAL_cheren_r_particleID[7]) / trueE);

        hscintiE_pin->Fill((depositedEnergyECAL_scinti_f_particleID[0] + depositedEnergyECAL_scinti_r_particleID[0]) / trueE);
        hscintiE_pin_ion->Fill((depositedIonEnergyECAL_scinti_f_particleID[0] + depositedIonEnergyECAL_scinti_r_particleID[0]) / trueE);
        hcherenE_pin->Fill((depositedEnergyECAL_cheren_f_particleID[0] + depositedEnergyECAL_cheren_r_particleID[0]) / trueE);

        hscintiE_pip->Fill((depositedEnergyECAL_scinti_f_particleID[4] + depositedEnergyECAL_scinti_r_particleID[4]) / trueE);
        hscintiE_pip_ion->Fill((depositedIonEnergyECAL_scinti_f_particleID[4] + depositedIonEnergyECAL_scinti_r_particleID[4]) / trueE);
        hcherenE_pip->Fill((depositedEnergyECAL_cheren_f_particleID[4] + depositedEnergyECAL_cheren_r_particleID[4]) / trueE);
        if (Count_CherenPhoton_in_scinti)
        {
            hcherenN->Fill(tot_phot_cer_ECAL_scinti_f_total + tot_phot_cer_ECAL_scinti_r_total + tot_phot_cer_ECAL_cheren_f_total + tot_phot_cer_ECAL_cheren_r_total);
            hcherenN_en->Fill(tot_phot_cer_ECAL_scinti_f_particleID[2] + tot_phot_cer_ECAL_scinti_r_particleID[2] + tot_phot_cer_ECAL_cheren_f_particleID[2] + tot_phot_cer_ECAL_cheren_r_particleID[2]);
            hcherenN_ep->Fill(tot_phot_cer_ECAL_scinti_f_particleID[1] + tot_phot_cer_ECAL_scinti_r_particleID[1] + tot_phot_cer_ECAL_cheren_f_particleID[1] + tot_phot_cer_ECAL_cheren_r_particleID[1]);
            hcherenN_gamma->Fill(tot_phot_cer_ECAL_scinti_f_particleID[3] + tot_phot_cer_ECAL_scinti_r_particleID[3] + tot_phot_cer_ECAL_cheren_f_particleID[3] + tot_phot_cer_ECAL_cheren_r_particleID[3]);
            hcherenN_n->Fill(tot_phot_cer_ECAL_scinti_f_particleID[6] + tot_phot_cer_ECAL_scinti_r_particleID[6] + tot_phot_cer_ECAL_cheren_f_particleID[6] + tot_phot_cer_ECAL_cheren_r_particleID[6]);
            hcherenN_p->Fill(tot_phot_cer_ECAL_scinti_f_particleID[7] + tot_phot_cer_ECAL_scinti_r_particleID[7] + tot_phot_cer_ECAL_cheren_f_particleID[7] + tot_phot_cer_ECAL_cheren_r_particleID[7]);
            hcherenN_pin->Fill(tot_phot_cer_ECAL_scinti_f_particleID[0] + tot_phot_cer_ECAL_scinti_r_particleID[0] + tot_phot_cer_ECAL_cheren_f_particleID[0] + tot_phot_cer_ECAL_cheren_r_particleID[0]);
            hcherenN_pip->Fill(tot_phot_cer_ECAL_scinti_f_particleID[4] + tot_phot_cer_ECAL_scinti_r_particleID[4] + tot_phot_cer_ECAL_cheren_f_particleID[4] + tot_phot_cer_ECAL_cheren_r_particleID[4]);
        }
        else
        {

            hcherenN->Fill(tot_phot_cer_ECAL_cheren_f_total + tot_phot_cer_ECAL_cheren_r_total);
            hcherenN_en->Fill(tot_phot_cer_ECAL_cheren_f_particleID[2] + tot_phot_cer_ECAL_cheren_r_particleID[2]);
            hcherenN_ep->Fill(tot_phot_cer_ECAL_cheren_f_particleID[1] + tot_phot_cer_ECAL_cheren_r_particleID[1]);
            hcherenN_gamma->Fill(tot_phot_cer_ECAL_cheren_f_particleID[3] + tot_phot_cer_ECAL_cheren_r_particleID[3]);
            hcherenN_n->Fill(tot_phot_cer_ECAL_cheren_f_particleID[6] + tot_phot_cer_ECAL_cheren_r_particleID[6]);
            hcherenN_p->Fill(tot_phot_cer_ECAL_cheren_f_particleID[7] + tot_phot_cer_ECAL_cheren_r_particleID[7]);
            hcherenN_pin->Fill(tot_phot_cer_ECAL_cheren_f_particleID[0] + tot_phot_cer_ECAL_cheren_r_particleID[0]);
            hcherenN_pip->Fill(tot_phot_cer_ECAL_cheren_f_particleID[4] + tot_phot_cer_ECAL_cheren_r_particleID[4]);
        }
        /**********************************************/
    }

    h_localtime_z_st->Add(((TH2F *)f->Get("h_localtime_z_st")), 1.);
    h_localtime_z_st_en->Add(((TH2F *)f->Get("h_localtime_z_st_en")), 1.);
    h_localtime_z_st_ep->Add(((TH2F *)f->Get("h_localtime_z_st_ep")), 1.);
    h_localtime_z_st_gamma->Add(((TH2F *)f->Get("h_localtime_z_st_gamma")), 1.);
    h_localtime_z_st_n->Add(((TH2F *)f->Get("h_localtime_z_st_n")), 1.);
    h_localtime_z_st_p->Add(((TH2F *)f->Get("h_localtime_z_st_p")), 1.);
    h_localtime_z_st_pin->Add(((TH2F *)f->Get("h_localtime_z_st_pin")), 1.);
    h_localtime_z_st_pip->Add(((TH2F *)f->Get("h_localtime_z_st_pip")), 1.);
    h_parentID_Edep->Add(((TH1F *)f->Get("h_parentID_Edep")), 1.);

    f->Close();

    h_localtime_z_st->Scale(1 / eventnumber);
    h_localtime_z_st_en->Scale(1 / eventnumber);
    h_localtime_z_st_ep->Scale(1 / eventnumber);
    h_localtime_z_st_gamma->Scale(1 / eventnumber);
    h_localtime_z_st_n->Scale(1 / eventnumber);
    h_localtime_z_st_p->Scale(1 / eventnumber);
    h_localtime_z_st_pin->Scale(1 / eventnumber);
    h_localtime_z_st_pip->Scale(1 / eventnumber);
    h_parentID_Edep->Scale(1 / eventnumber);

    TFile *out = new TFile(outputfilename, "RECREATE");

    //TTree *newtree = TTree::MergeTrees(list);
    //newtree->SetName("tree");
    //newtree->Write();

    //the total energy in different part
    hTotalE->Write();
    hecalE->Write();
    hecal_absorbE->Write();
    hecal_scintiE->Write();
    hecal_cherenE->Write();
    //the ionization energy in sinctillation fiber
    hscintiE->Write();

    //the total energy of different particles
    hscintiE_en->Write();
    hcherenE_en->Write();
    hscintiE_ep->Write();
    hcherenE_ep->Write();
    hscintiE_gamma->Write();
    hcherenE_gamma->Write();
    hscintiE_n->Write();
    hcherenE_n->Write();
    hscintiE_p->Write();
    hcherenE_p->Write();
    hscintiE_pin->Write();
    hcherenE_pin->Write();
    hscintiE_pip->Write();
    hcherenE_pip->Write();

    hscintiE_en_ion->Write();
    hscintiE_ep_ion->Write();
    hscintiE_gamma_ion->Write();
    hscintiE_n_ion->Write();
    hscintiE_p_ion->Write();
    hscintiE_pin_ion->Write();
    hscintiE_pip_ion->Write();

    hcherenN->Write();
    hcherenN_en->Write();
    hcherenN_ep->Write();
    hcherenN_gamma->Write();
    hcherenN_n->Write();
    hcherenN_p->Write();
    hcherenN_pin->Write();
    hcherenN_pip->Write();

    h_localtime_z_st->Write();
    h_localtime_z_st_en->Write();
    h_localtime_z_st_ep->Write();
    h_localtime_z_st_gamma->Write();
    h_localtime_z_st_n->Write();
    h_localtime_z_st_p->Write();
    h_localtime_z_st_pin->Write();
    h_localtime_z_st_pip->Write();
    h_parentID_Edep->Write();

    out->Close();
}
