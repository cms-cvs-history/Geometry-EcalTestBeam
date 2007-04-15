//<<<<<< INCLUDES                                                       >>>>>>

//#include "Geometry/EcalPreshowerData/interface/DDTestAlgorithm.h"
#include "Geometry/EcalTestBeam/plugins/DDTBH4Algo.h"
#include "DetectorDescription/Algorithm/interface/DDAlgorithmFactory.h"

//DEFINE_SEAL_PLUGIN (DDAlgorithmFactory, DDTestAlgorithm, "DDTestAlgorithm");

DEFINE_EDM_PLUGIN (DDAlgorithmFactory, DDTBH4Algo, "DDTBH4Algo");

#include "Geometry/EcalTestBeam/plugins/EcalTBHodoscopeGeometryEP.h"

DEFINE_ANOTHER_FWK_EVENTSETUP_MODULE(EcalTBHodoscopeGeometryEP);

#include "Geometry/EcalTestBeam/plugins/EcalTBGeometryBuilder.h"

DEFINE_ANOTHER_FWK_EVENTSETUP_MODULE(EcalTBGeometryBuilder);