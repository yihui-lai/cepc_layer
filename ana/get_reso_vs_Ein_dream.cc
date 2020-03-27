#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"
#include "TRandom.h"

//this file can be used to calculate the mean total/elec/scinti energy
//and plot them as fraction vs True energy
//need to change parameters in get_reso_vs_Ein_dream(){...}

//double sampling_frac_e_scinti[6]={65.55,60.49,58.95,58.13,57.22,56.59};
double sampling_frac_e_scinti = 1/0.019;
bool Count_CherenPhoton_in_scinti_fiber = false;
bool Count_scinti_in_cheren_fiber = true;
bool savepictures = true;

void CC_scinti(const char *inputfilename, const char *tagname, double energy, double *aamean, double *aarms)
{
    TCanvas *cs = new TCanvas();
    TFile *f = new TFile(inputfilename);
    TTree *t1 = (TTree *)f->Get("tree");

    TH1F *htest = new TH1F("htest", "htest", 100, 0.5, 1.5);
    char dra_str[500];
    if (Count_scinti_in_cheren_fiber)
    {
        sprintf(dra_str, "(depositedIonEnergyECAL_f[1] + depositedIonEnergyECAL_r[1]+depositedIonEnergyECAL_f[2] + depositedIonEnergyECAL_r[2]) / %g>>htest", energy / sampling_frac_e_scinti);
    }
    else
    {
        sprintf(dra_str, "(depositedIonEnergyECAL_f[1] + depositedIonEnergyECAL_r[1]) / %g>>htest", energy / sampling_frac_e_scinti);
    }
    t1->Draw(dra_str);

    int imax = htest->GetMaximumBin();
    double amax = htest->GetBinCenter(imax);
    int imin = htest->GetMinimumBin();
    double amin = htest->GetBinCenter(imin);
    std::cout << "hist max at " << amax << std::endl;
    double arms = htest->GetRMS();
    std::cout << "hist rms is " << arms << std::endl;

    TH1F *nhist = new TH1F("nhist", "nhist", 100, amax - 3 * arms, amax + 3 * arms);
    char dra_strs[500];
    if (Count_scinti_in_cheren_fiber)
    {
        sprintf(dra_strs, "(depositedIonEnergyECAL_f[1] + depositedIonEnergyECAL_r[1]+depositedIonEnergyECAL_f[2] + depositedIonEnergyECAL_r[2]) / %g>>htest", energy / sampling_frac_e_scinti);
    }
    else
    {
        sprintf(dra_strs, "(depositedIonEnergyECAL_f[1] + depositedIonEnergyECAL_r[1]) / %g>>htest", energy / sampling_frac_e_scinti);
    }
    t1->Draw(dra_strs);

    TF1 *f1 = new TF1("f1", "gaus", amax - 2 * arms, amax + 2 * arms);
    nhist->Fit("f1", "R Q");

    TF1 *fit = nhist->GetFunction("f1");
    double p0 = f1->GetParameter(0);
    double p1 = f1->GetParameter(1);
    double p2 = f1->GetParameter(2);
    std::cout << "fit parameters are " << p0 << " " << p1 << " " << p2 << std::endl;

    *aamean = p1;
    *aarms = p2;

    nhist->GetXaxis()->SetTitle("Energy/Etrue");
    nhist->GetYaxis()->SetTitle("Events");

    if (savepictures)
        cs->SaveAs(tagname);
    delete cs;
    f->Close();

    return 0;
}
void CC_cheren(const char *inputfilename, const char *tagname, double energy, double *aamean, double *aarms)
{
    TCanvas *cc = new TCanvas();
    //cherenkov light
    TFile *f = new TFile(inputfilename);
    TTree *t1 = (TTree *)f->Get("tree");
    TH1F *htest = new TH1F("htest", "htest", 800, 0, 4000000);

    char dra_str[500];
    if (Count_CherenPhoton_in_scinti_fiber)
    {
        sprintf(dra_str, "(tot_phot_cer_ECAL_scinti_f_total + tot_phot_cer_ECAL_scinti_r_total+tot_phot_cer_ECAL_cheren_f_total + tot_phot_cer_ECAL_cheren_r_total) >>htest");
    }
    else
    {
        sprintf(dra_str, "(tot_phot_cer_ECAL_cheren_f_total + tot_phot_cer_ECAL_cheren_r_total) >>htest");
    }
    t1->Draw(dra_str);
    int imax = htest->GetMaximumBin();
    double amax = htest->GetBinCenter(imax);
    int imin = htest->GetMinimumBin();
    double amin = htest->GetBinCenter(imin);
    std::cout << "hist max at " << amax << std::endl;
    double arms = htest->GetRMS();
    std::cout << "hist rms is " << arms << std::endl;

    TH1F *nhist = new TH1F("nhist", "nhist", 500, amax - 30 * arms, amax + 30 * arms);

    char dra_strs[500];
    if (Count_CherenPhoton_in_scinti_fiber)
    {
        sprintf(dra_strs, "(tot_phot_cer_ECAL_scinti_f_total + tot_phot_cer_ECAL_scinti_r_total+tot_phot_cer_ECAL_cheren_f_total + tot_phot_cer_ECAL_cheren_r_total) >>nhist");
    }
    else
    {
        sprintf(dra_strs, "(tot_phot_cer_ECAL_cheren_f_total + tot_phot_cer_ECAL_cheren_r_total) >>nhist");
    }
    t1->Draw(dra_strs);
    TF1 *f1 = new TF1("f1", "gaus", amax - 2 * arms, amax + 2 * arms);
    nhist->Fit("f1", "R Q");

    TF1 *fit = nhist->GetFunction("f1");
    double p0 = f1->GetParameter(0);
    double p1 = f1->GetParameter(1);
    double p2 = f1->GetParameter(2);
    std::cout << "fit parameters are " << p0 << " " << p1 << " " << p2 << std::endl;

    *aamean = p1;
    *aarms = p2;
    nhist->GetXaxis()->SetTitle("Nceren");
    nhist->GetYaxis()->SetTitle("Events");
    if (savepictures)
        cc->SaveAs(tagname);
    delete cc;
    f->Close();
    return 0;
}

void CC_Fem(const char *inputfilename, const char *tagname, double energy, double *aamean, double *aarms)
{
    TCanvas *cf = new TCanvas();

    TFile *f = new TFile(inputfilename);
    TTree *t1 = (TTree *)f->Get("tree");

    TH1F *htest = new TH1F("htest", "htest", 100, 0.1, 1.5);

    char dra_str[500];
    sprintf(dra_str, "(depositedElecEnergyECAL_f[1] + depositedElecEnergyECAL_r[1] + depositedElecEnergyTiming_f + depositedElecEnergyTiming_r) / %g>>htest", energy / sampling_frac_e_scinti);
    t1->Draw(dra_str);
    int imax = htest->GetMaximumBin();
    double amax = htest->GetBinCenter(imax);
    int imin = htest->GetMinimumBin();
    double amin = htest->GetBinCenter(imin);
    std::cout << "hist max at " << amax << std::endl;
    double arms = htest->GetRMS();
    std::cout << "hist rms is " << arms << std::endl;

    TH1F *nhist = new TH1F("nhist", "nhist", 100, amax - 3 * arms, amax + 3 * arms);
    char dra_strs[500];
    sprintf(dra_strs, "(depositedElecEnergyECAL_f[1] + depositedElecEnergyECAL_r[1] + depositedElecEnergyTiming_f + depositedElecEnergyTiming_r) / %g>>nhist", energy / sampling_frac_e_scinti);
    t1->Draw(dra_strs);

    TF1 *f1 = new TF1("f1", "gaus", amax - 2 * arms, amax + 2 * arms);
    nhist->Fit("f1", "R Q");

    TF1 *fit = nhist->GetFunction("f1");
    double p0 = f1->GetParameter(0);
    double p1 = f1->GetParameter(1);
    double p2 = f1->GetParameter(2);
    std::cout << "fit parameters are " << p0 << " " << p1 << " " << p2 << std::endl;

    *aamean = p1;
    *aarms = p2;

    nhist->GetXaxis()->SetTitle("E_elec/Etrue");
    nhist->GetYaxis()->SetTitle("Events");
    if (savepictures)
        cf->SaveAs(tagname);
    delete cf;
    f->Close();
    return 0;
}

void get_reso_vs_Ein_dream()
{

    std::cout << "running on normal files" << std::endl;

    ///////////////////////////////////////////
    //chnage the following parameters
    ///////////////////////////////////////////
    // draw somthing vs Etrue
    int draw_option = 4; //1 for scinti, 2 for Cheren, 3 for electric, 4 for c/s

    int npoints = 1; //how many energy points
    double arrres[npoints], aatruemean[npoints];
    aatruemean[0] = 1;
    /*
    aatruemean[1] = 40;
    aatruemean[2] = 70;
    aatruemean[3] = 100;
    aatruemean[4] = 150;
    aatruemean[5] = 200;*/
    char dtag[100] = ""; // file tag, shoule be changed

    ///////////////////////////////////////////
    //end
    ///////////////////////////////////////////

    int nhst = 2;
    char filenames_p[npoints][50];
    char filenames_e[npoints][50];
    char soutname_p[npoints][50];
    char soutname_e[npoints][50];
    char coutname_p[npoints][50];
    char coutname_e[npoints][50];
    char foutname_p[npoints][50];
    char foutname_e[npoints][50];
    char dpi[10] = "pion";
    char de[10] = "electron";
    char dtagpic[100] = "pic_layers"; //output pictures tag

    for (int lp = 0; lp < npoints; lp++)
    {

        sprintf(filenames_p[lp], "%s_%s_%gGeV.root", dtag, dpi, aatruemean[lp]);
        sprintf(filenames_e[lp], "%s_%s_%gGeV.root", dtag, de, aatruemean[lp]);

        sprintf(soutname_p[lp], "s_%s_%s_%gGeV.C", dtagpic, dpi, aatruemean[lp]);
        sprintf(soutname_e[lp], "s_%s_%s_%gGeV.C", dtagpic, de, aatruemean[lp]);

        sprintf(coutname_p[lp], "c_%s_%s_%gGeV.C", dtagpic, dpi, aatruemean[lp]);
        sprintf(coutname_e[lp], "c_%s_%s_%gGeV.C", dtagpic, de, aatruemean[lp]);

        sprintf(foutname_p[lp], "f_%s_%s_%gGeV.C", dtagpic, dpi, aatruemean[lp]);
        sprintf(foutname_e[lp], "f_%s_%s_%gGeV.C", dtagpic, de, aatruemean[lp]);
        cout << filenames_p[lp] << endl;
        cout << filenames_e[lp] << endl;
        cout << soutname_p[lp] << endl;
        cout << soutname_e[lp] << endl;
    }

    double rrmeans[npoints][nhst];
    double rrrmss[npoints][nhst];
    double rrress[npoints][nhst];
    double rrmeanc[npoints][nhst];
    double rrrmsc[npoints][nhst];
    double rrresc[npoints][nhst];
    double rrmeanf[npoints][nhst];
    double rrrmsf[npoints][nhst];
    double rrresf[npoints][nhst];
    double means, rmss, meanc, rmsc, meanf, rmsf;
    double cali_r[npoints], cali_ce[npoints], cali_sc[npoints];
    double SS[npoints], CC[npoints], Fem[npoints];
    double SS_reso[npoints], CC_reso[npoints], Fem_reso[npoints];
    //ceren
    //sinti
    for (int k = 0; k < nhst; k++)
    {
        for (int j = 0; j < npoints; j++)
        {

            if (k == 0)
            {
                CC_scinti(filenames_e[j], soutname_e[j], aatruemean[j], &means, &rmss);
                cali_sc[j] = means;
                CC_cheren(filenames_e[j], coutname_e[j], aatruemean[j], &meanc, &rmsc);
                cali_ce[j] = meanc;
                CC_Fem(filenames_e[j], foutname_e[j], aatruemean[j], &meanf, &rmsf);
                cali_r[j] = meanf;
            }
            if (k == 1)
            {
                CC_scinti(filenames_p[j], soutname_p[j], aatruemean[j], &means, &rmss);
                CC_cheren(filenames_p[j], coutname_p[j], aatruemean[j], &meanc, &rmsc);
                CC_Fem(filenames_p[j], foutname_p[j], aatruemean[j], &meanf, &rmsf);
            }
            rrmeans[j][k] = means; /// cali_sc[j];
            rrrmss[j][k] = rmss;   /// cali_sc[j];
            rrress[j][k] = 0;
            if (rrmeans[j][k] != 0)
                rrress[j][k] = rrrmss[j][k] / rrmeans[j][k];

            rrmeanc[j][k] = meanc; /// cali_ce[j];
            rrrmsc[j][k] = rmsc;   /// cali_ce[j];
            rrresc[j][k] = 0;
            if (rrmeanc[j][k] != 0)
                rrresc[j][k] = rrrmsc[j][k] / rrmeanc[j][k];

            rrmeanf[j][k] = meanf; ///cali_r[j];
            rrrmsf[j][k] = rmsf;   ///cali_r[j];
            rrresf[j][k] = 0;
            if (rrmeanf[j][k] != 0)
                rrresf[j][k] = rrrmsf[j][k] / rrmeanf[j][k];
        }
    }

    cout << "********************************************************************************************** " << endl;
    for (int l = 0; l < npoints; l++)
    {
        SS[l] = rrmeans[l][1];
        SS_reso[l] = rrress[l][1];
        cout << "SS_e " << rrmeans[l][0] << " SS_p[l]: " << SS[l] << " SS_reso[l]: " << SS_reso[l] << endl;
    }
    for (int l = 0; l < npoints; l++)
    {
        cout << "ratio: " << rrmeans[l][1] / rrmeans[l][0] << endl;
    }
    cout << "********************************************************************************************** " << endl;

    for (int l = 0; l < npoints; l++)
    {
        CC[l] = rrmeanc[l][1];
        CC_reso[l] = rrresc[l][1];
        cout << "CC_e " << rrmeanc[l][0] << " CC_p[l]: " << CC[l] << " CC_reso[l]: " << CC_reso[l] << endl;
    }
    for (int l = 0; l < npoints; l++)
    {
        cout << "ratio: " << rrmeanc[l][1] / rrmeanc[l][0] << endl;
    }
    cout << "********************************************************************************************** " << endl;
    for (int l = 0; l < npoints; l++)
    {
        Fem[l] = rrmeanf[l][1];
        Fem_reso[l] = rrresf[l][1];
        cout << "Fem_e " << rrmeanf[l][0] << " Fem_p[l]: " << Fem[l] << endl;
    }
    for (int l = 0; l < npoints; l++)
    {
        cout << "ratio: " << rrmeanf[l][1] / rrmeanf[l][0] << endl;
    }
    cout << "********************************************************************************************** " << endl;
    //calculate the total energy and resolution
    double chi[npoints];
    double C_to_S[npoints];
    double h_S[npoints], h_C[npoints];
    double E_total[npoints], E_reso[npoints];
    for (int l = 0; l < npoints; l++)
    {
        //h_S[l] = (SS[l] - Fem[l]) / (1 - Fem[l]);
        //h_C[l] = (CC[l] - Fem[l]) / (1 - Fem[l]);
        //chi[l] = (1 - h_S[l]) / (1 - h_C[l]);
        C_to_S[l] = (CC[l] / rrmeanc[l][0]) / (SS[l] / rrmeans[l][0]);
        //E_total[l] = (SS[l] - chi[l] * CC[l]) / (1 - chi[l]);
        //E_reso[l] = (sqrt(SS_reso[l] * SS_reso[l] + chi[l] * CC_reso[l] * chi[l] * CC_reso[l])) / (1 - chi[l]);
        cout << "C/S: " << C_to_S[l] << " S:" << SS[l] << endl;
    }

    /*
    //add functions here, change the way calculating E total and E reso
    //rotating method
    for (int loop_f = 3; loop_f < npoints; loop_f++)
    {

        TFile *f = new TFile(filenames_p[loop_f]);
        TTree *t1 = (TTree *)f->Get("tree");

        int tot_phot_cer_ECAL_scinti_f_total;
        int tot_phot_cer_ECAL_scinti_r_total;
        int tot_phot_cer_ECAL_cheren_f_total;
        int tot_phot_cer_ECAL_cheren_r_total;
        float depositedIonEnergyECAL_f[3], depositedIonEnergyECAL_r[3];
        float depositedElecEnergyECAL_f[3], depositedElecEnergyECAL_r[3];
        float depositedEnergyECAL_f[3], depositedEnergyECAL_r[3];

        float depositedEnergyECAL_scinti_f[8];
        float depositedEnergyECAL_scinti_r[8];
        float depositedIonEnergyECAL_scinti_f[8];
        float depositedIonEnergyECAL_scinti_r[8];

        t1->SetBranchAddress("tot_phot_cer_ECAL_scinti_f_total", &tot_phot_cer_ECAL_scinti_f_total);
        t1->SetBranchAddress("tot_phot_cer_ECAL_scinti_r_total", &tot_phot_cer_ECAL_scinti_r_total);
        t1->SetBranchAddress("tot_phot_cer_ECAL_cheren_f_total", &tot_phot_cer_ECAL_cheren_f_total);
        t1->SetBranchAddress("tot_phot_cer_ECAL_cheren_r_total", &tot_phot_cer_ECAL_cheren_r_total);
        t1->SetBranchAddress("depositedEnergyECAL_f", &depositedEnergyECAL_f);
        t1->SetBranchAddress("depositedEnergyECAL_r", &depositedEnergyECAL_r);
        t1->SetBranchAddress("depositedElecEnergyECAL_f", &depositedElecEnergyECAL_f);
        t1->SetBranchAddress("depositedElecEnergyECAL_r", &depositedElecEnergyECAL_r);
        t1->SetBranchAddress("depositedIonEnergyECAL_f", &depositedIonEnergyECAL_f);
        t1->SetBranchAddress("depositedIonEnergyECAL_r", &depositedIonEnergyECAL_r);

        t1->SetBranchAddress("depositedEnergyECAL_scinti_f", &depositedEnergyECAL_scinti_f);
        t1->SetBranchAddress("depositedEnergyECAL_scinti_r", &depositedEnergyECAL_scinti_r);
        t1->SetBranchAddress("depositedIonEnergyECAL_scinti_f", &depositedIonEnergyECAL_scinti_f);
        t1->SetBranchAddress("depositedIonEnergyECAL_scinti_r", &depositedIonEnergyECAL_scinti_r);

        const int nentries = t1->GetEntries();
        cout << "*******************************cali: " << cali_ce[loop_f] << " " << cali_sc[loop_f] << endl;
        double C_E[nentries], S_E[nentries];
        for (Int_t ii = 0; ii < nentries; ii++)
        {
            t1->GetEntry(ii);

            if (Count_CherenPhoton_in_scinti_fiber)
            {
                C_E[ii] = (tot_phot_cer_ECAL_scinti_f_total + tot_phot_cer_ECAL_scinti_r_total + tot_phot_cer_ECAL_cheren_f_total + tot_phot_cer_ECAL_cheren_r_total) / cali_ce[loop_f];
            }
            else
            {
                C_E[ii] = (tot_phot_cer_ECAL_cheren_f_total + tot_phot_cer_ECAL_cheren_r_total) / cali_ce[loop_f];
            }
            S_E[ii] = (depositedEnergyECAL_f[1] - depositedIonEnergyECAL_f[1] + depositedEnergyECAL_r[1] - depositedIonEnergyECAL_r[1]) * sampling_frac_e_scinti / aatruemean[loop_f] / cali_sc[loop_f];
        }

        auto g_fit = new TGraph(nentries, S_E, C_E);
        auto Canvas = new TCanvas("Canvas", "Canvas", 200, 10, 700, 500);

        g_fit->GetXaxis()->SetRangeUser(0, 2);
        g_fit->GetYaxis()->SetRangeUser(0, 2);
        g_fit->GetXaxis()->SetTitle("S/E");
        g_fit->GetXaxis()->SetTickLength(0.02);
        g_fit->GetXaxis()->SetLabelSize(0.03);
        g_fit->GetYaxis()->SetTitle("C/E");
        g_fit->GetYaxis()->SetLabelSize(0.03);

        TF1 *f1 = new TF1("f1", "[0]*x+[1]", 0, 2);
        g_fit->Fit("f1", "R");

        TF1 *fit = g_fit->GetFunction("f1");
        double p0 = f1->GetParameter(0);
        double p1 = f1->GetParameter(1);

        g_fit->SetMarkerStyle(21);
        g_fit->SetMarkerSize(1.5);
        g_fit->Draw("AP");
        //TH1F* nhist = new TH1F("nhist","nhist",400,0.2,1.8);
        TH2F *nhist = new TH2F("nhist", "nhist", 200, 0.2, 1.8, 200, 0.2, 1.8);
        //TH2F* nhist = new TH2F("nhist","nhist",200,3,4,200,1100000,1450000);
        double xx, yy;
        for (Int_t ii = 0; ii < nentries; ii++)
        {
            t1->GetEntry(ii);

            if (Count_CherenPhoton_in_scinti_fiber)
            {
                yy = (tot_phot_cer_ECAL_scinti_f_total + tot_phot_cer_ECAL_scinti_r_total + tot_phot_cer_ECAL_cheren_f_total + tot_phot_cer_ECAL_cheren_r_total) / cali_ce[loop_f];
            }
            else
            {
                yy = (tot_phot_cer_ECAL_cheren_f_total + tot_phot_cer_ECAL_cheren_r_total) / cali_ce[loop_f];
            }
            xx = (depositedEnergyECAL_f[1] - depositedIonEnergyECAL_f[1] + depositedEnergyECAL_r[1] - depositedIonEnergyECAL_r[1]) * sampling_frac_e_scinti / aatruemean[loop_f] / cali_sc[loop_f];

            //xx=((depositedEnergyECAL_scinti_f[1]- depositedIonEnergyECAL_scinti_f[1] +depositedEnergyECAL_scinti_r[1]- depositedIonEnergyECAL_scinti_r[1])*51.5   + (depositedEnergyECAL_scinti_f[7]- depositedIonEnergyECAL_scinti_f[7] +depositedEnergyECAL_scinti_r[7]- depositedIonEnergyECAL_scinti_r[7])*15 + (depositedEnergyECAL_scinti_f[2]- depositedIonEnergyECAL_scinti_f[2] +depositedEnergyECAL_scinti_r[2]- depositedIonEnergyECAL_scinti_r[2])*51.5)/aatruemean[loop_f]/cali_sc[loop_f];

            nhist->Fill(xx, yy);
            //nhist->Fill(1+(p0*xx-yy+p1)/sqrt(1+p0*p0));
        }
        nhist->Draw("colz");
        nhist->GetXaxis()->SetTitle("Scintillation signal");
        nhist->GetXaxis()->SetTickLength(0.02);
        nhist->GetXaxis()->SetLabelSize(0.03);
        nhist->GetYaxis()->SetTitle("Cherenkov signal ");
        return;
        TF1 *ff1 = new TF1("ff1", "gaus", 0.2, 1.8);
        nhist->Fit("ff1", "R");
        double pp0 = ff1->GetParameter(0);
        double pp1 = ff1->GetParameter(1);
        double pp2 = ff1->GetParameter(2);
        E_reso[loop_f] = pp2 / pp1;
    }
*/

    //plots
    double arrmean[npoints];
    float x1_l = 0.8;
    float y1_l = 0.8;
    float dx_l = 0.2;
    float dy_l = 0.2;
    float x0_l = x1_l - dx_l;
    float y0_l = y1_l - dy_l;

    auto Canvas = new TCanvas("Canvas", "Canvas", 200, 10, 700, 500);
    TLegend *lgd = new TLegend(x0_l, y0_l, x1_l, y1_l);
    lgd->SetBorderSize(0);
    lgd->SetTextSize(0.04);
    lgd->SetTextFont(62);
    lgd->SetFillColor(0);
    TH1 *frame = new TH1F("frame", "", 1000, 0, 210);
    frame->SetMinimum(0);
    frame->SetMaximum(1.1);
    frame->SetStats(0);
    frame->GetXaxis()->SetTitle("true energy (GeV)");
    frame->GetXaxis()->SetTickLength(0.02);
    frame->GetXaxis()->SetLabelSize(0.03);
    frame->GetYaxis()->SetTitle("N_{Cheren}/E_{scinti} ");
    frame->GetYaxis()->SetLabelSize(0.03);
    frame->Draw("");

    /*
    //draw resolution
    for (int k = 0; k < npoints; k++){  arrmean[k] = SS_reso[k];}
    auto g_resos = new TGraph(npoints, aatruemean, arrmean);
    for (int k = 0; k < npoints; k++){  arrmean[k] = CC_reso[k]; }
    auto g_resoc = new TGraph(npoints, aatruemean, arrmean);
    
    TF1 *f_s = new TF1("f_s","sqrt([0]*[0]/x+[1]*[1]/x/x+[2]*[2])");
    TF1 *f_c = new TF1("f_c","sqrt([0]*[0]/x+[1]*[1]/x/x+[2]*[2])");
    //TF1 *f_factor = new TF1("f_factor","sqrt([0]*[0]/x+[1]*[1]/x/x+[2]*[2])");
    g_resos->Fit("f_s");
    double g_s_a= f_s->GetParameter(0);
    double g_s_b= f_s->GetParameter(1);
    double g_s_c= f_s->GetParameter(2);
    g_resoc->Fit("f_c");
    double g_c_a= f_c->GetParameter(0);
    double g_c_b= f_c->GetParameter(1);
    double g_c_c= f_c->GetParameter(2);
    //g_factor->Fit("f_factor");
    //double g_factor_a= f_factor->GetParameter(0);
    //double g_factor_b= f_factor->GetParameter(1);
    //double g_factor_c= f_factor->GetParameter(2);
    
    //auto g_factor = new TGraph(npoints,arrmean,SS);
    //TF1 *ff = new TF1("ff","[0]+x*[1]+x*x*[2]+x*x*x*[3]",0.54,1);
    //g_factor->Fit("ff","R");

    
    //g_factor->SetMarkerColor(kRed);
    //g_factor->SetMarkerStyle(21);
    //g_factor->SetMarkerSize(1.5);
    //g_factor->SetLineColor(kRed);
    //g_factor->Draw("CP");
    //lgd->AddEntry(g_factor, Form("S+C #frac{%0.2g}{#sqrt{x}} & #frac{%0.2g}{x} & %0.2g",g_factor_a,g_factor_b,g_factor_c), "L");
 
    g_resos->SetMarkerColor(kBlue);
    g_resos->SetMarkerStyle(21);
    g_resos->SetMarkerSize(1.5);
    g_resos->SetLineColor(kBlue);
    g_resos->Draw("P");
    g_resoc->SetMarkerColor(kGreen);
    g_resoc->SetMarkerStyle(23);
    g_resoc->SetMarkerSize(1.5);
    g_resoc->SetLineColor(kGreen);
    g_resoc->Draw("P");
    lgd->AddEntry(g_resos, Form("Scinti #frac{%0.2g}{#sqrt{x}} & #frac{%0.2g}{x} & %0.2g",g_s_a,g_s_b,g_s_c), "L");
    lgd->AddEntry(g_resoc, Form("Ceren #frac{%0.2g}{#sqrt{x}} & #frac{%0.2g}{x} & %0.2g",g_c_a,g_c_b,g_c_c), "L");
    frame->GetXaxis()->SetTitle("E_{in}");
    frame->GetYaxis()->SetTitle("resolution");    
    frame->SetMinimum(0.);
    frame->SetMaximum(0.4);
*/

    for (int k = 0; k < npoints; k++)
    {
        arrmean[k] = rrmeans[k][0] / rrmeans[k][0];
    }
    auto g_uniform = new TGraph(npoints, aatruemean, arrmean);

    //draw SS
    if (draw_option == 1)
    {
        for (int k = 0; k < npoints; k++)
        {
            arrmean[k] = rrmeans[k][1] / rrmeans[k][0];
        }
        auto g_ss = new TGraph(npoints, aatruemean, arrmean);
        g_ss->SetMarkerColor(kBlue);
        g_ss->SetMarkerStyle(21);
        g_ss->SetMarkerSize(1.5);
        g_ss->SetLineColor(kBlue);
        g_ss->Draw("CP");
        g_uniform->SetMarkerColor(kGreen);
        g_uniform->SetMarkerStyle(23);
        g_uniform->SetMarkerSize(1.5);
        g_uniform->SetLineColor(kGreen);
        g_uniform->Draw("CP");
        lgd->AddEntry(g_uniform, "e-", "L");
        lgd->AddEntry(g_ss, "pi-", "L");
        frame->SetMinimum(0.2);
        frame->SetMaximum(1.3);
        frame->GetXaxis()->SetTitle("true energy (GeV)");
        frame->GetYaxis()->SetTitle("relative scintillation energy ");
    }
    //draw CC
    if (draw_option == 2)
    {
        for (int k = 0; k < npoints; k++)
        {
            arrmean[k] = rrmeanc[k][1] / rrmeanc[k][0];
        }
        auto g_cc = new TGraph(npoints, aatruemean, arrmean);
        g_cc->SetMarkerColor(kBlue);
        g_cc->SetMarkerStyle(21);
        g_cc->SetMarkerSize(1.5);
        g_cc->SetLineColor(kBlue);
        g_cc->Draw("CP");
        g_uniform->SetMarkerColor(kGreen);
        g_uniform->SetMarkerStyle(23);
        g_uniform->SetMarkerSize(1.5);
        g_uniform->SetLineColor(kGreen);
        g_uniform->Draw("CP");
        lgd->AddEntry(g_uniform, "e-", "L");
        lgd->AddEntry(g_cc, "pi-", "L");
        frame->SetMinimum(0.2);
        frame->SetMaximum(1.3);
        frame->GetXaxis()->SetTitle("true energy (GeV)");
        frame->GetYaxis()->SetTitle("relative Cherenkov photon number ");
    }
    if (draw_option == 3)
    {
        for (int k = 0; k < npoints; k++)
        {
            arrmean[k] = rrmeanf[k][1] / rrmeanf[k][0];
        }
        auto g_fem = new TGraph(npoints, aatruemean, arrmean);
        g_fem->SetMarkerColor(kBlue);
        g_fem->SetMarkerStyle(21);
        g_fem->SetMarkerSize(1.5);
        g_fem->SetLineColor(kBlue);
        g_fem->Draw("CP");
        g_uniform->SetMarkerColor(kGreen);
        g_uniform->SetMarkerStyle(23);
        g_uniform->SetMarkerSize(1.5);
        g_uniform->SetLineColor(kGreen);
        g_uniform->Draw("CP");
        lgd->AddEntry(g_uniform, "e-", "L");
        lgd->AddEntry(g_fem, "pi-", "L");
        frame->SetMinimum(0.2);
        frame->SetMaximum(1.3);
        frame->GetXaxis()->SetTitle("true energy (GeV)");
        frame->GetYaxis()->SetTitle("relative electric energy");
    }
    //draw C/S vs E_in
    if (draw_option == 4)
    {
        for (int k = 0; k < npoints; k++)
        {
            arrmean[k] = C_to_S[k];
        }
        auto g_c2s_s = new TGraph(npoints, aatruemean, arrmean);
        for (int k = 0; k < npoints; k++)
        {
            arrmean[k] = 1;
        }
        auto g_c2s_c = new TGraph(npoints, aatruemean, arrmean);
        g_c2s_s->SetMarkerColor(kBlue);
        g_c2s_s->SetMarkerStyle(21);
        g_c2s_s->SetMarkerSize(1.5);
        g_c2s_s->SetLineColor(kBlue);
        g_c2s_s->Draw("CP");
        g_c2s_c->SetMarkerColor(kGreen);
        g_c2s_c->SetMarkerStyle(23);
        g_c2s_c->SetMarkerSize(1.5);
        g_c2s_c->SetLineColor(kGreen);
        g_c2s_c->Draw("CP");
        lgd->AddEntry(g_c2s_c, "e-", "L");
        lgd->AddEntry(g_c2s_s, "pi-", "L");
        frame->SetMinimum(0.4);
        frame->SetMaximum(1.1);
    }
    lgd->Draw();
    //Canvas->Print("h.png",".png");

    return;
}
