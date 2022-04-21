void macro()
{
    float x[5] = {1, 2, 3, 4, 5};
    float y[]  = {1, 4, 9, 15, 25};

    TGraph gr(5,x,y);
    
    TCanvas canvas;  // TCanvas class is required to plot your graph
    gr.Draw("alp");
    gr.SetTitle("Title");
    gr.GetXaxis()->SetTitle("X-axis");
    gr.GetYaxis()->SetTitle("Y-axis");
    canvas.Print("gr_plot.png");   // you can print your plot as pdf, png, jpg, etc...
}

