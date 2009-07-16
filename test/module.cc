#include "Geometry/CaloEventSetup/interface/CaloGeometryEP.h"
#include "Geometry/EcalAlgo/interface/EcalEndcapGeometry.h"

template class CaloGeometryEP< EcalEndcapGeometry    > ;

typedef CaloGeometryEP< EcalEndcapGeometry > EcalEndcapGeometryEP ;
DEFINE_FWK_EVENTSETUP_MODULE(EcalEndcapGeometryEP);
