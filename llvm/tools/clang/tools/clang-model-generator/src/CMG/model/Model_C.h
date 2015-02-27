//#ifndef _MODEL_MODEL_C_
//#define _MODEL_MODEL_C_
//
//#include "cppming/model/Model.h"
//
//extern "C"{
//  /*
//   Model
//   */
//  void* cppming_Model_getGlobalNamespace(void* that);
//  
//  void cppming_Model_destroy(void* that);
//  
//  
//  /*
//   Class
//   */
//  
//  const char* cppming_Class_getName(void* that);
//  
//  bool cppming_Class_isFinal(void* that);
//  
//  int cppming_Class_getNumMethods(void* that);
//  
//  void* cppming_Class_getMethod(void* that, int i);
//  
//  
//  /*
//   Method
//   */
//  
//  const char* cppming_Method_getName(void* that);
//  
//  bool cppming_Method_isFinal(void* that);
//  
//  bool cppming_Method_isStatic(void* that);
//  
//  bool cppming_Method_isConst(void* that);
//  
//  bool cppming_Method_isPure(void* that);
//  
//  int cppming_Method_getNumParameters(void* that);
//  
//  void* cppming_Method_getParameter(void* that, int i);
//  
//  
//  /*
//   Namespace
//   */
//  
//  const char* cppming_Namespace_getName(void* that);
//  
//  int cppming_Namespace_getNumClasses(void* that);
//  
//  void* cppming_Namespace_getClass(void* that, int i);
//  
//  int cppming_Namespace_getNumNamespaces(void* that);
//  
//  void* cppming_Namespace_getNamespace(void* that, int i);
//  
//  
//  /*
//   Parameter
//   */
//  
//  const char* cppming_Parameter_getName(void* that);
//  
//  void* cppming_Parameter_getType(void* that);
//  
//  
//  /*
//   Type
//   */
//  
//  const char* cppming_Type_getName(void* that);
//  
//  bool cppming_Type_isConst(void* that);
//  
//  bool cppming_Type_isReference(void* that);
//  
//  bool cppming_Type_isPointer(void* that);
//    
//}
//#endif