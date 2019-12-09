#include "Exception.h"
#include <string.h>


ostream& operator <<(ostream& os, Exception &e)
{
	os << endl << "---------------" << endl << "Line  " << e.Line << endl << "File  " << e.File << endl << "Func  " << e.Function << endl << e.Desc << endl << "---------------" << endl;
	return os;
}