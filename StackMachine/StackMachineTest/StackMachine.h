#pragma once
#include <type_traits>
#include <iostream>
#include <map>
#include <array>
#include <tuple>
#include <string>
#include <vector>
namespace VirtualMachine {
	#include "StackMachine/AdressArgs.h"
	#include "StackMachine/Order.h"
	#include "StackMachine/OrderVector.h"
	#include "StackMachine/StackMachine.h"
}

#include "StackMachine/RunMachine.h"

namespace VirtualMachine {
	#include "StackMachine/PUSH.h"
	#include "StackMachine/POP.h"
	#include "StackMachine/LD.h"
	#include "StackMachine/JMP.h"
	#include "StackMachine/END.h"
	#include "StackMachine/ADD.h"
	#include "StackMachine/MUL.h"
	#include "StackMachine/DIV.h"
	#include "StackMachine/MOD.h"
	#include "StackMachine/AND.h"
	#include "StackMachine/OR.h"
	#include "StackMachine/XOR.h"
	#include "StackMachine/NOT.h"
	#include "StackMachine/CPAEQ.h"
	#include "StackMachine/CPANEQ.h"
	#include "StackMachine/JMPB.h"
	#include "StackMachine/INC.h"
	#include "StackMachine/REF.h"
	#include "StackMachine/DREF.h"
	#include "StackMachine/LDR.h"
	#include "StackMachine/CAST.h"
	#include "StackMachine/CALL.h"
	#include "StackMachine/RET.h"
	#include "StackMachine/SCAN.h"
	#include "StackMachine/Print.h"
	#include "StackMachine/SPRINT.h"
}
