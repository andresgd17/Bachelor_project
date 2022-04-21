void readtree()
{
    // open the root file
    TFile file("myRootFile.root","read");
    
    // To retrieve the tree we create a TTree pointer
    TTree * tree = (TTree*) file.Get("tree_name");

    //define the variable of the branch
    float energy;

    // we set the branch to be read 
    tree->SetBranchAddress("Energy", &energy);

    // get the total of enetries in the tree
    int nentries = tree->GetEntries();

    // lets print the total entries of the tree
    cout << "total entries: " << nentries << endl;

    // loop over the entries
    for (int i = 0; i < nentries ; i ++)
    {
        // get the current entry of the branch
        tree->GetEntry(i);

        cout << "energy: " << energy << endl;
    }
}

