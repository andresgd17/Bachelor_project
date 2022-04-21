void macro_pointers()
{
    float x[5] = {1, 2, 3, 4, 5};
    float y[]  = {1, 4, 9, 15, 25};

    TGraph *gr = new TGraph(5,x,y); // pointer of TGraph
    
    TCanvas *canvas = new TCanvas();
    gr->Draw("alp");
    canvas->Print("gr_plot_with_pointers.png");
    
    //delete canvas, gr;  // you can de-allocate memory using delete 
}

