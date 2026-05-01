#pragma once
#include <cstdint>
#include "isa.h"

Instruction decode(uint32_t raw);
InstructionType decode_instruction_type(uint32_t raw);