// -*- C++ -*-
//
// Package:    EcalTBHodoscopeGeometryEP
// Class:      EcalTBHodoscopeGeometryEP
// 
/**\class EcalTBHodoscopeGeometryEP    

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//

// $Id: EcalTBHodoscopeGeometryEP.cc,v 1.3 2006/04/26 12:49:40 fabiocos Exp $
//
//

#include "Geometry/EcalTestBeam/interface/EcalTBHodoscopeGeometryEP.h"
#include "Geometry/EcalTestBeam/interface/EcalTBHodoscopeGeometryLoaderFromDDD.h"
#include "DetectorDescription/Core/interface/DDCompactView.h"

#include <iostream>
//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
EcalTBHodoscopeGeometryEP::EcalTBHodoscopeGeometryEP(const edm::ParameterSet& iConfig)
{
   //the following line is needed to tell the framework what
   // data is being produced
  setWhatProduced(this,"EcalLaserPnDiode");
  //now do what ever other initialization is needed
  loader_=new EcalTBHodoscopeGeometryLoaderFromDDD(); 
}


EcalTBHodoscopeGeometryEP::~EcalTBHodoscopeGeometryEP()
{ 
  delete loader_;
}


//
// member functions
//

// ------------ method called to produce the data  ------------
EcalTBHodoscopeGeometryEP::ReturnType
EcalTBHodoscopeGeometryEP::produce(const IdealGeometryRecord& iRecord)
{
   using namespace edm::es;

   edm::ESHandle<DDCompactView> cpv;
   iRecord.get( cpv );
   
   std::cout << "[EcalTBHodoscopeGeometryEP]::Constructing EcalTBHodoscopeGeometry" <<  std::endl;
   std::auto_ptr<CaloSubdetectorGeometry> pCaloSubdetectorGeometry(loader_->load(&(*cpv))) ;
   return pCaloSubdetectorGeometry ;
}


