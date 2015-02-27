//#ifndef _MODEL_MODEL_C_
//#define _MODEL_MODEL_C_
//
//#include "cppming/model/Model_C.h"
//#include "cppming/model/Class.h"
//#include "cppming/model/Method.h"
//#include "cppming/model/Namespace.h"
//#include "cppming/model/Parameter.h"
//#include "cppming/model/Type.h"
//
//#include <iostream>
//
//extern "C"{
//  using namespace cppming;
//  /*
//   Model
//   */
//  void* cppming_Model_getGlobalNamespace(void* that){
//    return ((Model*)that)->getGlobalNamespace();
//  }
//  
//  void cppming_Model_destroy(void* that){
//    delete ((Model*)that);
//  }
//  
//  
//  /*
//   Class
//   */
//  
//  const char* cppming_Class_getName(void* that){
//    return ((Class*)that)->getName().c_str();
//  }
//  
//  bool cppming_Class_isFinal(void* that){
//    return ((Class*)that)->isFinal();
//  }
//  
//  int cppming_Class_getNumMethods(void* that){
//    return ((Class*)that)->getNumMethods();
//  }
//  
//  void* cppming_Class_getMethod(void* that, int i){
//    return (void*) ((Class*)that)->getMethod(i);
//  }
//  
//  
//  /*
//   Method
//   */
//  
//  const char* cppming_Method_getName(void* that){
//    return ((Method*)that)->getName().c_str();
//  }
//  
//  bool cppming_Method_isFinal(void* that){
//    return ((Method*)that)->isFinal();
//  }
//  
//  bool cppming_Method_isStatic(void* that){
//    return ((Method*)that)->isStatic();
//  }
//  
//  bool cppming_Method_isConst(void* that){
//    return ((Method*)that)->isConst();
//  }
//  
//  bool cppming_Method_isPure(void* that){
//    return ((Method*)that)->isPure();
//  }
//  
//  int cppming_Method_getNumParameters(void* that){
//    return ((Method*)that)->getNumParameters();
//  }
//  
//  void* cppming_Method_getParameter(void* that, int i){
//    return (void*) ((Method*)that)->getParameter(i);
//  }
//  
//  
//  /*
//   Namespace
//   */
//  
//  const char* cppming_Namespace_getName(void* that){
//    return ((Namespace*)that)->getName().c_str();
//  }
//  
//  int cppming_Namespace_getNumClasses(void* that){
//    return ((Namespace*)that)->getNumClasses();
//  }
//  
//  void* cppming_Namespace_getClass(void* that, int i){
//    return (void*) ((Namespace*)that)->getClass(i);
//  }
//  
//  int cppming_Namespace_getNumNamespaces(void* that){
//    return ((Namespace*)that)->getNumNamespaces();
//  }
//  
//  void* cppming_Namespace_getNamespace(void* that, int i){
//    return (void*) ((Namespace*)that)->getNamespace(i);
//  }
//  
//  
//  /*
//   Parameter
//   */
//  
//  const char* cppming_Parameter_getName(void* that){
//    return ((Parameter*)that)->getName().c_str();
//  }
//  
//  void* cppming_Parameter_getType(void* that){
//    return (void*) &((Parameter*)that)->getType();
//  }
//  
//  
//  /*
//   Type
//   */
//  
//  const char* cppming_Type_getName(void* that){
//    return ((Type*)that)->getName().c_str();
//  }
//  
//  bool cppming_Type_isConst(void* that){
//    return ((Type*)that)->isConst();
//  }
//  
//  bool cppming_Type_isReference(void* that){
//    return ((Type*)that)->isReference();
//  }
//  
//  bool cppming_Type_isPointer(void* that){
//    return ((Type*)that)->isPointer();
//  }
//    
//}
//#endif 