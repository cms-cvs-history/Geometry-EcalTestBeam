// -*- C++ -*-
//
// Package:    CrystalCenterDump
// Class:      CrystalCenterDump
// 
/**\class CrystalCenterDump CrystalCenterDump.cc test/CrystalCenterDump/src/CrystalCenterDump.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//



// system include files
#include <memory>
#include <cmath>
#include <iomanip>

// user include files
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "Geometry/CaloGeometry/interface/CaloSubdetectorGeometry.h"
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "Geometry/CaloGeometry/interface/CaloCellGeometry.h"
#include "Geometry/CaloGeometry/interface/TruncatedPyramid.h"
#include "Geometry/Records/interface/IdealGeometryRecord.h"
#include "DataFormats/EcalDetId/interface/EcalSubdetector.h"
#include "DataFormats/EcalDetId/interface/EBDetId.h"

#include <fstream>

#include "CLHEP/Vector/ThreeVector.h"

//
// class decleration
//

class CrystalCenterDump : public edm::EDAnalyzer {
   public:
      explicit CrystalCenterDump( const edm::ParameterSet& );
      ~CrystalCenterDump();


      virtual void analyze( const edm::Event&, const edm::EventSetup& );
   private:
      // ----------member data ---------------------------
  void build(const CaloGeometry& cg, DetId::Detector det, int subdetn, const char* name);
  int pass_;

  double A_;
  double B_;
  double beamEnergy_;

  double crystalDepth(){ return A_*(B_+log(beamEnergy_)); }

};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
CrystalCenterDump::CrystalCenterDump( const edm::ParameterSet& iConfig )
{
   //now do what ever initialization is needed
  pass_=0;

  A_ = iConfig.getUntrackedParameter<double>("Afac",0.89);
  B_ = iConfig.getUntrackedParameter<double>("Bfac",5.7);
  beamEnergy_ = iConfig.getUntrackedParameter<double>("BeamEnergy",120.);

  edm::LogInfo("CrysInfo") << "Position computed according to the depth " << crystalDepth() << 
    " based on:" << "\n A = " << A_ << " cm " << "\n B = " << B_ << "\n BeamEnergy = " << beamEnergy_ << " GeV";

}


CrystalCenterDump::~CrystalCenterDump()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


void CrystalCenterDump::build(const CaloGeometry& cg, DetId::Detector det, int subdetn, const char* name) {
  std::fstream f(name,std::ios_base::out);
  const CaloSubdetectorGeometry* geom=cg.getSubdetectorGeometry(det,subdetn);

  int n=0;
  std::vector<DetId> ids=geom->getValidDetIds(det,subdetn);
  for (std::vector<DetId>::iterator i=ids.begin(); i!=ids.end(); i++) {
    n++;
    const CaloCellGeometry* cell=geom->getGeometry(*i);
    if (det == DetId::Ecal)
      {
        if (subdetn == EcalBarrel) {
          EBDetId ebid(i->rawId());
          if (ebid.ism() == 1) {
            
            float depth = (crystalDepth());
            double crysX = dynamic_cast<const TruncatedPyramid*>(cell)->getPosition(depth).x();
            double crysY = dynamic_cast<const TruncatedPyramid*>(cell)->getPosition(depth).y();
            double crysZ = dynamic_cast<const TruncatedPyramid*>(cell)->getPosition(depth).z();

            Hep3Vector crysPos(crysX,crysY,crysZ);
            double crysEta = crysPos.eta();
            double crysTheta = crysPos.theta();
            double crysPhi = crysPos.phi();

            edm::LogInfo("CrysPos") << ebid.ic() << " x = " << crysX << " y = " << crysY << " z = " << crysZ << " \n " 
                                    << " eta = " << crysEta << " phi = " << crysPhi << " theta = " << crysTheta;
            f << std::setw(4) << ebid.ic() << " " 
              << std::setw(8) << std::setprecision(6) << crysEta << " " 
              << std::setw(8) << std::setprecision(6) << crysPhi << " " 
              << std::endl;
          }
        }
      }
  }
  f.close();
}

//
// member functions
//

// ------------ method called to produce the data  ------------
void
CrystalCenterDump::analyze( const edm::Event& iEvent, const edm::EventSetup& iSetup )
{
   using namespace edm;
   
   std::cout << "Writing the center (eta,phi) for crystals in barrel SM 1 " << std::endl;

   edm::ESHandle<CaloGeometry> pG;
   iSetup.get<IdealGeometryRecord>().get(pG);     
   //
   // get the ecal & hcal geometry
   //
   if (pass_==0) {
     build(*pG,DetId::Ecal,EcalBarrel,"BarrelSM1CrystalCenter.dat");
   }

   pass_++;
      
}

//define this as a plug-in
DEFINE_SEAL_MODULE();
DEFINE_ANOTHER_FWK_MODULE(CrystalCenterDump);
