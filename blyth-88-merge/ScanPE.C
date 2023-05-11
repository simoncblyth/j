{
   TFile* f = new TFile("sample_detsim_user.root") ; 
   TTree* e = (TTree*)f->Get("evt"); 
   e->Scan("nPhotons:totalPE:LpmtPE:SpmtPE:NNVTPE:HamaPE:CDPE:WPPE"); 
}
