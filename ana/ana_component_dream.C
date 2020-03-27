void ana_component_dream()
{
    //draw the various components of the energy type we are interested
    //bool savepictures = false;
    int draw_option = 1; //1 is scintillating energy, 2 is Cherenkov energy, 3 is Cherenkov photons, 4 for energy vs depth, 5 for energy vs time

    bool set_normlize = true;
    TFile *fp = new TFile("layer_brass_plastics408_pion_60GeV_ana.root"); //use ana file here, not the original root file

    TH1F *hp;
    TH1F *hpen;
    TH1F *hpep;
    TH1F *hpgamma;
    TH1F *hpn;
    TH1F *hpp;
    TH1F *hppin;
    TH1F *hppip;

    TH2F *hp2;
    TH2F *hpen2;
    TH2F *hpep2;
    TH2F *hpgamma2;
    TH2F *hpn2;
    TH2F *hpp2;
    TH2F *hppin2;
    TH2F *hppip2;

    if (draw_option == 1)
    {
        hp = (TH1F *)fp->Get("hecal_scintiE");
        hpen = (TH1F *)fp->Get("hscintiE_en");
        hpep = (TH1F *)fp->Get("hscintiE_ep");
        hpgamma = (TH1F *)fp->Get("hscintiE_gamma");
        hpn = (TH1F *)fp->Get("hscintiE_n");
        hpp = (TH1F *)fp->Get("hscintiE_p");
        hppin = (TH1F *)fp->Get("hscintiE_pin");
        hppip = (TH1F *)fp->Get("hscintiE_pip");
    }
    else if (draw_option == 2)
    {

        hp = (TH1F *)fp->Get("hecal_cherenE");
        hpen = (TH1F *)fp->Get("hcherenE_en");
        hpep = (TH1F *)fp->Get("hcherenE_ep");
        hpgamma = (TH1F *)fp->Get("hcherenE_gamma");
        hpn = (TH1F *)fp->Get("hcherenE_n");
        hpp = (TH1F *)fp->Get("hcherenE_p");
        hppin = (TH1F *)fp->Get("hcherenE_pin");
        hppip = (TH1F *)fp->Get("hcherenE_pip");
    }
    else if (draw_option == 3)
    {
        hp = (TH1F *)fp->Get("hcherenN");
        hpen = (TH1F *)fp->Get("hcherenN_en");
        hpep = (TH1F *)fp->Get("hcherenN_ep");
        hpgamma = (TH1F *)fp->Get("hcherenN_gamma");
        hpn = (TH1F *)fp->Get("hcherenN_n");
        hpp = (TH1F *)fp->Get("hcherenN_p");
        hppin = (TH1F *)fp->Get("hcherenN_pin");
        hppip = (TH1F *)fp->Get("hcherenN_pip");
    }
    else if (draw_option == 4)
    {

        hp2 = (TH2F *)fp->Get("h_localtime_z_st");
        hpen2 = (TH2F *)fp->Get("h_localtime_z_st_en");
        hpep2 = (TH2F *)fp->Get("h_localtime_z_st_ep");
        hpgamma2 = (TH2F *)fp->Get("h_localtime_z_st_gamma");
        hpn2 = (TH2F *)fp->Get("h_localtime_z_st_n");
        hpp2 = (TH2F *)fp->Get("h_localtime_z_st_p");
        hppin2 = (TH2F *)fp->Get("h_localtime_z_st_pin");
        hppip2 = (TH2F *)fp->Get("h_localtime_z_st_pip");

        hp = (TH1F *)hp2->ProjectionX();
        hpen = (TH1F *)hpen2->ProjectionX();
        hpep = (TH1F *)hpep2->ProjectionX();
        hpgamma = (TH1F *)hpgamma2->ProjectionX();
        hpn = (TH1F *)hpn2->ProjectionX();
        hpp = (TH1F *)hpp2->ProjectionX();
        hppin = (TH1F *)hppin2->ProjectionX();
        hppip = (TH1F *)hppip2->ProjectionX();
    }
    else if (draw_option == 5)
    {

        hp2 = (TH2F *)fp->Get("h_localtime_z_st");
        hpen2 = (TH2F *)fp->Get("h_localtime_z_st_en");
        hpep2 = (TH2F *)fp->Get("h_localtime_z_st_ep");
        hpgamma2 = (TH2F *)fp->Get("h_localtime_z_st_gamma");
        hpn2 = (TH2F *)fp->Get("h_localtime_z_st_n");
        hpp2 = (TH2F *)fp->Get("h_localtime_z_st_p");
        hppin2 = (TH2F *)fp->Get("h_localtime_z_st_pin");
        hppip2 = (TH2F *)fp->Get("h_localtime_z_st_pip");

        hp = (TH1F *)hp2->ProjectionY();
        hpen = (TH1F *)hpen2->ProjectionY();
        hpep = (TH1F *)hpep2->ProjectionY();
        hpgamma = (TH1F *)hpgamma2->ProjectionY();
        hpn = (TH1F *)hpn2->ProjectionY();
        hpp = (TH1F *)hpp2->ProjectionY();
        hppin = (TH1F *)hppin2->ProjectionY();
        hppip = (TH1F *)hppip2->ProjectionY();
    }
    if (draw_option == 4 || draw_option == 5)
    {
        double time_min, time_max;
        double z_min, z_max;
        time_min = 0.00001;
        time_max = 0.5;
        z_min = 100;
        z_max = 2000;

        TCanvas *t_pro = new TCanvas();
        gStyle->SetOptStat(0000);

        hp->Draw("HIST");
        hp->SetLineColor(1);
        if (draw_option == 4)
        {
            hp->GetXaxis()->SetTitle("Depth (mm)");
            hp->GetYaxis()->SetTitle("Energy (GeV)");
            hp->GetXaxis()->SetRangeUser(z_min, z_max);
        }
        else
        {
            t_pro->SetLogy();
            hp->GetXaxis()->SetTitle("localtime (ns)");
            hp->GetYaxis()->SetTitle("Energy (GeV)");
            hp->GetXaxis()->SetRangeUser(time_min, time_max);
        }

        hpen->Draw("HIST same");
        hpen->SetLineColor(4);
        hpep->Draw("HIST same");
        hpep->SetLineColor(2);
        hpgamma->Draw("HIST same");
        hpgamma->SetLineColor(3);
        hpn->Draw("HIST same");
        hpn->SetLineColor(46);
        hpp->Draw("HIST same");
        hpp->SetLineColor(6);
        hppin->Draw("HIST same");
        hppin->SetLineColor(30);
        hppip->Draw("HIST same");
        hppip->SetLineColor(28);
        hpen->SetLineWidth(3);
        hpen->SetLineWidth(3);
        hpep->SetLineWidth(3);
        hpgamma->SetLineWidth(3);
        hpn->SetLineWidth(3);
        hpp->SetLineWidth(3);
        hppin->SetLineWidth(3);
        hppip->SetLineWidth(3);
        float x1_l = 0.8;
        float y1_l = 0.80;
        float dx_l = 0.20;
        float dy_l = 0.2;
        float x0_l = x1_l - dx_l;
        float y0_l = y1_l - dy_l;
        TLegend *lgd = new TLegend(x0_l, y0_l, x1_l, y1_l);
        lgd->SetBorderSize(0);
        lgd->SetTextSize(0.04);
        lgd->SetTextFont(62);
        lgd->SetFillColor(0);

        lgd->AddEntry(hp, "total", "l");
        lgd->AddEntry(hpen, "e-", "l");
        lgd->AddEntry(hpep, "e+", "l");
        lgd->AddEntry(hpgamma, "#gamma", "l");
        lgd->AddEntry(hpn, "n", "l");
        lgd->AddEntry(hpp, "p", "l");
        lgd->AddEntry(hppin, "#pi -", "l");
        lgd->AddEntry(hppip, "#pi +", "l");
        lgd->Draw();
        return;
    }

    int imax = hp->GetMaximumBin();
    double amax = hp->GetBinCenter(imax);
    std::cout << "hist max at " << amax << std::endl;
    double arms = hp->GetRMS();
    std::cout << "hist rms is " << arms << std::endl;
    TF1 *f1 = new TF1("f1", "gaus", amax - 2 * arms, amax + 2 * arms);
    hp->Fit("f1", "R Q");
    double norm_c = 1.0 / f1->GetParameter(1);
    if (!set_normlize)
        norm_c = 1;

    std::cout << "hist norm is " << norm_c << std::endl;
    double y_max = hp->GetMaximum();
    if (hpen->GetMaximum() > y_max)
        y_max = hpen->GetMaximum();
    if (hpep->GetMaximum() > y_max)
        y_max = hpep->GetMaximum();
    if (hpgamma->GetMaximum() > y_max)
        y_max = hpgamma->GetMaximum();

    TCanvas *cnew = new TCanvas();
    int nbins = hp->GetXaxis()->GetNbins();
    int newnbins = nbins;
    double maxx = hp->GetBinCenter(nbins) * norm_c;

    double x, y, xnew;

    TH1F *hp_scale = new TH1F("hp_scale", "", newnbins, 0, maxx);
    for (int i = 1; i <= nbins; i++)
    {
        y = hp->GetBinContent(i);
        x = hp->GetXaxis()->GetBinCenter(i);
        xnew = norm_c * x;
        hp_scale->Fill(xnew, y);
    }
    hp_scale->Draw("HIST");
    hp_scale->SetLineColor(1);
    hp_scale->GetXaxis()->SetRangeUser(0, 1.3);
    hp_scale->GetYaxis()->SetRangeUser(0, y_max);
    hp_scale->GetYaxis()->SetTitle("count");
    if (draw_option == 1)
    {
        hp_scale->SetTitle("energy deposition in scintillating fiber");
        hp_scale->GetXaxis()->SetTitle("scintillation energy (normalized)");
    }
    else if (draw_option == 2)
    {
        hp_scale->SetTitle("energy deposition in Cherenkov fiber");
        hp_scale->GetXaxis()->SetTitle("Cherenkov energy (normalized)");
    }
    else
    {
        hp_scale->SetTitle("Cherenkov photons");
        hp_scale->GetXaxis()->SetTitle("number of Cherenkov photon (normalized)");
    }
    gStyle->SetOptStat(0000);

    nbins = hpen->GetXaxis()->GetNbins();
    TH1F *hpen_scale = new TH1F("hpen_scale", "", newnbins, 0, maxx);
    for (int i = 1; i <= nbins; i++)
    {
        y = hpen->GetBinContent(i);
        x = hpen->GetXaxis()->GetBinCenter(i);
        xnew = norm_c * x;
        hpen_scale->Fill(xnew, y);
    }
    hpen_scale->Draw("HIST same");
    hpen_scale->SetLineColor(4);

    nbins = hpep->GetXaxis()->GetNbins();
    TH1F *hpep_scale = new TH1F("hpep_scale", "", newnbins, 0, maxx);
    for (int i = 1; i <= nbins; i++)
    {
        y = hpep->GetBinContent(i);
        x = hpep->GetXaxis()->GetBinCenter(i);
        xnew = norm_c * x;
        hpep_scale->Fill(xnew, y);
    }
    hpep_scale->Draw("HIST same");
    hpep_scale->SetLineColor(2);

    nbins = hpgamma->GetXaxis()->GetNbins();
    TH1F *hpgamma_scale = new TH1F("hpgamma_scale", "", newnbins, 0, maxx);
    for (int i = 1; i <= nbins; i++)
    {
        y = hpgamma->GetBinContent(i);
        x = hpgamma->GetXaxis()->GetBinCenter(i);
        xnew = norm_c * x;
        hpgamma_scale->Fill(xnew, y);
    }
    hpgamma_scale->Draw("HIST same");
    hpgamma_scale->SetLineColor(3);

    nbins = hpn->GetXaxis()->GetNbins();
    TH1F *hpn_scale = new TH1F("hpn_scale", "", newnbins, 0, maxx);
    for (int i = 1; i <= nbins; i++)
    {
        y = hpn->GetBinContent(i);
        x = hpn->GetXaxis()->GetBinCenter(i);
        xnew = norm_c * x;
        hpn_scale->Fill(xnew, y);
    }
    hpn_scale->Draw("HIST same");
    hpn_scale->SetLineColor(46);

    nbins = hpp->GetXaxis()->GetNbins();
    TH1F *hpp_scale = new TH1F("hpp_scale", "", newnbins, 0, maxx);
    for (int i = 1; i <= nbins; i++)
    {
        y = hpp->GetBinContent(i);
        x = hpp->GetXaxis()->GetBinCenter(i);
        xnew = norm_c * x;
        hpp_scale->Fill(xnew, y);
    }
    hpp_scale->Draw("HIST same");
    hpp_scale->SetLineColor(6);

    nbins = hppin->GetXaxis()->GetNbins();
    TH1F *hppin_scale = new TH1F("hppin_scale", "", newnbins, 0, maxx);
    for (int i = 1; i <= nbins; i++)
    {
        y = hppin->GetBinContent(i);
        x = hppin->GetXaxis()->GetBinCenter(i);
        xnew = norm_c * x;
        hppin_scale->Fill(xnew, y);
    }
    hppin_scale->Draw("HIST same");
    hppin_scale->SetLineColor(30);

    nbins = hppip->GetXaxis()->GetNbins();
    TH1F *hppip_scale = new TH1F("hppip_scale", "", newnbins, 0, maxx);
    for (int i = 1; i <= nbins; i++)
    {
        y = hppip->GetBinContent(i);
        x = hppip->GetXaxis()->GetBinCenter(i);
        xnew = norm_c * x;
        hppip_scale->Fill(xnew, y);
    }
    hppip_scale->Draw("HIST same");
    hppip_scale->SetLineColor(28);

    hp_scale->SetLineWidth(3);
    hpen_scale->SetLineWidth(3);
    hpep_scale->SetLineWidth(3);
    hpgamma_scale->SetLineWidth(3);
    hpn_scale->SetLineWidth(3);
    hpp_scale->SetLineWidth(3);
    hppin_scale->SetLineWidth(3);
    hppip_scale->SetLineWidth(3);

    float x1_l = 0.7;
    float y1_l = 0.80;
    float dx_l = 0.20;
    float dy_l = 0.3;
    float x0_l = x1_l - dx_l;
    float y0_l = y1_l - dy_l;

    TLegend *lgdz = new TLegend(x0_l, y0_l, x1_l, y1_l);
    lgdz->SetBorderSize(0);
    lgdz->SetTextSize(0.04);
    lgdz->SetTextFont(62);
    lgdz->SetFillColor(0);
    //lgdz->SetLineWidth(2);
    lgdz->AddEntry(hp_scale, "total", "l");
    lgdz->AddEntry(hpen_scale, "e-", "l");
    lgdz->AddEntry(hpep_scale, "e+", "l");
    lgdz->AddEntry(hpgamma_scale, "#gamma", "l");
    lgdz->AddEntry(hpn_scale, "n", "l");
    lgdz->AddEntry(hpp_scale, "p", "l");
    lgdz->AddEntry(hppin_scale, "#pi -", "l");
    lgdz->AddEntry(hppip_scale, "#pi +", "l");
    lgdz->Draw();
}
