#pragma once

#ifdef _MSC_VER
#ifdef clang_model_generator_EXPORTS
#define CMG_API __declspec(dllexport)
#else
#define CMG_API __declspec(dllimport)
#endif
#else
#define CMG_API
#endif