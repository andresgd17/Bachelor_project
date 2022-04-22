void chain()
{
   //TChain Header("Header");
   //Header.Add("../data/conex_qgsjetII04_092353445_0.root"); ///   1000 air showers events initiated by gamma
   //Header.Add("../data/conex_qgsjetII04_040390428_5600.root");  /// 1000 air showers events initiated by iron
   //int particle;
   //Header.SetBranchAddress("Particle", &particle);  

   TChain Shower("Shower");
   Shower.Add("../data/conex_qgsjetII04_092353445_0.root"); ///   1000 air showers events initiated by gamma
   Shower.Add("../data/conex_qgsjetII04_040390428_5600.root");  /// 1000 air showers events initiated by iron

   const int maxX = 20000;
   float     X[maxX], N[maxX];
   float     energy, zenith;
   int       nX;

   Shower.SetBranchAddress("lgE",    &energy);  // energy of primary particle
   Shower.SetBranchAddress("zenith", &zenith);  // zeinth angle of primary particle
   Shower.SetBranchAddress("nX",     &nX);      // number of points in slant depth
   Shower.SetBranchAddress("N",      N);        // array of particles(X)
   Shower.SetBranchAddress("X",      X);        // array of slant depth
   
   int nentries = Shower.GetEntries();

   for(int i=0;i<nentries;i++)
   {
     Shower.GetEntry(i);
     //cout << energy << endl;
   }

   TCanvas* canvas = new TCanvas("v1","profile for charged particles",800,10,700,500);

   // -------------------get event 0-----------gamma shower --------
   // ----------------------------------------------------------
   Shower.GetEntry(0); // get event 0
   TGraph* graph1 = new TGraph(nX,X,N);

   graph1->SetMarkerStyle(20);
   graph1->SetMarkerSize(.7);
   graph1->SetTitle("");
   graph1->GetXaxis()->SetTitle("X [g/cm^{2}]");
   graph1->GetYaxis()->SetTitle("number of charged particles");
   graph1->GetYaxis()->SetTitleOffset(1.);
   graph1->Draw("ap");

   // draw shower parameters 
   // ----------------------------------
   // ----------------------------------
   TLatex* leg = new TLatex();
   leg->SetNDC();
   leg->SetTextAlign(12);
   leg->SetTextSize(0.03);
   
   float xfirst = 0.15;
   float yfirst = 0.85;
   float dy = 0.05;

   leg->DrawLatex(xfirst,yfirst," gamma event");
   char legend[100];
   
   yfirst-=dy;
   float y = yfirst-0.07;
   sprintf(legend,"lg(E/eV)=%5.2f",energy);
   leg->DrawLatex(xfirst, y, legend); 
   y-=dy;
   sprintf(legend,"zenith=%5.2f",zenith);
   leg->DrawLatex(xfirst, y, legend); 
   // ----------------------------------
   // -----------------------------------

   // -----------------get event 1003----------iron shower---------
   // ----------------------------------------------------------
   Shower.GetEntry(1993); // get event 0
   TGraph* graph2 = new TGraph(nX,X,N);

   graph2->SetMarkerStyle(20);
   graph2->SetMarkerSize(.7);
   graph2->SetTitle("");
   graph2->SetMarkerColor(kBlue);
   graph2->GetXaxis()->SetTitle("X [g/cm^{2}]");
   graph2->GetYaxis()->SetTitle("number of charged particles");
   graph2->GetYaxis()->SetTitleOffset(1.);
   graph2->Draw("same p");
   
   // draw shower parameters 
   // ----------------------------------
   // ----------------------------------
   xfirst = 0.15;
   yfirst = 0.45;

   leg->DrawLatex(xfirst, yfirst," #color[4]{iron shower}");

   yfirst-=dy;
   y = yfirst-0.07;
   sprintf(legend,"#color[4]{lg(E/eV)=%5.2f}",energy);
   leg->DrawLatex(xfirst, y, legend); 
   y-=dy;
   sprintf(legend,"#color[4]{zenith=%5.2f}",zenith);
   leg->DrawLatex(xfirst, y, legend); 
   // ----------------------------------
   // -----------------------------------

}