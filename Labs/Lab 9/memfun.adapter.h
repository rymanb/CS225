// In this question you will implement a member function adapter for a member
// function that takes a single argument (STL allows only void member functions.)
// Refer to the example implementation of member function adapter with no
// arguments, see class web-site.

#ifndef MEMFUN_ADAPTER_H
#define MEMFUN_ADAPTER_H
template <typename RetType, typename ClassType, typename ArgType>
class MFA_1arg {
	typedef RetType (ClassType::*MemFunPtr)(ArgType);
	MemFunPtr mfp;
	public:
		MFA_1arg( RetType (ClassType::*_pointer) (ArgType) ) : mfp(_pointer) {}
		RetType operator() (ClassType& obj, ArgType arg) const {
			return (obj.*mfp)(arg);
		}
};

//helper functions
//for non-const member function
template <typename RetType, typename ClassType, typename ArgType>
MFA_1arg<RetType,ClassType,ArgType> mfp_1arg(RetType (ClassType::*pointer) (ArgType) ) { 
	return MFA_1arg<RetType,ClassType,ArgType>(pointer);
}
#endif
