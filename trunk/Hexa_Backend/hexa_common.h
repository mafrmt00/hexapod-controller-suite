#include <cstddef> // NULL
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


#include <boost/archive/tmpdir.hpp>

//#include <boost/archive/text_iarchive.hpp>
//#include <boost/archive/text_oarchive.hpp>

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/split_member.hpp>

//XML serialization support
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>


#include <cmath>
#include <list>

#include <unistd.h>

using namespace std;

#include "my_types.h"

#include "commandcontainer.h"

#include "servo.h"
#include "joint.h"
#include "leg.h"
#include "hip_sagit.h"
#include "hip.h"
#include "bodypart.h"
#include "hipgroup.h"


