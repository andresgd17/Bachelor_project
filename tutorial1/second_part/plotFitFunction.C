//
//  plotProfile()
//
//  ROOT macro to display simulated profile
//
//    usage: .x plotProfile.C("conex.root",3)
//
//       to plot profile of event no. 3 in file conex.root
//

double pol2(double* x, double* par);
double findMaxPosition(TGraph *G);

void plotFitFunction(const char* file="", int ievt=-1) 
{
  // check the event number is correct
  if (ievt<0 ) {
    cout << "\n usage: .x plotProfile.C(\"conex.root\",3) \n"
	 << "         to plot profile of event no. 3 in file contex.root\n" << endl;
    return;
  }
   
   TFile* f = new TFile(file, "read");
  
   // set and read tree
   TTree* Shower = (TTree*) f->Get("Shower");

   int nevent=Shower->GetEntries();
   if ( ievt >= nevent ) {
     cout << " Error - requested event number exceeds number of events in file!"
          << "\n         ievt=" << ievt << " nevent=" << nevent
          << "\n exit ..." << endl;
     return;
   }

   const int maxX=20000;
   float     X[maxX], N[maxX];
   float     energy, zenith;
   int       nX;

   Shower->SetBranchAddress("lgE",    &energy);  // energy of primary particle
   Shower->SetBranchAddress("zenith", &zenith);  // zeinth angle of primary particle
   Shower->SetBranchAddress("nX",     &nX);      // number of points in slant depth
   Shower->SetBranchAddress("N",      N);        // array of particles(X)
   Shower->SetBranchAddress("X",      X);        // array of slant depth

   Shower->GetEntry(ievt);

   TCanvas* canvas = new TCanvas("v1","profile for charged particles",800,10,700,500);
   TGraph* graph1 = new TGraph(nX,X,N);

   graph1->SetMarkerStyle(20);
   graph1->SetMarkerSize(.7);
   graph1->SetTitle("");
   graph1->GetXaxis()->SetTitle("X [g/cm^{2}]");
   graph1->GetYaxis()->SetTitle("number of charged particles");
   graph1->GetYaxis()->SetTitleOffset(1.);
   graph1->Draw("AP");

   // draw shower parameters

   TLatex* leg = new TLatex();
   leg->SetNDC();
   leg->SetTextAlign(12);
   leg->SetTextSize(0.03);
   

   float xfirst = 0.15;
   float yfirst = 0.85;
   float dy = 0.05;
   int iPart = 5600;

   leg->DrawLatex(0.15,0.85," iron");

   char legend[100];
   
   yfirst-=dy;
   float y = yfirst-0.07;
   sprintf(legend,"lg(E/eV)=%5.2f",energy);
   leg->DrawLatex(xfirst, y, legend); 
   y-=dy;
   sprintf(legend,"zenith=%5.2f",zenith);
   leg->DrawLatex(xfirst, y, legend); 


   /// fitting your TGraph
   //------------------------------------------------------
   //------------------------------------------------------
   double lim_inf = findMaxPosition(graph1) - 100;
   double lim_sup = findMaxPosition(graph1) + 100;

   TF1 fpol2("name_function",pol2,lim_inf,lim_sup,3);
   graph1->Fit(&fpol2,"R");
   
   cout << "p0: " << fpol2.GetParameter(0) << endl;
   cout << "p1: " << fpol2.GetParameter(1) << endl;
   cout << "p2: " << fpol2.GetParameter(2) << endl;
   //------------------------------------------------------
   //------------------------------------------------------


   canvas->Print(("plot_Fitting_Profile_event" + to_string(ievt) + ".pdf").c_str());
   
   return;

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