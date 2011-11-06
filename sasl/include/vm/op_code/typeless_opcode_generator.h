#ifndef SASL_VM_OP_CODE_TYPELESS_OPCODE_GENERATOR_H
#define SASL_VM_OP_CODE_TYPELESS_OPCODE_GENERATOR_H

#include "instruction.h"

#define SASL_DECL_TYPELESS_CODE_GENERATOR( GENERATOR_CLASS_NAME, INSTRUCTION, MACHINE_T )			\
	BOOST_PP_CAT(GENERATOR_CLASS_NAME,&)				\
		SASL_UNDERLINE_PREFIXED_IFN( INSTRUCTION ) (	\
			BOOST_PP_CAT(MACHINE_T,::operand_t) arg0,	\
			BOOST_PP_CAT(MACHINE_T,::operand_t) arg1	\
			)

#define SASL_DECL_TYPELESS_CODE_GENERATOR_I( r, data, elem )	\
	SASL_DECL_TYPELESS_CODE_GENERATOR( BOOST_PP_TUPLE_ELEM(2, 0, data), elem, BOOST_PP_TUPLE_ELEM(2, 1, data) );

#define SASL_DECL_TYPELESS_CODE_GENERATORS( GENERATOR_CLASS_NAME, INSTRUCTIONS, MACHINE_T )	\
	BOOST_PP_SEQ_FOR_EACH(SASL_DECL_TYPELESS_CODE_GENERATOR_I, (GENERATOR_CLASS_NAME, MACHINE_T), INSTRUCTIONS )

#define SASL_TYPELESS_CODE_GENERATOR_IMPL( GENERATOR_CLASS_NAME, INSTRUCTION, MACHINE_T )	\
	BOOST_PP_CAT(GENERATOR_CLASS_NAME,&)				\
		BOOST_PP_CAT(BOOST_PP_CAT(GENERATOR_CLASS_NAME, ::), SASL_UNDERLINE_PREFIXED_IFN( INSTRUCTION )) (		\
			BOOST_PP_CAT(MACHINE_T,::operand_t) arg0,	\
			BOOST_PP_CAT(MACHINE_T,::operand_t) arg1	\
			){											\
			return emit_op(SASL_NAMESAPCED_IFN(INSTRUCTION), arg0, arg1);\
		}

#define SASL_TYPELESS_CODE_GENERATOR_IMPL_I( r, data, elem )	\
	SASL_TYPELESS_CODE_GENERATOR_IMPL( BOOST_PP_TUPLE_ELEM(2,0,data), elem, BOOST_PP_TUPLE_ELEM(2,1,data) )

#define SASL_TYPELESS_CODE_GENERATORS_IMPL( GENERATOR_CLASS_NAME, INSTRUCTIONS, MACHINE_T )	\
	BOOST_PP_SEQ_FOR_EACH( SASL_TYPELESS_CODE_GENERATOR_IMPL_I, (GENERATOR_CLASS_NAME, MACHINE_T), INSTRUCTIONS )
#endif