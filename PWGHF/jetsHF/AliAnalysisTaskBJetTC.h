#ifndef ALIANALYSISTASKBJETTC_H
#define ALIANALYSISTASKBJETTC_H
#include "AliAnalysisTaskEmcalJet.h"
#include "AliV0ReaderV1.h"
#include "AliConvEventCuts.h"
class AliEmcalJet;
class AliAODVertex;
class AliAODTrack;
class TList;
class TH1D;
class TH2D;
class THnSparse;
class AliHFJetsTagging;
class TClonesArray;
class AliAODMCParticle;
class AliAnalysisUtils;
class TRandom3;
class AliPIDResponse;



class AliAnalysisTaskBJetTC: public AliAnalysisTaskEmcalJet
{
public:

	enum TTypeImpPar {kXY,kXYSig,kXYZ,kXYZSig,kXYZSigmaOnly};

	AliAnalysisTaskBJetTC();
	AliAnalysisTaskBJetTC(const char *name);
	//AliAnalysisTaskBJetTC(const AliAnalysisTaskBJetTC&);	// copy constructor not implemented yet
	//AliAnalysisTaskBJetTC& operator=(const AliAnalysisTaskBJetTC&);	// assignment operator not implemented yet

	virtual ~AliAnalysisTaskBJetTC();
	virtual void  UserCreateOutputObjects();
  	virtual void  Terminate(Option_t *);
	virtual Bool_t Run();
	virtual Double_t GetDeltaPtRandomCone();
	virtual Double_t GetDeltaPtRandomConeTagCuts();
	virtual Bool_t Notify();


  	void SetPtHardBin(Int_t b){ fSelectPtHardBin   = b;}

	Bool_t IsEventSelected();
	  enum EPileup {kNoPileupSelection,kRejectPileupEvent,kRejectTracksFromPileupVertex};
	  enum ERejBits {kNotSelTrigger,kNoVertex,kTooFewVtxContrib,kZVtxOutFid,kPileupSPD,kOutsideCentrality,kVertexZContrib,kPhysicsSelection,
		kNoContributors,kDeltaVertexZ,kNoVertexTracks,kVertexZResolution,kMVPileup,kSPDClusterCut,kZVtxSPDOutFid,kCentralityFlattening,kSelPtHardBin};
	Bool_t IsSelected(Int_t &WhyRejected,ULong_t &RejectionBits);
        void DoJetProbabilityAnalysis(Bool_t val=true){fDoJetProbabilityAnalysis=val;}
        void DoPtRelAnalysis(Bool_t val=true){fDoPtRelAnalysis=val;}

	void UseCorrectedRhoPt(bool val = true){fUseCorrPt =val;};
	void UseGammaV0Rejection(bool val = true){fEnableV0GammaRejection =val;};
  	Bool_t IsV0InJet(TVector3 vV0, Double_t dJetPtMin);
	Bool_t IsElectronHF(AliAODTrack* track);
  	void FillCandidates(Bool_t isK, Bool_t isL, Bool_t isAL, Int_t iCut);
  	void FillCandidateJet(Int_t CutIndex, Int_t JetFlavor);

	// V0 selection
	void SetCutTPCRefit(Bool_t val = kTRUE) {fbTPCRefit = val;}
	void SetCutRejectKinks(Bool_t val = kTRUE) {fbRejectKinks = val;}
	void SetCutFindableClusters(Bool_t val = kTRUE) {fbFindableClusters = val;}
	void SetCutNCrossedRowsTPCMin(Double_t val = 70.) {fdCutNCrossedRowsTPCMin = val;}
	void SetCutCrossedRowsOverFindMin(Double_t val = 0.8) {fdCutCrossedRowsOverFindMin = val;}
	void SetCutCrossedRowsOverFindMax(Double_t val = 1e3) {fdCutCrossedRowsOverFindMax = val;}
	void SetCutPtDaughterMin(Double_t val = 0.150) {fdCutPtDaughterMin = val;}
	void SetCutDCAToPrimVtxMin(Double_t val = 0.1) {fdCutDCAToPrimVtxMin = val;}
	void SetCutDCADaughtersMax(Double_t val = 1.) {fdCutDCADaughtersMax = val;}
	void SetCutEtaDaughterMax(Double_t val = 0.8) {fdCutEtaDaughterMax = val;}
	void SetCutNSigmadEdxMax(Double_t val = 3.) {fdCutNSigmadEdxMax = val;}
	void SetPtProtonPIDMax(Double_t val = 1.) {fdPtProtonPIDMax = val;}
	void SetOnFly(Bool_t val = 0) {fbOnFly = val;}
	void SetCutCPAKMin(Double_t val = 0.998) {fdCutCPAKMin = val;}
	void SetCutCPALMin(Double_t val = 0.998) {fdCutCPALMin = val;}
	void SetCutRadiusDecayMin(Double_t val = 5.) {fdCutRadiusDecayMin = val;}
	void SetCutRadiusDecayMax(Double_t val = 100.) {fdCutRadiusDecayMax = val;}
	void SetCutEtaV0Max(Double_t val = 0.7) {fdCutEtaV0Max = val;}
	void SetCutRapV0Max(Double_t val = 0.75) {fdCutRapV0Max = val;}
	void SetCutNTauKMax(Double_t val = 5.0) {fdCutNTauKMax = val;}
	void SetCutNTauLMax(Double_t val = 5.0) {fdCutNTauLMax = val;}
	void SetCutArmPod(Bool_t val = kTRUE) {fbCutArmPod = val;}
	void SetCutCross(Bool_t val = kTRUE) {fbCutCross = val;}

	Bool_t SetResFunction(TF1 *f, Int_t j){
	    fResolutionFunction[j] = f;
	    return kTRUE;
	}

	void ApplyV0Reconstruction(Bool_t val = kTRUE) {fApplyV0Rec = val;}
	void ApplyV0RejectionAll(Bool_t val = kTRUE) {fApplyV0RejectionAll = val;}

	void SetV0ReaderName(TString name){fV0ReaderName=name; return;}

	// B jet tracks selection

	void SetTrackMinPt(Double_t val){ fTCMinTrackPt = val;}
	void SetTPCClusterMin(Int_t val){ fTCMinClusTPC = val;}
	void SetITSHitsMin(Int_t val){ fTCMinHitsITS = val;}
	void SetMaxChi2perNDF(Double_t val){ fTCMaxChi2pNDF = val;}
	void SetMaxIPxy(Double_t val){ fTCMaxIPxy = val;}
	void SetMaxIPz(Double_t val){ fTCMaxIPz = val;}
	void SetMaxbDecayLength(Double_t val){ fTCMaxDecayLength = val;}
	void SetMaxDCATrackJet(Double_t val){ fTCMaxDCATrackJet = val;}

private:

	AliV0ReaderV1*           fV0Reader;//!
    	TString                  fV0ReaderName;//
    	TClonesArray*            fReaderGammas;//!

	Bool_t SelectV0CandidateVIT();
  	Bool_t IsParticleInCone(const AliVParticle* part, const AliEmcalJet* jet, Double_t dRMax) const; // decides whether a particle is inside a jet cone
	Bool_t CalculateTrackImpactParameter(AliAODTrack * track,double *impar, double * cov); // Removes track from Vertex calculation first
	Bool_t CalculateTrackImpactParameterTruth(AliAODTrack * track,double *impar, double * cov); // calculates DCA on MC particle/event information
	Bool_t CalculateJetSignedTrackImpactParameter(AliAODTrack * track,AliEmcalJet * jet ,double *impar, double * cov, double &sign, double &dcajetrack, double &lineardecaylength);
	Double_t GetValImpactParameter(TTypeImpPar type,double *impar, double * cov);
	Bool_t IsV0PhotonFromBeamPipeDaughter(const AliAODTrack* track);
	Bool_t IsV0Daughter(const AliAODTrack* track);
	Bool_t IsTrackAccepted(AliAODTrack* track);
	Bool_t IsTrackAcceptedFidutial(AliAODTrack* track);
	Bool_t IsTrackAcceptedQuality(AliAODTrack* track ,AliEmcalJet* Jet, Int_t &QualityClass, double *imp, double * cov, double &sign);
	Bool_t IsTrackAcceptedBJetCuts(AliAODTrack* track, Int_t jetFlavour);
	Bool_t MatchJetsGeometricDefault(); //jet matching function 1/4
	void   DoJetLoop(); //jet matching function 2/4
	void   SetMatchingLevel(AliEmcalJet *jet1, AliEmcalJet *jet2, int matching=0); //jet matching function 3/4
	void   GetGeometricalMatchingLevel(AliEmcalJet *jet1, AliEmcalJet *jet2, Double_t &d) const; //jet matching function 4/4
  	Double_t CalculateTrackProb(Double_t significance, Int_t trclass);
  	Double_t CalculateJetProb(AliEmcalJet * jet);//!
  	void FillResolutionFunctionHists(AliAODTrack * track,AliEmcalJet * jet);

	AliAODMCParticle* GetMCTrack( const AliAODTrack* _track);

	Double_t GetPtRel(AliAODTrack* Lep, AliEmcalJet* jet, Bool_t AddLepToJet);
	void	 GetTrkClsEtaPhiDiff(AliVTrack *t, AliVCluster *v, Double_t &phidiff, Double_t &etadiff);

	AliHFJetsTagging* fHFJetUtils;//!

	Bool_t fUseCorrPt;//
	Bool_t fEnableV0GammaRejection;//
	Float_t fPythiaEventWeight;//!

  	AliPIDResponse   *fRespoPID;//!

	TRandom3* fRandom;//! Random cone input

	TH1D * fh1dEventRejectionRDHFCuts;//! Store Rejection reasons and number of accepted events
	TH1D * fh1dVertexZ;//!
	TH1D * fh1dVertexZAccepted;//!
	TH2D * fh1dVertexR;//!
	TH2D * fh1dVertexRAccepted;//!


	// Bjet cuts
	Double_t fTCMinTrackPt;//
	Int_t    fTCMinClusTPC;//
	Int_t 	 fTCMinHitsITS;//
	Double_t fTCMaxChi2pNDF;//
	Double_t fTCMaxIPxy;//
	Double_t fTCMaxIPz;//
	Double_t fTCMaxDecayLength;//
	Double_t fTCMaxDCATrackJet;//
	
	TH1D * fhistInclusiveJetCuts;//!
	TH1D * fhistbJetCuts;//!
	TH1D * fhistcJetCuts;//!
	TH1D * fhistlfJetCuts;//!

	TH1D * fh1dTracksAccepeted;//!

	TH1D * fh1dJetRecPtAcceptedunCorr;//!

	TH1D * fhist_BJet_Background_Fluctuation;//!
	TH2D * f2histRhoVsDeltaPt;//!

	TH1D * fh1dTracksImpParXY;//! R Impact Parameter
	TH1D * fh1dTracksImpParXYZ;//! R+z Impact Parameter
	TH1D * fh1dTracksImpParXYSignificance;//! R Impact Parameter Significance
	TH1D * fh1dTracksImpParXYZSignificance;//! R+z Impact Parameter Significance

	TH1D * fh1dTracksImpParXYTruth;//! R Impact Parameter truth
	TH1D * fh1dTracksImpParXYZTruth;//! R+z Impact Parameter truth
	TH1D * fh1dTracksImpParXYResidualTruth;//! Delta R Impact Parameter over uncertainty
	TH1D * fh1dTracksImpParXYZResidualTruth;//! Delta R+z Impact Parameter truth over uncertainty
	// inclusive  impact parameter distributions  for tracks with light meson (TODO D meson) correction in Monte Carlo

	TH2D * fh2dVertexChi2NDFNESDTracks;//!

	TH1D * fh1dJetGenPt; //! Generator level jet momentum for unfolding
	TH1D * fh1dJetGenPtUnidentified; //!
	TH1D * fh1dJetGenPtudsg; //!
	TH1D * fh1dJetGenPtc; //!
	TH1D * fh1dJetGenPtb; //!

	TH1D * fh1dJetRecPt; //! Detector level jets
	TH1D * fh1dJetRecPtAccepted; //! Detector level jets accepted
	TH2D * fh1dJetRecEtaPhiAccepted; //! Detector level jets accepted

	TH1D * fh1dJetRecPtUnidentified; //!
	TH1D * fh1dJetRecPtudsg; //!
	TH1D * fh1dJetRecPtc; //!
	TH1D * fh1dJetRecPtb; //!
	TH1D * fh1dJetRecPtUnidentifiedAccepted; //!
	TH1D * fh1dJetRecPtudsgAccepted; //!
	TH1D * fh1dJetRecPtcAccepted; //!
	TH1D * fh1dJetRecPtbAccepted; //!

	TH2D * fh2dJetGenPtVsJetRecPt; //! raw momentum response matrix
	TH2D * fh2dJetGenPtVsJetRecPtb; //! b momentum response matrix
	TH2D * fh2dJetGenPtVsJetRecPtc; //! c momentum response matrix
	TH2D * fh2dJetGenPtVsJetRecPtudsg; //! udsg momentum response matrix
	// inclusive signed impact parameter distributions
	TH2D * fh2dJetSignedImpParXY; //!
	TH2D * fh2dJetSignedImpParXYUnidentified; //!
	TH2D * fh2dJetSignedImpParXYudsg; //!
	TH2D * fh2dJetSignedImpParXYb; //!
	TH2D * fh2dJetSignedImpParXYc; //!

	TH2D * fh2dJetSignedImpParXYSignificance; //!
	TH2D * fh2dJetSignedImpParXYSignificanceUnidentified; //!
	TH2D * fh2dJetSignedImpParXYSignificanceudsg; //!
	TH2D * fh2dJetSignedImpParXYSignificanceb; //!
	TH2D * fh2dJetSignedImpParXYSignificancec; //!

	TH2D * fh2dJetSignedImpParXYZ; //!
	TH2D * fh2dJetSignedImpParXYZUnidentified; //!
	TH2D * fh2dJetSignedImpParXYZudsg; //!
	TH2D * fh2dJetSignedImpParXYZb; //!
	TH2D * fh2dJetSignedImpParXYZc; //!

	TH2D * fh2dJetSignedImpParXYZSignificance; //!
	TH2D * fh2dJetSignedImpParXYZSignificanceUnidentified; //!
	TH2D * fh2dJetSignedImpParXYZSignificanceudsg; //!
	TH2D * fh2dJetSignedImpParXYZSignificanceb; //!
	TH2D * fh2dJetSignedImpParXYZSignificancec; //!

	//################################ Jet Probabilty
        TH2D * fh2dJetSignedImpParXY_Class1;//!
        TH2D * fh2dJetSignedImpParXYSignificance_Class1;//!
        TH2D * fh2dJetSignedImpParXYZ_Class1;//!
        TH2D * fh2dJetSignedImpParXYZSignificance_Class1;//!

        TH2D * fh2dJetSignedImpParXY_Class2;//!
        TH2D * fh2dJetSignedImpParXYSignificance_Class2;//!
        TH2D * fh2dJetSignedImpParXYZ_Class2;//!
        TH2D * fh2dJetSignedImpParXYZSignificance_Class2;//!

        TH2D * fh2dJetSignedImpParXY_Class3;//!
        TH2D * fh2dJetSignedImpParXYSignificance_Class3;//!
        TH2D * fh2dJetSignedImpParXYZ_Class3;//!
        TH2D * fh2dJetSignedImpParXYZSignificance_Class3;//!

        TH2D * fh2dJetSignedImpParXY_Class4;//!
        TH2D * fh2dJetSignedImpParXYSignificance_Class4;//!
        TH2D * fh2dJetSignedImpParXYZ_Class4;//!
        TH2D * fh2dJetSignedImpParXYZSignificance_Class4;//!


	TH2D * fhistJetProbability;//!
        TH2D * fhistJetProbability_Unidentified;//!
        TH2D * fhistJetProbability_udsg;//!
        TH2D * fhistJetProbability_c;//!
        TH2D * fhistJetProbability_b;//!

	TH2D * fhistJetProbabilityLog;//!
        TH2D * fhistJetProbability_UnidentifiedLog;//!
        TH2D * fhistJetProbability_udsgLog;//!
        TH2D * fhistJetProbability_cLog;//!
        TH2D * fhistJetProbability_bLog;//!


	// inclusive signed impact parameter distributions
	//First
	TH2D * fh2dJetSignedImpParXYFirst; //!
	TH2D * fh2dJetSignedImpParXYUnidentifiedFirst; //!
	TH2D * fh2dJetSignedImpParXYudsgFirst; //!
	TH2D * fh2dJetSignedImpParXYbFirst; //!
	TH2D * fh2dJetSignedImpParXYcFirst; //!

	TH2D * fh2dJetSignedImpParXYSignificanceFirst; //!
	TH2D * fh2dJetSignedImpParXYSignificanceUnidentifiedFirst; //!
	TH2D * fh2dJetSignedImpParXYSignificanceudsgFirst; //!
	TH2D * fh2dJetSignedImpParXYSignificancebFirst; //!
	TH2D * fh2dJetSignedImpParXYSignificancecFirst; //!

	TH2D * fh2dJetSignedImpParXYZFirst; //!
	TH2D * fh2dJetSignedImpParXYZUnidentifiedFirst; //!
	TH2D * fh2dJetSignedImpParXYZudsgFirst; //!
	TH2D * fh2dJetSignedImpParXYZbFirst; //!
	TH2D * fh2dJetSignedImpParXYZcFirst; //!

	TH2D * fh2dJetSignedImpParXYZSignificanceFirst; //!
	TH2D * fh2dJetSignedImpParXYZSignificanceUnidentifiedFirst; //!
	TH2D * fh2dJetSignedImpParXYZSignificanceudsgFirst; //!
	TH2D * fh2dJetSignedImpParXYZSignificancebFirst; //!
	TH2D * fh2dJetSignedImpParXYZSignificancecFirst; //!
	//Second
	TH2D * fh2dJetSignedImpParXYSecond; //!
	TH2D * fh2dJetSignedImpParXYUnidentifiedSecond; //!
	TH2D * fh2dJetSignedImpParXYudsgSecond; //!
	TH2D * fh2dJetSignedImpParXYbSecond; //!
	TH2D * fh2dJetSignedImpParXYcSecond; //!

	TH2D * fh2dJetSignedImpParXYSignificanceSecond; //!
	TH2D * fh2dJetSignedImpParXYSignificanceUnidentifiedSecond; //!
	TH2D * fh2dJetSignedImpParXYSignificanceudsgSecond; //!
	TH2D * fh2dJetSignedImpParXYSignificancebSecond; //!
	TH2D * fh2dJetSignedImpParXYSignificancecSecond; //!

	TH2D * fh2dJetSignedImpParXYZSecond; //!
	TH2D * fh2dJetSignedImpParXYZUnidentifiedSecond; //!
	TH2D * fh2dJetSignedImpParXYZudsgSecond; //!
	TH2D * fh2dJetSignedImpParXYZbSecond; //!
	TH2D * fh2dJetSignedImpParXYZcSecond; //!

	TH2D * fh2dJetSignedImpParXYZSignificanceSecond; //!
	TH2D * fh2dJetSignedImpParXYZSignificanceUnidentifiedSecond; //!
	TH2D * fh2dJetSignedImpParXYZSignificanceudsgSecond; //!
	TH2D * fh2dJetSignedImpParXYZSignificancebSecond; //!
	TH2D * fh2dJetSignedImpParXYZSignificancecSecond; //!
	//Third
	TH2D * fh2dJetSignedImpParXYThird; //!
	TH2D * fh2dJetSignedImpParXYUnidentifiedThird; //!
	TH2D * fh2dJetSignedImpParXYudsgThird; //!
	TH2D * fh2dJetSignedImpParXYbThird; //!
	TH2D * fh2dJetSignedImpParXYcThird; //!

	TH2D * fh2dJetSignedImpParXYSignificanceThird; //!
	TH2D * fh2dJetSignedImpParXYSignificanceUnidentifiedThird; //!
	TH2D * fh2dJetSignedImpParXYSignificanceudsgThird; //!
	TH2D * fh2dJetSignedImpParXYSignificancebThird; //!
	TH2D * fh2dJetSignedImpParXYSignificancecThird; //!

	TH2D * fh2dJetSignedImpParXYZThird; //!
	TH2D * fh2dJetSignedImpParXYZUnidentifiedThird; //!
	TH2D * fh2dJetSignedImpParXYZudsgThird; //!
	TH2D * fh2dJetSignedImpParXYZbThird; //!
	TH2D * fh2dJetSignedImpParXYZcThird; //!

	TH2D * fh2dJetSignedImpParXYZSignificanceThird; //!
	TH2D * fh2dJetSignedImpParXYZSignificanceUnidentifiedThird; //!
	TH2D * fh2dJetSignedImpParXYZSignificanceudsgThird; //!
	TH2D * fh2dJetSignedImpParXYZSignificancebThird; //!
	TH2D * fh2dJetSignedImpParXYZSignificancecThird; //!



	TH2D* fh2dKshortMassVsPt;//!
	TH2D* fh2dLamdaMassVsPt;//!
	TH2D* fh2dAnLamdaMassVsPt;//!
	
	TH2D* fh2dKshortMassVsPtReal;//!
	TH2D* fh2dLamdaMassVsPtReal;//!
	TH2D* fh2dAnLamdaMassVsPtReal;//!

	TH2D* fh2dKshortRecPtVsGenPt;//!
	TH2D* fh2dLamdaRecPtVsGenPt;//!
	TH2D* fh2dAnLamdaRecPtVsGenPt;//!

	TH2D* fh2dPhotonMassVsPt;//!

	TH1D* fh1dKshortPtMC;//!
	TH1D* fh1dLamdaPtMC;//!
	TH1D* fh1dAnLamdaPtMC;//!

	TH2D* fh2dKshortPtVsJetPtMC;//!
	TH2D* fh2dLamdaPtVsJetPtMC;//!
	TH2D* fh2dAnLamdaPtVsJetPtMC;//!

	//V0 Reconstruction
	TH1D* fh1V0CounterCentK0s; //! number of K0s candidates after various cuts
	TH1D* fh1V0CounterCentLambda; //! number of Lambda candidates after various cuts
	TH1D* fh1V0CounterCentALambda; //! number of ALambda candidates after various cuts


	TClonesArray * fMCArray;//!
    	TClonesArray  *fCaloClusters;//! Tender cluster
	AliAnalysisUtils *fUtils;//!
  	Bool_t fDoJetProbabilityAnalysis;//
	Bool_t fDoPtRelAnalysis;//
	Bool_t fUsePicoTracks;//!


  // V0 selection
  // Daughter tracks
  Bool_t fbTPCRefit; // (yes) TPC refit for daughter tracks
  Bool_t fbRejectKinks; // (no) reject kink-like production vertices of daughter tracks
  Bool_t fbFindableClusters; // (no) require positive number of findable clusters
  Double_t fdCutNCrossedRowsTPCMin; // (70.) min number of crossed TPC rows
  Double_t fdCutCrossedRowsOverFindMin; // (0.8) min ratio crossed rows / findable clusters
  Double_t fdCutCrossedRowsOverFindMax; // (1e3) max ratio crossed rows / findable clusters
  Double_t fdCutPtDaughterMin; // (0.150) [GeV/c] min transverse momentum of daughter tracks, to reject primaries which do not make it to the TPC
  Double_t fdCutDCAToPrimVtxMin; // (0.1) [cm] min DCA of daughters to the prim vtx
  Double_t fdCutDCADaughtersMax; // (1.) [sigma of TPC tracking] max DCA between daughters
  Double_t fdCutEtaDaughterMax; // (0.8) max |pseudorapidity| of daughter tracks, historical reasons: tracking in MC for 2010 was restricted to 0.7
  Double_t fdCutNSigmadEdxMax; // (3.) [sigma dE/dx] max difference between measured and expected signal of dE/dx in the TPC
  Double_t fdPtProtonPIDMax; // (1.) [GeV/c] maxium pT of proton for applying PID cut in Pb-Pb
  // V0 candidate
  Bool_t fbOnFly; // (0) on-the-fly (yes) or offline (no) reconstructed
  Double_t fdCutCPAKMin; // (0.998) min cosine of the pointing angle, K0S
  Double_t fdCutCPALMin; // (0.998) min cosine of the pointing angle, Lambda
  Double_t fdCutRadiusDecayMin; // (5.) [cm] min radial distance of the decay vertex
  Double_t fdCutRadiusDecayMax; // (100.) [cm] max radial distance of the decay vertex
  Double_t fdCutEtaV0Max; // (0.7) max |pseudorapidity| of V0
  Double_t fdCutRapV0Max; // (0.75) max |rapidity| of V0 (turned off)
  Double_t fdCutNTauKMax; // (5.0) [tau] max proper lifetime in multiples of the mean lifetime, K0S
  Double_t fdCutNTauLMax; // (5.0) [tau] max proper lifetime in multiples of the mean lifetime, Lambda
  Bool_t fbCutArmPod; // (yes) Armenteros-Podolanski for K0S
  Bool_t fbCutCross; // (no) cross-contamination

  THnSparse* fhnV0InJetK0s; //! V0 in jet cones, in a centrality bin, m_V0; pt_V0; eta_V0; pt_jet
  THnSparse* fhnV0InJetLambda; //!
  THnSparse* fhnV0InJetALambda; //!

  //########################## PtRel
  TH1D* fhistPtRelEvents;//!
  TH2D* fhistPtRelVsJetPt;//!
  TH2D* fhistLepIPVsJetPt;//!
  TH2D* fhistPtRelVsJetPtUnidentified;//!
  TH2D* fhistPtRelVsJetPtudsg;//!
  TH2D* fhistPtRelVsJetPtc;//!
  TH2D* fhistPtRelVsJetPtb;//!
  TH2D* fhistLepIPVsJetPtUnidentified;//!
  TH2D* fhistLepIPVsJetPtudsg;//!
  TH2D* fhistLepIPVsJetPtc;//!
  TH2D* fhistLepIPVsJetPtb;//!
  TH2D* fHistMcEopEle;//!
  TH2D* fHistMcEopHad;//!
  TH2D* fTPCnsigMcEle;//!
  TH2D* fTPCnsigMcHad;//!

  TH2D* fhistPtRelVsJetPtTaggedFirst;//!
  TH2D* fhistLepIPVsJetPtTaggedFirst;//!

  TH2D* fhistPtRelVsJetPtTaggedUnidentifiedFirst;//!
  TH2D* fhistLepIPVsJetPtTaggedUnidentifiedFirst;//!

  TH2D* fhistPtRelVsJetPtTaggedudsgFirst;//!
  TH2D* fhistLepIPVsJetPtTaggedudsgFirst;//!

  TH2D* fhistPtRelVsJetPtTaggedcFirst;//!
  TH2D* fhistLepIPVsJetPtTaggedcFirst;//!

  TH2D* fhistPtRelVsJetPtTaggedbFirst;//!
  TH2D* fhistLepIPVsJetPtTaggedbFirst;//!

  TH2D* fhistPtRelVsJetPtTaggedSecond;//!
  TH2D* fhistLepIPVsJetPtTaggedSecond;//!

  TH2D* fhistPtRelVsJetPtTaggedUnidentifiedSecond;//!
  TH2D* fhistLepIPVsJetPtTaggedUnidentifiedSecond;//!

  TH2D* fhistPtRelVsJetPtTaggedudsgSecond;//!
  TH2D* fhistLepIPVsJetPtTaggedudsgSecond;//!

  TH2D* fhistPtRelVsJetPtTaggedcSecond;//!
  TH2D* fhistLepIPVsJetPtTaggedcSecond;//!

  TH2D* fhistPtRelVsJetPtTaggedbSecond;//!
  TH2D* fhistLepIPVsJetPtTaggedbSecond;//!

  TH2D* fhistPtRelVsJetPtTaggedThird;//!
  TH2D* fhistLepIPVsJetPtTaggedThird;//!

  TH2D* fhistPtRelVsJetPtTaggedUnidentifiedThird;//!
  TH2D* fhistLepIPVsJetPtTaggedUnidentifiedThird;//!

  TH2D* fhistPtRelVsJetPtTaggedudsgThird;//!
  TH2D* fhistLepIPVsJetPtTaggedudsgThird;//!

  TH2D* fhistPtRelVsJetPtTaggedcThird;//!
  TH2D* fhistLepIPVsJetPtTaggedcThird;//!

  TH2D* fhistPtRelVsJetPtTaggedbThird;//!
  TH2D* fhistLepIPVsJetPtTaggedbThird;//!

  

  Bool_t fApplyV0Rec;//
  Bool_t fApplyV0RejectionAll;//

  TClonesArray* fV0CandidateArray;//!
  AliJetContainer       *fJetContainerMC;  //! Container with reconstructed jets
  AliJetContainer       *fJetContainerData;//! Container with reconstructed jets
  AliAODEvent*		fAODIn;//! AOD Input Event
  AliAODVertex*		fPrimaryVertex; //! Event Primary Vertex

  TF1* fResolutionFunction[7];//

  static const Double_t fgkMassPion;    //
  static const Double_t fgkMassKshort;  //
  static const Double_t fgkMassLambda;  //
  static const Double_t fgkMassProton;  //
  static const Int_t fgkiNCategV0 = 18; // number of V0 selection steps

	ClassDef(AliAnalysisTaskBJetTC, 42)
};
#endif




 //
