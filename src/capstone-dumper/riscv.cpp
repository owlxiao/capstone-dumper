/**
 * @file src/capstone-dumper/xcore.cpp
 * @brief RISCV specific code.
 * 
 */

#include <cassert>
#include <iomanip>
#include <iostream>

#include "capstone-dumper/capstone_dumper.h"

using namespace std;

namespace capstone_dumper {

std::string riscv_op_type_2_string(riscv_op_type opt)
{
    switch (opt)
    {
        case RISCV_OP_INVALID: return "RISCV_OP_INVALID";
        case RISCV_OP_REG    : return "RISCV_OP_REG"    ;
        case RISCV_OP_MEM    : return "RISCV_OP_MEM"    ;
        case RISCV_OP_IMM    : return "RISCV_OP_IMM"    ;
        default              : return "UNKNOWN"         ;
    }
}

void dump_cs_riscv_op(csh handle, cs_riscv_op& op)
{
    cout << "\t\t\t" << "op type : " << riscv_op_type_2_string(op.type) << endl;

    switch (op.type)
    {
        case RISCV_OP_INVALID:
        {
            break;
        }
        case RISCV_OP_REG:
        {
            cout << "\t\t\t" << "reg     : " << reg_2_string(handle, op.reg) << endl;
            break;
        }
        case RISCV_OP_IMM:
        {
            cout << "\t\t\t" << "imm     : " << hex << op.imm << endl;
            break;
        }
        case RISCV_OP_MEM:
        {
            cout << "\t\t\t" << "base reg: " << reg_2_string(handle, op.mem.base) << endl;
            cout << "\t\t\t" << "disp    : " << dec << op.mem.disp << endl;
            break;
        }
        default : 
        {
            assert(false && "unhandled value");
            break;
        }
    }
}


void dumpInstructionArchDependentRiscv(csh handle, cs_riscv* i)
{
	cout << "\t\t" << "need effective addr: " << boolalpha << i->need_effective_addr << endl;
    cout << "\t\t" << "op count           : " << dec       << unsigned(i->op_count)  << endl;

    for(unsigned j = 0; j < i->op_count; ++j)
    {
        cout << endl;
        dump_cs_riscv_op(handle, i->operands[j]);
    }
}

} // namespace capstone_dumper
