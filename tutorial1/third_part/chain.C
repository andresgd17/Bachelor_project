double pol2(double* x, double* par);
double findMaxPosition(TGraph *G);
double GaisserHillas(double* x, double* par);

void chain()
{
  // Create the TTree to save info your rootfile
  TFile *myfile = new TFile("gamma.root", "recreate");
  TTree *tree   = new TTree("name", "title");
  
  float xmaxpol2, lgE;
  tree->Branch("xmaxpol2", &xmaxpol2);
  tree->Branch("lgE",      &lgE);

  ///   files of gamma air showers 
  TChain Shower("Shower");
  Shower.Add("../data/conex_qgsjetII04_1691065738_0.root"); 
  //Shower.Add("../data/conex_qgsjetII04_092353445_0.root"); 
  //Shower.Add("../data/conex_qgsjetII04_307297119_0.root"); 
  //Shower.Add("../data/conex_qgsjetII04_403001170_0.root"); 

  const int maxX = 20000;
  float     X[maxX], N[maxX];
  int       nX;

  Shower.SetBranchAddress("lgE",    &lgE);     // lgE energy of primary particle
  Shower.SetBranchAddress("nX",     &nX);      // number of points in slant depth
  Shower.SetBranchAddress("N",      N);        // array of particles(X)
  Shower.SetBranchAddress("X",      X);        // array of slant depth
  
  int nentries = Shower.GetEntries();
  TH1D *histo = new TH1D("name","title",100, 0, 1000);
  
  for(int i=0;i<nentries;i++)
  {
    Shower.GetEntry(i);

    // Define the TGraph with the shower profile for the i-th event
    TGraph *graph1 = new TGraph(nX,X,N);
    
    cout << "Event " << i << endl;
    cout << "Energy of the primary particle = " << TMath::Power(10,lgE)/(1e12) << " TeV" <<  endl;
    
    /// fitting your TGraph with second degree pol
    //------------------------------------------------------
    //------------------------------------------------------
    
    //get the x coordinate of the maximum point of a TGraph using function findMaxPosition()
    double lim_inf = findMaxPosition(graph1) - 100;
    double lim_sup = findMaxPosition(graph1) + 100;
    
    // define function of second  degree
    TF1 fpol2("name_function",pol2,lim_inf,lim_sup,3);
    // fit method
    graph1->Fit(&fpol2,"RQ");
    
    cout << "f(X) = " << fpol2.GetParameter(0) << " + " << fpol2.GetParameter(1) << "* X  + " << fpol2.GetParameter(2) << " *X^2 " << endl;            
    
    xmaxpol2       = -fpol2.GetParameter(1)/(2.0*fpol2.GetParameter(2));
    float nmaxpol2 = fpol2.GetParameter(0) + fpol2.GetParameter(1)*xmaxpol2 + fpol2.GetParameter(2)*xmaxpol2*xmaxpol2;
    //------------------------------------------------------
    //------------------------------------------------------
    /// fitting your TGraph with GH
    //------------------------------------------------------
    //------------------------------------------------------
    TF1 GH("GaisserHillas",GaisserHillas,0,1000,4);
    
    // Initialized parameters before invoking the Fit method.
    GH.SetParameter(0, nmaxpol2); // Nmax
    GH.SetParameter(1, xmaxpol2); // Xmax
    GH.SetParameter(2, -120.);    // X0            // GH.FixParameter(2, -120.); // use this if you want to fix the parameter during the fitting 
    GH.SetParameter(3,  90.);     // lambda

    // Set the bounds for each parameter
    GH.SetParLimits(0,nmaxpol2-10000,nmaxpol2+10000);
    GH.SetParLimits(1,xmaxpol2 -200 ,nmaxpol2 + 200);
    GH.SetParLimits(2,-1000 ,1000);
    GH.SetParLimits(3,10 ,200);

    graph1->Fit(&GH,"R");
    //------------------------------------------------------
    //------------------------------------------------------

    cout << "xmax from pol2 = " << xmaxpol2 << endl;
    cout << "\n" << endl;
    //------------------------------------------------------
    //------------------------------------------------------
    
    tree->Fill();
    
    graph1->Draw("alp");
    //delete graph1;
    histo->Fill(xmaxpol2);
  }

  

  TCanvas* canvas = new TCanvas("v1","profile for charged particles",800,10,700,500);
  histo->Draw();
  
  myfile->cd();
  tree->Write();
  //myfile->Close();

  return 0;
}

 //
 //  double quadratic funtion (double *x, double *par)
 //   
 //   returns number of electrons at depth x[0]
 //   with second-order polynomial parameters
 //
 //        p0 =par[0]
 //        p1 =par[1]
 //        p2 =par[2]
 //       
 //      (f = p0 + p1*x + p2*x^2 )
 //

 double pol2(double* x, double* par)
 {
   double t  = x[0];
   double p0 = par[0];
   double p1 = par[1];
   double p2 = par[2];

   double result = p0 + p1*t + p2*t*t;
   return result;
 }

//
//  function to find the x coordinate of the maximum value in the y coordinate 
//
double findMaxPosition(TGraph *G) {
    double x, y;
    G->GetPoint(0, x, y);
    double max_x = x, max_y = y;
    for(int i = 1; i < G->GetN(); i++)
    {
        G->GetPoint(i, x, y);
        if(y > max_y) {
           max_x = x;
           max_y = y;
        }
    }
    return max_x;
}


 //
 //  double GaisserHillas(double *x, double *par)
 //
 //   returns number of electrons at depth x[0]
 //   with Gaisser-Hillas parameters
 //
 //        Nmax=par[0]
 //        Xmax=par[1]
 //        X0  =par[2]
 //        lb  =par[3]
 //
 //      (lambda=lb)
 //
 double GaisserHillas(double* x, double* par)
 {
   double t =x[0];
   double anmax   = par[0];
   double tmax    = par[1];
   double t0      = par[2];
   double lambda  = par[3];

   double expo = (tmax-t0)/lambda;
   double f = anmax*pow((t-t0)/(tmax-t0),expo);
   expo = (tmax-t)/lambda;
   f = f*exp(expo);

   return f;
 }
