#ifndef VM_H
#define VM_H

#include "instruction.h"
#include "memory.h"
#include "relocatable.h"
#include "run_context.h"
#include "utils.h"

typedef struct {
	enum VirtualMachineError error;
	bool is_ok;
} vm_result;

typedef struct {
	run_context run_context;
	memory memory;
} virtual_machine;

// ---------------------
// execution structures
// ---------------------

typedef struct operands {
	maybe_relocatable dst;
	maybe_relocatable res;
	maybe_relocatable op0;
	maybe_relocatable op1;
} operands;

typedef struct operands_addresses {
	relocatable dst_addr;
	relocatable op0_addr;
	relocatable op1_addr;
} operands_addresses;

typedef struct computed_operands {
	operands oprs;
	operands_addresses op_addrs;
	uint8_t deduced_operands;
} computed_operands;

typedef union computed_operands_value {
	computed_operands ops;
	VirtualMachineError error;
} computed_operands_value;

typedef struct computed_operands_res {
	computed_operands_value value;
	bool is_error;
} computed_operands_res;

// ---------------------
//    VM functions
// ---------------------

// Creates a new, empty virtual_machine
virtual_machine vm_new(void);
// executes an instruction in the vm
vm_result run_instruction(virtual_machine vm, Instruction instr);
// Creates a new, empty virtual_machine
maybe_relocatable compute_res(Instruction instr, maybe_relocatable op0, maybe_relocatable op1);
#endif
