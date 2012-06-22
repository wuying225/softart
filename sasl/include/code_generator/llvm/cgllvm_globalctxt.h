#ifndef SASL_CODE_GENERATOR_LLVM_CGLLVM_GLOBALCTXT_H
#define SASL_CODE_GENERATOR_LLVM_CGLLVM_GLOBALCTXT_H

#include <sasl/include/code_generator/forward.h>
#include <sasl/include/code_generator/llvm/cgllvm_api.h>
#include <sasl/include/semantic/abi_info.h>

namespace llvm{
	class LLVMContext;
	class Module;
	class ConstantFolder;
	class Type;
	template <bool preserveNames> class IRBuilderDefaultInserter;
	template< bool preserveNames, typename T, typename Inserter
        > class IRBuilder;
    typedef IRBuilder<true, ConstantFolder, IRBuilderDefaultInserter<true> >
        DefaultIRBuilder;
}

#include <boost/shared_ptr.hpp>
#include <string>

BEGIN_NS_SASL_CODE_GENERATOR();

/////////////////////////////////////////
// support LLVMContext, Module, IRBuilder and other data use by code generator.
// General module created by llvm code generator.
class llvm_module_impl: public llvm_module{
public:
	llvm_module_impl();
	void create_module( const std::string& modname );

	virtual llvm::Module* module() const;
	virtual boost::shared_ptr<llvm::DefaultIRBuilder> builder() const;
	virtual llvm::Module* get_ownership() const;
	virtual void dump() const;
	virtual void dump( std::ostream& ostr ) const;

	virtual llvm::LLVMContext& context();
	llvm::Type*	entry_param_type( salviar::sv_usage st ) const;
	void		entry_param_type( salviar::sv_usage st, llvm::Type* t );

	~llvm_module_impl();

protected:
	boost::shared_ptr<llvm::LLVMContext> lctxt;
	boost::shared_ptr<llvm::DefaultIRBuilder> irbuilder;
	llvm::Type* param_types[salviar::storage_usage_count];

	llvm::Module* mod;

	mutable bool have_mod;
};

class cgllvm_modvs: public llvm_module_impl{
public:

};

END_NS_SASL_CODE_GENERATOR();

#endif
